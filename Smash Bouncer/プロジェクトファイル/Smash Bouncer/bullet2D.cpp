//==============================================================================================================================================
//
// 2D�o���b�g�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "bullet2D.h"//2D�o���b�g
#include "trajectory2D.h"//�O��(2D)
#include "titleframe.h"//�^�C�g���t���[��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CBullet2D::CBullet2D() : CObject2D()
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CBullet2D::~CBullet2D()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CBullet2D::Init()
{
	//�p�����[�^�ݒ�
	SetSize(BULLET2D_SIZE);//�T�C�Y
	SetColor({ 0.0f,0.0f,1.0f,1.0f });

	//�e�N�X�`������
	CTexture* pTex = CManager::GetTexture();//�擾
	int nTextureIdx = pTex->Regist(TEXTURE_FILE);//�o�^
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
void CBullet2D::Uninit()
{
	//2D�I�u�W�F�N�g�I������
	CObject2D::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CBullet2D::Update()
{
	//�폜�t���O��true�̏ꍇ
	if (GetDeleteFlag())
	{
		//�����𔲂���
		return;
	}

	//���[�J���ϐ��錾
	D3DXVECTOR2 pos = GetPos();//�ʒu���
	D3DXVECTOR2 move = GetMove();//�ړ��ʏ��

	//�ړ��ʂ����Z
	pos += move;

	//X���W���͈͊O�̏ꍇ
	if (pos.x <= CTitleFrame::FRAME_SIZE.x || pos.x >= CProcess::SCREEN_WIDTH - CTitleFrame::FRAME_SIZE.x)
	{
		//X���̈ړ������𔽓]������
		move.x *= -1.0f;
	}

	//Y���W���͈͊O�̏ꍇ
	if (pos.y <= CTitleFrame::FRAME_SIZE.y || pos.y >= CProcess::SCREEN_HEIGHT - CTitleFrame::FRAME_SIZE.y)
	{
		//Y���̈ړ������𔽓]������
		move.y *= -1.0f;
	}

	//�O�Ղ𐶐�
	CTrajectory2D::Create(pos, GetSize() * 0.5f, { 0.0f, 1.0f, 1.0f, 0.3f }, TEXTURE_FILE);

	//�X�V���ݒ�
	SetPos(pos);//�ʒu
	CObject2D::SetMove(move);//�ړ���

	//2D�I�u�W�F�N�g�X�V����
	CObject2D::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CBullet2D::Draw()
{
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
CBullet2D* CBullet2D::Create(D3DXVECTOR2 pos)
{
	CBullet2D* pBullet2D = NEW CBullet2D();

	pBullet2D->SetType(CObject::BULLET);//�I�u�W�F�N�g�^�C�v
	pBullet2D->SetPos(pos);//�����ʒu�ݒ�
	pBullet2D->SetMove();//�ړ��ʏ��ݒ�
	pBullet2D->Init();//����������

	return pBullet2D;
}

//===========================================================================================================
// �ړ��ʐݒ�
//===========================================================================================================
void CBullet2D::SetMove()
{
	//�p�����[�^�ݒ�
	float fRandAngle = float((rand() % 629 + 1) - 314) / 100.0f; //�p�x
	float fMoveX = sinf(fRandAngle) * BULLET2D_SPEED;//X���W�̈ړ���
	float fMoveY = cosf(fRandAngle) * BULLET2D_SPEED;//Y���W�̈ړ���

	//�ړ��ʏ���ݒ�
	CObject2D::SetMove({ fMoveX, fMoveY });
}

