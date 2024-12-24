//==============================================================================================================================================
//
// �{�X�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "boss.h"//�{�X
#include "player.h"//�v���C���[
#include "bullet.h"//�o���b�g

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CBoss::CBoss(int nPriority) : CEnemy(nPriority)
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CBoss::~CBoss()
{
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CBoss::Update()
{
	//���݂̃X�e�[�W�ƍ��W����v���Ȃ��ꍇ
	if (CGame::GetNumStage() != GetPostStageID())
	{
		//�X�V�����ɏ����𔲂���
		return;
	}

	//�v���C���[�Ƃ̋���
	float fLength = 0.0f;

	//�����擾
	D3DXVECTOR3 Pos = GetPos();//�ʒu
	D3DXVECTOR3 Rot = GetRot();//����

	//�w�肵�����ԂɃI�u�W�F�N�g�����擾����
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		//�擪
		CObject* pObj = CObject::GetTop(nCnt);

		//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
		while (pObj != nullptr)
		{
			//���̃I�u�W�F�N�g�����擾
			CObject* pNext = pObj->GetNext();

			//�I�u�W�F�N�g�^�C�v�̎擾
			CObject::TYPE type = pObj->GetType();

			//�^�C�v���v���C���[�̏ꍇ
			if (type == CObject::TYPE::PLAYER)
			{
				//�I�u�W�F�N�g�����v���C���[���ɕϊ�
				CPlayer* pPlayer = (CPlayer*)pObj;

				//�v���C���[�̈ʒu�����擾
				D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

				//�e���W�̃v���C���[�ƃo���b�g�̋��������߂�
				D3DXVECTOR3 Distance{ Pos.x - PlayerPos.x, Pos.y - PlayerPos.y, Pos.z - PlayerPos.z };

				//�v���C���[�܂ł̊p�x�����߂�
				float fAngle = atan2f(Distance.x, Distance.z);

				//�v���C���[�܂ł̋��������߂�
				fLength = sqrtf(powf(Distance.x, 2.0f) + powf(Distance.z, 2.0f)) * 0.5f;

				//�G�l�~�[���v���C���[�̕����Ɍ�����
				Rot.y = fAngle;
			}

			//�I�u�W�F�N�g�������̏��ɕύX����
			pObj = pNext;
		}
	}

	//���̐ݒ�
	SetRot(Rot);//����

	//�e���˂��J�E���g
	int nCntShot = GetCntShot();//���݂̃J�E���g���擾
	SetCntShot(nCntShot + 1);//�J�E���g�����Z���Đݒ�

	//�J�E���g���ő�܂ŒB�����ꍇ
	if (nCntShot >= CProcess::MAX_FRAME * GetInterval())
	{
		//�o�E���h�o���b�g���ˏ���
		ShotBound(Pos, Rot);

		//�J�E���g���Z�b�g
		SetCntShot(0);

		//���̒e���˂܂ł̎��Ԃ�ݒ�
		SetInterval();
	}

	//�ړ�����
	CEnemy::Move();

	//�G�l�~�[�̍X�V����
	CEnemy::Update();
}

//===========================================================================================================
// �o�E���h�o���b�g���ˏ���
//===========================================================================================================
void CBoss::ShotBound(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�e�̈ړ���
	D3DXVECTOR3 BulletMove = {};

	for (int nCnt = 0; nCnt < DIFFUSION_BULLET + 1; nCnt++)
	{
		//1�Ԗڂ̃o���b�g�̏ꍇ
		if (nCnt == 0)
		{
			//�e�̈ړ��ʂ�ݒ�
			BulletMove = D3DXVECTOR3(sinf(rot.y + D3DX_PI) * BULLET_SPEED, 0.0f, cosf(rot.y + D3DX_PI) * BULLET_SPEED);

			//�e�𐶐�
			CBullet::Create(pos, BulletMove, CBullet::BULLETTYPE::BOUND_INVINCIBLE);
		}
		//2�Ԗڈȍ~�̃o���b�g�̏ꍇ
		else
		{
			//�e�̈ړ��ʂ�ݒ�
			BulletMove = D3DXVECTOR3(sinf(rot.y - DISTANCE_BULLET * (float)nCnt + D3DX_PI) * BULLET_SPEED,
				0.0f,
				cosf(rot.y - DISTANCE_BULLET * (float)nCnt + D3DX_PI) * BULLET_SPEED);

			//�e�𐶐�
			CBullet::Create(pos, BulletMove, CBullet::BULLETTYPE::BOUND_INVINCIBLE);

			//�e�̈ړ��ʂ�ݒ�
			BulletMove = D3DXVECTOR3(sinf(rot.y + DISTANCE_BULLET * (float)nCnt + D3DX_PI) * BULLET_SPEED,
				0.0f,
				cosf(rot.y + DISTANCE_BULLET * (float)nCnt + D3DX_PI) * BULLET_SPEED);

			//�e�𐶐�
			CBullet::Create(pos, BulletMove, CBullet::BULLETTYPE::BOUND_INVINCIBLE);
		}
	}
}
