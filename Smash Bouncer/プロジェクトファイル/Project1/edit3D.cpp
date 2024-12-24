//==============================================================================================================================================
//
// 3D�G�f�B�^�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifdef _DEBUG

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "edit3D.h"//�G�f�B�^
#include "debugproc.h"//�f�o�b�O�\��
#include "keyboard.h"//�L�[�{�[�h
#include "game.h"//�Q�[���V�[��
#include "camera.h"//�J����

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
CEdit3D* CEdit3D::m_apEditObj[MAX_EDIT3D] = {};//�I�u�W�F�N�g���
CEdit3D::EDIT_MODE CEdit3D::m_mode = MODE_MOVE;//���샂�[�h
int CEdit3D::m_nNumAll = 0;//���v�f�[�^��
int CEdit3D::m_nTarget = 0;//�ҏW�Ώ۔ԍ�
bool CEdit3D::m_bTrigger = false;//�ړ����@���g���K�[���ǂ���

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CEdit3D::CEdit3D(int nPriority) : CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_EDIT3D; nCnt++)
	{
		//�f�[�^�����݂��Ȃ��ꍇ
		if (m_apEditObj[nCnt] == nullptr)
		{
			//�������g����
			m_apEditObj[nCnt] = this;

			//�����o�[�ϐ�������
			m_apEditObj[nCnt]->m_pos = { 0.0f, 0.0f, 0.0f };//�ʒu
			m_apEditObj[nCnt]->m_rot = { 0.0f, 0.0f, 0.0f };//����
			m_apEditObj[nCnt]->m_Scale = { 1.0f, 1.0f, 1.0f };//�g�嗦
			m_apEditObj[nCnt]->m_apModel = {};//���f�����
			m_apEditObj[nCnt]->m_bUse = true;//�g�p�t���O
			m_apEditObj[nCnt]->m_nID = nCnt;//�������g��ID
			m_apEditObj[nCnt]->m_nType = 0;//�^�C�v
			m_apEditObj[nCnt]->m_nCategory = 0;//�J�e�S���[

			//�������Z
			m_nNumAll++;

			//���[�v�𔲂���
			break;
		}
	}

	//�ҏW�Ώېݒ�
	m_nTarget = m_apEditObj[m_nID]->m_nID;
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CEdit3D::~CEdit3D()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CEdit3D::Init()
{
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
void CEdit3D::Uninit()
{
	//�I������
	CObjectX::Uninit();
}

//===========================================================================================================
// �S�I�u�W�F�N�g�I������
//===========================================================================================================
void CEdit3D::UninitAll()
{
	for (int nCnt = 0; nCnt < MAX_EDIT3D; nCnt++)
	{
		//�f�[�^�����݂���ꍇ
		if (m_apEditObj[nCnt] != nullptr)
		{
			//�f�[�^�����
			m_apEditObj[nCnt]->Uninit();
			m_apEditObj[nCnt] = nullptr;
		}
	}

	//�������Z�b�g
	m_nNumAll = 0;
}

//===========================================================================================================
// �������
//===========================================================================================================
void CEdit3D::Release()
{
	//ID��ۑ�
	int nID = m_nID;
	m_apEditObj[nID] = nullptr;
}

//===========================================================================================================
// �G�f�B�^���X�V����
//===========================================================================================================
void CEdit3D::EditUpdate()
{
	//=======================================================================
	// �ړ����@�؂�ւ�
	//=======================================================================
	if (CManager::GetKeyboard()->GetTrigger(DIK_1))
	{//1�L�[�������ꂽ�ꍇ
		m_bTrigger = m_bTrigger ? false : true;
	}

	//=======================================================================
	// ���샂�[�h�ύX
	//=======================================================================

	//F5�L�[�������ꂽ�ꍇ
	if (CManager::GetKeyboard()->GetTrigger(DIK_F5))
	{
		//�ړ�
		m_mode = MODE_MOVE;
	}
	//F6�L�[�������ꂽ�ꍇ
	else if (CManager::GetKeyboard()->GetTrigger(DIK_F6))
	{
		//�g��
		m_mode = MODE_SCALE;
	}

	//=======================================================================
	// �ҏW�ΏەύX
	//=======================================================================

	//N�L�[�������ꂽ�ꍇ
	if (CManager::GetKeyboard()->GetRepeat(DIK_N))
	{
		//��SHIFT�L�[��������Ă���ꍇ
		if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
		{
			//10�O�̃I�u�W�F�N�g��Ώۂɂ���
			m_nTarget -= 10;
		}
		else
		{
			//�O�̃I�u�W�F�N�g��Ώۂɂ���
			m_nTarget--;
		}

		//�J�E���g���I�u�W�F�N�g�̍ő吔�ɓ��B�����ꍇ
		if (m_nTarget < 0)
		{
			//��ԍŌ�Ƀ��[�v����
			m_nTarget = m_nNumAll - 1;
		}

		//�J�����̍��W�ݒ菈��
		SetCameraPos();
	}
	//M�L�[�������ꂽ�ꍇ
	else if (CManager::GetKeyboard()->GetRepeat(DIK_M))
	{
		//��SHIFT�L�[��������Ă���ꍇ
		if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
		{
			//10��̃I�u�W�F�N�g��Ώۂɂ���
			m_nTarget += 10;
		}
		else
		{
			//��̃I�u�W�F�N�g��Ώۂɂ���
			m_nTarget++;
		}

		//�J�E���g���I�u�W�F�N�g�̍ő吔�ɓ��B�����ꍇ
		if (m_nTarget > m_nNumAll - 1)
		{
			//��ԍŏ��Ƀ��[�v����
			m_nTarget = 0;
		}

		//�J�����̍��W�ݒ菈��
		SetCameraPos();
	}

	//=======================================================================
	// �z�u
	//=======================================================================
	if (CManager::GetKeyboard()->GetTrigger(DIK_B))
	{//B�L�[�������ꂽ�ꍇ

		//���̔z�u�I�u�W�F�N�g�𐶐�
		Create();

		//���̃I�u�W�F�N�g�ɑO�̃I�u�W�F�N�g�̏��𔽉f
		m_apEditObj[m_nTarget]->m_pos = m_apEditObj[m_nTarget - 1]->m_pos;//�ʒu
		m_apEditObj[m_nTarget]->m_rot = m_apEditObj[m_nTarget - 1]->m_rot;//�p�x
		m_apEditObj[m_nTarget]->m_Scale = m_apEditObj[m_nTarget - 1]->m_Scale;//�g�嗦
		m_apEditObj[m_nTarget]->m_nCategory = m_apEditObj[m_nTarget - 1]->m_nCategory;//�J�e�S���[
		m_apEditObj[m_nTarget]->m_nType = m_apEditObj[m_nTarget - 1]->m_nType;//�^�C�v

		//�J�����̍��W�ݒ菈��
		SetCameraPos();
	}

	//=======================================================================
	// �폜
	//=======================================================================
	if (CManager::GetKeyboard()->GetTrigger(DIK_DELETE))
	{//DELETE�L�[�������ꂽ�ꍇ

		//�z�u����Ă��Ȃ���Ԃɂ���
		m_apEditObj[m_nTarget]->m_bUse = false;

		//�������
		m_apEditObj[m_nTarget]->SetDeleteFlag(true);
		
		//�Ώۂ�1�O����
		m_nTarget--;

		//�^�[�Q�b�g�ԍ���0�ȉ��ɂȂ�Ȃ悤�ɒ���
		if (m_nTarget < 0)
		{
			m_nTarget = 0;
		}

		//���������Z
		m_nNumAll--;

		//�J�����̍��W�ݒ菈��
		SetCameraPos();
	}

	//=======================================================================
	// �폜���ꂽ���̃f�[�^���l�߂�
	//=======================================================================
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		//�O�̃f�[�^���󂢂Ă���ꍇ
		if (m_apEditObj[nCnt] == nullptr && m_apEditObj[nCnt + 1] != nullptr)
		{
			//�f�[�^���l�߂�
			m_apEditObj[nCnt] = m_apEditObj[nCnt + 1];

			//�l�߂����̃f�[�^�����
			m_apEditObj[nCnt + 1]->Release();

			//ID���C������
			m_apEditObj[nCnt]->m_nID = nCnt;
		}
	}

	//=======================================================================
	// �f�[�^�̏����o��
	//=======================================================================
	if (CManager::GetKeyboard()->GetTrigger(DIK_F3))
	{//F3�L�[�������ꂽ�ꍇ

		//�����o������
		Save();
	}
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CEdit3D::Update()
{
	//�G�f�B�^���[�h�ł͂Ȃ��ꍇ
	if (!CManager::GetScene()->GetEditMode())
	{//�`�悹���ɏ����𔲂���
		return;
	}

	//�ҏW�Ώۂ�ID����v����ꍇ
	if (m_nTarget == m_nID)
	{
		//=========================================================================================
		// ������@�\��
		//=========================================================================================
		PrintDebugProc("==============================\n ����( F5 : �ړ��@F6 : �g�� )\n==============================\n");

		switch (m_mode)
		{
		case MODE_MOVE:
			PrintDebugProc("�ړ�\nX���ړ�:T,G�@Y���ړ�:Y,H�@Z���ړ�:U,J\n\n");
			break;
		case MODE_SCALE:
			PrintDebugProc("�g��\nX���g��:T,G�@Y���g��:Y,H�@Z���g��:U,J\n\n");
			break;
		default:
			break;
		}

		PrintDebugProc("��]\n����]:Z�@�E��]:X\n\n");
		PrintDebugProc("�ʒu�ƌ��������Z�b�g:R\n\n");
		PrintDebugProc("�J����\n�ړ�:WASD\n\n");
		PrintDebugProc("�J�e�S���[�ύX:��SHIFT + Q,E\n");
		PrintDebugProc("��ނ�ύX:Q,E\n");
		PrintDebugProc("�z�u:B\n");
		PrintDebugProc("�ҏW�ΏەύX:N,M\n");
		PrintDebugProc("�폜:DELETE\n");
		PrintDebugProc("�S���Z�b�g:0\n");
		PrintDebugProc("�����o��:F3\n\n");

		//�z�u���f�[�^�\��
		PrintDebugProc("==============================\n �z�u���f�[�^ \n==============================\n");

		//���샂�[�h��\��
		PrintDebugProc("���샂�[�h( 1�Ő؂�ւ� ) : ");
		if (!m_bTrigger)
		{//�v���X
			PrintDebugProc("Press\n\n");
		}
		else
		{//�g���K�[
			PrintDebugProc("Trigger\n\n");
		}

		//���샂�[�h�ʂɊg�嗦�𒲐�
		switch (m_mode)
		{
			//�ʒu
		case MODE_MOVE:
			PrintDebugProc("POS\nX:%f�@Y:%f�@Z:%f\n\n", m_apEditObj[m_nTarget]->m_pos.x, m_apEditObj[m_nTarget]->m_pos.y, m_apEditObj[m_nTarget]->m_pos.z);
			break;

			//�g�嗦
		case MODE_SCALE:
			PrintDebugProc("SCALE\nX:%f�@Y:%f�@Z:%f\n\n", m_apEditObj[m_nTarget]->m_Scale.x, m_apEditObj[m_nTarget]->m_Scale.y, m_apEditObj[m_nTarget]->m_Scale.z);
			break;

		default:
			break;
		}

		PrintDebugProc("ROT\nX:%f�@Y:%f  Z:%f\n\n", m_apEditObj[m_nTarget]->m_rot.x, m_apEditObj[m_nTarget]->m_rot.y, m_apEditObj[m_nTarget]->m_rot.z);//����
		PrintDebugProc("CATEGORY:%d\n\n", m_apEditObj[m_nTarget]->m_nCategory);//�J�e�S���[
		PrintDebugProc("TYPE:%d\n\n", m_apEditObj[m_nTarget]->m_nType);//���
		PrintDebugProc("�z�u��:%d/%d\n", m_apEditObj[m_nTarget]->m_nID + 1, m_nNumAll);//�z�u��

		//=========================================================================================
		// �I�u�W�F�N�g�f�[�^�X�V
		//=========================================================================================

		//���f���f�[�^�𔽉f
		m_apEditObj[m_nTarget]->m_apModel = CXfile::GetSaveModelInfo(m_apEditObj[m_nTarget]->m_nCategory, m_apEditObj[m_nTarget]->m_nType);
		
		//���샂�[�h�ʏ���
		switch (m_mode)
		{
			//�ړ�
		case MODE_MOVE:
			Move();
			break;

			//�g��
		case MODE_SCALE:
			Scale();
			break;

		default:
			break;
		}

		//=======================================================================
		// ��]
		//=======================================================================
		if (CManager::GetKeyboard()->GetTrigger(DIK_Z))
		{//Z�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_rot.y -= TURN;//�E��]
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_X))
		{//X�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_rot.y += TURN;//����]
		}

		//�p�x�̕␳
		if (m_apEditObj[m_nTarget]->m_rot.y <= -D3DX_PI)
		{
			m_apEditObj[m_nTarget]->m_rot.y = D3DX_PI;
		}
		else if (m_apEditObj[m_nTarget]->m_rot.y >= D3DX_PI)
		{
			m_apEditObj[m_nTarget]->m_rot.y = -D3DX_PI;
		}

		//=======================================================================
		// ���Z�b�g
		//=======================================================================

		//R�L�[�������ꂽ�ꍇ
		if (CManager::GetKeyboard()->GetTrigger(DIK_R))
		{
			//�p�����[�^���Z�b�g
			m_apEditObj[m_nTarget]->m_pos = { 0.0f,0.0f,0.0f };//�ʒu
			m_apEditObj[m_nTarget]->m_rot = { 0.0f,0.0f,0.0f };//�p�x
			m_apEditObj[m_nTarget]->m_Scale = { 1.0f,1.0f,1.0f };//�g�嗦

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}

		//=======================================================================
		// �J�e�S���[�E��ޕύX
		//=======================================================================
		if (CManager::GetKeyboard()->GetTrigger(DIK_Q))
		{//Q�L�[�������ꂽ�ꍇ
			if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
			{
				//��SHIFT��������Ă���ꍇ
				if (m_apEditObj[m_nTarget]->m_nCategory > 0)
				{
					//�J�e�S���[�ύX
					m_apEditObj[m_nTarget]->m_nCategory--;

					//��ނ��ŏ��ɖ߂�
					m_apEditObj[m_nTarget]->m_nType = 0;
				}
			}
			else
			{
				//��SHIFT��������Ă��Ȃ��ꍇ
				if (m_apEditObj[m_nTarget]->m_nType > 0)
				{
					//��ޕύX
					m_apEditObj[m_nTarget]->m_nType--;
				}
			}
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_E))
		{//E�L�[�������ꂽ�ꍇ
			if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
			{//��SHIFT��������Ă���ꍇ
				if (m_apEditObj[m_nTarget]->m_nCategory < CXfile::MAX_CATEGORY - 1)
				{
					//��ޕύX
					m_apEditObj[m_nTarget]->m_nCategory++;

					//��ނ��ŏ��ɖ߂�
					m_apEditObj[m_nTarget]->m_nType = 0;
				}
			}
			else
			{//��SHIFT��������Ă��Ȃ��ꍇ
				if (m_apEditObj[m_nTarget]->m_nType < (int)CObjectX::m_nNumType[m_apEditObj[m_nTarget]->m_nCategory] - 1)
				{//��ޕύX
					m_apEditObj[m_nTarget]->m_nType++;
				}
			}
		}
	}
}

//===========================================================================================================
// �ړ�����
//===========================================================================================================
void CEdit3D::Move()
{
	//Press
	if (!m_bTrigger)
	{
		if (CManager::GetKeyboard()->GetPress(DIK_T))
		{//T�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.x -= MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_G))
		{//G�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.x += MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_Y))
		{//Y�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.y += MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_H))
		{//H�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.y -= MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_U))
		{//U�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.z += MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_J))
		{//J�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.z -= MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
	}
	//Trigger
	else
	{
		if (CManager::GetKeyboard()->GetTrigger(DIK_T))
		{//T�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.x -= MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_G))
		{//G�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.x += MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_Y))
		{//Y�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.y += MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_H))
		{//H�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.y -= MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_U))
		{//U�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.z += MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_J))
		{//J�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_pos.z -= MOVE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
	}
}

//===========================================================================================================
// �g�又��
//===========================================================================================================
void CEdit3D::Scale()
{
	//Press
	if (!m_bTrigger)
	{
		if (CManager::GetKeyboard()->GetPress(DIK_T))
		{//T�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.x -= SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_G))
		{//G�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.x += SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_Y))
		{//Y�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.y += SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_H))
		{//H�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.y -= SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_U))
		{//U�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.z += SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_J))
		{//J�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.z -= SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
	}
	//Trigger
	else
	{
		if (CManager::GetKeyboard()->GetTrigger(DIK_T))
		{//T�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.x -= SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_G))
		{//G�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.x += SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_Y))
		{//Y�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.y += SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_H))
		{//H�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.y -= SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_U))
		{//U�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.z += SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_J))
		{//J�L�[�������ꂽ�ꍇ
			m_apEditObj[m_nTarget]->m_Scale.z -= SCALE;

			//�J�����̍��W�ݒ菈��
			SetCameraPos();
		}
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CEdit3D::Draw()
{
	//�G�f�B�^���[�h�ł͂Ȃ��ꍇ
	if (!CManager::GetScene()->GetEditMode())
	{//�`�悹���ɏ����𔲂���
		return;
	}

	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���̃f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�@���̒�����1�ɂ���B
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_apModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_apModel->dwNumMat; nCntMat++)
	{
		//�ҏW�Ώۂ̃I�u�W�F�N�g�̏ꍇ
		if (m_nTarget == m_nID)
		{
			//���f���̐F��ω�
			pMat[nCntMat].MatD3D.Diffuse.a = 0.5f;
		}
		//�ҏW�Ώۂ̃I�u�W�F�N�g�ł͂Ȃ��ꍇ
		else
		{
			//���f���̐F�����ɖ߂�
			pMat[nCntMat].MatD3D.Diffuse = 
			{ 
				m_apModel->FirstDiffuse[nCntMat].r, 
				m_apModel->FirstDiffuse[nCntMat].g, 
				m_apModel->FirstDiffuse[nCntMat].b, 
				m_apModel->FirstDiffuse[nCntMat].a 
			};
		}

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_apModel->m_pTexture);

		//���f��(�p�[�c)�̕`��
		m_apModel->pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================================
// ��������
//===========================================================================================================
CEdit3D* CEdit3D::Create()
{
	CEdit3D* pEdit = NEW CEdit3D();

	//����������
	pEdit->Init();
	
	return pEdit;
}

//===========================================================================================================
// �Z�[�u����
//===========================================================================================================
void CEdit3D::Save()
{
	//���[�J���ϐ��錾
	const char* StageFile = {""};//�X�e�[�W���t�@�C���p�X

	//�V�[���ɉ����ăt�@�C����ύX
	switch (CManager::GetScene()->GetMode())
	{
		//�`���[�g���A��
	case CScene::MODE_TUTORIAL:
		StageFile = CManager::TUTORIAL_STAGE;
		break;

		//�Q�[��
	case CScene::MODE_GAME:
		StageFile = CManager::GAME_STAGE;
		break;

	default:
		break;
	}

	//�t�@�C�����J��
	FILE* pFile = fopen(StageFile, "wb");

	//�t�@�C�������������ꍇ
	if (pFile != nullptr)
	{
		//�z�u���������o��
		fwrite(&m_nNumAll, sizeof(int), 1, pFile);

		for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
		{
			//�g�p����Ă���ꍇ
			if (m_apEditObj[nCnt] != nullptr && m_apEditObj[nCnt]->m_bUse)
			{
				//�f�[�^�̋L�^
				fwrite(&m_apEditObj[nCnt]->m_pos, sizeof(D3DXVECTOR3), 1, pFile);//�ʒu
				fwrite(&m_apEditObj[nCnt]->m_rot, sizeof(D3DXVECTOR3), 1, pFile);//����
				fwrite(&m_apEditObj[nCnt]->m_Scale, sizeof(D3DXVECTOR3), 1, pFile);//�g�嗦
				fwrite(&m_apEditObj[nCnt]->m_nCategory, sizeof(int), 1, pFile);//�J�e�S���[
				fwrite(&m_apEditObj[nCnt]->m_nType, sizeof(int), 1, pFile);//���
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//===========================================================================================================
// ���[�h����
//===========================================================================================================
void CEdit3D::LoadInfo(const char* FileName)
{
	//���[�J���ϐ��錾
	int nNumAll = 0;//����

	//�t�@�C�����J��
	FILE* pFile = fopen(FileName, "rb");

	//�I�u�W�F�N�g�f�[�^�̓ǂݍ���
	if (pFile != nullptr)
	{
		//�t�@�C���̓ǂݍ���
		fread(&nNumAll, sizeof(int), 1, pFile);

		for (int nCnt = 0; nCnt < nNumAll; nCnt++)
		{
			//�f�[�^�̎擾
			Create();//��������
			fread(&m_apEditObj[nCnt]->m_pos, sizeof(D3DXVECTOR3), 1, pFile);//�ʒu
			fread(&m_apEditObj[nCnt]->m_rot, sizeof(D3DXVECTOR3), 1, pFile);//����
			fread(&m_apEditObj[nCnt]->m_Scale, sizeof(D3DXVECTOR3), 1, pFile);//�g�嗦
			fread(&m_apEditObj[nCnt]->m_nCategory, sizeof(int), 1, pFile);//�J�e�S���[
			fread(&m_apEditObj[nCnt]->m_nType, sizeof(int), 1, pFile);//���

			//���f�����𔽉f
			m_apEditObj[nCnt]->m_apModel = CXfile::GetSaveModelInfo(m_apEditObj[nCnt]->m_nCategory, m_apEditObj[nCnt]->m_nType);
		}

		//�t�@�C�������
		fclose(pFile);
	}

	//�I�u�W�F�N�g�f�[�^��1�����݂��Ȃ��ꍇ
	if (nNumAll <= 0)
	{
		//�I�u�W�F�N�g��1����
		Create();
	}
}

//===========================================================================================================
// �J�����̍��W�ݒ�
//===========================================================================================================
void CEdit3D::SetCameraPos()
{
	//�ʒu�����擾
	D3DXVECTOR3 pos = m_apEditObj[m_nTarget]->m_pos;//�I�u�W�F�N�g
	D3DXVECTOR3 Camerapos = CManager::GetCamera()->FirstPosV;//�J�����̏����ʒu

	//�J�����̎��_�ƒ����_���I�u�W�F�N�g�ʒu�ɍ��킹�Đݒ�
	CManager::GetCamera()->SetPosV(D3DXVECTOR3(pos.x, Camerapos.y, pos.z + Camerapos.z));//���_
	CManager::GetCamera()->SetPosR(m_apEditObj[m_nTarget]->m_pos);//�����_
}

#endif // _DEBUG