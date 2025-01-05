//===========================================================================================================================================================================================
//
// Joypad���͏����Ɋւ���w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//===========================================================================================================================================================================================
#ifndef _JOYPAD_H_  //���̃}�N����`������Ȃ�������
#define _JOYPAD_H_  //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "input.h"

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CInputJoypad : public CInput
{
public:
	//======================================
	// �񋓌^��`
	//======================================
	
	//�L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,//��
		JOYKEY_DOWN,//��
		JOYKEY_LEFT,//��
		JOYKEY_RIGHT,//��
		JOYKEY_START,//START
		JOYKEY_BACK,//BACK
		JOYKEY_L3,//���X�e�B�b�N������
		JOYKEY_R3,//�E�X�e�B�b�N������
		JOYKEY_LB,//LB
		JOYKEY_RB,//RB
		JOYKEY_LT,//LT
		JOYKEY_RT,//RT
		JOYKEY_A,//A
		JOYKEY_B,//B
		JOYKEY_X,//X
		JOYKEY_Y,//Y
		JOYKEY_MAX
	}JOYKEY;

	//�X�e�B�b�N�̔ԍ�
	typedef enum
	{
		STICKTYPE_LEFT = 0,//���X�e�B�b�N
		STICKTYPE_RIGHT,//�E�X�e�B�b�N
		STICKTYPE_MAX
	}STICKTYPE;

	//�X�e�B�b�N�̕���
	typedef enum
	{
		STICKANGLE_UP = 0,//��
		STICKANGLE_DOWN,//��
		STICKANGLE_LEFT,//��
		STICKANGLE_RIGHT,//�E
		STICKANGLE_MAX,
	}STICKANGLE;

	//======================================
	// �\����
	//======================================

	//�X�e�B�b�N�̓��͏��
	typedef struct
	{
		float afTplDiameter[STICKTYPE_MAX];//�X�e�B�b�N�̓|���
		float afAngle[STICKTYPE_MAX];//�X�e�B�b�N�̊p�x
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];//�X�e�B�b�N�̕����v���X���
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];//�X�e�B�b�N�̕����g���K�[���
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];//�X�e�B�b�N�̕������s�[�g���
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];//�X�e�B�b�N�̕��������[�X���
	}STICKINPUT;

	//======================================
	// �֐�
	//======================================
	CInputJoypad();//�R���X�g���N�^
	~CInputJoypad();//�f�X�g���N�^
	HRESULT Init();//����������
	void Uninit();//�I������
	void Update();//�X�V����
	bool GetPress(JOYKEY key);//�v���X���擾
	bool GetTrigger(JOYKEY key);//�g���K�[���擾
	bool GetRepeat(JOYKEY key);//���s�[�g���擾
	STICKINPUT GetStick();//�X�e�B�b�N�̏����擾
	float FindAngleL(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);//L�X�e�B�b�N��2�_�̊p�x�����߂�֐�
	float FindAngleR(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);//R�X�e�B�b�N��2�_�̊p�x�����߂�֐�
	float GetAngleL() { return m_fLStickAngle; }//L�X�e�B�b�N�̊p�x���擾
	float GetAngleR() { return m_fRStickAngle; }//R�X�e�B�b�N�̊p�x���擾

private:
	//======================================
	// �֐�
	//======================================
	XINPUT_STATE* GetXInputState();//�R���g���[���[�̓��͏��̎擾
	void UpdateStick();//�X�e�B�b�N�̍X�V����
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

	//======================================
	// �ϐ�
	//======================================
	const int SPEED_REPEAT = 5;//���s�[�g�Ԋu
	const int DEADZONE = 1;//�f�b�h�]�[��
	static int m_nCntKey;//���������Ԍv��
	XINPUT_STATE m_JoyKeyState;//�v���X���
	XINPUT_STATE m_JoyKeyStateTrigger;//�g���K�[���
	XINPUT_STATE m_JoyKeyStateRepeat;//���s�[�g���
	XINPUT_STATE m_aJoypadCurrentTime;//�R���g���[���[�̌��݂̓��͎���
	XINPUT_STATE m_aJoypadExecLastTime;//�R���g���[���[�̍Ō��true��Ԃ�������
	D3DXVECTOR3 m_JoyStickPos;//�X�e�B�b�N�̌X��
	DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX];//�X�e�B�b�N�̌��݂̓��͎���
	DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX];//�X�e�B�b�N�̍Ō��true��Ԃ�������
	STICKINPUT m_Stick;//�X�e�B�b�N�̓��͏��
	XINPUT_STATE m_XInput;//�R���g���[���[�̏��
	float m_fLStickAngle;//L�X�e�B�b�N�p�x
	float m_fRStickAngle;//R�X�e�B�b�N�p�x
	bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX];//�e�X�e�B�b�N�p�x�̓��̓t���O
};

#endif
