//==============================================================================================================================================
//
// ���C�������Ɋւ���w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _MAIN_H_ //���̃}�N����`������Ȃ�������
#define _MAIN_H_ //2�d�C���N���[�h�h�~�̃}�N����`
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�}�N��

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include <Windows.h>
#include "d3dx9.h" //�`�揈���p
#include "dinput.h" //���͏����p
#include "xaudio2.h" //�T�E���h�����p
#include "Xinput.h" //�W���C�p�b�h�����p
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <time.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define FIND_MEM_LEAKS
#endif // _DEBUG

#ifdef FIND_MEM_LEAKS
#define NEW new (_NORMAL_BLOCK , __FILE__, __LINE__)
#else
#define NEW new
#endif // FIND_MEM_LEAKS

//===========================================================================================================
// ���C�u�����̃����N
//===========================================================================================================
#pragma comment(lib,"d3d9.lib") //�`�揈���p
#pragma comment(lib,"d3dx9.lib") //[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib") //DirectX�R���|�l�[�g(���i)�g�p
#pragma comment(lib,"winmm.lib") //�V�X�e�������擾�p
#pragma comment(lib,"dinput8.lib") //���͏����p
#pragma comment(lib,"xinput.lib") //�W���C�p�b�h�����p

//===========================================================================================================
// �N���X
//===========================================================================================================
class CProcess
{
public:
	//======================================
	// �֐�
	//======================================
	CProcess();//�R���X�g���N�^
	~CProcess();//�f�X�g���N�^
	static void ToggleFullscreen(HWND hWnd);//�t���X�N���[������

	//======================================
	// �ϐ�
	//======================================
	const char* WINDOW_NAME = "Bound Smash";//�E�B���h�E�l�[��
	static constexpr const char* CLASS_NAME = "WindowClass";//�E�C���h�E�N���X�̖��O
	static constexpr int FVF_VERTEX_2D = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	static constexpr int FVF_VERTEX_3D = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	static constexpr int MAX_TEXT = 256;//�e�L�X�g������
	static constexpr int MAX_VER = 4;//���_��
	static constexpr int MAX_FRAME = 60;//�t���[����
	static constexpr int SCREEN_WIDTH = 1280;//�E�C���h�E�̕�
	static constexpr int SCREEN_HEIGHT = 720;//�E�C���h�E�̍���

private:
	//======================================
	// �ϐ�
	//======================================
	static RECT m_windowRect;//�E�B���h�E�؂�ւ��p�ϐ�
	static bool m_isFullscreen;//�E�B���h�E�؂�ւ��p�t���O
};

//===========================================================================================================
// �\����
//===========================================================================================================

//=======================================================
// ���_���(2D)
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

//=======================================================
// ���_���(3D)
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 nor;//�@���x�N�g��
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_3D;

//===========================================================================================================
// �v���g�^�C�v�錾
//===========================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//�E�C���h�E�v���V�[�W��

#endif
