//==============================================================================================================================================
//
// Joypad���͏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "joypad.h"//�W���C�p�b�h

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
int CInputJoypad::m_nCntKey = 0;//����������

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CInputJoypad::CInputJoypad() : m_JoyKeyState(), m_JoyKeyStateTrigger(), m_JoyKeyStateRepeat()
{
	//�����o�ϐ�������
	m_Stick = {};//�X�e�B�b�N�̓��͏��
	m_XInput = {};//�R���g���[���[�̏��
	m_aJoypadCurrentTime = {};//�R���g���[���[�̌��݂̓��͎���
	m_aJoypadExecLastTime = {};//�R���g���[���[�̍Ō��true��Ԃ�������
	m_fLStickAngle = 0.0f;//L�X�e�B�b�N�p�x
	m_fRStickAngle = 0.0f;//R�X�e�B�b�N�p�x

	for (int nCntStickType = 0; nCntStickType < STICKTYPE_MAX; nCntStickType++)
	{
		for (int nCntStickAngle = 0; nCntStickAngle < STICKANGLE_MAX; nCntStickAngle++)
		{
			m_aStickCurrentTime[nCntStickType][nCntStickAngle] = {};//�X�e�B�b�N�̌��݂̓��͎���
			m_aStickExecLastTime[nCntStickType][nCntStickAngle] = {};//�X�e�B�b�N�̍Ō��true��Ԃ�������
			m_bAngle[nCntStickType][nCntStickAngle] = false;//�e�X�e�B�b�N�p�x�̓��̓t���O
		}
	}
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CInputJoypad::~CInputJoypad()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CInputJoypad::Init()
{
	//�������̃N���A
	memset(&m_JoyKeyState, 0, sizeof(XINPUT_STATE));

	//�������̃N���A
	memset(&m_JoyKeyState, 0, sizeof(XINPUT_VIBRATION));

	//XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CInputJoypad::Uninit()
{
	//����������
	m_nCntKey = 0;

	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CInputJoypad::Update()
{
	XINPUT_STATE joykeyState; //�W���C�p�b�h�̓��͏��

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_JoyKeyState.Gamepad.wButtons;
		m_JoyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;//�g���K�[����
		joykeyState.Gamepad.wButtons |= GetJoypadStick(m_JoyKeyState.Gamepad.sThumbLX, m_JoyKeyState.Gamepad.sThumbLY, (SHORT)DEADZONE);

		// ���݂̎��Ԃ��擾����
		m_aJoypadCurrentTime.Gamepad.wButtons = (WORD)timeGetTime();

		if (joykeyState.Gamepad.wButtons && ((m_aJoypadCurrentTime.Gamepad.wButtons - m_aJoypadExecLastTime.Gamepad.wButtons) > SPEED_REPEAT))
		{
			// �Ō��true��Ԃ������Ԃ�ۑ�
			m_aJoypadExecLastTime.Gamepad.wButtons = m_aJoypadCurrentTime.Gamepad.wButtons;

			// �R���g���[���[�̃��s�[�g����ۑ�
			m_JoyKeyStateRepeat = joykeyState;
		}
		else
		{
			// �R���g���[���[�̃��s�[�g����ۑ�
			m_JoyKeyStateRepeat.Gamepad.wButtons = 0;
		}

		m_JoyKeyState = joykeyState;// �v���X����
	}

	//�X�e�B�b�N�̍X�V����
	UpdateStick();
}

//===========================================================================================================
// �X�e�B�b�N�X�V����
//===========================================================================================================
void CInputJoypad::UpdateStick()
{
	float fX = 0.0f, fY = 0.0f; //�X�e�B�b�N��X���AY��

	//�R���g���[���[�̏�Ԃ��擾
	if (XInputGetState(0, &m_XInput) == ERROR_SUCCESS)
	{
		for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
		{
			switch (nCntStick)
			{
				//L�X�e�B�b�N
			case STICKTYPE_LEFT:
				fX = (GetXInputState()->Gamepad.sThumbLX);
				fY = (GetXInputState()->Gamepad.sThumbLY);

				//�p�x���擾
				m_Stick.afAngle[nCntStick] = FindAngleL(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;
				break;

				//R�X�e�B�b�N
			case STICKTYPE_RIGHT:
				fX = (GetXInputState()->Gamepad.sThumbRX);
				fY = (GetXInputState()->Gamepad.sThumbRY);

				//�p�x���擾
				m_Stick.afAngle[nCntStick] = FindAngleR(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;
				break;
			}

			//�X�e�B�b�N�̓|������擾
			m_Stick.afTplDiameter[nCntStick] = fabsf(fX);

			if (m_Stick.afTplDiameter[nCntStick] < fabsf(fY))
			{
				m_Stick.afTplDiameter[nCntStick] = fabsf(fY);
			}

			m_Stick.afTplDiameter[nCntStick] /= 32768.0f; //�|���Ă����Ԃ̏����l

			//�������̓t���O��������
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				m_bAngle[nCntStick][nCntAngle] = false;
			}

			if (m_Stick.afTplDiameter[nCntStick] > 0.1f)
			{
				//�p�x����
				if (m_Stick.afAngle[nCntStick] < -D3DX_PI)
				{
					m_Stick.afAngle[nCntStick] = D3DX_PI - (D3DX_PI + m_Stick.afAngle[nCntStick]) * -1.0f;
				}

				//�p�x���l�����ŏ�Ɉʒu���鎞�A��t���O��true�ɂ���
				if ((m_Stick.afAngle[nCntStick] < D3DX_PI * -0.625f) || (m_Stick.afAngle[nCntStick] > D3DX_PI * 0.625f))
				{
					m_bAngle[nCntStick][STICKANGLE_UP] = true;
				}

				//�p�x���l�����ŉ��Ɉʒu���鎞�A���t���O��true�ɂ���
				if ((m_Stick.afAngle[nCntStick] > D3DX_PI * -0.375f) && (m_Stick.afAngle[nCntStick] < D3DX_PI * 0.375f))
				{
					m_bAngle[nCntStick][STICKANGLE_DOWN] = true;
				}

				//�p�x���l�����ŉE�Ɉʒu���鎞�A�E�t���O��true�ɂ���
				if ((m_Stick.afAngle[nCntStick] > D3DX_PI * 0.125f) && (m_Stick.afAngle[nCntStick] < D3DX_PI * 0.875f))
				{
					m_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
				}

				//�p�x���l�����ō��Ɉʒu���鎞�A���t���O��true�ɂ���
				if ((m_Stick.afAngle[nCntStick] > D3DX_PI * -0.875f) && (m_Stick.afAngle[nCntStick] < D3DX_PI * -0.125f))
				{
					m_bAngle[nCntStick][STICKANGLE_LEFT] = true;
				}
			}

			//�p�x�ɉ��������͏���
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				//�X�e�B�b�N�̃g���K�[����ۑ�
				m_Stick.abAngleTrigger[nCntStick][nCntAngle] = (m_Stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & m_bAngle[nCntStick][nCntAngle];

				//�X�e�B�b�N�̃����[�X����ۑ�
				m_Stick.abAngleRelease[nCntStick][nCntAngle] = (m_Stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & m_bAngle[nCntStick][nCntAngle];

				//���݂̎��Ԃ��擾
				m_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();

				if (m_bAngle[nCntStick][nCntAngle] && ((m_aStickCurrentTime[nCntStick][nCntAngle] - m_aStickExecLastTime[nCntStick][nCntAngle]) > (unsigned)SPEED_REPEAT))
				{
					//�Ō��true��Ԃ������Ԃ�ۑ�
					m_aStickExecLastTime[nCntStick][nCntAngle] = m_aStickCurrentTime[nCntStick][nCntAngle];

					//�X�e�B�b�N�̃��s�[�g����ۑ�
					m_Stick.abAngleRepeat[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
				}
				else
				{
					//�X�e�B�b�N�̃��s�[�g����ۑ�
					m_Stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
				}

				//�X�e�B�b�N�̃v���X����ۑ�
				m_Stick.abAnglePress[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
			}
		}
	}
}

//===========================================================================================================
// L�X�e�B�b�N��2�_�̊p�x�����߂�
//===========================================================================================================
float CInputJoypad::FindAngleL(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	//�p�x
	m_fLStickAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	m_fLStickAngle -= (D3DX_PI * 0.5f);
	m_fLStickAngle *= -1.0f;

	return m_fLStickAngle;
}

//===========================================================================================================
// R�X�e�B�b�N��2�_�̊p�x�����߂�
//===========================================================================================================
float CInputJoypad::FindAngleR(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	//�p�x
	m_fRStickAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	m_fRStickAngle -= (D3DX_PI * 0.5f);
	m_fRStickAngle *= -1.0f;

	return m_fRStickAngle;
}

//===========================================================================================================
// �v���X���擾
//===========================================================================================================
bool CInputJoypad::GetPress(JOYKEY key)
{
	return (m_JoyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//===========================================================================================================
// �g���K�[���擾
//===========================================================================================================
bool CInputJoypad::GetTrigger(JOYKEY key)
{
	return (m_JoyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//===========================================================================================================
// ���s�[�g���擾
//===========================================================================================================
bool CInputJoypad::GetRepeat(JOYKEY key)
{
	//�L�[�������Ă����
	if (GetPress(key))
	{
		if (GetTrigger(key))
		{
			m_nCntKey = 0;
			return true;
		}

		m_nCntKey++; //�����Ă���Ԃ��J�E���g

		if (m_nCntKey >= SPEED_REPEAT) //�����������
		{
			m_nCntKey = 0;
			return true;
		}
	}

	return false;
}

//===========================================================================================================
// �R���g���[���[�̓��͏��擾
//===========================================================================================================
XINPUT_STATE* CInputJoypad::GetXInputState()
{
	return &m_XInput;
}

//===========================================================================================================
// �X�e�B�b�N���擾
//===========================================================================================================
CInputJoypad::STICKINPUT CInputJoypad::GetStick()
{
	return m_Stick;
}

//===========================================================================================================
// �X�e�B�b�N���擾
//===========================================================================================================
WORD CInputJoypad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}
