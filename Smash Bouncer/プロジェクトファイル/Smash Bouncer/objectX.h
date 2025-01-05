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
	void DrawOutLine();//�A�E�g���C���`�揈��
	void BindModel(CXfile::CModel* aModelInfo) { m_aModelInfo = *aModelInfo; }//���f�����蓖��
	void SetModelIdx(int nIdx) { m_nModelIdx = nIdx; }//���f��ID�擾
	CXfile::CModel GetModelInfo() { return m_aModelInfo; }//���f�����擾

	//�T�C�Y
	void SetSize();//�L�����N�^�[�T�C�Y�ݒ�
	void SetUpdateSize(D3DXVECTOR3 size) { m_Size = size; }//�X�V���ꂽ����ݒ�
	D3DXVECTOR3 GetSize() { return m_Size; }//�擾

	//�g�嗦
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }//�ݒ�
	D3DXVECTOR3 GetScale() { return m_Scale; }//�擾

	//�A�E�g���C���`��t���O
	void SetOutLineFlag(bool bDrawOutLine) { m_bDrawOutLine = bDrawOutLine; }//�ݒ�
	bool GetOutLineFlag() { return m_bDrawOutLine; }//�擾

	//======================================
	// �ϐ�
	//======================================
	static int m_nNumType[CXfile::MAX_CATEGORY];//�e�J�e�S���[�̃^�C�v��

private:
	//======================================
	// �萔
	//======================================
	const float OUTLINE_SCALE = 1.3f;//�A�E�g���C���̊g�嗦(����)

	//======================================
	// �ϐ�
	//======================================
	int m_nModelIdx;//���f����ID
	bool m_bDrawOutLine;//�A�E�g���C���`��t���O
	D3DXVECTOR3 m_vtxMin;//�ŏ����_���W
	D3DXVECTOR3 m_vtxMax;//�ő咸�_���W
	D3DXVECTOR3 m_Size;//�T�C�Y
	D3DXVECTOR3 m_Scale;//�g�嗦
	CXfile::CModel m_aModelInfo;//�e���f�����
};

#endif