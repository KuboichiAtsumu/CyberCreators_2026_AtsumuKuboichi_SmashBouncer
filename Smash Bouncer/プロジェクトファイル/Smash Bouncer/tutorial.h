//==============================================================================================================================================
//
// �`���[�g���A����ʂɊւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _TUTORIAL_H_ //���̃}�N����`������Ȃ�������
#define _TUTORIAL_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "manager.h"//�}�l�[�W���[

//===========================================================================================================
// �O���錾
//===========================================================================================================
class CBlockManager;//�u���b�N�}�l�[�W���[
class CEnemyManager;//�G�l�~�[�}�l�[�W���[
class CBulletManager;//�o���b�g�}�l�[�W���[

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CTutorial : public CScene
{
public:
	//======================================
	// �֐�
	//======================================
	CTutorial();//�R���X�g���N�^
	~CTutorial() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CTutorial* Create();//��������
	void SetSpawnTime() { m_nSpawnTime = SPAWN_INTERVAL; }//�G�l�~�[�X�|�[���܂ł̎��Ԑݒ菈��
	static CBlockManager* GetBlockManager() { return m_pBlockManager; }//�u���b�N�}�l�[�W���[���
	static CEnemyManager* GetEnemyManager() { return m_pEnemyManager; }//�G�l�~�[�}�l�[�W���[���
	static CBulletManager* GetBulletManager() { return m_pBulletManager; }//�o���b�g�}�l�[�W���[���

private:
	//======================================
	// �ϐ�
	//======================================
	const D3DXVECTOR3 ENEMY_SPAWN_POS = { 120.0f, 0.0f, 0.0f };//�G�l�~�[�̃X�|�[���ʒu
	const D3DXVECTOR3 ENEMY_SPAWN_ROT = { 0.0f, D3DX_PI * 0.5f, 0.0f };//�G�l�~�[�̃X�|�[���p�x
	const int SPAWN_INTERVAL = 30;//�G�l�~�[�X�|�[���܂ł̎���
	static constexpr float FIRST_SPAWN = -160.0f;//�����X�|�[���ʒu
	static CBlockManager* m_pBlockManager;//�u���b�N�}�l�[�W���[���
	static CEnemyManager* m_pEnemyManager;//�G�l�~�[�}�l�[�W���[���
	static CBulletManager* m_pBulletManager;//�o���b�g�}�l�[�W���[���
	int m_nSpawnTime;//�G�l�~�[�X�|�[���܂ł̃J�E���g
};

#endif
