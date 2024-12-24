//==============================================================================================================================================
//
// �A�C�e���Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CItem : public CObjectX
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//�^�C�v
	typedef enum
	{
		HEART,//�n�[�g
		BONUS,//�{�[�i�X
		MAX
	}ITEMTYPE;

	//======================================
	// �֐�
	//======================================
	CItem(int nPriority = 3);//�R���X�g���N�^
	~CItem() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);//��������
	virtual bool Collision(D3DXVECTOR3 pos, D3DXVECTOR3 size, int& nLife);//�����蔻��
	CItem* GetPrevItem() { return m_pPrev; }//�O�̃I�u�W�F�N�g���̎擾
	CItem* GetNextItem() { return m_pNext; }//���̃I�u�W�F�N�g���̎擾
	void SetPrevItem(CItem* pItem) { m_pPrev = pItem; }//�O�̃I�u�W�F�N�g����ݒ�
	void SetNextItem(CItem* pItem) { m_pNext = pItem; }//���̃I�u�W�F�N�g����ݒ�

private:
	//======================================
	// �֐�
	//======================================
	void SetItemType(ITEMTYPE type) { m_ItemType = type; }//�^�C�v�ݒ�
	
	//======================================
	// �ϐ�
	//======================================
	ITEMTYPE m_ItemType;//���
	static constexpr float TURN = 0.02f;//��]���x
	CItem* m_pPrev;//�O�̃I�u�W�F�N�g�̃|�C���^
	CItem* m_pNext;//���̃I�u�W�F�N�g�̃|�C���^
};

#endif

