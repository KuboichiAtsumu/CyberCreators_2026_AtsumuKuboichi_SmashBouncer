//==============================================================================================================================================
//
// �Q�[����ʂɊւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "game.h"//�Q�[���V�[��
#include "fade.h"//�t�F�[�h
#include "edit3D.h"//3D�G�f�B�^
#include "camera.h"//�J����
#include "field.h"//�t�B�[���h
#include "player.h"//�v���C���[
#include "zone.h"//�]�[��
#include "score.h"//�X�R�A���
#include "scorenumber.h"//�X�R�A�\��
#include "stagenumber.h"//�X�e�[�W���\��
#include "gameUI.h"//���o��
#include "blockmanager.h"//�u���b�N�}�l�[�W���[
#include "enemymanager.h"//�G�l�~�[�}�l�[�W���[
#include "itemmanager.h"//�A�C�e���}�l�[�W���[
#include "pointmanager.h"//�|�C���g�}�l�[�W���[
#include "gimmickmanager.h"//�M�~�b�N�}�l�[�W���[
#include "bulletmanager.h"//�o���b�g�}�l�[�W���[

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
CGame::STAGE CGame::m_Stage = STAGE_1;//���݂̃X�e�[�W
CGame::GAMESTATE CGame::m_GameState = STATE_GAME;//�Q�[���̏��
CBlockManager* CGame::m_pBlockManager = nullptr;//�u���b�N�}�l�[�W���[���
CEnemyManager* CGame::m_pEnemyManager = nullptr;//�G�l�~�[�}�l�[�W���[���
CItemManager* CGame::m_pItemManager = nullptr;//�A�C�e���}�l�[�W���[���
CPointManager* CGame::m_pPointManager = nullptr;//�|�C���g�}�l�[�W���[���
CGimmickManager* CGame::m_pGimmickManager = nullptr;//�M�~�b�N�}�l�[�W���[���
CBulletManager* CGame::m_pBulletManager = nullptr;//�o���b�g�}�l�[�W���[���
CScore* CGame::m_pScore = nullptr;//�X�R�A���

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CGame::CGame()
{
	//�����o�ϐ�������
	m_Stage = STAGE_1;//���݂̃X�e�[�W
	m_GameState = STATE_GAME;//�Q�[���̏��
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CGame::~CGame()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CGame::Init()
{
	//���f���E�e�N�X�`�����̓ǂݍ��݂Ɠo�^����
	CXfile::LoadModelFile();//���f���t�@�C���p�X�Ǎ�
	CXfile::LoadTextureFile();//�e�N�X�`���t�@�C���p�X�Ǎ�
	CXfile::Regist();//�o�^����

	//�f�o�b�O���̂�
#ifdef _DEBUG
	//�G�f�B�^�p�I�u�W�F�N�g���Ǎ�
	CEdit3D::LoadInfo(CManager::GAME_STAGE);

	//�w�肵���X�e�[�W�Ƀv���C���[����
	CPlayer::Create({ FIRST_SPAWN + (CZone::STAGEZONE_WIDTH * (float)SPAWN_STAGE), 0.0f, 0.0f });
#else
	//�����ʒu�Ƀv���C���[����
	CPlayer::Create({ FIRST_SPAWN, 0.0f, 0.0f });
#endif // _DEBUG

	//�t�B�[���h��������
	CField::Create({ -450.0f, 0.0f, 0.0f }, { CField::FIELD_WIDTH, 0.0f, CField::FIELD_HEIGHT });

	//�X�e�[�W�e�N�X�`���t�@�C���p�X�Ǎ�����
	CZone::LoadZoneTexFile();

	//�X�e�[�W�敪�]�[������
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		CZone::Create({ 10.0f + CZone::STAGEZONE_WIDTH * (float)nCnt, 0.01f, 0.0f }, { CZone::STAGEZONE_WIDTH, 0.0f, CZone::STAGEZONE_HEIGHT }, CZone::STAGE);
	}

	//���˃]�[������
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		CZone::Create({ FIRST_SPAWN + (CZone::STAGEZONE_WIDTH * (float)nCnt), 0.02f, 0.0f }, { CZone::REFLECTZONE_WIDTH, 0.0f, CZone::REFLECTZONE_HEIGHT }, CZone::REFLECT);
	}

	//�X�R�A��������
	for (int nCnt = 0; nCnt < CScoreNumber::MAX_NUMBER; nCnt++)
	{
		CScoreNumber::Create(nCnt, { 1240.0f, 50.0f }, { 40.0f, 80.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	//���݂̃X�e�[�W����
	for (int nCnt = 0; nCnt < CStageNumber::MAX_NUMBER; nCnt++)
	{
		CStageNumber::Create(nCnt);
	}

	//���o������
	CGameUI::Create(CGameUI::UI_ATTENTION, { CProcess::SCREEN_WIDTH * 0.5f, 650.0f }, { 800.0, 80.0f });//�x��
	CGameUI::Create(CGameUI::UI_STAGE, { 130.0f, 55.0f }, { 250.0, 100.0f });//�x��
	CGameUI::Create(CGameUI::UI_ALLSTAGE, { 400.0f, 55.0f }, { 100.0, 95.0f });//�x��

	//�u���b�N�̐���
	m_pBlockManager = NEW CBlockManager();
	m_pBlockManager->Init();//����������

	//�G�l�~�[�̐���
	m_pEnemyManager = NEW CEnemyManager();
	m_pEnemyManager->Init();//����������

	//�A�C�e���̐���
	m_pItemManager = NEW CItemManager();
	m_pItemManager->Init();//����������

	//�|�C���g�̐���
	m_pPointManager = NEW CPointManager();
	m_pPointManager->Init();//����������

	//�M�~�b�N�̐���
	m_pGimmickManager = NEW CGimmickManager();
	m_pGimmickManager->Init();//����������

	//�o���b�g�̐���
	m_pBulletManager = NEW CBulletManager();
	m_pBulletManager->Init();//����������

	//�X�R�A��񐶐�
	m_pScore = NEW CScore();
	m_pScore->Init();//����������

	//BGM�Đ�
	CManager::GetSound()->Play(CSound::BGM_GAME);

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CGame::Uninit()
{
	//BGM�Đ�
	CManager::GetSound()->Stop(CSound::BGM_GAME);

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

	//�A�C�e���}�l�[�W���[
	if (m_pItemManager != nullptr)
	{
		m_pItemManager->Uninit();
		m_pEnemyManager = nullptr;
	}

	//�|�C���g�}�l�[�W���[
	if (m_pPointManager != nullptr)
	{
		m_pPointManager->Uninit();
		m_pPointManager = nullptr;
	}

	//�M�~�b�N�}�l�[�W���[
	if (m_pGimmickManager != nullptr)
	{
		m_pGimmickManager->Uninit();
		m_pGimmickManager = nullptr;
	}

	//�o���b�g�}�l�[�W���[
	if (m_pBulletManager != nullptr)
	{
		m_pBulletManager->Uninit();
		m_pBulletManager = nullptr;
	}

	//�X�R�A
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	//�J�����̈ʒu�������Z�b�g
	CManager::GetCamera()->Reset();

	//�f�o�b�O���̂�
#ifdef _DEBUG
	//�S�G�f�B�^�I�u�W�F�N�g�̏I������
	CEdit3D::UninitAll();
#endif // _DEBUG

	//�V�[���̏I������
	CScene::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CGame::Update()
{
	//�V�[���X�V����
	CScene::Update();

	//�f�o�b�O�̂�
#ifdef _DEBUG
	//�Q�[�����[�h�̏ꍇ
	if(!CManager::GetScene()->GetEditMode())
	{
		//Enter�L�[�������ꂽ�ꍇ
		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN)
			|| CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)
			|| CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_START))
		{
			//���U���g��ʂֈڍs
			CManager::GetFade()->SetFade(MODE_RESULT);
		}
	}
#endif // DEBUG

	//�G�l�~�[��S�ē|�����ꍇ
	if (CObject3D::GetAllEachStageID(CGame::GetNumStage(), CObject::ENEMY) <= 0)
	{
		//�Q�[���̏�Ԃ��ړ����ɂ���
		CGame::SetGameState(CGame::STATE_MOVE);
	}

	//�G�̑�����0�ɂȂ����ꍇ
	if (CEnemy::GetAllENemy() <= 0)
	{
		//���U���g��ʂֈڍs
		CManager::GetFade()->SetFade(MODE_RESULT);
	}
	
	//�J�����̍X�V����
	CManager::GetCamera()->Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CGame::Draw()
{
	//�J�����̐ݒ�
	CManager::GetCamera()->SetCamera();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CGame* CGame::Create()
{
	//�������𓮓I�m��
	CGame* pGame = NEW CGame();

	//����������
	pGame->Init();

	return pGame;
}

//===========================================================================================================
// �Q�[���̏�Ԑݒ菈��
//===========================================================================================================
void CGame::SetGameState(GAMESTATE state)
{
	//�Q�[���̏�Ԃ��w�肳�ꂽ��Ԃɐݒ�
	m_GameState = state;

	//�ݒ肳�ꂽ��Ԃ��ړ���Ԃ̏ꍇ
	if (m_GameState == STATE_MOVE)
	{
		//�w�肵�����ԂɃI�u�W�F�N�g�����擾����
		for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
		{
			//�擪
			CObject* pObj = CObject::GetTop(nCnt);

			//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
			while (pObj != nullptr)
			{
				//���̃I�u�W�F�N�g�����擾
				CObject* pNext = pObj->GetNext();

				//�I�u�W�F�N�g�^�C�v�̎擾
				CObject::TYPE type = pObj->GetType();

				//�I�u�W�F�N�g�^�C�v���]�[���̏ꍇ
				if (type == CObject::ZONE)
				{
					//�I�u�W�F�N�g�����]�[�����ɕϊ�
					CZone* pZone = (CZone*)pObj;

					//�]�[���^�C�v�����˃]�[���̏ꍇ
					//���݂̃X�e�[�W�ƃ]�[����ID����v����ꍇ
					if (pZone->GetZoneType() == CZone::REFLECT && pZone->GetID() == GetNumStage())
					{
						//�����蔻��𖳌�������
						pZone->SetCollisionFlag(false);
					}
				}

				//�I�u�W�F�N�g�������̏��ɕύX����
				pObj = pNext;
			}
		}
	}
}
