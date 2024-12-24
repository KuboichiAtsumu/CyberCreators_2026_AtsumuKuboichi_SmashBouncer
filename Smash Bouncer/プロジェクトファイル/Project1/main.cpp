//==============================================================================================================================================
//
// �X�N���[���Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "main.h"//���C��
#include "manager.h"//�}�l�[�W���[

//===========================================================================================================
// �萔
//===========================================================================================================
RECT CProcess::m_windowRect = {};//�E�B���h�E�؂�ւ��p�ϐ�
bool CProcess::m_isFullscreen = false;//�E�B���h�E�؂�ւ��p�t���O

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CProcess::CProcess()
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CProcess::~CProcess()
{
}

//===========================================================================================================
// ���C���֐�
//===========================================================================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hInstancePrev*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CProcess process;
	CManager manager;
	int nCountFPS = 0;//FPS�J�E���^

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,//�E�C���h�E�̃X�^�C��
		WindowProc,//�E�C���h�E�v���V�[�W��
		0,//0�ɂ���
		0,//0�ɂ���
		hInstance,//�C���X�^���X�n���h��
		LoadIcon(nullptr,IDI_ASTERISK),//�^�X�N�o�[�̃A�C�R��
		LoadCursor(nullptr,IDC_CROSS),//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_ACTIVECAPTION),//�N���C�A���g�̈�̔w�i�F
		nullptr,//���j���[�o�[
		process.CLASS_NAME,//�E�C���h�E�N���X�̖��O
		LoadIcon(nullptr,IDI_APPLICATION)//�t�@�C���̃A�C�R��
	};

	HWND hWnd;//�E�C���h�E�n���h��(���ʎq)
	MSG msg;//���b�Z�[�W���i�[����ϐ�
	RECT rect = { 0,0,process.SCREEN_WIDTH,process.SCREEN_HEIGHT };
	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime;//�Ō�ɏ�����������
	DWORD dwFrameCount;//�t���[���J�E���g
	DWORD dwFPSLastTime;//�Ō��FPS���v����������

	RegisterClassEx(&wcex);//�E�C���h�E�N���X�̓o�^

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);//�N���C�A���g�̈���w��̃T�C�Y�ɒ���

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,//�g���E�C���h�E�X�^�C��
		process.CLASS_NAME,//�E�C���h�E�N���X�̖��O
		process.WINDOW_NAME,//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,//�E�C���h�E����X���W
		CW_USEDEFAULT,//�E�C���h�E����Y���W
		(rect.right - rect.left),//�E�C���h�E�̕�
		(rect.bottom - rect.top),//�E�C���h�E�̍���
		nullptr,//�e�E�C���h�E�̃n���h��
		nullptr,//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,//�C���X�^���X�n���h��
		nullptr);//�E�C���h�E�̍쐬�f�[�^

	//����������
	if (FAILED(manager.Init(hInstance, hWnd, TRUE)))
	{
		return -1;//���������������s�����ꍇ
	}

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);//�E�C���h�E�̕\����Ԃ̐ݒ�
	UpdateWindow(hWnd);//�N���C�A���g�̈���X�V

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;//����������
	dwExecLastTime = timeGetTime();//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();
	unsigned int FPS_TIME_SPACE = 500;

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{
			//windows�̏���
			if (msg.message == WM_QUIT) //�I��
			{
				break;//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);//�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{
			//DirectX�̏���
			dwCurrentTime = timeGetTime(); //���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= FPS_TIME_SPACE) //0.5�b�o��
			{
				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);//FPS���v��
				dwFPSLastTime = dwCurrentTime;//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / process.MAX_FRAME))
			{
				//���Ԍo��
				dwExecLastTime = dwCurrentTime;//���ݎ�����ۑ�

				//�X�V����
				manager.Update();

				//�`�揈��
				manager.Draw();

				dwFrameCount++;//�t���[���J�E���g�����Z
			}
		}
	}

	//�}�l�[�W���[�������
	manager.Uninit();

	UnregisterClass(process.CLASS_NAME, wcex.hInstance);//�E�C���h�E�N���X�̓o�^������

	return(int)msg.wParam;
}

//===========================================================================================================
// �E�C���h�E�v���V�[�W��
//===========================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID; //�Ԃ�l�i�[�p

	switch (uMsg)
	{
	case WM_DESTROY://�E�C���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);//WM_QUIT���b�Z�[�W�𑗂�
		break;

	case WM_KEYDOWN://�L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE://[ESC]�L�[����

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNOCANCEL | MB_ICONQUESTION);//�I�����b�Z�[�W

			if (nID == IDYES)//�͂�
			{
				DestroyWindow(hWnd);//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				break;
			}
			break;
		case VK_F11:
			CProcess::ToggleFullscreen(hWnd);
			break;

		}
		break;

	case WM_CLOSE: //����{�^���̃��b�Z�[�W

		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNOCANCEL | MB_ICONQUESTION);	//�I�����b�Z�[�W

		if (nID == IDYES) //�͂�
		{
			DestroyWindow(hWnd);//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
		}
		else
		{
			return 0; //0��Ԃ��Ȃ��ƏI��
		}
		break;

	case WM_LBUTTONDOWN:	//�}�E�X���N���b�N�̃��b�Z�[�W
		SetFocus(hWnd);	//�E�C���h�E�Ƀt�H�[�J�X�����킹��
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//===========================================================================================================
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//===========================================================================================================
void CProcess::ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (m_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, m_windowRect.left, m_windowRect.top,
			m_windowRect.right - m_windowRect.left, m_windowRect.bottom - m_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &m_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	m_isFullscreen = !m_isFullscreen;
}

