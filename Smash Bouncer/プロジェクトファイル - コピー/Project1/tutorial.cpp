//==============================================================================================================================================
//
// �`���[�g���A����ʂɊւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "tutorial.h"//�`���[�g���A��
#include "edit3D.h"//3D�G�f�B�^
#include "camera.h"//�J����
#include "fade.h"//�t�F�[�h

//�I�u�W�F�N�g
#include "player.h"//�v���C���[
#include "field.h"//�t�B�[���h
#include "zone.h"//�]�[��

//UI
#include "heading.h"//���o��
#include "operation.h"//������@UI
#include "gamestart.h"//GameStartUI

//�}�l�[�W���[
#include "blockmanager.h"//�u���b�N�}�l�[�W���[
#include "enemymanager.h"//�G�l�~�[�}�l�[�W���[
#include "bulletmanager.h"//�o���b�g�}�l�[�W���[

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
CBlockManager* CTutorial::m_pBlockManager = nullptr;//�u���b�N�}�l�[�W���[���
CEnemyManager* CTutorial::m_pEnemyManager = nullptr;//�G�l�~�[�}�l�[�W���[���
CBulletManager* CTutorial::m_pBulletManager = nullptr;//�o���b�g�}�l�[�W���[���

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CTutorial::CTutorial()
{
	//�����o�ϐ�������
	m_nSpawnTime = 0;//�G�l�~�[�X�|�[���܂ł̃J�E���g
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CTutorial::~CTutorial()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CTutorial::Init()
{
	//���f���E�e�N�X�`�����̓ǂݍ��݂Ɠo�^����
	CXfile::LoadModelFile();//���f���t�@�C���p�X�Ǎ�
	CXfile::LoadTextureFile();//�e�N�X�`���t�@�C���p�X�Ǎ�
	CXfile::Regist();//�o�^����

	//�f�o�b�O���̂�
#ifdef _DEBUG
	//�G�f�B�^�p�I�u�W�F�N�g���Ǎ�
	CEdit3D::LoadInfo(CManager::TUTORIAL_STAGE);
#endif // _DEBUG

	//�w�肵���X�e�[�W�Ƀv���C���[����
	CPlayer::Create({ FIRST_SPAWN, 0.0f, 0.0f });

	//�t�B�[���h��������
	CField::Create({ -450.0f, 0.0f, 0.0f }, { CField::FIELD_WIDTH, 0.0f, CField::FIELD_HEIGHT });

	//�X�e�[�W�e�N�X�`���t�@�C���p�X�Ǎ�����
	CZone::LoadZoneTexFile();

	//�X�e�[�W�敪�]�[������
	CZone::Create({ 10.0f, 0.01f, 0.0f }, { CZone::STAGEZONE_WIDTH, 0.0f, CZone::STAGEZONE_HEIGHT }, CZone::STAGE);

	//���˃]�[������
	CZone::Create({ FIRST_SPAWN, 0.02f, 0.0f }, { CZone::REFLECTZONE_WIDTH, 0.0f, CZone::REFLECTZONE_HEIGHT }, CZone::REFLECT);

	//UI����
	CHeading::Create();//���o��
	COperation::Create();//������@UI
	CGameStart::Create();//GameStartUI

	//�u���b�N�̐���
	m_pBlockManager = NEW CBlockManager();
	m_pBlockManager->Init();//����������

	//�G�l�~�[�̐���
	m_pEnemyManager = NEW CEnemyManager();
	m_pEnemyManager->Init();//����������

	//�o���b�g�}�l�[�W���[�̐���
	m_pBulletManager = NEW CBulletManager();
	m_pBulletManager->Init();//����������

	//BGM�Đ�
	CManager::GetSound()->Play(CSound::BGM_TUTORIAL);

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CTutorial::Uninit()
{
	//BGM�Đ��I��
	CManager::GetSound()->Stop(CSound::BGM_TUTORIAL);

	//�u���b�N�}�l�[�W���[
	if (m_pBlockManager != nullptr)
	{
		m_pBlockManager->Uninit();
		m_pBlockManager = nullptr;
	}

	//�G�l�~�[�}�l�[�W���[
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Uninit();
		m_pEnemyManager = nullptr;
	}

	//�o���b�g�}�l�[�W���[
	if (m_pBulletManager != nullptr)
	{
		m_pBulletManager->Uninit();
		m_pBulletManager = nullptr;
	}

	//�f�o�b�O���̂�
#ifdef _DEBUG
	//�S�G�f�B�^�I�u�W�F�N�g�̏I������
	CEdit3D::UninitAll();
#endif // _DEBUG

	//�V�[���I������
	CScene::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CTutorial::Update()
{
	//�V�[���X�V����
	CScene::Update();

	//Enter�L�[�������ꂽ�ꍇ
	//START�{�^���������ꂽ�ꍇ
	if ((CManager::GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_START))
		&& !GetEditMode())
	{
		//SE�Đ�
		CManager::GetSound()->Play(CSound::SE_MODE);

		//�Q�[����ʂֈڍs
		CManager::GetFade()->SetFade(MODE_GAME);
	}

	//�G�̑�����0�ɂȂ����ꍇ
	if (CEnemy::GetAllENemy() <= 0)
	{
		//�G�l�~�[�X�|�[���܂ł̃J�E���g��0�̏ꍇ
		if (m_nSpawnTime <= 0)
		{
			//�G���X�|�[��������
			m_pEnemyManager->Regist(CEnemy::Create(ENEMY_SPAWN_POS, ENEMY_SPAWN_ROT, 0));//�G�l�~�[�}�l�[�W���[�ɃG�l�~�[����o�^
			
			//�G�l�~�[�X�|�[���܂ł̃J�E���g��ݒ�
			SetSpawnTime();
		}
		//�G�l�~�[�X�|�[���܂ł̃J�E���g���c���Ă���ꍇ
		else
		{
			//�J�E���g�����炷
			m_nSpawnTime--;
		}
	}

	//�J�����̍X�V����
	CManager::GetCamera()->Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CTutorial::Draw()
{
	//�J�����̐ݒ�
	CManager::GetCamera()->SetCamera();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CTutorial* CTutorial::Create()
{
	CTutorial* pTutorial = NEW CTutorial();

	//����������
	pTutorial->Init();

	return pTutorial;
}
