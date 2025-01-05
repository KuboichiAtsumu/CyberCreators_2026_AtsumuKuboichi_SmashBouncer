//==============================================================================================================================================
//
// �G�l�~�[�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "enemy.h"//�G�l�~�[
#include "greenslime.h"//�O���[���X���C��
#include "blueslime.h"//�u���[�X���C��
#include "whiteghost.h"//�z���C�g�S�[�X�g
#include "blackghost.h"//�u���b�N�S�[�X�g
#include "redbat.h"//���b�h�o�b�g
#include "purplebat.h"//�p�[�v���o�b�g
#include "midboss.h"//���{�X
#include "boss.h"//�{�X
#include "billboard.h"//�r���{�[�h�w�b�_�[

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
int CEnemy::m_nAllEnemy = 0;//�G�̑���

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	//�����o�ϐ�������
	m_pPrev = nullptr;//�O�̃G�l�~�[���
	m_pNext = nullptr;//���̃G�l�~�[���
	m_EnemyType = {};//�G�l�~�[�^�C�v
	m_State = ENEMY_STATE_NORMAL;//���
	m_FirstPos = {};//�ŏ��̈ʒu
	m_nIntervalShot = MIN_INTERVAL;//���̔��˂܂ł̎���
	m_nCntShot = 0;//�e���˂܂ł̃J�E���g
	m_nCntState = 0;//��ԃJ�E���g
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CEnemy::~CEnemy()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CEnemy::Init()
{
	//�e�N�X�`������
	CTexture* pTex = CManager::GetTexture();//�擾
	int nTextureIdx = pTex->Regist(CXfile::GetSaveModelInfo(CXfile::ENEMY, m_EnemyType)->aTextureFile);//�o�^
	BindTexture(pTex->GetAddress(nTextureIdx));//�ݒ�
	SetTextureIdx(nTextureIdx);//ID�ݒ�

	//���f������
	CXfile* pModel = CManager::GetModel();//�擾
	int nModelIdx = pModel->Regist(CXfile::GetSaveModelInfo(CXfile::ENEMY, m_EnemyType)->aModelFile);//�o�^
	BindModel(pModel->GetAddress(nModelIdx));//�ݒ�
	SetModelIdx(nModelIdx);//ID�ݒ�
	SetSize();//�T�C�Y�ݒ�

	//����������X�e�[�WID��o�^
	SetPostStageID();

	//�����ʒu��ۑ�
	m_FirstPos = GetPos();

	//�G�̑��������Z
	m_nAllEnemy++;

	//X�t�@�C���I�u�W�F�N�g����������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CEnemy::Uninit()
{
	//X�t�@�C���I�u�W�F�N�g�I������
	CObjectX::Uninit();
}

//===========================================================================================================
// �������
//===========================================================================================================
void CEnemy::Release()
{
	//X�t�@�C���I�u�W�F�N�g�������
	CObjectX::Release();

	//�G�̑��������Z
	m_nAllEnemy--;
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CEnemy::Update()
{
	//���[�J���ϐ��錾
	CXfile::CModel aModelInfo = GetModelInfo();

	for (int nCntMat = 0; nCntMat < (int)aModelInfo.dwNumMat; nCntMat++)
	{
		//��Ԃɉ����ĐF��ω�
		switch (m_State)
		{
			//�ʏ���
		case ENEMY_STATE_NORMAL:
			//�����l�̐F�ɐݒ�
			aModelInfo.Diffuse[nCntMat] = aModelInfo.FirstDiffuse[nCntMat];
			break;

			//�_���[�W���
		case ENEMY_STATE_DAMAGE:
			//�ԐF�̐ݒ�
			aModelInfo.Diffuse[nCntMat] = { 1.0f, 0.0f, 0.0f, 1.0f };

			//��ԃJ�E���g���c���Ă���ꍇ
			if (m_nCntState > 0)
			{
				//�J�E���g������
				m_nCntState--;

				//�J�E���g��0�̏ꍇ
				if (m_nCntState <= 0)
				{
					//�ʏ��Ԃɐݒ�
					m_State = ENEMY_STATE_NORMAL;
				}
			}
			break;

		default:
			break;
		}
	}

	//�X�V���ꂽ���f������ݒ�
	BindModel(&aModelInfo);

	//X�t�@�C���I�u�W�F�N�g�X�V����
	CObjectX::Update();
}

//===========================================================================================================
// �ړ�����
//===========================================================================================================
void CEnemy::Move()
{
	//�����擾
	D3DXVECTOR3 Pos = GetPos();//�ʒu
	D3DXVECTOR3 Move = GetMove();//�ړ���

	//�ړ��ʂ����Z
	Pos += Move;

	//�G�̈ʒu���ړ����𒴂����ꍇ
	if (Pos.z >= m_FirstPos.z + MOVE_WIDTH || Pos.z <= m_FirstPos.z - MOVE_WIDTH)
	{
		//�ړ�������؂�ւ���
		Move *= -1.0f;
	}

	//����ݒ�
	SetPos(Pos);//�ʒu
	SetMove(Move);//�ړ���
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CEnemy::Draw()
{
	//�G�f�B�^���[�h�̏ꍇ
	if (CManager::GetScene()->GetEditMode())
	{//�`�悹���ɏ����𔲂���
		return;
	}

	//X�t�@�C���I�u�W�F�N�g�`�揈��
	CObjectX::Draw();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	//�^�C�v�ɉ����ē��I�m��
	CEnemy* pEnemy = nullptr;
	switch (nType)
	{
	//�O���[���X���C��
	case GREEN_SLIME:
		pEnemy = NEW CGreenSlime();
		break;

	//�u���[�X���C��
	case BLUE_SLIME:
		pEnemy = NEW CBlueSlime();
		break;

	//�z���C�g�S�[�X�g
	case WHITE_GHOST:
		pEnemy = NEW CWhiteGhost();
		break;

	//�u���b�N�S�[�X�g
	case BLACK_GHOST:
		pEnemy = NEW CBlackGhost();
		break;

	//���b�h�o�b�g
	case RED_BAT:
		pEnemy = NEW CRedBat();
		break;

	//�p�[�v���o�b�g
	case PURPLE_BAT:
		pEnemy = NEW CPurpleBat();
		break;

	//���{�X
	case MID_BOSS:
		pEnemy = NEW CMidBoss();
		break;

	//�{�X
	case BOSS:
		pEnemy = NEW CBoss();
		break;

	default:
		break;
	}

	//�p�����[�^�ݒ�
	pEnemy->SetType(TYPE::ENEMY);//�I�u�W�F�N�g�^�C�v�ݒ�
	pEnemy->SetEnemyType((ENEMYTYPE)nType);//�G�l�~�[�^�C�v�ݒ�
	pEnemy->SetPos(pos);//�ʒu�ݒ�
	pEnemy->SetRot(rot);//�����ݒ�
	pEnemy->SetMove({ 0.0f, 0.0f, MOVE_SPEED });//�ړ��ʐݒ�
	pEnemy->SetLife(ENEMY_LIFE[nType]);//���C�t�ݒ�

	//����������
	pEnemy->Init();

	return pEnemy;
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
bool CEnemy::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//���[�J���ϐ��錾
	bool bCollision = false; //�����蔻��t���O
	D3DXVECTOR3 Pos = GetPos();//�ʒu���
	D3DXVECTOR3 Size = GetSize();//�T�C�Y���

	//�d�Ȃ����ꍇ
	if (pos.x + size.x * 0.5f >= Pos.x - Size.x * 0.5f && pos.x - size.x * 0.5f <= Pos.x + Size.x * 0.5f
		&& pos.z - size.z * 0.5f <= Pos.z + Size.z * 0.5f && pos.z + size.z * 0.5f >= Pos.z - Size.z * 0.5f)
	{
		//�����蔻���true�ɂ���
		bCollision = true;
	}

	//�����蔻�茋�ʂ�Ԃ�
	return bCollision;
}

//===========================================================================================================
// �q�b�g����
//===========================================================================================================
void CEnemy::Hit()
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();//�ʒu���
	int nLife = GetLife();//���C�t���

	//�G�l�~�[�̃��C�t�����炷
	nLife--;

	//SE�Đ�
	CManager::GetSound()->Play(CSound::SE_HIT);

	//�G�l�~�[�̃��C�t��0�ɂȂ����ꍇ
	if (nLife <= 0)
	{
		//�����ʒu�𒲐�
		pos.y += GetSize().y * 0.5f;

		//�r���{�[�h��������
		CBillboard::Create(CBillboard::BILLBOARD_EXPLOSION, pos, { 40.0f,40.0f,0.0f });

		//�I������
		Uninit();
	}
	//�G�l�~�[�̃��C�t���c���Ă���ꍇ
	else
	{
		//�_���[�W��Ԃɐݒ�
		m_State = ENEMY_STATE_DAMAGE;

		//��ԃJ�E���g�ݒ�
		m_nCntState = 5;
	}

	//�G�l�~�[�̃��C�t��ݒ肷��
	SetLife(nLife);
}
