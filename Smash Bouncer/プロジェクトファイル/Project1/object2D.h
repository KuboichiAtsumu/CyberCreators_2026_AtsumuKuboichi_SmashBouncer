#pragma once
//==============================================================================================================================================
//
// 2D�I�u�W�F�N�g�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _OBJECT2D_H_ //���̃}�N����`������Ȃ�������
#define _OBJECT2D_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "object.h"//�I�u�W�F�N�g

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CObject2D : public CObject
{
public:
	//======================================
	// �֐�
	//======================================
	CObject2D(int nPriority = 3);//�R���X�g���N�^
	~CObject2D() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Release() override;//�������
	void Update() override;//�X�V����
	void UpdateAnim();//�A�j���[�V��������
	void Draw() override;//�`�揈��

	//�p�����[�^�ݒ�
	void SetPos(D3DXVECTOR2 pos) { m_pos = pos; }//�ʒu
	void SetSize(D3DXVECTOR2 size) { m_size = size; }//�T�C�Y
	void SetMove(D3DXVECTOR2 move) { m_move = move; }//�ړ���
	void SetColor(D3DXCOLOR col) { m_col = col; }//�J���[

	//�p�����[�^���擾
	D3DXVECTOR2 GetPos() { return m_pos; }//�ʒu
	D3DXVECTOR2 GetSize() { return m_size; }//�T�C�Y
	D3DXVECTOR2 GetMove() { return m_move; }//�ړ���
	D3DXCOLOR GetColor() { return m_col; }//�J���[

private:
	//======================================
	// �ϐ�
	//======================================
	D3DXVECTOR2 m_pos;//�ʒu
	D3DXVECTOR2 m_size;//�T�C�Y
	D3DXVECTOR2 m_move;//�ړ���
	D3DXVECTOR3 m_rot;//����
	D3DXCOLOR m_col;//�J���[
	int m_nDivisionTex;//�e�N�X�`��������
	int m_nDelayAnim;//�A�j���[�V�����x��
	int m_nPatternAnim;//�A�j���[�V�����p�^�[��
	int m_nCounterAnim;//�A�j���[�V�����J�E���^
	float m_fAngle;//�Ίp���̊p�x
	float m_fLength;//�Ίp���̒���
};

#endif