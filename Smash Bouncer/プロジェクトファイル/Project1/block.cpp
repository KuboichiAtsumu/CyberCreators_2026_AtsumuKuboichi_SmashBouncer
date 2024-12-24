//==============================================================================================================================================
//
// �u���b�N�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "block.h"//�u���b�N
#include "wallblock.h"//�ǃu���b�N
#include "barrier.h"//�o���A�u���b�N
#include "boundary.h"//�X�e�[�W���E�u���b�N
#include "battery.h"//�o�b�e���[
#include "keyblock.h"//���t���u���b�N
#include "collapseblock.h"//�����u���b�N
#include "effect3D.h"//3D�G�t�F�N�g

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	//�����o�ϐ�������
	m_pPrev = nullptr;//�O�̃u���b�N���
	m_pNext = nullptr;//���̃u���b�N���
	m_BlockType = {};//�u���b�N�^�C�v
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CBlock::~CBlock()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CBlock::Init()
{
	//�e�N�X�`������
	CTexture* pTex = CManager::GetTexture();//�擾
	int nTextureIdx = pTex->Regist(CXfile::GetSaveModelInfo(CXfile::BLOCK, m_BlockType)->aTextureFile);//�o�^
	BindTexture(pTex->GetAddress(nTextureIdx));//�ݒ�
	SetTextureIdx(nTextureIdx);//ID�ݒ�

	//���f������
	CXfile* pModel = CManager::GetModel();//�擾
	int nModelIdx = pModel->Regist(CXfile::GetSaveModelInfo(CXfile::BLOCK, m_BlockType)->aModelFile);//�o�^
	BindModel(pModel->GetAddress(nModelIdx));//�ݒ�
	SetModelIdx(nModelIdx);//ID�ݒ�
	SetSize();//�T�C�Y�ݒ�

	//����������X�e�[�WID��o�^
	SetPostStageID();

	//X�t�@�C���I�u�W�F�N�g����������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CBlock::Uninit()
{
	//X�t�@�C���I�u�W�F�N�g�I������
	CObjectX::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CBlock::Update()
{
	//X�t�@�C���I�u�W�F�N�g�X�V����
	CObjectX::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CBlock::Draw()
{
	//�G�f�B�^���[�h�̏ꍇ
	if (CManager::GetScene()->GetEditMode())
	{//�`�悹���ɏ����𔲂���
		return;
	}

	//X�t�@�C���̃I�u�W�F�N�g�`�揈��
	CObjectX::Draw();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int nType)
{
	//�^�C�v�ɉ����ē��I�m��
	CBlock* pBlock = NEW CBlock();
	switch (nType)
	{
		//�ǃu���b�N
	case WALL:
		pBlock = NEW CWallBlock();
		break;

		//�o���A�u���b�N
	case BARRIER:
		pBlock = NEW CBarrier();
		break;

		//�X�e�[�W���E�u���b�N
	case BOUNDARY:
		pBlock = NEW CBoundary();
		break;

		//�C��
	case BATTERY:
		pBlock = NEW CBattery();
		break;

		//���t���u���b�N
	case KEY:
		pBlock = NEW CKeyBlock();
		break;

		//�����u���b�N
	case COLLAPSE:
		pBlock = NEW CCollapseBlock();
		break;

	default:
		break;
	}

	//�p�����[�^�ݒ�
	pBlock->SetType(TYPE::BLOCK);//�I�u�W�F�N�g�^�C�v�ݒ�
	pBlock->SetPos(pos);//�ʒu
	pBlock->SetRot(rot);//����
	pBlock->SetScale(scale);//�g�嗦
	pBlock->SetBlockType((BLOCKTYPE)nType);//�u���b�N�^�C�v�ݒ�

	//����������
	pBlock->Init();

	return pBlock;
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
void CBlock::Collision(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& size)
{
	//�����擾
	D3DXVECTOR3 Pos = GetPos();//�ʒu
	D3DXVECTOR3 Size = GetSize();//�T�C�Y

	//�����̔���
	if (pos.x + size.x * 0.5f >= Pos.x - Size.x * 0.5f
		&& oldpos.x + size.x * 0.5f < Pos.x - Size.x * 0.5f)
	{//�d�Ȃ����ꍇ
		if (pos.z + size.z * 0.5f > Pos.z - Size.z * 0.5f
			&& pos.z - size.z * 0.5f < Pos.z + Size.z * 0.5f)
		{//�Ώۂ̎�O�����牜���܂ł͈͓̔��ɂ���ꍇ
			pos.x = oldpos.x;
		}
	}

	//�E���̔���
	if (pos.x - size.x * 0.5f <= Pos.x + Size.x * 0.5f
		&& oldpos.x - size.x * 0.5f > Pos.x + Size.x * 0.5f)
	{//�d�Ȃ����ꍇ
		if (pos.z + size.z * 0.5f > Pos.z - Size.z * 0.5f
			&& pos.z - size.z * 0.5f < Pos.z + Size.z * 0.5f)
		{//�Ώۂ̎�O�����牜���܂ł͈͓̔��ɂ���ꍇ
			pos.x = oldpos.x;
		}
	}

	//��O���̔���
	if (pos.z + size.z * 0.5f >= Pos.z - Size.z * 0.5f
		&& oldpos.z + size.z * 0.5f < Pos.z - Size.z * 0.5f)
	{//�d�Ȃ����ꍇ
		if (pos.x + size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& pos.x - size.x * 0.5f < Pos.x + Size.x * 0.5f)
		{//�Ώۂ̍�������E���܂ł͈͓̔��ɂ���ꍇ
			pos.z = oldpos.z;
		}
	}

	//�����̔���
	if (pos.z - size.z * 0.5f <= Pos.z + Size.z * 0.5f
		&& oldpos.z - size.z * 0.5f > Pos.z + Size.z * 0.5f)
	{//�d�Ȃ����ꍇ
		if (pos.x + size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& pos.x - size.x * 0.5f < Pos.x + Size.x * 0.5f)
		{//�Ώۂ̍�������E���܂ł͈͓̔��ɂ���ꍇ
			pos.z = oldpos.z;
		}
	}
}

//===========================================================================================================
// ���ˏ���
//===========================================================================================================
bool CBlock::Reflection(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& move, D3DXVECTOR3& rot, D3DXVECTOR3& size)
{
	//���[�J���ϐ��錾
	bool bReflection = false;//���˃t���O
	D3DXVECTOR3 Pos = GetPos();//�ʒu���
	D3DXVECTOR3 Size = GetSize();//�T�C�Y���

	//�����̔���
	if (pos.x + size.x * 0.5f >= Pos.x - Size.x * 0.5f && oldpos.x + size.x * 0.5f < Pos.x - Size.x * 0.5f)
	{//�d�Ȃ����ꍇ
		if (pos.z + size.z * 0.5f >= Pos.z - Size.z * 0.5f && pos.z - size.z * 0.5f <= Pos.z + Size.z * 0.5f)
		{//�Ώۂ̎�O�����牜���܂ł͈͓̔��ɂ���ꍇ

			////�u���b�N�̐����x�N�g�������߂�
			//SEGMENT(Pos.x, Pos.z - Size.z * 0.5f, Pos.x, Pos.z + Size.z * 0.5f);

			////�e�̕����x�N�g�������߂�
			//D3DXVECTOR3 f = pos - oldpos;

			////�i�s�x�N�g���𐳋K��
			//D3DXVec3Normalize(&f, &f);

			////�W�������߂�
			//D3DXVECTOR3 a(-f.x * m_Normal.x, -f.y * m_Normal.y, -f.z * m_Normal.z);

			////�W���𐳋K��
			//D3DXVec3Normalize(&a, &a);

			////���s�x�N�g�������߂�
			//D3DXVECTOR3 p(f.x + a.x * m_Normal.x, f.y + a.y * m_Normal.y, f.z + a.z * m_Normal.z);

			////���s�x�N�g���𐳋K��
			//D3DXVec3Normalize(&p, &p);

			////���˃x�N�g�������߂�
			//D3DXVECTOR3 r(f.x + 2.0f * a.x * m_Normal.x, f.y + 2.0f * a.y * m_Normal.y, f.z + 2.0f * a.z * m_Normal.z);

			////���˃x�N�g���𐳋K��
			//D3DXVec3Normalize(&r, &r);

			////���˃x�N�g���ɑ΂��āA�e�̌�����ύX
			//if (r.z > 0.0f)
			//{//���˃x�N�g����������̏ꍇ
			//	rot = D3DXVECTOR3(0.0f, (-D3DX_PI * 0.5f) * (2.0f + r.x), 0.0f);
			//}
			//else
			//{//���˃x�N�g�����������̏ꍇ
			//	rot = D3DXVECTOR3(0.0f, (-D3DX_PI * 0.5f) * r.x, 0.0f);
			//}

			////�����ɍ��킹�Ĉړ��ʂ�ύX
			//move = D3DXVECTOR3(sinf(rot.y + D3DX_PI) * 4.0f, 0.0f, cosf(rot.y + D3DX_PI) * 4.0f);

			//�ړ��ʂ�ύX
			move.x *= -1.0f;

			//���˃t���O��true�ɂ���
			bReflection = true;

			//�Ռ��g�G�t�F�N�g����
			CEffect3D::Create(CEffect3D::EFFECT_3D_SHOCKWAVE, {pos.x, Pos.y + 10.0f, pos.z}, { -D3DX_PI * 0.5f, D3DX_PI * 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f });

			//�^�C�g����ʈȊO
			if (CManager::GetScene()->GetMode() != CScene::MODE_TITLE)
			{
				//���ʉ��Đ�
				CManager::GetSound()->Play(CSound::SE_BOUND);
			}
		}
	}

	//�E���̔���
	if (pos.x - size.x * 0.5f <= Pos.x + Size.x * 0.5f && oldpos.x - size.x * 0.5f > Pos.x + Size.x * 0.5f)
	{//�d�Ȃ����ꍇ
		if (pos.z + size.z * 0.5f >= Pos.z - Size.z * 0.5f && pos.z - size.z * 0.5f <= Pos.z + Size.z * 0.5f)
		{//�Ώۂ̎�O�����牜���܂ł͈͓̔��ɂ���ꍇ

			////�u���b�N�̐����x�N�g�������߂�
			//SEGMENT(Pos.x, Pos.z + Size.z * 0.5f, Pos.x, Pos.z - Size.z * 0.5f);

			////�e�̕����x�N�g�������߂�
			//D3DXVECTOR3 f = pos - oldpos;

			////�i�s�x�N�g���𐳋K��
			//D3DXVec3Normalize(&f, &f);

			////�W�������߂�
			//D3DXVECTOR3 a(-f.x * m_Normal.x, -f.y * m_Normal.y, -f.z * m_Normal.z);

			////�W���𐳋K��
			//D3DXVec3Normalize(&a, &a);

			////���s�x�N�g�������߂�
			//D3DXVECTOR3 p(f.x + a.x * m_Normal.x, f.y + a.y * m_Normal.y, f.z + a.z * m_Normal.z);

			////���s�x�N�g���𐳋K��
			//D3DXVec3Normalize(&p, &p);

			////���˃x�N�g�������߂�
			//D3DXVECTOR3 r(f.x + 2.0f * a.x * m_Normal.x, f.y + 2.0f * a.y * m_Normal.y, f.z + 2.0f * a.z * m_Normal.z);

			////���˃x�N�g���𐳋K��
			//D3DXVec3Normalize(&r, &r);

			////���˃x�N�g���ɑ΂��āA�e�̌�����ύX
			//if (r.z > 0.0f)
			//{//���˃x�N�g����������̏ꍇ
			//	rot = D3DXVECTOR3(0.0f, (D3DX_PI * 0.5f) * (2.0f + r.x), 0.0f);
			//}
			//else
			//{//���˃x�N�g�����������̏ꍇ
			//	rot = D3DXVECTOR3(0.0f, (-D3DX_PI * 0.5f) * r.x, 0.0f);
			//}

			////�����ɍ��킹�Ĉړ��ʂ�ύX
			//move = D3DXVECTOR3(sinf(rot.y + D3DX_PI) * 4.0f, 0.0f, cosf(rot.y + D3DX_PI) * 4.0f);

			//�ړ��ʂ�ύX
			move.x *= -1.0f;

			//���˃t���O��true�ɂ���
			bReflection = true;

			//�Ռ��g�G�t�F�N�g����
			CEffect3D::Create(CEffect3D::EFFECT_3D_SHOCKWAVE, { pos.x, Pos.y + 10.0f, pos.z }, { -D3DX_PI * 0.5f, -D3DX_PI * 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f });

			//�^�C�g����ʈȊO
			if (CManager::GetScene()->GetMode() != CScene::MODE_TITLE)
			{
				//���ʉ��Đ�
				CManager::GetSound()->Play(CSound::SE_BOUND);
			}
		}
	}

	//�����̔���
	if (pos.z - size.z * 0.5f <= Pos.z + Size.z * 0.5f && oldpos.z - size.z * 0.5f > Pos.z + Size.z * 0.5f)
	{//�d�Ȃ����ꍇ
		if (pos.x + size.z * 0.5f >= Pos.x - Size.x * 0.5f && pos.x - size.z * 0.5f <= Pos.x + Size.x * 0.5f)
		{//�Ώۂ̍�������E���܂ł͈͓̔��ɂ���ꍇ

			////�u���b�N�̐����x�N�g�������߂�
			//SEGMENT(Pos.x - Size.x * 0.5f, Pos.z, Pos.x + Size.x * 0.5f, Pos.z);

			////�e�̐i�s�x�N�g�������߂�
			//D3DXVECTOR3 f = pos - oldpos;

			////�i�s�x�N�g���𐳋K��
			//D3DXVec3Normalize(&f, &f);

			////�W�������߂�
			//D3DXVECTOR3 a(-f.x * m_Normal.x, -f.y * m_Normal.y, -f.z * m_Normal.z);

			////�W���𐳋K��
			//D3DXVec3Normalize(&a, &a);

			////���s�x�N�g�������߂�
			//D3DXVECTOR3 p(f.x + a.x * m_Normal.x, f.y + a.y * m_Normal.y, f.z + a.z * m_Normal.z);

			////���s�x�N�g���𐳋K��
			//D3DXVec3Normalize(&p, &p);

			////���˃x�N�g�������߂�
			//D3DXVECTOR3 r(f.x + 2.0f * a.x * m_Normal.x, f.y + 2.0f * a.y * m_Normal.y, f.z + 2.0f * a.z * m_Normal.z);

			////���˃x�N�g���𐳋K��
			//D3DXVec3Normalize(&r, &r);

			////���˃x�N�g���ɑ΂��āA�e�̌�����ύX
			//if (r.x > 0.0f)
			//{//���˃x�N�g�����E�����̏ꍇ
			//	rot = D3DXVECTOR3(0.0f, -D3DX_PI * r.z, 0.0f);
			//}
			//else
			//{//���˃x�N�g�����������̏ꍇ
			//	rot = D3DXVECTOR3(0.0f, D3DX_PI * r.z, 0.0f);
			//}

			////�����ɍ��킹�Ĉړ��ʂ�ύX
			//move = D3DXVECTOR3(sinf(rot.y + D3DX_PI) * 4.0f, 0.0f, cosf(rot.y + D3DX_PI) * 4.0f);

			//�ړ��ʂ�ύX
			move.z *= -1.0f;

			//���˃t���O��true�ɂ���
			bReflection = true;

			//�Ռ��g�G�t�F�N�g����
			CEffect3D::Create(CEffect3D::EFFECT_3D_SHOCKWAVE, { pos.x, Pos.y + 10.0f, pos.z }, { -D3DX_PI * 0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });

			//�^�C�g����ʈȊO
			if (CManager::GetScene()->GetMode() != CScene::MODE_TITLE)
			{
				//���ʉ��Đ�
				CManager::GetSound()->Play(CSound::SE_BOUND);
			}
		}
	}

	//��O���̔���
	if (pos.z + size.z * 0.5f >= Pos.z - Size.z * 0.5f && oldpos.z + size.z * 0.5f < Pos.z - Size.z * 0.5f)
	{//�d�Ȃ����ꍇ
		if (pos.x + size.z * 0.5f >= Pos.x - Size.x * 0.5f && pos.x - size.z * 0.5f <= Pos.x + Size.x * 0.5f)
		{//�Ώۂ̍�������E���܂ł͈͓̔��ɂ���ꍇ

			////�u���b�N�̐����x�N�g�������߂�
			//SEGMENT(Pos.x + Size.x * 0.5f, Pos.z, Pos.x - Size.x * 0.5f, Pos.z);

			////�e�̐i�s�x�N�g�������߂�
			//D3DXVECTOR3 f = pos - oldpos;

			////�i�s�x�N�g���𐳋K��
			//D3DXVec3Normalize(&f, &f);

			////�W�������߂�
			//D3DXVECTOR3 a(-f.x * m_Normal.x, -f.y * m_Normal.y, -f.z * m_Normal.z);

			////�W���𐳋K��
			//D3DXVec3Normalize(&a, &a);

			////���s�x�N�g�������߂�
			//D3DXVECTOR3 p(f.x + a.x * m_Normal.x, f.y + a.y * m_Normal.y, f.z + a.z * m_Normal.z);

			////���s�x�N�g���𐳋K��
			//D3DXVec3Normalize(&p, &p);

			////���˃x�N�g�������߂�
			//D3DXVECTOR3 r(f.x + 2.0f * a.x * m_Normal.x, f.y + 2.0f * a.y * m_Normal.y, f.z + 2.0f * a.z * m_Normal.z);

			////���˃x�N�g���𐳋K��
			//D3DXVec3Normalize(&r, &r);

			////���˃x�N�g���ɑ΂��āA�e�̌�����ύX
			//if (r.x > 0.0f)
			//{//���˃x�N�g�����E�����̏ꍇ
			//	rot = D3DXVECTOR3(0.0f, -D3DX_PI * (1.0f + r.z), 0.0f);
			//}
			//else
			//{//���˃x�N�g�����������̏ꍇ
			//	rot = D3DXVECTOR3(0.0f, D3DX_PI * (1.0f + r.z), 0.0f);
			//}

			////�����ɍ��킹�Ĉړ��ʂ�ύX
			//move = D3DXVECTOR3(sinf(rot.y + D3DX_PI) * 4.0f, 0.0f, cosf(rot.y + D3DX_PI) * 4.0f);

			//�ړ��ʂ�ύX
			move.z *= -1.0f;

			//���˃t���O��true�ɂ���
			bReflection = true;

			//�Ռ��g�G�t�F�N�g����
			CEffect3D::Create(CEffect3D::EFFECT_3D_SHOCKWAVE, { pos.x, Pos.y + 10.0f, pos.z }, { -D3DX_PI * 0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });

			//�^�C�g����ʈȊO
			if (CManager::GetScene()->GetMode() != CScene::MODE_TITLE)
			{
				//���ʉ��Đ�
				CManager::GetSound()->Play(CSound::SE_BOUND);
			}
		}
	}

	//���˃t���O��true�̏ꍇ
	if (bReflection)
	{
		//�ΏۃI�u�W�F�N�g���ߋ��̈ʒu�ɖ߂�
		pos = oldpos;
	}

	//���˃t���O��Ԃ�
	return bReflection;
}

//===========================================================================================================
// �����x�N�g���v�Z����
//===========================================================================================================
void CBlock::SEGMENT(float StartX, float StartZ, float EndX, float EndZ)
{
	//�����x�N�g�������߂�
	D3DXVECTOR3 Start(StartX, 0.0f, StartZ);
	D3DXVECTOR3 End(EndX, 0.0f, EndZ);

	D3DXVECTOR3 r = End - Start;

	m_Normal.x = -r.z;
	m_Normal.z = r.x;

	//�x�N�g���𐳋K��
	D3DXVec3Normalize(&m_Normal, &m_Normal);
}
