//==============================================================================================================================================
//
// �T�E���h�����Ɋւ���w�b�_�[�t�@�C��
// Author : Yuudai Takaya
//
//==============================================================================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "main.h"//���C���w�b�_�[

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CSound
{
public:
	//======================================
	// �T�E���h�ꗗ
	//======================================
	typedef enum
	{
		BGM_TITLE = 0,//�^�C�g��BGM
		BGM_TUTORIAL,//�`���[�g���A��BGM
		BGM_GAME,//�Q�[��BGM
		BGM_RESULT,//���U���gBGM
		SE_MODE,//��ʑJ�ڌ��ʉ�
		SE_SMASH,//���ˌ��ʉ�
		SE_WARP,//���[�v���ʉ�
		SE_SWITCH,//�X�C�b�`���ʉ�
		SE_BONUS,//�{�[�i�X���ʉ�
		SE_HIT,//�q�b�g���ʉ�
		SE_BOUND,//���ˌ��ʉ�
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//======================================
	// �T�E���h���̍\���̒�`
	//======================================
	typedef struct
	{
		const char* pFilename;// �t�@�C����
		int nCntLoop;// ���[�v�J�E���g
		float Volume;// ����
	}SOUNDINFO;

	//======================================
	// �T�E���h�̏��
	//======================================
	CSound::SOUNDINFO m_aSoundInfo[CSound::SOUND_LABEL_MAX] =
	{
		"data/SOUND/BGM/Title000.wav", 1, 1.0f,//�^�C�g��BGM
		"data/SOUND/BGM/Tutorial000.wav", 1, 1.0f,//�`���[�g���A��BGM
		"data/SOUND/BGM/Game000.wav", 1, 1.0f,//�Q�[��BGM
		"data/SOUND/BGM/Result000.wav", 1, 1.0f,//���U���gBGM
		"data/SOUND/SE/ChangeMode000.wav", 0, 1.0f,//��ʑJ�ڌ��ʉ�
		"data/SOUND/SE/Smash000.wav", 0, 2.0f,//���ˌ��ʉ�
		"data/SOUND/SE/Warp000.wav", 0, 1.0f,//���[�v���ʉ�
		"data/SOUND/SE/Switch000.wav", 0, 1.0f,//�X�C�b�`���ʉ�
		"data/SOUND/SE/Bonus000.wav", 0, 1.0f,//�{�[�i�X�l�����ʉ�
		"data/SOUND/SE/Hit000.wav", 0, 1.0f,//�q�b�g���ʉ�
		"data/SOUND/SE/Bound000.wav", 0, 0.7f,//���ˌ��ʉ�
	};

	//======================================
	// �֐�
	//======================================
	HRESULT Init(HWND hWnd);//����������
	void Uninit();//�I������
	HRESULT Play(SOUND_LABEL label);//�Đ�����
	void Stop(SOUND_LABEL label);//��~����(�I��)
	void Stop();//�S��~����

private:
	//======================================
	// �֐�
	//======================================
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//======================================
	// �ϐ�
	//======================================
	IXAudio2* m_pXAudio2 = nullptr;// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = nullptr;// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
