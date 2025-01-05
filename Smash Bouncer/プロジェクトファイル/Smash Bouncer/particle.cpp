//==============================================================================================================================================
//
// �p�[�e�B�N���Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "particle.h"

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CParticle::CParticle() :
	CBillboard{},
	m_MaxSize{},
	m_type{ TYPE::NONE },
	m_nLife{ 30 },
	m_nMaxLife{ m_nLife }
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CParticle::~CParticle()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CParticle::Init()
{
	//�e�N�X�`������
	CTexture* pTex = CManager::GetTexture();//�擾
	int nTexIdx = pTex->Regist("data/TEXTURE/Effect/effect000.jpg");//�o�^
	BindTexture(pTex->GetAddress(nTexIdx));//�ݒ�

	//�ړ��ʐݒ�
	SetMoveValue();

	//�J���[�ݒ�
	SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	//���N���X����������
	if (FAILED(CBillboard::Init())) return E_FAIL;

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CParticle::Uninit()
{
	//���N���X�I������
	CBillboard::Uninit();
}

//===========================================================================================================
// �������
//===========================================================================================================
void CParticle::Release()
{
	//���N���X�������
	CBillboard::Release();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CParticle::Update()
{
	//���W�X�V
	SetPos(GetPos() + GetMove());

	//��������
	m_nLife--;

	//������0
	if (m_nLife <= 0)
	{
		//�I������
		Uninit();
	}

	//�����ɍ��킹�Ĕ�������
	D3DXVECTOR3 size = GetSize();
	size.x = m_MaxSize.x * (static_cast<float>(m_nLife) / static_cast<float>(m_nMaxLife));
	size.y = m_MaxSize.y * (static_cast<float>(m_nLife) / static_cast<float>(m_nMaxLife));
	SetSize(size);

	//���N���X�X�V����
	CBillboard::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CParticle::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�擾�p
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();//�e�N�X�`�����ւ̃|�C���^
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X���
	D3DXVECTOR3 Pos = GetPos();//���W���

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&mtxWorld, nullptr, &mtxView);//�t�s������߂�
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//���W�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���C�g�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�o�b�t�@�������ݖ�����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CProcess::FVF_VERTEX_3D);

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//a�u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���C�g��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�o�b�t�@�������ݗL����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//===========================================================================================================
// �ړ��ʐݒ�
//===========================================================================================================
void CParticle::SetMoveValue()
{
	//�e���W�̈ړ������x�N�g����ݒ�
	float fX = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;
	float fY = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;
	float fZ = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;

	//�ړ��ʐݒ�
	SetMove({ fX, fY, fZ });
}
