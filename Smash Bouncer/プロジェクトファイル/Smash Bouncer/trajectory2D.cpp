//==============================================================================================================================================
//
// 2D�̋O�ՂɊւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "trajectory2D.h"//�O��(2D)

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CTrajectory2D::CTrajectory2D(int nPriority) : CObject2D(nPriority)
{
	//�����o�ϐ�������
	m_nLife = MAX_LIFE;//���C�t
	m_TextureFile = {};//�e�N�X�`���t�@�C���p�X
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CTrajectory2D::~CTrajectory2D()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CTrajectory2D::Init()
{
	//�e�N�X�`������
	CTexture* pTex = CManager::GetTexture();//�擾
	int nTextureIdx = pTex->Regist(m_TextureFile);//�o�^
	BindTexture(pTex->GetAddress(nTextureIdx));//�ݒ�
	SetTextureIdx(nTextureIdx);//ID�ݒ�

	//2D�I�u�W�F�N�g����������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CTrajectory2D::Uninit()
{
	//2D�I�u�W�F�N�g�I������
	CObject2D::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CTrajectory2D::Update()
{
	//���[�J���ϐ��錾
	D3DXVECTOR2 size = GetSize();//�T�C�Y���

	//���C�t����
	m_nLife--;

	//���C�t�ɍ��킹�ăT�C�Y���k�����Ă���
	size *= (float)m_nLife / (float)MAX_LIFE;

	//�X�V���ݒ�
	SetSize(size);//�T�C�Y

	//2D�I�u�W�F�N�g�X�V����
	CObject2D::Update();

	//���C�t��0�̏ꍇ
	if (m_nLife <= 0)
	{
		//�I������
		Uninit();
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CTrajectory2D::Draw()
{
	//�폜�t���O��true�̏ꍇ
	if (GetDeleteFlag())
	{
		//�����𔲂���
		return;
	}

	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//2D�I�u�W�F�N�g�`�揈��
	CObject2D::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================================================================================================
// ��������
//===========================================================================================================
CTrajectory2D* CTrajectory2D::Create(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, const char* TextureFile)
{
	CTrajectory2D* pTrajectory = NEW CTrajectory2D();

	//�p�����[�^�ݒ�
	pTrajectory->SetType(UI);//�I�u�W�F�N�g�^�C�v
	pTrajectory->SetPos(pos);//�ʒu
	pTrajectory->SetSize(size);//�T�C�Y
	pTrajectory->SetColor(col);//�J���[
	pTrajectory->SetTextureFile(TextureFile);//�e�N�X�`���t�@�C��

	//����������
	pTrajectory->Init();

	return pTrajectory;
}
