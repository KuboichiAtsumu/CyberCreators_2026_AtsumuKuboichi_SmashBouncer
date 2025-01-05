#pragma once
//==============================================================================================================================================
//
// �����u���b�N�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _COLLAPSEBLOCK_H_ //���̃}�N����`������Ȃ�������
#define _COLLAPSEBLOCK_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "BLOCK.h"//�u���b�N�w�b�_�[

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CCollapseBlock : public CBlock
{
public:
	//======================================
	// �֐�
	//======================================
	CCollapseBlock(int nPriority = 3);//�R���X�g���N�^
	~CCollapseBlock() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	void Collision(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& size) override;//�����蔻��
	virtual bool Reflection(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& move, D3DXVECTOR3& rot, D3DXVECTOR3& size) override;//���ˏ���

private:
	//======================================
	// �֐�
	//======================================
	void Hit();//�q�b�g����

	//======================================
	// �ϐ�
	//======================================

	static constexpr int MAX_LIFE = 3;//�ő僉�C�t
	int m_nLife;//���C�t

	//�̗͂��Ƃ̃e�N�X�`��
	static constexpr const char* COLLAPSE_TEXTURE[MAX_LIFE] = 
	{
		"data/TEXTURE/CollapseBlock000.png",
		"data/TEXTURE/CollapseBlock001.png",
		"data/TEXTURE/CollapseBlock002.png"
	};
};

#endif
