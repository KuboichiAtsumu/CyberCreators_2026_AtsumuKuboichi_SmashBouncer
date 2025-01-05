//==============================================================================================================================================
//
// �v���C���[�o���b�g�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "playerbullet.h"//�v���C���[�o���b�g�w�b�_�[
#include "blockmanager.h"//�u���b�N�}�l�[�W���[�w�b�_�[
#include "enemymanager.h"//�G�l�~�[�}�l�[�W���[�w�b�_�[
#include "itemmanager.h"//�A�C�e���}�l�[�W���[�w�b�_�[
#include "gimmickmanager.h"//�M�~�b�N�}�l�[�W���[�w�b�_�[
#include "score.h"//�X�R�A�w�b�_�[
#include "tutorial.h"//�`���[�g���A���V�[��
#include "addscore.h"//���Z�X�R�A�\��
#include "title.h"//�^�C�g���V�[��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CPlayerBullet::CPlayerBullet(int nPriority) : CBullet(nPriority)
{
	//�����o�ϐ�������
	m_fScoreMag = 1.0f;//�X�R�A�{��
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CPlayerBullet::~CPlayerBullet()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CPlayerBullet::Init()
{
	//�o���b�g����������
	if (FAILED(CBullet::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CPlayerBullet::Uninit()
{
	//�o���b�g�I������
	CBullet::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CPlayerBullet::Update()
{
	//�o���b�g�̍X�V����
	CBullet::Update();

	//���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();//�ʒu���
	D3DXVECTOR3 oldpos = GetOldPos();//�ߋ��̈ʒu���
	D3DXVECTOR3 rot = GetRot();//�������
	D3DXVECTOR3 move = GetMove();//�ړ��ʏ��
	D3DXVECTOR3 size = GetSize();//�T�C�Y���
	int nLife = GetLife();//���C�t���
	CBlockManager* pBlockManager = nullptr;//�u���b�N�}�l�[�W���[
	CEnemyManager* pEnemyManager = nullptr;//�G�l�~�[�}�l�[�W���[
	CItemManager* pItemManager = nullptr;//�A�C�e���}�l�[�W���[
	CGimmickManager* pGimmickManager = nullptr;//�M�~�b�N�}�l�[�W���[

	//�V�[���ɉ����ă}�l�[�W���[�����擾
	switch (CManager::GetScene()->GetMode())
	{
		//�^�C�g��
	case CScene::MODE_TITLE:
		pBlockManager = CTitle::GetBlockManager();
		break;

		//�`���[�g���A��
	case CScene::MODE_TUTORIAL:
		pBlockManager = CTutorial::GetBlockManager();
		pEnemyManager = CTutorial::GetEnemyManager();
		break;

		//�Q�[��
	case CScene::MODE_GAME:
		pBlockManager = CGame::GetBlockManager();
		pEnemyManager = CGame::GetEnemyManager();
		pItemManager = CGame::GetItemManager();
		pGimmickManager = CGame::GetGimmickManager();
		break;

	default:
		break;
	}

	//�u���b�N���ˏ���
	if (pBlockManager != nullptr && pBlockManager->Reflection(pos, oldpos, move, rot, size))
	{
		//�X�R�A�{���𑝉�
		m_fScoreMag += 0.1f;
	}
	
	//�G�l�~�[�̓����蔻��
	if (pEnemyManager != nullptr && pEnemyManager->Collision(pos, size))
	{
		//�X�R�A�����Z
		if (CGame::GetScore() != nullptr)
		{
			CGame::GetScore()->AddScore((int)(100.0f * m_fScoreMag));
		}

		//���݂̈ʒu����ۑ�
		D3DXVECTOR3 CreatePos = GetPos();

		//�����ʒu�̍����𒲐�
		CreatePos.y += 40.0f;

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			//���Z�X�R�A��\��
			CAddScore::Create(nCnt, CreatePos, { 10.0f, 20.0f, 0.0f }, (int)(100.0f * m_fScoreMag));
		}

		//�I������
		Uninit();
	}

	//�A�C�e���}�l�[�W���[�̏�񂪑��݂���ꍇ
	if (pItemManager != nullptr)
	{
		//�A�C�e���̓����蔻��
		pItemManager->Collision(pos, size, nLife);
	}

	//�M�~�b�N�}�l�[�W���[�̏�񂪑��݂���ꍇ
	if (pGimmickManager != nullptr)
	{
		//�M�~�b�N�Ƃ̓����蔻��
		pGimmickManager->Collision(pos, move, size, rot);
	}

	//�X�V���ꂽ����ݒ�
	SetPos(pos);//�ʒu
	SetRot(rot);//����
	SetMove(move);//�ړ���
	SetLife(nLife);//���C�t
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CPlayerBullet::Draw()
{
	//�o���b�g�`�揈��
	CBullet::Draw();
}
