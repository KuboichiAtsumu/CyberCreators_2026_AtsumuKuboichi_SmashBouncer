//==============================================================================================================================================
//
// �Q�[���}�l�[�W���[
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "manager.h"//�}�l�[�W���[
#include "keyboard.h"//�L�[�{�[�h
#include "mouse.h"//�}�E�X
#include "joypad.h"//�W���C�p�b�h
#include "camera.h"//�J����
#include "light.h"//���C�g
#include "fade.h"//�t�F�[�h

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
CRenderer* CManager::m_pRenderer = nullptr;//�����_��
CInputKeyboard* CManager::m_pKeyboard = nullptr;//�L�[�{�[�h
CInputMouse* CManager::m_pMouse = nullptr;//�}�E�X
CInputJoypad* CManager::m_pJoypad = nullptr;//Pad
CSound* CManager::m_pSound = nullptr;//�T�E���h
CCamera* CManager::m_pCamera = nullptr;//�J����
CLight* CManager::m_pLight = nullptr;//���C�g
CScene* CManager::m_pScene = nullptr;//�V�[��
CFade* CManager::m_pFade = nullptr;//�t�F�[�h
CTexture* CManager::m_pTexture = nullptr;//�e�N�X�`��
CXfile* CManager::m_pModel = nullptr;//���f��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CManager::CManager()
{
	srand((unsigned)time(nullptr));
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CManager::~CManager()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐���
	m_pRenderer = NEW CRenderer();
	m_pRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h�̏�����
	m_pKeyboard = NEW CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd);

	//�}�E�X�̏�����
	m_pMouse = NEW CInputMouse();
	m_pMouse->Init(hInstance, hWnd);

	//�W���C�p�b�h�̏�����
	m_pJoypad = NEW CInputJoypad();
	m_pJoypad->Init();

	//�T�E���h�̏�����
	m_pSound = NEW CSound();
	m_pSound->Init(hWnd);

	//�J�����̏�����
	m_pCamera = NEW CCamera();
	m_pCamera->Init();

	//���C�g�̏�����
	m_pLight = NEW CLight();
	m_pLight->Init();

	//�e�N�X�`���̏�����
	m_pTexture = NEW CTexture();

	//���f���̏�����
	m_pModel = NEW CXfile();

	//�t�F�[�h��ʐ���
	m_pFade = CFade::Create();

	//���[�h�̏�����
	SetMode(CScene::MODE_TITLE);

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CManager::Uninit()
{
	//�T�E���h�S��~
	GetSound()->Stop();

	//�t�F�[�h
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	//�V�[��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//�����_���[
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�L�[�{�[�h
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//�}�E�X
	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	//Pad
	if (m_pJoypad != nullptr)
	{
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	//�T�E���h
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//�J����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//���C�g
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//�e�N�X�`��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//���f��
	if (m_pModel != nullptr)
	{
		m_pModel->Unload();
		delete m_pModel;
		m_pModel = nullptr;
	}
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CManager::Update()
{
	//�L�[�{�[�h�X�V����
	m_pKeyboard->Update();

	//�}�E�X�X�V����
	m_pMouse->Update();

	//�W���C�p�b�h�X�V����
	m_pJoypad->Update();

	//�V�[���X�V����
	m_pScene->Update();

	//�����_���[�X�V����
	m_pRenderer->Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CManager::Draw()
{
	//�����_���[�`�揈��
	m_pRenderer->Draw();
}

//===========================================================================================================
// ���[�h�̐ݒ�
//===========================================================================================================
void CManager::SetMode(CScene::MODE mode)
{
	//�V�[����񂪑��݂���ꍇ
	if (m_pScene != nullptr)
	{
		//�I������
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = nullptr;
	}

	//�V���ȃV�[���𐶐�
	m_pScene = CScene::Create(mode);
}
