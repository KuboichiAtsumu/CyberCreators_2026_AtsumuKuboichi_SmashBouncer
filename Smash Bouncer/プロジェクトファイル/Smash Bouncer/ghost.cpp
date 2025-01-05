//==============================================================================================================================================
//
// �S�[�X�g�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "ghost.h"//�S�[�X�g�w�b�_�[
#include "bullet.h"//�o���b�g�w�b�_�[
#include "pointmanager.h"//�|�C���g�}�l�[�W���[
#include "effect3D.h"//3D�G�t�F�N�g

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CGhost::CGhost(int nPriority) : CEnemy(nPriority)
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CGhost::~CGhost()
{
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CGhost::Update()
{
	//�e���˂��J�E���g
	int nCntShot = GetCntShot();//���݂̃J�E���g���擾
	SetCntShot(nCntShot + 1);//�J�E���g�����Z���Đݒ�

	//�J�E���g���ő�܂ŒB�����ꍇ
	if (nCntShot >= CProcess::MAX_FRAME * GetInterval())
	{
		//�|�C���g�̐����擾
		int nPoint = GetAllEachStageID(CGame::GetNumStage(), CObject::SHOTPOINT);

		//�����_���Ŕ��ˈʒu��ݒ�
		int nTarget = rand() % nPoint;

		//�擪�̃I�u�W�F�N�g�����擾
		CPoint* pPoint = CGame::GetPointManager()->GetTop();

		//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
		while (pPoint != nullptr)
		{
			//���̃I�u�W�F�N�g�����擾
			CPoint* pNext = pPoint->GetNextPoint();

			//�|�C���g���G�l�~�[�Ɠ����X�e�[�W�ɂ���ꍇ
			//���ˈʒu�̃|�C���g��ID�ƃ^�[�Q�b�g�ԍ�����v����ꍇ
			if (pPoint->GetPostStageID() == GetPostStageID() && pPoint->GetEachStageID() == nTarget)
			{
				//���ˈʒu�ݒ�
				SetPoint(pPoint);
				break;
			}
		
			//�I�u�W�F�N�g�������̏��ɕύX����
			pPoint = pNext;
		}

		//�J�E���g���Z�b�g
		SetCntShot(0);

		//���̒e���˂܂ł̎��Ԃ�ݒ�
		SetInterval();
	}

	//�G�l�~�[�̍X�V����
	CEnemy::Update();
}

//===========================================================================================================
// ���ˈʒu�ݒ�
//===========================================================================================================
void CGhost::SetPoint(CPoint* pPoint)
{
	//�|�C���g�Ƃ̋���
	float fLength = 0.0f;

	//�����擾
	D3DXVECTOR3 pos = GetPos();//�ʒu
	D3DXVECTOR3 rot = GetRot();//����

	//�|�C���g�̈ʒu�����擾
	D3DXVECTOR3 PointPos = pPoint->GetPos();

	//�e���W�̃|�C���g�ƃo���b�g�̋��������߂�
	D3DXVECTOR3 Distance{ pos.x - PointPos.x, pos.y - PointPos.y, pos.z - PointPos.z };

	//�|�C���g�܂ł̊p�x�����߂�
	float fAngle = atan2f(Distance.x, Distance.z);

	//�|�C���g�܂ł̋��������߂�
	fLength = sqrtf(powf(Distance.x, 2.0f) + powf(Distance.z, 2.0f)) * 0.5f;

	//�G�l�~�[���|�C���g�̕����Ɍ�����
	rot.y = fAngle;

	//���̐ݒ�
	SetRot(rot);//����

	//�e�̈ړ��ʂ�ݒ�
	D3DXVECTOR3 BulletMove = D3DXVECTOR3(sinf(rot.y + D3DX_PI) * (fLength * 0.03f), 10.0f, cosf(rot.y + D3DX_PI) * (fLength * 0.03f));

	//�e�𐶐�
	CBullet::Create(pos, BulletMove, CBullet::BULLETTYPE::LAUNCH_ENEMY);

	//�^�[�Q�b�g�𐶐�
	PointPos.y += 0.03f;
	CEffect3D::Create(CEffect3D::EFFECT_3D_TARGET, PointPos, { 0.0f, 0.0f, 0.0f }, { 30.0f, 0.0f, 30.0f });

	//�J�E���g���Z�b�g
	SetCntShot(0);
}
