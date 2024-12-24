//==============================================================================================================================================
//
// �o���b�g�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "bullet.h"//�o���b�g
#include "playerbullet.h"//�v���C���[�o���b�g
#include "clonebullet.h"//�N���[���o���b�g
#include "boundenemybullet.h"//�G�l�~�[�o���b�g(����)
#include "launchenemybullet.h"//�G�l�~�[�o���b�g(�ł��グ)
#include "boundinvincible.h"//���G�o���b�g(����)
#include "launchinvincible.h"//���G�o���b�g(�ł��グ)
#include "bulletmanager.h"//�o���b�g�}�l�[�W���[
#include "tutorial.h"//�`���[�g���A���V�[��
#include "title.h"//�^�C�g���V�[��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CBullet::CBullet(int nPriority) : CObjectX(nPriority)
{
	//�����o�ϐ�������
	m_pPrev = nullptr;//�O�̃o���b�g���
	m_pNext = nullptr;//���̃o���b�g���
	m_BulletType = NONE;//�o���b�g�^�C�v
	m_Distance = {};//�ΏۃI�u�W�F�N�g�Ƃ̊e���W����
	m_fLength = 100.0f;//�ΏۃI�u�W�F�N�g�Ƃ̑Ίp����
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CBullet::~CBullet()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CBullet::Init()
{
	//���f������
	CXfile* pModel = CManager::GetModel();//�擾
	int nModelIdx = pModel->Regist("data/MODEL/bullet000.x");//�o�^
	BindModel(pModel->GetAddress(nModelIdx));//�ݒ�
	SetModelIdx(nModelIdx);//ID�ݒ�
	SetSize();//�T�C�Y�ݒ�

	//����������X�e�[�WID��o�^
	SetPostStageID();

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
void CBullet::Uninit()
{
	//X�t�@�C���I�u�W�F�N�g�I������
	CObjectX::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CBullet::Update()
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();//�ʒu���
	D3DXVECTOR3 move = GetMove();//�ړ��ʏ��
	int nLife = GetLife();//���C�t���

	//�^�C�g����ʂł͂Ȃ��ꍇ
	if (CManager::GetScene()->GetMode() != CScene::MODE_TITLE)
	{
		//��������
		nLife--;
		SetLife(nLife);

		//�������s�����ꍇ
		if (nLife <= 0)
		{
			//�I������
			Uninit();
		}
	}

	//�ߋ��̈ʒu�̐ݒ�
	SetOldPos(pos);

	//�ړ��ʂ����Z
	pos += move;

	//����ݒ�
	SetPos(pos);//�ʒu
	SetMove(move);//�ړ���

	//����������X�e�[�W�ƌ��݂̃X�e�[�W����v���Ȃ��ꍇ
	//�X�e�[�W�ړ����̏ꍇ
	if (GetPostStageID() != CGame::GetNumStage() || CGame::GetGameState() == CGame::STATE_MOVE)
	{
		//�I������
		Uninit();
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CBullet::Draw()
{
	//X�t�@�C���I�u�W�F�N�g�`�揈��
	CObjectX::Draw();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE m_type)
{
	//���[�J���ϐ��錾
	CBulletManager* pBulletManager = nullptr;//�o���b�g�}�l�[�W���[

	//�V�[���ɉ����ă}�l�[�W���[�����擾
	switch (CManager::GetScene()->GetMode())
	{
		//�^�C�g��
	case CScene::MODE_TITLE:
		pBulletManager = CTitle::GetBulletManager();
		break;

		//�`���[�g���A��
	case CScene::MODE_TUTORIAL:
		pBulletManager = CTutorial::GetBulletManager();
		break;

		//�Q�[��
	case CScene::MODE_GAME:
		pBulletManager = CGame::GetBulletManager();
		break;

	default:
		break;
	}

	//�^�C�v���Ƃɓ��I�m��
	CBullet* pBullet = nullptr;
	switch (m_type)
	{
		//�v���C���[
	case PLAYER:
		pBullet = NEW CPlayerBullet();
		break;

		//�N���[��
	case CLONE:
		pBullet = NEW CCloneBullet();
		break;

		//�G�l�~�[(����)
	case BOUND_ENEMY:
		pBullet = NEW CBoundEnemyBullet();
		break;

		//�G�l�~�[(�ł��グ)
	case LAUNCH_ENEMY:
		pBullet = NEW CLaunchEnemyBullet();
		break;

		//���G(����)
	case BOUND_INVINCIBLE:
		pBullet = NEW CBoundInvincible();
		break;

		//���G(�ł��グ)
	case LAUNCH_INVINCIBLE:
		pBullet = NEW CLaunchInvincible();
		break;

	default:
		break;
	}

	//�p�����[�^�ݒ�
	pBullet->SetType(TYPE::BULLET);//�I�u�W�F�N�g�^�C�v�̐ݒ�
	pBullet->SetPos(pos);//�����ʒu�ݒ�
	pBullet->SetOldPos(pos);//�ߋ��̈ʒu
	pBullet->SetMove(move);//���������ݒ�

	//����������
	pBullet->Init();
	pBullet->SetBulletType(m_type);//�e�̃^�C�v�ݒ�

	//�o���b�g�����}�l�[�W���[�ɓo�^
	pBulletManager->Regist(pBullet);

	return pBullet;
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
bool CBullet::Collision(D3DXVECTOR3 pos)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 BulletPos = GetPos();//�o���b�g�̈ʒu���

	//�ΏۃI�u�W�F�N�g�Ƃ̊e���W���������߂�
	m_Distance = { abs(pos.x - BulletPos.x), abs(pos.y - BulletPos.y), abs(pos.z - BulletPos.z)	};

	//�ΏۃI�u�W�F�N�g�Ƃ�XZ�Ԃ̑Ίp���������߂�
	float fLength = sqrtf(powf(m_Distance.x, 2.0f) + powf(m_Distance.z, 2.0f));

	//�ΏۃI�u�W�F�N�g�Ƃ̑Ίp���������߂�
	m_fLength = sqrtf(powf(fLength, 2.0f) + powf(m_Distance.y, 2.0f));

	return false;
}

//===========================================================================================================
// �e�̃^�C�v�ݒ菈��
//===========================================================================================================
void CBullet::SetBulletType(BULLETTYPE BulletType)
{
	//�^�C�v�𔽉f
	m_BulletType = BulletType;

	//���C�t���Z�b�g
	SetLife(360);

	//���f�����擾
	CXfile::CModel aModelInfo = GetModelInfo();

	//�^�C�v���ƂɐF��ݒ�
	switch (m_BulletType)
	{
	//�v���C���[
	case PLAYER:
		for (int nCntMat = 0; nCntMat < (int)aModelInfo.dwNumMat; nCntMat++)
		{
			//�F
			aModelInfo.Diffuse[nCntMat].r = 0.0f;
			aModelInfo.Diffuse[nCntMat].g = 0.849f;
			aModelInfo.Diffuse[nCntMat].b = 1.0f;
		}
		break;

	//�N���[��
	case CLONE:
		for (int nCntMat = 0; nCntMat < (int)aModelInfo.dwNumMat; nCntMat++)
		{
			//���F
			aModelInfo.Diffuse[nCntMat].r = 0.878f;
			aModelInfo.Diffuse[nCntMat].g = 1.0f;
			aModelInfo.Diffuse[nCntMat].b = 1.0f;
		}
		break;
		
	//�G�l�~�[
	case BOUND_ENEMY:
	case LAUNCH_ENEMY:
		for (int nCntMat = 0; nCntMat < (int)aModelInfo.dwNumMat; nCntMat++)
		{
			//�ԐF
			aModelInfo.Diffuse[nCntMat].r = 0.862f;
			aModelInfo.Diffuse[nCntMat].g = 0.078f;
			aModelInfo.Diffuse[nCntMat].b = 0.235f;
		}
		break;

	//���G
	case BOUND_INVINCIBLE:
	case LAUNCH_INVINCIBLE:
		for (int nCntMat = 0; nCntMat < (int)aModelInfo.dwNumMat; nCntMat++)
		{
			//���F
			aModelInfo.Diffuse[nCntMat].r = 1.0f;
			aModelInfo.Diffuse[nCntMat].g = 1.0f;
			aModelInfo.Diffuse[nCntMat].b = 0.0f;
		}
		break;

	default:
		break;
	}

	//���f�����ݒ�
	BindModel(&aModelInfo);
}
