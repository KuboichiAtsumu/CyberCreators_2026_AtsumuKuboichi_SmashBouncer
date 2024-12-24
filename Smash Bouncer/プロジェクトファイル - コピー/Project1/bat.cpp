//==============================================================================================================================================
//
// �o�b�g�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "bat.h"//�R�E����
#include "bullet.h"//�o���b�g
#include "player.h"//�v���C���[
#include "effect3D.h"//3D�G�t�F�N�g

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CBat::CBat(int nPriority) : CEnemy(nPriority)
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CBat::~CBat()
{
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CBat::Update()
{
	//�v���C���[�Ƃ̋���
	float fLength = 0.0f;

	//�����擾
	D3DXVECTOR3 pos = GetPos();//�ʒu
	D3DXVECTOR3 rot = GetRot();//����
	D3DXVECTOR3 PlayerPos = {};

	//�w�肵�����ԂɃI�u�W�F�N�g�����擾
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
				PlayerPos = pPlayer->GetPos();

				//�e���W�̃v���C���[�ƃo���b�g�̋��������߂�
				D3DXVECTOR3 Distance{ pos.x - PlayerPos.x, pos.y - PlayerPos.y, pos.z - PlayerPos.z };

				//�v���C���[�܂ł̊p�x�����߂�
				float fAngle = atan2f(Distance.x, Distance.z);

				//�v���C���[�܂ł̋��������߂�
				fLength = sqrtf(powf(Distance.x, 2.0f) + powf(Distance.z, 2.0f)) * 0.5f;

				//�G�l�~�[���v���C���[�̕����Ɍ�����
				rot.y = fAngle;
			}

			//�I�u�W�F�N�g�������̏��ɕύX����
			pObj = pNext;
		}
	}

	//���̐ݒ�
	SetRot(rot);//����

	//�e���˂��J�E���g
	int nCntShot = GetCntShot();//���݂̃J�E���g���擾
	SetCntShot(nCntShot + 1);//�J�E���g�����Z���Đݒ�

	//�J�E���g���ő�܂ŒB�����ꍇ
	if (nCntShot >= CProcess::MAX_FRAME * GetInterval())
	{
		//�e�̈ړ��ʂ�ݒ�
		D3DXVECTOR3 BulletMove = D3DXVECTOR3(sinf(rot.y + D3DX_PI) * (fLength * 0.03f), 10.0f, cosf(rot.y + D3DX_PI) * (fLength * 0.03f));

		//�e�𐶐�
		CBullet::Create(pos, BulletMove, CBullet::BULLETTYPE::LAUNCH_ENEMY);

		//�^�[�Q�b�g�𐶐�
		PlayerPos.y += 0.03f;
		CEffect3D::Create(CEffect3D::EFFECT_3D_TARGET, PlayerPos, { 0.0f, 0.0f, 0.0f }, { 30.0f, 0.0f, 30.0f });

		//�J�E���g���Z�b�g
		SetCntShot(0);

		//���̒e���˂܂ł̎��Ԃ�ݒ�
		SetInterval();
	}

	//�G�l�~�[�̍X�V����
	CEnemy::Update();
}
