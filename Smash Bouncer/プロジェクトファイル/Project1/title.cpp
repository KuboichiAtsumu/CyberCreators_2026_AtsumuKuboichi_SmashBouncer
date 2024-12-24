//==============================================================================================================================================
//
// �^�C�g����ʂɊւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "title.h"//�^�C�g��
#include "fade.h"//�t�F�[�h
#include "logo.h"//�^�C�g�����S
#include "push.h"//PUSH UI
#include "camera.h"//�J����
#include "fade.h"//�t�F�[�h

//�I�u�W�F�N�g
#include "field.h"//�t�B�[���h
#include "zone.h"//�]�[��

//�}�l�[�W���[
#include "blockmanager.h"//�u���b�N�}�l�[�W���[
#include "bulletmanager.h"//�o���b�g�}�l�[�W���[

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
CBlockManager* CTitle::m_pBlockManager = nullptr;//�u���b�N�}�l�[�W���[���
CBulletManager* CTitle::m_pBulletManager = nullptr;//�o���b�g�}�l�[�W���[���

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CTitle::CTitle()
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CTitle::~CTitle()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CTitle::Init()
{
	//���f���E�e�N�X�`�����̓ǂݍ��݂Ɠo�^����
	CXfile::LoadModelFile();//���f���t�@�C���p�X�Ǎ�
	CXfile::LoadTextureFile();//�e�N�X�`���t�@�C���p�X�Ǎ�
	CXfile::Regist();//�o�^����

	//�^�C�g�����S����
	CLogo::Create();

	//PUSH UI����
	CPush::Create();

	//�t�B�[���h��������
	CField::Create({ -450.0f, 0.0f, 0.0f }, { CField::FIELD_WIDTH, 0.0f, CField::FIELD_HEIGHT });

	//�X�e�[�W�e�N�X�`���t�@�C���p�X�Ǎ�����
	CZone::LoadZoneTexFile();

	//�X�e�[�W�敪�]�[������
	CZone::Create({ 10.0f, 0.01f, 0.0f }, { CZone::STAGEZONE_WIDTH, 0.0f, CZone::STAGEZONE_HEIGHT }, CZone::STAGE);

	//���˃]�[������
	CZone::Create({ -160.0f, 0.02f, 0.0f }, { CZone::REFLECTZONE_WIDTH, 0.0f, CZone::REFLECTZONE_HEIGHT }, CZone::REFLECT);

	//�u���b�N�̐���
	m_pBlockManager = NEW CBlockManager();
	m_pBlockManager->Init();//����������

	//�o���b�g�}�l�[�W���[�̐���
	m_pBulletManager = NEW CBulletManager();
	m_pBulletManager->Init();//����������

	for (int nCnt = 0; nCnt < NUM_CREATE_BULLET; nCnt++)
	{
		//�o���b�g����
		CBullet::Create({ 0.0f,0.0f,0.0f }, 
			{ sinf(0.5f * (nCnt + 1) + D3DX_PI) * 5.0f, 0.0f, cosf(0.5f * (nCnt + 1) + D3DX_PI) * 5.0f },
			(CBullet::BULLETTYPE)(nCnt % 2 + 1));
	}

	//BGM�Đ�
	CManager::GetSound()->Play(CSound::BGM_TITLE);

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CTitle::Uninit()
{
	//BGM�Đ��I��
	CManager::GetSound()->Stop(CSound::BGM_TITLE);

	//�u���b�N�}�l�[�W���[
	if (m_pBlockManager != nullptr)
	{
		m_pBlockManager->Uninit();
		m_pBlockManager = nullptr;
	}

	//�o���b�g�}�l�[�W���[
	if (m_pBulletManager != nullptr)
	{
		m_pBulletManager->Uninit();
		m_pBulletManager = nullptr;
	}

	//�V�[���I������
	CScene::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CTitle::Update()
{
	//Enter�L�[�AA�{�^���AStart�{�^���������ꂽ�ꍇ
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)
		|| CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_START))
	{
		//SE�Đ�
		CManager::GetSound()->Play(CSound::SE_MODE);

		//�`���[�g���A����ʂֈڍs
		CManager::GetFade()->SetFade(MODE_TUTORIAL);
	}

	//�J�����̍X�V����
	CManager::GetCamera()->Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CTitle::Draw()
{
	//�J�����̐ݒ�
	CManager::GetCamera()->SetCamera();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CTitle* CTitle::Create()
{
	//�������𓮓I�m��
	CTitle* pTitle = NEW CTitle();

	//����������
	pTitle->Init();

	return pTitle;
}
