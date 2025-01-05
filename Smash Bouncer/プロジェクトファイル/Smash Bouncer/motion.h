//==============================================================================================================================================
//
// ���[�V�����Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _MOTION_H_ //���̃}�N����`������Ȃ�������
#define _MOTION_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"//X�t�@�C���I�u�W�F�N�g

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CMotionCharacter : public CObjectX
{
public:
	//=============================================================
	// �񋓌^��`
	//=============================================================

	//==========================
	// ���
	//==========================
	typedef enum
	{
		NEUTRAL = 0,//�j���[�g����
		MOVE,//�ړ�
		ACTION,//�A�N�V����
		MAX_STATE
	}MOTION_STATE;

	//==========================
	// ���[�V�����̃^�C�v
	//==========================
	typedef enum
	{
		PLAYER,//�v���C���[
		MAX_TYPE
	}MOTION_TYPE;

	//=============================================================
	// �֐�
	//=============================================================
	CMotionCharacter(int nPriority = 3);//�R���X�g���N�^
	~CMotionCharacter() override;//�f�X�g���N�^
	void Release() override;//�������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	void LoadParts(MOTION_TYPE type);//�p�[�c�t�@�C���Ǎ�����
	void LoadMotion(MOTION_TYPE type);//���[�V�������Ǎ�����

	//���̐ݒ�
	void SetState(MOTION_STATE state) { m_State = state; }//��ԏ��
	void SetPartsFlash(float a);//�p�[�c�̃J���[
	void SetAllPartsSize();//�S�p�[�c�����킹���T�C�Y

	//���̎擾
	MOTION_STATE GetState() { return m_State; }//���݂̏��
	float GetSpeed() { return m_fSpeed; }//���x�̏����擾

	//=============================================================
	// �ÓI�����o�ϐ�
	//=============================================================
	static constexpr float MAX_JUDGE_MOVE = 0.1f;//�ړ���Ԕ���̈ړ��ʔ͈�

private:
	//=============================================================
	// �񋓌^��`
	//=============================================================

	//==========================
	// �p�[�c�̔��g
	//==========================
	typedef enum
	{
		UP_BODY,//�㔼�g
		DOWN_BODY,//�����g
		MAX_HALF
	}HALF_BODY;

	//==========================
	// �^�C�v���Ƃ̏��t�@�C��
	//==========================
	static constexpr const char* PARTS_FILE[MAX_TYPE] =
	{
		"data/MODEL/PLAYER/SetPlayer.txt",
	};

	//=============================================================
	// �֐�
	//=============================================================
	void Motion(MOTION_STATE state, int nParts, int nKeySet);//���[�V��������
	void SetPartsInfo(CXfile::CModel aModelInfo, int nParts);//�p�[�c���f�����ݒ菈��
	
	//=============================================================
	// �ÓI�����o�ϐ�
	//=============================================================
	static constexpr int MAX_PARTS = 20;//�ő�p�[�c��
	static constexpr int MAX_MOTION = 5;//�ő僂�[�V������
	static constexpr int MAX_KEYSET = 10;//�ő�L�[�Z�b�g��
	static constexpr int MAX_MAT = 100;//�ő�}�e���A����
	static constexpr int MAX_TEXT = 256;//�ő�e�L�X�g�Ǎ��o�C�g��

	//=============================================================
	// �\����
	//=============================================================
	
	//==========================
	// �e�L�[�̏��
	//==========================
	typedef struct
	{
		D3DXVECTOR3 pos;//�ʒu
		D3DXVECTOR3 rot;//����
	}Key;

	//==========================
	// �e�L�[�Z�b�g�̏��
	//==========================
	typedef struct
	{
		Key aKey[MAX_PARTS];//�L�[�̏��̍\����
		int nMaxFrame;//�ő�t���[����
	}KeySet;

	//==========================
	// �e���[�V�����̏��
	//==========================
	typedef struct
	{
		KeySet aKeyset[MAX_KEYSET];//�p�[�c�̏��
		MOTION_TYPE type;//���[�V�����̑ΏۃI�u�W�F�N�g�^�C�v
		int nCntKeySet;//�L�[���J�E���^
		int nCntFrame;//�t���[�����J�E���^
		int nMaxKeySet;//�e���[�V�����̍ő�L�[�Z�b�g��
		int nLoop;//�e���[�V���������[�v���邩�ǂ���
	}MotionSet;

	//==========================
	// �e�p�[�c�̏��
	//==========================
	typedef struct
	{
		LPD3DXMESH pMesh;//���b�V���̒��_���ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
		DWORD dwNumMat;//�}�e���A���̐�
		D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
		D3DCOLORVALUE Diffuse[MAX_MAT];//�}�e���A�����
		D3DCOLORVALUE FirstDiffuse[MAX_MAT];//�}�e���A����񏉊��l
		D3DXVECTOR3 pos;//�ʒu
		D3DXVECTOR3 rot;//����
		MOTION_TYPE type;//���[�V�����̑ΏۃI�u�W�F�N�g�^�C�v
		int nIndex;//�ԍ�
		int nParent;//�e�̔ԍ�
		int nHalf;//���g�̔���
		char aPartsFile[MAX_TEXT];//�p�[�c�̃t�@�C����
	}ModelParts;

	//=============================================================
	// �����o�ϐ�
	//=============================================================
	MotionSet m_aMotion[MAX_MOTION];//���[�V�������̍\����
	ModelParts m_aParts[MAX_PARTS];//�e�p�[�c���̍\����
	MOTION_STATE m_State;//���݂̏��
	int m_nParts;//�p�[�c��
	int m_nMotion;//���[�V������
	float m_fSpeed;//���x
};

#endif
