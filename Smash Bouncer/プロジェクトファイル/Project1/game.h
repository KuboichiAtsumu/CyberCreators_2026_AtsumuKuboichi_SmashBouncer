//==============================================================================================================================================
//
// �Q�[����ʂɊւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _GAME_H_ //���̃}�N����`������Ȃ�������
#define _GAME_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "manager.h"//�}�l�[�W���[

//===========================================================================================================
// �O���錾
//===========================================================================================================
class CBlockManager;//�u���b�N�}�l�[�W���[
class CEnemyManager;//�G�l�~�[�}�l�[�W���[
class CItemManager;//�A�C�e���}�l�[�W���[
class CPointManager;//�|�C���g�}�l�[�W���[
class CGimmickManager;//�M�~�b�N�}�l�[�W���[
class CBulletManager;//�o���b�g�}�l�[�W���[
class CScore;//�X�R�A���

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CGame : public CScene
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//�Q�[���̏��
	typedef enum
	{
		STATE_GAME,//�Q�[����
		STATE_MOVE,//�X�e�[�W�ړ���
		MAX_STATE
	}GAMESTATE;

	//�X�e�[�W
	typedef enum
	{
		STAGE_1,//�X�e�[�W1
		STAGE_2,//�X�e�[�W2
		STAGE_3,//�X�e�[�W3
		STAGE_4,//�X�e�[�W4
		STAGE_5,//�X�e�[�W5
		STAGE_6,//�X�e�[�W6
		STAGE_7,//�X�e�[�W7
		STAGE_8,//�X�e�[�W8
		STAGE_9,//�X�e�[�W9
		STAGE_10,//�X�e�[�W10
		MAX_STAGE
	}STAGE;

	//======================================
	// �֐�
	//======================================
	CGame();//�R���X�g���N�^
	~CGame() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGame* Create();//��������

	//���̎擾
	static CBlockManager* GetBlockManager() { return m_pBlockManager; }//�u���b�N�}�l�[�W���[���
	static CEnemyManager* GetEnemyManager() { return m_pEnemyManager; }//�G�l�~�[�}�l�[�W���[���
	static CItemManager* GetItemManager() { return m_pItemManager; }//�A�C�e���}�l�[�W���[���
	static CPointManager* GetPointManager() { return m_pPointManager; }//�|�C���g�}�l�[�W���[���
	static CGimmickManager* GetGimmickManager() { return m_pGimmickManager; }//�M�~�b�N�}�l�[�W���[���
	static CBulletManager* GetBulletManager() { return m_pBulletManager; }//�o���b�g�}�l�[�W���[���
	static CScore* GetScore() { return m_pScore; }//�X�R�A���
	static STAGE GetNumStage() { return m_Stage; }//���݂̃X�e�[�W
	static GAMESTATE GetGameState() { return m_GameState; }//�Q�[���̏��

	//���̐ݒ�
	static void SetNumStage(int m_nStage) { m_Stage = (STAGE)m_nStage; }//���݂̃X�e�[�W
	static void SetGameState(GAMESTATE state);//�Q�[���̏��

private:
	//======================================
	// �ϐ�
	//======================================
#ifdef _DEBUG
	static constexpr int SPAWN_STAGE = STAGE_1;//�X�|�[������X�e�[�W
#endif // _DEBUG
	static constexpr float FIRST_SPAWN = -160.0f;//�����X�|�[���ʒu
	static CBlockManager* m_pBlockManager;//�u���b�N�}�l�[�W���[���
	static CEnemyManager* m_pEnemyManager;//�G�l�~�[�}�l�[�W���[���
	static CItemManager* m_pItemManager;//�A�C�e���}�l�[�W���[���
	static CPointManager* m_pPointManager;//�|�C���g�}�l�[�W���[���
	static CGimmickManager* m_pGimmickManager;//�M�~�b�N�}�l�[�W���[���
	static CBulletManager* m_pBulletManager;//�o���b�g�}�l�[�W���[���
	static CScore* m_pScore;//�X�R�A���
	static STAGE m_Stage;//���݂̃X�e�[�W
	static GAMESTATE m_GameState;//�Q�[���̏��
};

#endif
