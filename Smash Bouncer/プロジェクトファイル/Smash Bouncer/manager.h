//==============================================================================================================================================
//
// �}�l�[�W���[�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _MANAGER_H_ //���̃}�N����`������Ȃ�������
#define _MANAGER_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "main.h"//���C��
#include "texture.h"//�e�N�X�`���ꊇ�Ǘ�
#include "xfile.h"//���f���ꊇ�Ǘ�
#include "keyboard.h"//�L�[�{�[�h
#include "joypad.h"//�W���C�p�b�h
#include "mouse.h"//�}�E�X
#include "scene.h"//�V�[��
#include "debugproc.h"//�f�o�b�O�\��
#include "renderer.h"//�����_���[
#include "sound.h"//�T�E���h

//===========================================================================================================
// �O���錾
//===========================================================================================================
class CCamera;//�J�����N���X
class CLight;//���C�g�N���X
class CFade;//�t�F�[�h�N���X

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CManager
{
public:
	//======================================
	// �֐�
	//======================================
	CManager();//�R���X�g���N�^
	~CManager();//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//����������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	static void SetMode(CScene::MODE mode);//���[�h�̐ݒ�

	//���̎擾
	static CRenderer* GetRenderer() { return m_pRenderer; }//�����_���[
	static CInputKeyboard* GetKeyboard() { return m_pKeyboard; }//�L�[�{�[�h
	static CInputJoypad* GetJoypad() { return m_pJoypad; }//�W���C�p�b�h
	static CInputMouse* GetMouse() { return m_pMouse; }//�}�E�X
	static CSound* GetSound() { return m_pSound; }//�T�E���h
	static CCamera* GetCamera() { return m_pCamera; }//�J����
	static CLight* GetLight() { return m_pLight; }//���C�g
	static CFade* GetFade() { return m_pFade; }//�t�F�[�h
	static CScene* GetScene() { return m_pScene; }//�V�[��
	static CTexture* GetTexture() { return m_pTexture; }//�e�N�X�`���ꊇ���
	static CXfile* GetModel() { return m_pModel; }//���f���ꊇ���

	//======================================
	// �ϐ�
	//======================================
	static constexpr const char* GAME_STAGE = "data\\STAGE\\Stage.bin";//�Q�[���X�e�[�W���
	static constexpr const char* TUTORIAL_STAGE = "data\\STAGE\\TutorialStage.bin";//�`���[�g���A���X�e�[�W���

private:
	//======================================
	// �ϐ�
	//======================================
	static CRenderer* m_pRenderer;//�����_���[���
	static CInputKeyboard* m_pKeyboard;//�L�[�{�[�h���
	static CInputJoypad* m_pJoypad;//Pad���
	static CInputMouse* m_pMouse;//Pad���
	static CSound* m_pSound;//�T�E���h
	static CCamera* m_pCamera;//�J�������
	static CLight* m_pLight;//���C�g���
	static CScene* m_pScene;//���݂̉��
	static CFade* m_pFade;//�t�F�[�h
	static CTexture* m_pTexture;//�e�N�X�`���ꊇ���
	static CXfile* m_pModel;//���f���ꊇ���
};

#endif