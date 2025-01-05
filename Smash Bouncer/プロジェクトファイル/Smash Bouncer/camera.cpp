//==============================================================================================================================================
//
// �J�����̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "camera.h"//�J����
#include "manager.h"//�}�l�[�W���[
#include "keyboard.h"//�L�[�{�[�h
#include "player.h"//�v���C���[
#include "zone.h"//�]�[��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CCamera::CCamera()
{
	//�����o�ϐ�������
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
	m_posV = FirstPosV;//���_
	m_fLength = sqrtf(powf(m_posV.y, 2.0f) + powf(m_posV.z, 2.0f)) * 0.5f;//����
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����_
	m_nShakeFrame = 0;//�h���t���[����
	m_nMaxNumShake = 0;//�h��̗ʂ̍ő�l
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CCamera::~CCamera()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CCamera::Init()
{
	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CCamera::Uninit()
{
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CCamera::Update()
{
#ifdef _DEBUG
	//�ړ�����
	Move();
#endif // _DEBUG

	//�Q�[�����̏ꍇ
	if (!CManager::GetScene()->GetEditMode())
	{
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

				//�I�u�W�F�N�g�^�C�v���v���C���[�̏ꍇ
				//�Q�[���̏�Ԃ��ړ����̏ꍇ
				if (type == CObject::PLAYER && CGame::GetGameState() == CGame::STATE_MOVE)
				{
					//�v���C���[�̈ʒu���Q�Ƃ������_�E�����_�ݒ�
					SetPlayerPos(pObj);
				}

				//�I�u�W�F�N�g�^�C�v���]�[���̏ꍇ
				//�Q�[���̏�Ԃ��Q�[�����̏ꍇ
				if (type == CObject::ZONE && CGame::GetGameState() == CGame::STATE_GAME)
				{
					//�]�[���̈ʒu���Q�Ƃ������_�E�����_�ݒ�
					SetZonePos(pObj);
				}

				//�I�u�W�F�N�g�������̏��ɕύX����
				pObj = pNext;
			}
		}
	}
}

//===========================================================================================================
// �ړ�����
//===========================================================================================================
void CCamera::Move()
{
	DIMOUSESTATE pMouse = CManager::GetMouse()->Get();	//�}�E�X�̏����擾

	//���N���b�N�������Ă���ꍇ
	if (CManager::GetMouse()->GetPress(CInputMouse::MOUSE_LEFT))
	{//�}�E�X�̓����ɍ��킹�Ď��_�𓮂���
		m_rot.y += 0.05f * pMouse.lX * 0.1f;
		m_move.y -= 50.0f * pMouse.lY * 0.1f;
	}

	//�z�C�[���̓����ɍ��킹�ăJ����������
	m_posV.x += 5.0f * sinf(m_rot.y) * pMouse.lZ * 0.1f;
	m_posV.y += 5.0f * pMouse.lZ * 0.1f;
	m_posV.z += 5.0f * cosf(m_rot.y) * pMouse.lZ * 0.1f;

	//��ړ�(Z��)
	if (CManager::GetKeyboard()->GetPress(DIK_UP))//���L�[�������ꂽ
	{
		//����ړ�(Z��)
		if (CManager::GetKeyboard()->GetPress(DIK_LEFT))//���L�[�������ꂽ
		{
			//�ړ��ʂ����Z
			m_move.x += sinf(m_rot.y + D3DX_PI * -0.25f) * MAX_SPEED;//X��
			m_move.z += cosf(m_rot.y + D3DX_PI * -0.25f) * MAX_SPEED;//Z��
		}
		//�E��ړ�(Z��)
		else if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))//���L�[�������ꂽ
		{
			//�ړ��ʂ����Z
			m_move.x += sinf(m_rot.y + D3DX_PI * 0.25f) * MAX_SPEED;//X��
			m_move.z += cosf(m_rot.y + D3DX_PI * 0.25f) * MAX_SPEED;//Z��
		}
		//�^��ړ�(Z��)
		else
		{
			//�ړ��ʂ����Z
			m_move.x -= sinf(m_rot.y + D3DX_PI) * MAX_SPEED;//X��
			m_move.z -= cosf(m_rot.y + D3DX_PI) * MAX_SPEED;//Z��
		}
	}
	//���ړ�(Z��)
	else if (CManager::GetKeyboard()->GetPress(DIK_DOWN))//���L�[�������ꂽ
	{
		//�����ړ�(Z��)
		if (CManager::GetKeyboard()->GetPress(DIK_LEFT))//���L�[�������ꂽ
		{
			//�ړ��ʂ����Z
			m_move.x += sinf(m_rot.y + D3DX_PI * -0.75f) * MAX_SPEED;//X��
			m_move.z += cosf(m_rot.y + D3DX_PI * -0.75f) * MAX_SPEED;//Z��
		}
		//�E���ړ�(Z��)
		else if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))//���L�[�������ꂽ
		{
			//�ړ��ʂ����Z
			m_move.x += sinf(m_rot.y + D3DX_PI * 0.75f) * MAX_SPEED;//X��
			m_move.z += cosf(m_rot.y + D3DX_PI * 0.75f) * MAX_SPEED;//Z��
		}
		//�^���ړ�(Z��)
		else
		{
			//�ړ��ʂ����Z
			m_move.x += sinf(m_rot.y + D3DX_PI) * MAX_SPEED;//X��
			m_move.z += cosf(m_rot.y + D3DX_PI) * MAX_SPEED;//Z��
		}
	}
	//���ړ�
	else if (CManager::GetKeyboard()->GetPress(DIK_LEFT))//���L�[�������ꂽ
	{
		//�ړ��ʂ����Z
		m_move.x += sinf(m_rot.y + D3DX_PI * -0.5f) * MAX_SPEED;//X��
		m_move.z += cosf(m_rot.y + D3DX_PI * -0.5f) * MAX_SPEED;//Z��
	}
	//�E�ړ�
	else if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))//���L�[�������ꂽ
	{
		//�ړ��ʂ����Z
		m_move.x += sinf(m_rot.y + D3DX_PI * 0.5f) * MAX_SPEED;//X��
		m_move.z += cosf(m_rot.y + D3DX_PI * 0.5f) * MAX_SPEED;//Z��
	}

	//�ړ��ʂ̉��Z
	m_posV += m_move;

	//�ړ��ʂ�����
	m_move -= m_move;

	//�����_�̈ʒu�̍X�V
	m_posR.x = sinf(m_rot.y) * m_fLength + m_posV.x;
	m_posR.z = cosf(m_rot.y) * m_fLength + m_posV.z;
}

//===========================================================================================================
// �v���C���[�̈ʒu���Q�Ƃ������_�E�����_�ݒ�
//===========================================================================================================
void CCamera::SetPlayerPos(CObject* pObj)
{
	//�I�u�W�F�N�g�����v���C���[���ɕϊ�
	CPlayer* pPlayer = (CPlayer*)pObj;

	//�v���C���[�̈ʒu����ۑ�
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	//�v���C���[���J�������E���ɂ���ꍇ
	if (PlayerPos.x >= m_posV.x)
	{
		//�v���C���[�ɍ��킹�Ď��_�E�����_���X�V
		m_posV.x = PlayerPos.x;//���_
		m_posR.x = PlayerPos.x;//�����_
	}
}

//===========================================================================================================
// �]�[���̈ʒu���Q�Ƃ������_�E�����_�ݒ�
//===========================================================================================================
void CCamera::SetZonePos(CObject* pObj)
{
	//�I�u�W�F�N�g�����v���C���[���ɕϊ�
	CZone* pZone = (CZone*)pObj;

	//�]�[���^�C�v���X�e�[�W�敪�̏ꍇ
	//�]�[����ID�ƌ��݂̃X�e�[�W����v����ꍇ
	if (pZone->GetZoneType() == CZone::STAGE
		&& pZone->GetID() == CGame::GetNumStage())
	{
		//�]�[���̈ʒu�����擾
		D3DXVECTOR3 ZonePos = pZone->GetPos();

		//�J�������]�[���̒��S��荶���ɂ���ꍇ
		if (m_posV.x < ZonePos.x)
		{
			m_posV.x += ADJUST_POS_SPEED;
			m_posR.x += ADJUST_POS_SPEED;

			//���_�̈ʒu���]�[���̉E���𒴂��Ȃ��悤�ɒ���
			if (m_posV.x > ZonePos.x)
			{
				m_posV.x = ZonePos.x;
			}

			//�����_�̈ʒu���]�[���̉E���𒴂��Ȃ��悤�ɒ���
			if (m_posR.x > ZonePos.x)
			{
				m_posR.x = ZonePos.x;
			}
		}
	}
}

//===========================================================================================================
// �J�����̐ݒ�
//===========================================================================================================
void CCamera::SetCamera()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 adjust = { 0.0f, 0.0f, 0.0f };//�h��̗�

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)CProcess::SCREEN_WIDTH / (float)CProcess::SCREEN_HEIGHT, 1.0f, 5000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�t���[������0�ȏ�̏ꍇ
	if (m_nShakeFrame > 0)
	{
		//�t���[����������
		m_nShakeFrame--;

		//�h��̗ʂ̍ő�l��1�ȏ�̏ꍇ
		if (m_nMaxNumShake >= 1)
		{
			//�h��̗ʂ�ݒ�
			adjust.x = (float)(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
			adjust.y = (float)(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
			adjust.z = (float)(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
		}
	}

	//�h��̗ʂ����Z�������_�ƒ����_�̒l��ۑ�
	D3DXVECTOR3 posV = m_posV + adjust;
	D3DXVECTOR3 posR = m_posR + adjust;

	//�r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&m_mtxView, &posV, &posR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
