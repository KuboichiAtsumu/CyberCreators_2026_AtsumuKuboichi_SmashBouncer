//==============================================================================================================================================
//
// �M�~�b�N�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#pragma once
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"//X�t�@�C���I�u�W�F�N�g

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CGimmick : public CObjectX
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//���
	typedef enum
	{
		MOVEFLOOR,//�ړ���
		WARPHOLE,//���[�v�z�[��
		SWITCHBASE,//�X�C�b�`�x�[�X
		SWITCH,//�X�C�b�`
		MAX
	}GIMMICKTYPE;

	//======================================
	// �֐�
	//======================================
	CGimmick(int nPriority);//�R���X�g���N�^
	~CGimmick() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGimmick* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);//��������
	virtual bool Collision(D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXVECTOR3 size, D3DXVECTOR3& rot);//�����蔻��
	GIMMICKTYPE GetGimmickType() { return m_GimmickType; }//�M�~�b�N�^�C�v���擾
	CGimmick* GetPrevGimmick() { return m_pPrev; }//�O�̃I�u�W�F�N�g�����擾
	CGimmick* GetNextGimmick() { return m_pNext; }//���̃I�u�W�F�N�g�����擾
	void SetPrevGimmick(CGimmick* pGimmick) { m_pPrev = pGimmick; }//�O�̃I�u�W�F�N�g����ݒ�
	void SetNextGimmick(CGimmick* pGimmick) { m_pNext = pGimmick; }//���̃I�u�W�F�N�g����ݒ�

private:
	//======================================
	// �֐�
	//======================================
	void SetGimmickType(GIMMICKTYPE type) { m_GimmickType = type; }//�M�~�b�N�^�C�v�ݒ�
	
	//======================================
	// �ϐ�
	//======================================
	GIMMICKTYPE m_GimmickType;//���
	CGimmick* m_pPrev;//�O�̃I�u�W�F�N�g�̃|�C���^
	CGimmick* m_pNext;//���̃I�u�W�F�N�g�̃|�C���^
};

#endif
