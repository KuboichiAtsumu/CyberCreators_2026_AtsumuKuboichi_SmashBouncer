#pragma once
//==============================================================================================================================================
//
// �X�R�A�\���Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _SCORENUMBER_H_
#define _SCORENUMBER_H_

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "score.h"//�X�R�A

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CScoreNumber : public CScore
{
public:
	//======================================
	// �֐�
	//======================================
	CScoreNumber(int nPriority = 97);//�R���X�g���N�^
	~CScoreNumber() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Release() override;//�������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CScoreNumber* Create(int nIdx, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col);//��������
	static void SaveScore(int nScore) { m_nSaveScore = nScore; }//�X�R�A��ۑ�����

	//�p�����[�^�ݒ�
	static int GetDigit() { return m_nDigit; }//����

	//======================================
	// �ϐ�
	//======================================
	static const int MAX_NUMBER = 6;//����

private:
	//======================================
	// �֐�
	//======================================

	//�p�����[�^�ݒ�
	void SetIndex(int nIdx) { m_nIdx = nIdx; }//ID
	void SetPos(D3DXVECTOR2 pos);//�ʒu

	//======================================
	// �ϐ�
	//======================================
	static constexpr const char* TEXTURE_FILE = "data/TEXTURE/number000.png";//�e�N�X�`���t�@�C��
	const float COLOR_ASCENT = 0.02f;//�J���[�㏸���x
	static CScoreNumber* m_apNumber[MAX_NUMBER];//�e���̏��
	static int m_nSaveScore;//�X�R�A�ۑ�
	static int m_nDigit;//����
	int m_nIdx;//ID
	bool m_bUse;//�g�p�t���O
};

#endif
