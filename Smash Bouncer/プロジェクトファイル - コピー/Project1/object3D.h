#pragma once
//==============================================================================================================================================
//
// 3D�I�u�W�F�N�g�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _OBJECT3D_H_ //���̃}�N����`������Ȃ�������
#define _OBJECT3D_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "object.h"//�I�u�W�F�N�g
#include "game.h"//�Q�[���V�[��

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CObject3D : public CObject
{
public:
	//======================================
	// �֐�
	//======================================
	CObject3D(int nPriority = 3);//�R���X�g���N�^
	~CObject3D() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Release() override;//�������
	void Update() override;//�X�V����
	void UpdateAnim();//�e�N�X�`���A�j���[�V��������
	void Draw() override;//�`�揈��
	void DecreaseLife() { m_nLife--; }//���C�t��������

	//�p�����[�^�̐ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }//�ʒu
	void SetOldPos(D3DXVECTOR3 oldpos) { m_oldpos = oldpos; }//�ߋ��̈ʒu
	void SetMove(D3DXVECTOR3 move) { m_move = move; }//�ړ���
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }//����
	void SetSize(D3DXVECTOR3 size) { m_size = size; }//�T�C�Y
	void SetColor(D3DXCOLOR col) { m_col = col; }//�J���[
	void SetLife(int nLife) { m_nLife = nLife; }//���C�t
	void SetDelayAnim(int nDelayAnim) { m_nDelayAnim = nDelayAnim; }//�A�j���[�V�����x��
	void SetDivisionTex(int nWidth, int nHeight)//�e�N�X�`��������
	{
		m_nDivisionWidth = nWidth;//���̕�����
		m_nDivisionHeight = nHeight;//�c�̕�����
	}
	void SetPostStageID();//����������X�e�[�W��ID

	//�p�����[�^�擾
	D3DXVECTOR3 GetPos() { return m_pos; }//�ʒu
	D3DXVECTOR3 GetOldPos() { return m_oldpos; }//�ߋ��̈ʒu
	D3DXVECTOR3 GetMove() { return m_move; }//�ړ���
	D3DXVECTOR3 GetRot() { return m_rot; }//����
	D3DXVECTOR3 GetSize() { return m_size; }//�T�C�Y
	D3DXMATRIX GetMatrix() { return m_mtxWorld; }//���[���h�}�g���b�N�X
	D3DXCOLOR GetColor() { return m_col; }//�J���[
	int GetLife() { return m_nLife; }//���C�t
	int GetPostStageID() { return m_nPostStageID; }//����������X�e�[�W��ID
	int GetEachStageID() { return m_nEachStageID; }//�e�X�e�[�W���Ƃ̊e�I�u�W�F�N�g��ID
	int GetDivisionWidth() { return m_nDivisionWidth; }//���̃e�N�X�`��������
	int GetDivisionHeight() { return m_nDivisionHeight; }//�c�̃e�N�X�`��������
	int GetPatternAnimWidth() { return m_nPatternAnimWidth; }//���̃A�j���[�V�����p�^�[��
	int GetPatternAnimHeight() { return m_nPatternAnimHeight; }//�c�̃A�j���[�V�����p�^�[��
	static int GetAllEachStageID(int nStage, CObject::TYPE type) { return m_nAllEachStageID[nStage][type]; }//�e�X�e�[�W�̊e�I�u�W�F�N�g�^�C�v���v��

private:
	//======================================
	// �ϐ�
	//======================================
	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_oldpos;//�ߋ��̈ʒu
	D3DXVECTOR3 m_move;//�ړ���
	D3DXVECTOR3 m_rot;//����
	D3DXVECTOR3 m_size;//�T�C�Y
	D3DXCOLOR m_col;//�J���[
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	static int m_nAllEachStageID[CGame::MAX_STAGE][MAX_OBJECT_TYPE];//�e�X�e�[�W�̊e�I�u�W�F�N�g�^�C�v���Ƃ̍��v��
	int m_nLife;//����&�̗�
	int m_nPostStageID;//����������X�e�[�W��ID
	int m_nEachStageID;//�e�X�e�[�W���Ƃ̊e�I�u�W�F�N�gID
	int m_nDivisionWidth;//���̃e�N�X�`��������
	int m_nDivisionHeight;//���̃e�N�X�`��������
	int m_nDelayAnim;//�A�j���[�V�����x��
	int m_nPatternAnimWidth;//���̃A�j���[�V�����p�^�[��
	int m_nPatternAnimHeight;//�c�̃A�j���[�V�����p�^�[��
	int m_nCounterAnim;//�A�j���[�V�����J�E���^
};

#endif