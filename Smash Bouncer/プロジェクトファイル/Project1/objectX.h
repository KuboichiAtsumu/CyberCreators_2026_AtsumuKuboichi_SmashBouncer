//==============================================================================================================================================
//
// 3D�I�u�W�F�N�g�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _OBJECTX_H_ //���̃}�N����`������Ȃ�������
#define _OBJECTX_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "object3D.h"//3D�I�u�W�F�N�g
#include "xfile.h"//X�t�@�C���Ǘ�

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CObjectX : public CObject3D
{
public:
	//======================================
	// �֐�
	//======================================
	CObjectX(int nPriority = 3);//�R���X�g���N�^
	~CObjectX() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Release() override;//�������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	void BindModel(CXfile::CModel* aModelInfo) { m_aModelInfo = *aModelInfo; }//���f�����蓖��
	void SetModelIdx(int nIdx) { m_nModelIdx = nIdx; }//���f��ID�擾
	CXfile::CModel GetModelInfo() { return m_aModelInfo; }//���f�����擾

	//�p�����[�^�ݒ�
	void SetSize();//�T�C�Y
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }//�g�嗦
	void SetUpdateSize(D3DXVECTOR3 size) { m_Size = size; }//�X�V���ꂽ�T�C�Y����ݒ�

	//�p�����[�^�擾
	D3DXVECTOR3 GetSize() { return m_Size; }//�T�C�Y
	D3DXVECTOR3 GetScale() { return m_Scale; }//�g�嗦

	//======================================
	// �ϐ�
	//======================================
	static int m_nNumType[CXfile::MAX_CATEGORY];//�e�J�e�S���[�̃^�C�v��

private:
	//======================================
	// �ϐ�
	//======================================
	int m_nModelIdx;//���f����ID
	D3DXVECTOR3 m_vtxMin;//�ŏ����_���W
	D3DXVECTOR3 m_vtxMax;//�ő咸�_���W
	D3DXVECTOR3 m_Size;//�T�C�Y
	D3DXVECTOR3 m_Scale;//�g�嗦
	CXfile::CModel m_aModelInfo;//�e���f�����
};

#endif