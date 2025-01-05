//==============================================================================================================================================
//
// ���P�b�g�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "racket.h"

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CRacket::CRacket(int nPriority) : 
	CObjectX(nPriority),
	m_bDraw(false)
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CRacket::~CRacket()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CRacket::Init()
{
	//���f������
	CXfile* pModel = CManager::GetModel();//�擾
	int nModelIdx = pModel->Regist("data/MODEL/racket.x");//�o�^
	BindModel(pModel->GetAddress(nModelIdx));//�ݒ�
	SetModelIdx(nModelIdx);//ID�ݒ�
	
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
void CRacket::Uninit()
{
	//X�t�@�C���I�u�W�F�N�g�I������
	CObjectX::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
#include "player.h"
void CRacket::Update()
{
	//���[�J���ϐ��錾
	CInputJoypad* pJoypad = CManager::GetJoypad();//�W���C�p�b�h���
	CInputJoypad::STICKINPUT Stickinput = pJoypad->GetStick();//�X�e�B�b�N���͏��

	//�E�X�e�B�b�N���͒�
	if ((float)Stickinput.abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_UP] > 0.1f || 
		(float)Stickinput.abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_DOWN] > 0.1f || 
		(float)Stickinput.abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_RIGHT] > 0.1f || 
		(float)Stickinput.abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_LEFT] > 0.1f)
	{
		//�X�e�B�b�N�̌��݂̊p�x���擾
		float fStickAngle = pJoypad->GetAngleR();

		//�������g�̊p�x���擾
		D3DXVECTOR3 rot = GetRot();

		//�X�e�B�b�N�̊p�x�ɍ��킹�ĉ�]������
		rot.y = fStickAngle;

		//�p�x����ݒ�
		SetRot(rot);

		//�`��t���O��true�ɐݒ�
		m_bDraw = true;
	}
	//�E�X�e�B�b�N������
	else
	{
		//�`��t���O��false�ɐݒ�
		m_bDraw = false;
	}

	//�w�肵�����ԂɃI�u�W�F�N�g�����擾����
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		//�擪�̃I�u�W�F�N�g�����擾
		CObject* pObj = CObject::GetTop(nCnt);

		//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
		while (pObj != nullptr)
		{
			//���̃I�u�W�F�N�g�����擾
			CObject* pNext = pObj->GetNext();

			//�I�u�W�F�N�g�^�C�v�����擾
			CObject::TYPE type = pObj->GetType();

			//�I�u�W�F�N�g�^�C�v���v���C���[
			if (type == CObject::PLAYER)
			{
				//�v���C���[�N���X�Ƀ_�E���L���X�g
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

				//�v���C���[�̍��W
				D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

				//�X�V���W�ݒ�
				D3DXVECTOR3 UpdatePos(PlayerPos.x, PlayerPos.y + pPlayer->GetSize().y, PlayerPos.z);
				SetPos(UpdatePos);
			}

			//�I�u�W�F�N�g�������̏��ɕύX����
			pObj = pNext;
		}
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CRacket::Draw()
{
	//�`��t���O��true
	if (m_bDraw)
	{
		//X�t�@�C���I�u�W�F�N�g�`�揈��
		CObjectX::Draw();
	}
}

//===========================================================================================================
// ��������
//===========================================================================================================
CRacket* CRacket::Create(D3DXVECTOR3 pos)
{
	//�^�C�v���Ƃɓ��I�m��
	CRacket* pRacket = NEW CRacket();

	//�p�����[�^�ݒ�
	pRacket->SetPos(pos);//���W
	
	//����������
	pRacket->Init();
	
	return pRacket;
}
