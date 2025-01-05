//==============================================================================================================================================
//
// �X���C���̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "slime.h"//�X���C��
#include "bullet.h"//�o���b�g

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CSlime::CSlime(int nPriority) : CEnemy(nPriority)
{
	//�����o�ϐ�������
	m_bTurn = false;//��]����t���O
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CSlime::~CSlime()
{
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CSlime::Update()
{
	//�G�l�~�[�̍X�V����
	CEnemy::Update();

	//���[�J���ϐ��錾
	static float fTargetRot;//�ڕW�̌���
	int nCntShot = GetCntShot();//���݂̃J�E���g���擾

	//�G�l�~�[�̌��݂̌��������擾
	D3DXVECTOR3 SlimeRot = GetRot();

	//��]���肪false�̏ꍇ
	if (!m_bTurn)
	{
		//�J�E���g���ő�܂ŒB�����ꍇ
		if (nCntShot >= CProcess::MAX_FRAME * GetInterval())
		{
			//�ڕW�̌����������_���Őݒ�
			fTargetRot = SHOT_ANGLE[rand() % SHOT_PATTERN];

			//��]�����true�ɂ���
			m_bTurn = true;
		}
		//�J�E���g���ő�܂ŒB���Ă��Ȃ��ꍇ
		else
		{
			//�e���˂��J�E���g
			SetCntShot(nCntShot + 1);//�J�E���g�����Z���Đݒ�
		}
	}
	//��]���肪true�̏ꍇ
	else
	{
		//�ڕW�̌����̒l�����v���C���[�̌����̒l�̂ق����傫���ꍇ
		if (SlimeRot.y - fTargetRot > 0)
		{
			//�G�l�~�[����]������
			SlimeRot.y -= TURN_SPEED;

			//�ڕW�̌����ɓ��B�����ꍇ
			if (SlimeRot.y - fTargetRot <= 0.0f)
			{
				//�ڕW�̌����𒴂��Ȃ��悤�ɒ���
				SlimeRot.y = fTargetRot;

				//�e�̈ړ��ʂ�ݒ�
				D3DXVECTOR3 BulletMove = D3DXVECTOR3(sinf(SlimeRot.y + D3DX_PI) * BULLET_SPEED, 0.0f, cosf(SlimeRot.y + D3DX_PI) * BULLET_SPEED);

				//�G�̈ʒu�����擾
				D3DXVECTOR3 SlimePos = GetPos();

				//���ˈʒu�̍�����^�񒆂ɏグ��
				SlimePos.y += GetSize().y * 0.5f;

				//�e�𐶐�
				CBullet::Create(SlimePos, BulletMove, CBullet::BULLETTYPE::BOUND_ENEMY);

				//��]�����false�ɂ���
				m_bTurn = false;

				//�J�E���g���Z�b�g
				SetCntShot(0);

				//���̒e���˂܂ł̎��Ԃ�ݒ�
				SetInterval();
			}
		}
		//�v���C���[�̌����̒l�����ڕW�̌����̒l�̂ق����傫���ꍇ
		else
		{
			//�G�l�~�[����]������
			SlimeRot.y += TURN_SPEED;

			//�ڕW�̌����ɓ��B�����ꍇ
			if (SlimeRot.y - fTargetRot >= 0.0f)
			{
				//�ڕW�̌����𒴂��Ȃ��悤�ɒ���
				SlimeRot.y = fTargetRot;

				//�e�̈ړ��ʂ�ݒ�
				D3DXVECTOR3 BulletMove = D3DXVECTOR3(sinf(SlimeRot.y + D3DX_PI) * BULLET_SPEED, 0.0f, cosf(SlimeRot.y + D3DX_PI) * BULLET_SPEED);

				//�G�̈ʒu�����擾
				D3DXVECTOR3 SlimePos = GetPos();

				//���ˈʒu�̍�����^�񒆂ɏグ��
				SlimePos.y += GetSize().y * 0.5f;

				//�e�𐶐�
				CBullet::Create(SlimePos, BulletMove, CBullet::BULLETTYPE::BOUND_ENEMY);

				//��]�����false�ɂ���
				m_bTurn = false;

				//�J�E���g���Z�b�g
				SetCntShot(0);

				//���̒e���˂܂ł̎��Ԃ�ݒ�
				SetInterval();
			}
		}
	}

	//��������ݒ�
	SetRot(SlimeRot);
}
