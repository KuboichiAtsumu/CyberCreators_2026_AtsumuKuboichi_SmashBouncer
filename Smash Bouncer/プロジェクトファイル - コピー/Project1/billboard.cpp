//==============================================================================================================================================
//
// �r���{�[�h�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "billboard.h"//�r���{�[�h
#include "explosion.h"//����
#include "addscore.h"//���Z�X�R�A�\��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CBillboard::CBillboard(int nPriority) : CObject3D(nPriority)
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CBillboard::~CBillboard()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CBillboard::Init()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 size = GetSize();//�T�C�Y���

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * CProcess::MAX_VER,
		D3DUSAGE_WRITEONLY,
		CProcess::FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	//���_�o�b�t�@�̐ݒ�
	SetVtxBuff(pVtxBuff);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x * 0.5f, size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size.x * 0.5f, size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x * 0.5f, -size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size.x * 0.5f, -size.y * 0.5f, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / (float)GetDivisionWidth(), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / (float)GetDivisionHeight());
	pVtx[3].tex = D3DXVECTOR2(1.0f / (float)GetDivisionWidth(), 1.0f / (float)GetDivisionHeight());

	for (int nCnt = 0; nCnt < CProcess::MAX_VER; nCnt++)
	{
		//�@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		
		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = GetColor();
	}

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	//�I�u�W�F�N�g�̏���������
	if (FAILED(CObject::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CBillboard::Uninit()
{
	//3D�I�u�W�F�N�g�I������
	CObject3D::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CBillboard::Update()
{
	//���[�J���ϐ��錾
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 size = GetSize();//�T�C�Y���

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x * 0.5f, size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size.x * 0.5f, size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x * 0.5f, -size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size.x * 0.5f, -size.y * 0.5f, 0.0f);

	for (int nCntVer = 0; nCntVer < CProcess::MAX_VER; nCntVer++)
	{
		//���_�J���[�̐ݒ�
		pVtx[nCntVer].col = GetColor();
	}

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CBillboard::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�擾�p
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();//�e�N�X�`�����ւ̃|�C���^
	D3DXMATRIX mtxWorld = GetMatrix();//���[���h�}�g���b�N�X���
	D3DXVECTOR3 Pos = GetPos();//�ʒu���

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&mtxWorld, nullptr, &mtxView);//�t�s������߂�
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CProcess::FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===========================================================================================================
// ��������
//===========================================================================================================
CBillboard* CBillboard::Create(BILLBOARD_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�^�C�v�ɉ����ă������𓮓I�m��
	CBillboard* pBillboard = nullptr;
	switch (type)
	{
		//����
	case BILLBOARD_EXPLOSION:
		pBillboard = NEW CExplosion(3);
		break;

		//���Z�X�R�A�\��
	case BILLBOARD_SCORE:
		pBillboard = NEW CAddScore(3);
		break;

	default:
		break;
	}

	//�p�����[�^�ݒ�
	pBillboard->SetType(BILLBOARD);//�I�u�W�F�N�g�^�C�v
	pBillboard->SetPos(pos);//�ʒu
	pBillboard->SetSize(size);//�T�C�Y

	//����������
	pBillboard->Init();
	
	return pBillboard;
}
