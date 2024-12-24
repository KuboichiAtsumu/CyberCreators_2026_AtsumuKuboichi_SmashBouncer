//==============================================================================================================================================
//
// �X�e�[�W�ʃ]�[���̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "zone.h"//�]�[��
#include "enemy.h"//�G�l�~�[

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
int CZone::m_nAllNumZone = 0;//�]�[���̑���
int CZone::m_nNumZone[MAX_ZONE_TYPE] = {};//�e�^�C�v�̑���
char CZone::m_aTextureFile[MAX_ZONE_TYPE][CProcess::MAX_TEXT] = {};//�e�^�C�v�̃e�N�X�`���t�@�C��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CZone::CZone(int nPriority) : CObject3D(nPriority)
{
	//�����o�ϐ�������
	m_ZoneType = STAGE;//�]�[���^�C�v
	m_nStageID = 0;//�e�]�[���̃X�e�[�WID
	m_bCollision = true;//�]�[���̓����蔻��̗L�����t���O
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CZone::~CZone()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CZone::Init()
{
	//�^�C�v�ʂɐF��ݒ�
	switch (m_ZoneType)
	{
	//�X�e�[�W�敪
	case STAGE:
#ifdef _DEBUG
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
#else
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
#endif // _DEBUG
		break;

	default:
		break;
	}

	//�X�e�[�WID�ݒ�
	m_nStageID = m_nNumZone[m_ZoneType];

	//�X�e�[�W�]�[���̑��������Z
	m_nNumZone[m_ZoneType]++;

	//���v�]�[���̐������Z
	m_nAllNumZone++;

	//�e�N�X�`������
	CTexture* pTex = CManager::GetTexture();//�擾
	int nTextureIdx = pTex->Regist(m_aTextureFile[m_ZoneType]);//�o�^
	BindTexture(pTex->GetAddress(nTextureIdx));//�ݒ�
	SetTextureIdx(nTextureIdx);//ID�ݒ�

	//3D�I�u�W�F�N�g����������
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CZone::Uninit()
{
	//���������炷
	m_nNumZone[m_ZoneType]--;
	m_nAllNumZone--;

	//�I�u�W�F�N�g�̏I������
	CObject3D::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CZone::Update()
{
	//�ړ����̏ꍇ�A�s�v�ȃ]�[�����g�p���Ȃ�
	if (CGame::GetGameState() == CGame::STATE_MOVE
		&& m_nStageID <= CGame::GetNumStage())
	{
		m_bCollision = false;
	}

	//�I�u�W�F�N�g�̍X�V����
	CObject3D::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CZone::Draw()
{
	//�I�u�W�F�N�g�̕`�揈��
	CObject3D::Draw();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CZone* CZone::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size, ZONETYPE type)
{
	//�������𓮓I�m��
	CZone* pZone = NEW CZone();

	//�p�����[�^�ݒ�
	pZone->SetType(TYPE::ZONE);//�I�u�W�F�N�g��ނ̐ݒ�
	pZone->SetPos(pos);//�ʒu�ݒ�
	pZone->SetSize(Size);//�T�C�Y�ݒ�
	pZone->SetZoneType(type);//�]�[���^�C�v�ݒ�

	//����������
	pZone->Init();

	return pZone;
}

//===========================================================================================================
// �Ώۂ�����X�e�[�W�̔��菈��
//===========================================================================================================
bool CZone::Judge(D3DXVECTOR3& pos)
{
	//���̎擾
	D3DXVECTOR3 StagePos = GetPos();//�ʒu
	D3DXVECTOR3 StageSize = GetSize();//�T�C�Y

	//�͈͓��������ꍇ
	//�����蔻�肪�L���̏ꍇ
	if (pos.x >= StagePos.x - StageSize.x * 0.5f
		&& pos.x <= StagePos.x + StageSize.x * 0.5f
		&& pos.z >= StagePos.z - StageSize.z * 0.5f
		&& pos.z <= StagePos.z + StageSize.z * 0.5f
		&& m_bCollision)
	{
		//�͈͓��̏ꍇtrue��Ԃ�
		return true;
	}

	//�͈͊O�̏ꍇfalse��Ԃ�
	return false;
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
void CZone::Collision(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& size)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Pos = GetPos();//�ʒu���
	D3DXVECTOR3 Size = GetSize();//�T�C�Y���

	//�����̔���
	if (pos.x - size.x * 0.5f < Pos.x - Size.x * 0.5f
		&& oldpos.x - size.x * 0.5f >=  Pos.x - Size.x * 0.5f)
	{
		//�ߋ��̈ʒu�ɖ߂�
		pos.x = oldpos.x;
	}

	//�ړ����͔��肵�Ȃ�
	if (CGame::GetGameState() != CGame::STATE_MOVE)
	{
		//�E���̔���
		if (pos.x + size.x * 0.5f > Pos.x + Size.x * 0.5f
			&& oldpos.x + size.x * 0.5f <= Pos.x + Size.x * 0.5f)
		{
			//�ߋ��̈ʒu�ɖ߂�
			pos.x = oldpos.x;
		}
	}

	//��O���̔���
	if (pos.z - size.z * 0.5f < Pos.z - Size.z * 0.5f
		&& oldpos.z - size.z * 0.5f >= Pos.z - Size.z * 0.5f)
	{
		//�ߋ��̈ʒu�ɖ߂�
		pos.z = oldpos.z;
	}

	//�����̔���
	if (pos.z + size.z * 0.5f > Pos.z + Size.z * 0.5f
		&& oldpos.z + size.z * 0.5f <= Pos.z + Size.z * 0.5f)
	{
		//�ߋ��̈ʒu�ɖ߂�
		pos.z = oldpos.z;
	}
}

//===========================================================================================================
// �e�]�[���^�C�v�̃e�N�X�`���t�@�C���Ǎ�����
//===========================================================================================================
void CZone::LoadZoneTexFile()
{
	//���[�J���ϐ��錾
	int nNumFile = 0;//�t�@�C���p�X�ԍ�
	char aDataSearch[CProcess::MAX_TEXT];//�����p�ϐ�

	//�t�@�C�����J��
	FILE* pFile = fopen(TEXTURE_FILE, "r");

	//�t�@�C�����J���Ȃ��ꍇ
	if (pFile == nullptr)
	{
		return;
	}

	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		//����
		int nResult = fscanf(pFile, "%s", aDataSearch);

		//EOF�����������ꍇ
		if (nResult == EOF)
		{//�ǂݍ��ݏI��
			fclose(pFile);
			break;
		}
		//BLOCK�����������ꍇ
		else if (!strcmp(aDataSearch, "FILE_SET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				//����
				fscanf(pFile, "%s", aDataSearch);

				//END_BLOCK�����������ꍇ
				if (!strcmp(aDataSearch, "END_FILE"))
				{//�ǂݍ��݂��I��
					break;
				}
				//�f�[�^�̓ǂݍ���
				else if (!strcmp(aDataSearch, "FILE"))
				{//�t�@�C���p�X
					fscanf(pFile, "%d", &nNumFile);//�t�@�C���p�X�ԍ�
					fscanf(pFile, "%s", &m_aTextureFile[nNumFile]);//�t�@�C���p�X
				}
			}
		}
		//��L�ȊO�����������ꍇ
		else
		{//��΂��Ă��̂܂ܓǍ��𑱂���

			continue;
		}
	}
}
