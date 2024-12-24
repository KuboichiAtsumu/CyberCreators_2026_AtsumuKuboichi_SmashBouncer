//==============================================================================================================================================
//
// 3D�I�u�W�F�N�g�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"//X�t�@�C���I�u�W�F�N�g

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
int CObjectX::m_nNumType[CXfile::MAX_CATEGORY] = {};//�e�J�e�S���[�̃^�C�v��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CObjectX::CObjectX(int nPriority) : CObject3D(nPriority)
{
	//�����o�ϐ�������
	m_aModelInfo = {};//���f�����
	m_nModelIdx = 0;//���f����ID
	m_vtxMin = { 0.0f, 0.0f, 0.0f };//�ŏ����_���W
	m_vtxMax = { 0.0f, 0.0f, 0.0f };//�ő咸�_���W
	m_Size = { 0.0f, 0.0f, 0.0f };//�T�C�Y
	m_Scale = { 1.0f, 1.0f, 1.0f };//�g�嗦
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CObjectX::~CObjectX()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CObjectX::Init()
{
	//�I�u�W�F�N�g����������
	if (FAILED(CObject::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CObjectX::Uninit()
{
	//3D�I�u�W�F�N�g�I������
	CObject3D::Uninit();
}

//===========================================================================================================
// �������
//===========================================================================================================
void CObjectX::Release()
{
	//���f�����폜
	m_aModelInfo = {};

	//3D�I�u�W�F�N�g�������
	CObject3D::Release();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CObjectX::Update()
{
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CObjectX::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���̃f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxWorld = GetMatrix();//���[���h�}�g���b�N�X���
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();//�e�N�X�`�����
	D3DXVECTOR3 Pos = GetPos();//�ʒu���
	D3DXVECTOR3 Rot = GetRot();//�������

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rot.y, Rot.x, Rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//�@���̒�����1�ɂ���B
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_aModelInfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aModelInfo.dwNumMat; nCntMat++)
	{
		//�F�����ݒ�
		pMat->MatD3D.Diffuse = m_aModelInfo.Diffuse[nCntMat];

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTexture);

		//���f���̕`��
		m_aModelInfo.pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================================
// ���f���o�^
//===========================================================================================================
void CObjectX::SetSize()
{
	//���[�J���ϐ��錾
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	int nNumVtx = m_aModelInfo.pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	DWORD sizeFVF = D3DXGetFVFVertexSize(m_aModelInfo.pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_aModelInfo.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nIdxVtx = 0; nIdxVtx < nNumVtx; nIdxVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���f���̍ŏ��l�ƍő�l���擾
		if (vtx.x < m_vtxMin.x)
		{//X���W�̍ŏ��l
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y < m_vtxMin.y)
		{//Y���W�̍ŏ��l
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z < m_vtxMin.z)
		{//Z���W�̍ŏ��l
			m_vtxMin.z = vtx.z;
		}
		if (vtx.x > m_vtxMax.x)
		{//X���W�̍ő�l
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y > m_vtxMax.y)
		{//Y���W�̍ő�l
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z > m_vtxMax.z)
		{//Z���W�̍ő�l
			m_vtxMax.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//��ނ��Ƃ̃T�C�Y�����߂�
	m_Size =
	{
		(m_vtxMax.x - m_vtxMin.x) * m_Scale.x,//x��
		(m_vtxMax.y - m_vtxMin.y) * m_Scale.y,//y��
		(m_vtxMax.z - m_vtxMin.z) * m_Scale.z//z��
	};

	//���_�o�b�t�@�̃A�����b�N
	m_aModelInfo.pMesh->UnlockVertexBuffer();
}
