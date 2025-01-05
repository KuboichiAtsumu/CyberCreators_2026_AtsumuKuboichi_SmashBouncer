//==============================================================================================================================================
//
// �G�l�~�[�̏����Ɋւ���w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"//X�t�@�C���I�u�W�F�N�g

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CEnemy : public CObjectX
{
public:
	//======================================
	// �֐�
	//======================================
	CEnemy(int nPriority = 3);//�R���X�g���N�^
	~CEnemy() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Release() override;//�������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);//��������
	virtual bool Collision(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�����蔻��
	virtual void Hit();//�q�b�g����
	virtual void Move();//�ړ�����
	CEnemy* GetPrevEnemy() { return m_pPrev; }//�O�̃I�u�W�F�N�g���擾����
	CEnemy* GetNextEnemy() { return m_pNext; }//���̃I�u�W�F�N�g���擾����
	static int GetAllENemy() { return m_nAllEnemy; }//�G�̑����擾����
	int GetInterval() {	return m_nIntervalShot; }//���ˎ��Ԏ擾����
	int GetCntShot() { return m_nCntShot; }//�e���˃J�E���g�擾����
	void SetPrevEnemy(CEnemy* pEnemy) { m_pPrev = pEnemy; }//�O�̃I�u�W�F�N�g���ݒ菈��
	void SetNextEnemy(CEnemy* pEnemy) { m_pNext = pEnemy; }//���̃I�u�W�F�N�g���ݒ菈��
	void SetInterval() { m_nIntervalShot = rand() % DIFFERENCE_INTERVAL + MIN_INTERVAL; }//���ˎ��Ԑݒ菈��
	void SetCntShot(int nCnt) { m_nCntShot = nCnt; }//�e���˃J�E���g��ݒ菈��

private:
	//======================================
	// �񋓌^��`
	//======================================

	//�G�l�~�[�^�C�v
	typedef enum
	{
		GREEN_SLIME,//�X���C��(�ΐF)
		BLUE_SLIME,//�X���C��(�F)
		WHITE_GHOST,//���΂�(���F)
		BLACK_GHOST,//���΂�(���F)
		RED_BAT,//�R�E����(�ԐF)
		PURPLE_BAT,//�R�E����(���F)
		MID_BOSS,//���{�X
		BOSS,//�{�X
		MAX_ENEMY_TYPE
	}ENEMYTYPE;

	//�G�l�~�[�̏��
	typedef enum
	{
		ENEMY_STATE_NORMAL,//�ʏ�
		ENEMY_STATE_DAMAGE,//�_���[�W
		ENEMY_STATE_MAX
	}ENEMY_STATE;

	//�e�G�l�~�[�^�C�v�̃��C�t
	static constexpr int ENEMY_LIFE[MAX_ENEMY_TYPE] =
	{
		5,
		5,
		5,
		5,
		5,
		5,
		15,
		30,
	};

	//======================================
	// �֐�
	//======================================
	void SetEnemyType(ENEMYTYPE type) { m_EnemyType = type; }//�^�C�v�ݒ�

	//======================================
	// �ϐ�
	//======================================
	static constexpr int MIN_INTERVAL = 2;//���ˎ��ԍŒZ����
	static constexpr int DIFFERENCE_INTERVAL = 3;//���ˎ��Ԃ͈̔�
	static constexpr float TURN_SPEED = 0.05f;//��]���x
	static constexpr float BULLET_SPEED = 4.0f;//�e�̔��ˑ��x�{��
	static constexpr float MOVE_SPEED = 0.5f;//�ړ����x
	static constexpr float MOVE_WIDTH = 20.0f;//�ړ���
	CEnemy* m_pPrev;//�O�̃I�u�W�F�N�g�̃|�C���^
	CEnemy* m_pNext;//���̃I�u�W�F�N�g�̃|�C���^
	ENEMYTYPE m_EnemyType;//�^�C�v
	ENEMY_STATE m_State;//���
	D3DXVECTOR3 m_FirstPos;//�����ʒu
	static int m_nAllEnemy;//�G�̑���
	int m_nIntervalShot;//�e�̔��ˊԊu
	int m_nCntShot;//�e���˂܂ł̃J�E���g
	int m_nCntState;//��ԃJ�E���g
};

#endif
