//==============================================================================================================================================
//
// �M�~�b�N�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "gimmick.h"//�M�~�b�N
#include "movefloor.h"//�ړ���
#include "warphole.h"//���[�v�z�[��
#include "switchbase.h"//�X�C�b�`�x�[�X
#include "switch.h"//�X�C�b�`

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority)
{
	//�����o�ϐ�������
	m_pPrev = nullptr;//�O�̃M�~�b�N���
	m_pNext = nullptr;//���̃M�~�b�N���
	m_GimmickType = {};//�M�~�b�N�^�C�v
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CGimmick::~CGimmick()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CGimmick::Init()
{
	//�e�N�X�`������
	CTexture* pTex = CManager::GetTexture();//�擾
	int nTextureIdx = pTex->Regist(CXfile::GetSaveModelInfo(CXfile::GIMMICK, m_GimmickType)->aTextureFile);//�o�^
	BindTexture(pTex->GetAddress(nTextureIdx));//�ݒ�
	SetTextureIdx(nTextureIdx);//ID�ݒ�

	//���f������
	CXfile* pModel = CManager::GetModel();//�擾
	int nModelIdx = pModel->Regist(CXfile::GetSaveModelInfo(CXfile::GIMMICK, m_GimmickType)->aModelFile);//�o�^
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
void CGimmick::Uninit()
{
	//X�t�@�C���I�u�W�F�N�g�I������
	CObjectX::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CGimmick::Update()
{
	//X�t�@�C���I�u�W�F�N�g�X�V����
	CObjectX::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CGimmick::Draw()
{
	//�G�f�B�^���[�h�̏ꍇ
	if (CManager::GetScene()->GetEditMode())
	{//�`�悹���ɏ����𔲂���
		return;
	}

	//X�t�@�C���̃I�u�W�F�N�g�`�揈��
	CObjectX::Draw();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CGimmick* CGimmick::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	//�^�C�v�ɉ����ē��I�m��
	CGimmick* pGimmick = nullptr;
	switch (nType)
	{
		//�ړ���
	case MOVEFLOOR:
		pGimmick = NEW CMoveFloor(4);
		break;

		//���[�v�z�[��
	case WARPHOLE:
		pGimmick = NEW CWarpHole(4);
		break;

		//�X�C�b�`�x�[�X
	case SWITCHBASE:
		pGimmick = NEW CSwitchBase(4);
		break;

		//�X�C�b�`
	case SWITCH:
		pGimmick = NEW CSwitch(4);
		break;

	default:
		break;
	}

	pGimmick->SetType(TYPE::GIMMICK);//�I�u�W�F�N�g�^�C�v�ݒ�
	pGimmick->SetPos(pos);//�ʒu�ݒ�
	pGimmick->SetRot(rot);//�����ݒ�
	pGimmick->SetGimmickType((GIMMICKTYPE)nType);//�A�C�e���^�C�v�ݒ�
	pGimmick->Init();//����������

	return pGimmick;
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
bool CGimmick::Collision(D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXVECTOR3 size, D3DXVECTOR3& rot)
{
	//���[�J���ϐ��錾
	bool bCollision = false;//�����蔻��̃t���O

	//�����擾
	D3DXVECTOR3 Pos = GetPos();//�ʒu
	D3DXVECTOR3 Size = GetSize();//�T�C�Y

	//X���W���d�Ȃ����ꍇ
	if (pos.x + size.x * 0.5f >= Pos.x - Size.x * 0.5f
		&& pos.x - size.x * 0.5f <= Pos.x + Size.x * 0.5f)
	{
		//Z���W���d�Ȃ����ꍇ
		if (pos.z + size.z * 0.5f >= Pos.z - Size.z * 0.5f
			&& pos.z + size.z * 0.5f <= Pos.z + Size.z * 0.5f)
		{
			//�����蔻��̃t���O��true�ɂ���
			bCollision = true;
		}
	}

	return bCollision;
}
