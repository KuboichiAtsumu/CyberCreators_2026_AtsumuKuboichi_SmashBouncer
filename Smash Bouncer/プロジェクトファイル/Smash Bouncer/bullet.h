#pragma once
//==============================================================================================================================================
//
// �o���b�g�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"//X�t�@�C���I�u�W�F�N�g

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CBullet : public CObjectX
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//�e�̃^�C�v
	typedef enum
	{
		NONE = 0,
		PLAYER,//�v���C���[
		CLONE,//�N���[��
		BOUND_ENEMY,//�G�l�~�[(����)
		LAUNCH_ENEMY,//�G�l�~�[(�ł��グ)
		BOUND_INVINCIBLE,//���G(����)
		LAUNCH_INVINCIBLE,//���G(�ł��グ)
		MAX
	}BULLETTYPE;

	//======================================
	// �֐�
	//======================================
	CBullet(int nPriority = 3);//�R���X�g���N�^
	~CBullet() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE m_type);//��������
	virtual bool Collision(D3DXVECTOR3 pos);//�����蔻��

	//���ݒ菈��
	void SetBulletType(BULLETTYPE BulletType);//�o���b�g�^�C�v
	void SetPrevBullet(CBullet* pBullet) { m_pPrev = pBullet; }//�O�̃I�u�W�F�N�g���
	void SetNextBullet(CBullet* pBullet) { m_pNext = pBullet; }//���̃I�u�W�F�N�g���

	//���擾����
	CBullet* GetPrevBullet() { return m_pPrev; }//�O�̃I�u�W�F�N�g���
	CBullet* GetNextBullet() { return m_pNext; }//���̃I�u�W�F�N�g���
	BULLETTYPE GetBulletType() { return m_BulletType; }//�o���b�g�^�C�v
	D3DXVECTOR3 GetDistance() { return m_Distance; }//�ΏۃI�u�W�F�N�g�Ƃ̊e���W����
	float GetLength() { return m_fLength; }//�ΏۃI�u�W�F�N�g�Ƃ̑Ίp����

private:
	//======================================
	// �ϐ�
	//======================================
	CBullet* m_pPrev;//�O�̃I�u�W�F�N�g�̃|�C���^
	CBullet* m_pNext;//���̃I�u�W�F�N�g�̃|�C���^
	BULLETTYPE m_BulletType;//�^�C�v
	D3DXVECTOR3 m_Distance;//�ΏۃI�u�W�F�N�g�Ƃ̊e���W����
	float m_fLength;//�ΏۃI�u�W�F�N�g�Ƃ̑Ίp����
};

#endif
