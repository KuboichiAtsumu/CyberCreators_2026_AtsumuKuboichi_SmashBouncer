//==============================================================================================================================================
//
// �u���b�N�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _BLOCK_H_ //���̃}�N����`������Ȃ�������
#define _BLOCK_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"//X�t�@�C���I�u�W�F�N�g�w�b�_�[

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CBlock : public CObjectX
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//���
	typedef enum
	{
		WALL,//��
		BARRIER,//�o���A
		BOUNDARY,//�X�e�[�W���E
		BATTERY,//�C��
		KEY,//���t���u���b�N
		COLLAPSE,//�����u���b�N
		MAX
	}BLOCKTYPE;

	//======================================
	// �֐�
	//======================================
	CBlock(int nPriority = 3);//�R���X�g���N�^
	~CBlock() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int nType);//��������
	virtual void Collision(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& size);//�����蔻��
	virtual bool Reflection(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& move, D3DXVECTOR3& rot, D3DXVECTOR3& size);//���ˏ���
	D3DXVECTOR3 GetNormal() { return m_Normal; }//�����x�N�g��
	CBlock* GetPrevBlock() { return m_pPrev; }//�O�̃I�u�W�F�N�g���
	CBlock* GetNextBlock() { return m_pNext; }//���̃I�u�W�F�N�g���
	BLOCKTYPE GetBlockType() { return m_BlockType; }//�u���b�N�^�C�v
	void SetPrevBlock(CBlock* pBLOCK) { m_pPrev = pBLOCK; }//�O�̃I�u�W�F�N�g���
	void SetNextBlock(CBlock* pBLOCK) { m_pNext = pBLOCK; }//���̃I�u�W�F�N�g���

private:
	//======================================
	// �֐�
	//======================================
	void SetBlockType(BLOCKTYPE type) { m_BlockType = type; }//�^�C�v�ݒ�
	void SEGMENT(float StartX, float StartZ, float EndX, float EndZ);//�����x�N�g���v�Z����

	//======================================
	// �ϐ�
	//======================================
	D3DXVECTOR3 m_Normal;//�����x�N�g��
	BLOCKTYPE m_BlockType;//���
	CBlock* m_pPrev;//�O�̃I�u�W�F�N�g�̃|�C���^
	CBlock* m_pNext;//���̃I�u�W�F�N�g�̃|�C���^
};

#endif
