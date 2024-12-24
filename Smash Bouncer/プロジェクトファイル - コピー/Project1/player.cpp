//==============================================================================================================================================
//
// �v���C���[�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "player.h"//�v���C���[
#include "block.h"//�u���b�N
#include "item.h"//�A�C�e��
#include "camera.h"//�J����
#include "game.h"//�Q�[���V�[��
#include "zone.h"//�]�[��
#include "blockmanager.h"//�u���b�N�}�l�[�W���[
#include "bulletmanager.h"//�o���b�g�}�l�[�W���[
#include "tutorial.h"//�`���[�g���A���V�[��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CPlayer::CPlayer(int nPriority) : CMotionCharacter(nPriority)
{
	//�����o�[�ϐ�
	m_State = NORMAL;//���
	m_nCntState = 0;//��ԃJ�E���^
	m_bLightUp = false;//���C�g�A�b�v�t���O
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CPlayer::~CPlayer()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CPlayer::Init()
{
	//�p�[�c�t�@�C���Ǎ�����
	LoadParts(CMotionCharacter::PLAYER);

	//���[�V�������Ǎ�����
	LoadMotion(CMotionCharacter::PLAYER);

	//�p�����[�^�ݒ�
	SetRot({ 0.0f, -D3DX_PI * 0.5f, 0.0f });//����
	SetAllPartsSize();//�T�C�Y

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
void CPlayer::Uninit()
{
	//X�t�@�C���I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CPlayer::Update()
{
	//�G�f�B�^���[�h�ł͂Ȃ��ꍇ
	if (CManager::GetScene()->GetEditMode())
	{//�`�悹���ɏ����𔲂���
		return;
	}

	//���[�J���ϐ��錾
	CBlockManager* pBlockManager = nullptr;//�u���b�N�}�l�[�W���[
	
	//�V�[���ɉ����ă}�l�[�W���[�����擾
	switch (CManager::GetScene()->GetMode())
	{
		//�`���[�g���A��
	case CScene::MODE_TUTORIAL:
		pBlockManager = CTutorial::GetBlockManager();
		break;

		//�Q�[��
	case CScene::MODE_GAME:
		pBlockManager = CGame::GetBlockManager();
		break;

	default:
		break;
	}

	//�_���[�W��Ԃ̏ꍇ
	if (m_State == DAMAGE)
	{
		//��ԃJ�E���^���c���Ă���ꍇ
		if (m_nCntState > 0)
		{
			//��ԃJ�E���^���c���Ă���ꍇ
			m_nCntState--;
		}
		//��ԃJ�E���^���O�̏ꍇ
		else
		{
			//�ʏ��Ԃɂ���
			m_State = NORMAL;
		}

		//���C�g�A�b�v���̏ꍇ
		if (m_bLightUp)
		{
			//���f���𖾂邭�ݒ�
			SetPartsFlash(1.0f);
		}
		else
		{
			//���f�����Â��ݒ�
			SetPartsFlash(0.3f);
		}

		//���C�g�A�b�v�t���O��؂�ւ���
		m_bLightUp = m_bLightUp ? false : true;
	}
	//�_���[�W��Ԃł͂Ȃ��ꍇ
	else
	{
		//���f���𖾂邭�ݒ�
		SetPartsFlash(1.0f);

		//�ړ�����
		Move();

		//���ˏ���
		Reflect();
	}

	//�p�����[�^�擾
	D3DXVECTOR3 pos = GetPos();//�ʒu
	D3DXVECTOR3 oldpos = GetOldPos();//�ߋ��̈ʒu
	D3DXVECTOR3 Size = GetSize();//�T�C�Y

	//�u���b�N�Ƃ̓����蔻��
	pBlockManager->Collision(pos, oldpos, Size);

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

			//�I�u�W�F�N�g�^�C�v�ʂɏ���
			switch (type)
			{
				//�]�[��
			case CObject::ZONE:
				//�]�[���Ƃ̓����蔻��
				CollisionZone(pos, pObj);
				break;

			default:
				break;
			}

			//�I�u�W�F�N�g�������̏��ɕύX����
			pObj = pNext;
		}
	}

	//�X�V���ꂽ����ݒ�
	SetPos(pos);//�ʒu
	SetOldPos(oldpos);//�ߋ��̈ʒu
	
	//���[�V��������
	CMotionCharacter::Update();
}

//===========================================================================================================
// �ړ�����
//===========================================================================================================
void CPlayer::Move()
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 CameraRot = CManager::GetCamera()->GetRot();//�J�����̌������
	D3DXVECTOR3 pos = GetPos();//�ʒu
	D3DXVECTOR3 oldpos = GetOldPos();//�ߋ��̈ʒu
	D3DXVECTOR3 rot = GetRot();//����
	D3DXVECTOR3 move = GetMove();//�ړ���
	float fDiaSpeed = GetSpeed();//���x�{��

	//��ړ�
	if (CManager::GetKeyboard()->GetPress(DIK_W)
		|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_LEFT][CInputJoypad::STICKANGLE_UP] > 0.1f)
	{
		//����ړ�
		if (CManager::GetKeyboard()->GetPress(DIK_A)
			|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_LEFT][CInputJoypad::STICKANGLE_LEFT] > 0.1f)
		{
			//�ړ��ʂ����Z
			move.x += sinf(CameraRot.y + D3DX_PI * -0.25f) * fDiaSpeed;//X��
			move.z += cosf(CameraRot.y + D3DX_PI * -0.25f) * fDiaSpeed;//Z��

			//�������X�V
			if (rot.y <= CameraRot.y + D3DX_PI * 0.75f && rot.y >= CameraRot.y + D3DX_PI * -0.25f)
			{
				//�E��]
				rot.y += MAX_TURN;

				//�������
				if (rot.y >= CameraRot.y + D3DX_PI * 0.75f)
				{
					rot.y = CameraRot.y + D3DX_PI * 0.75f;
				}
			}
			else
			{
				//����]
				rot.y -= MAX_TURN;

				//�������
				if (rot.y <= CameraRot.y + D3DX_PI * 0.75f)
				{
					rot.y = CameraRot.y + D3DX_PI * 0.75f;
				}
			}
		}
		//�E��ړ�
		else if (CManager::GetKeyboard()->GetPress(DIK_D)
			|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_LEFT][CInputJoypad::STICKANGLE_RIGHT] > 0.1f)
		{
			//�ړ��ʂ����Z
			move.x += sinf(CameraRot.y + D3DX_PI * 0.25f) * fDiaSpeed;//X��
			move.z += cosf(CameraRot.y + D3DX_PI * 0.25f) * fDiaSpeed;//Z��

			//�������X�V
			if (rot.y <= CameraRot.y + D3DX_PI * 0.25f && rot.y >= CameraRot.y + D3DX_PI * -0.75f)
			{
				rot.y -= MAX_TURN;//����]

				if (rot.y <= CameraRot.y + D3DX_PI * -0.75f)
				{
					rot.y = CameraRot.y + D3DX_PI * -0.75f;//�E�����
				}
			}
			else
			{
				rot.y += MAX_TURN;//�E��]

				if (rot.y >= CameraRot.y + D3DX_PI * -0.75f)
				{
					rot.y = CameraRot.y + D3DX_PI * -0.75f;//�E�����
				}
			}
		}
		//�^��ړ�
		else
		{
			//�ړ��ʂ����Z
			move.x += sinf(CameraRot.y) * fDiaSpeed;//X��
			move.z += cosf(CameraRot.y) * fDiaSpeed;//Z��

			rot.y = CameraRot.y + D3DX_PI;//�����
		}
	}

	//���ړ�
	else if (CManager::GetKeyboard()->GetPress(DIK_S)
		|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_LEFT][CInputJoypad::STICKANGLE_DOWN] > 0.1f)
	{
		//�����ړ�
		if (CManager::GetKeyboard()->GetPress(DIK_A)
			|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_LEFT][CInputJoypad::STICKANGLE_LEFT] > 0.1f)
		{
			//�ړ��ʂ����Z
			move.x += sinf(CameraRot.y + D3DX_PI * -0.75f) * fDiaSpeed;//X��
			move.z += cosf(CameraRot.y + D3DX_PI * -0.75f) * fDiaSpeed;//Z��

			//�������X�V
			if (rot.y >= CameraRot.y + D3DX_PI * -0.75f && rot.y <= CameraRot.y + D3DX_PI * 0.25f)
			{
				rot.y += MAX_TURN;//�E��]

				if (rot.y >= CameraRot.y + D3DX_PI * 0.25f)
				{
					rot.y = CameraRot.y + D3DX_PI * 0.25f;//��������
				}
			}
			else
			{
				rot.y -= MAX_TURN;//����]

				if (rot.y <= CameraRot.y + D3DX_PI * 0.25f)
				{
					rot.y = CameraRot.y + D3DX_PI * 0.25f;//��������
				}
			}
		}
		//�E���ړ�
		else if (CManager::GetKeyboard()->GetPress(DIK_D)
			|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_LEFT][CInputJoypad::STICKANGLE_RIGHT] > 0.1f)
		{
			//�ړ��ʂ����Z
			move.x += sinf(CameraRot.y + D3DX_PI * 0.75f) * fDiaSpeed;//X��
			move.z += cosf(CameraRot.y + D3DX_PI * 0.75f) * fDiaSpeed;//Z��

			//�������X�V
			if (rot.y >= CameraRot.y + D3DX_PI * -0.25f && rot.y <= CameraRot.y + D3DX_PI * 0.75f)
			{
				rot.y -= MAX_TURN;//����]

				if (rot.y <= CameraRot.y + D3DX_PI * -0.25f)
				{
					rot.y = CameraRot.y + D3DX_PI * -0.25f;//�E������
				}
			}
			else
			{
				rot.y += MAX_TURN;//�E��]

				if (rot.y >= CameraRot.y + D3DX_PI * -0.25f)
				{
					rot.y = CameraRot.y + D3DX_PI * -0.25f;//�E������
				}
			}
		}
		//�^���ړ�
		else
		{
			//�ړ��ʂ����Z
			move.x += sinf(CameraRot.y + D3DX_PI) * fDiaSpeed;//X��
			move.z += cosf(CameraRot.y + D3DX_PI) * fDiaSpeed;//Z��

			rot.y = CameraRot.y;//������
		}
	}

	//���ړ�
	else if (CManager::GetKeyboard()->GetPress(DIK_A)
	|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_LEFT][CInputJoypad::STICKANGLE_LEFT] > 0.1f)
	{
		//�ړ��ʂ����Z
		move.x += sinf(CameraRot.y + D3DX_PI * -0.5f) * fDiaSpeed;//X��
		move.z += cosf(CameraRot.y + D3DX_PI * -0.5f) * fDiaSpeed;//Z��

		//�������X�V
		if (rot.y >= CameraRot.y + D3DX_PI * -0.5f && rot.y <= CameraRot.y + D3DX_PI * 0.5f)
		{
			rot.y += MAX_TURN;//�E��]

			if (rot.y >= CameraRot.y + D3DX_PI * 0.5f)
			{
				rot.y = CameraRot.y + D3DX_PI * 0.5f;//������
			}
		}
		else
		{
			rot.y -= MAX_TURN;//����]

			if (rot.y <= CameraRot.y + D3DX_PI * 0.5f)
			{
				rot.y = CameraRot.y + D3DX_PI * 0.5f;//������
			}
		}
	}

	//�E�ړ�
	else if (CManager::GetKeyboard()->GetPress(DIK_D)
	|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_LEFT][CInputJoypad::STICKANGLE_RIGHT] > 0.1f)
	{
		//�ړ��ʂ����Z
		move.x += sinf(CameraRot.y + D3DX_PI * 0.5f) * fDiaSpeed;//X��
		move.z += cosf(CameraRot.y + D3DX_PI * 0.5f) * fDiaSpeed;//Z��

		//�������X�V
		if (rot.y >= CameraRot.y + D3DX_PI * -0.5f && rot.y <= CameraRot.y + D3DX_PI * 0.5f)
		{
			rot.y -= MAX_TURN;//����]

			if (rot.y <= CameraRot.y + D3DX_PI * -0.5f)
			{
				rot.y = CameraRot.y + D3DX_PI * -0.5f;//�E����
			}
		}
		else
		{
			rot.y += MAX_TURN;//�E��]

			if (rot.y >= CameraRot.y + D3DX_PI * -0.5f)
			{
				rot.y = CameraRot.y + D3DX_PI * -0.5f;//�E����
			}
		}
	}

	//�ߋ��̈ʒu��ۑ�
	oldpos = pos;

	//�ړ��ʂ����Z
	pos += move;

	//�ړ��ʂ�����
	move.x += (0.0f - move.x) * MAX_INERTIA;
	move.z += (0.0f - move.z) * MAX_INERTIA;

	//�X�V���ꂽ����ݒ�
	SetMove(move);
	SetRot(rot);//�p�x
	SetPos(pos);//�ʒu
	SetOldPos(oldpos);//�ߋ��̈ʒu

	//�����Ă��Ȃ��ꍇ
	//���݂̏�ԏ�񂪈ړ���Ԃ̏ꍇ
	if ((move.x <= MAX_JUDGE_MOVE && move.x >= -MAX_JUDGE_MOVE) && (move.z <= MAX_JUDGE_MOVE && move.z >= -MAX_JUDGE_MOVE)
		&& GetState() == MOVE)
	{
		//�j���[�g������Ԃɐݒ�
		SetState(CMotionCharacter::NEUTRAL);
	}
	//�����Ă���ꍇ
	else if((move.x >= MAX_JUDGE_MOVE || move.x <= -MAX_JUDGE_MOVE) || (move.z >= MAX_JUDGE_MOVE || move.z <= -MAX_JUDGE_MOVE))
	{
		//�ړ���Ԃɐݒ�
		SetState(CMotionCharacter::MOVE);
	}
}

//===========================================================================================================
// ���ˏ���
//===========================================================================================================
void CPlayer::Reflect()
{
	//���[�J���ϐ��錾
	static bool bStickInput = false;//�X�e�B�b�N���͔���
	static int nCommandTime = 0;//�R�}���h��t�t���[��
	static float fFirstAngle = 0.0f;//�E�X�e�B�b�N�����͂��ꂽ�u�Ԃ̊p�x
	static float fStickAngle = 0.0f;//���݂̃X�e�B�b�N�̊p�x
	static float fDistance = MIN_REFLECT_POWER;//�E�X�e�B�b�N�̋Ȃ�������
	D3DXVECTOR3 BulletMove = { 0.0f,0.0f,0.0f };//�o���b�g�̈ړ���
	D3DXVECTOR3 pos = GetPos();//�ʒu
	D3DXVECTOR3 rot = GetRot();//����
	CBulletManager* pBulletManager = nullptr;//�o���b�g�}�l�[�W���[

	//�V�[���ɉ����ă}�l�[�W���[�����擾
	switch (CManager::GetScene()->GetMode())
	{
		//�`���[�g���A��
	case CScene::MODE_TUTORIAL:
		pBulletManager = CTutorial::GetBulletManager();
		break;

		//�Q�[��
	case CScene::MODE_GAME:
		pBulletManager = CGame::GetBulletManager();
		break;

	default:
		break;
	}
	
	//�R�}���h���͎�t�t���[�����c���Ă���ꍇ
	if (nCommandTime > 0)
	{
		//��t�t���[�������炷
		nCommandTime--;
	}
	//�R�}���h���͂��󂯕t���Ă��Ȃ��ꍇ
	else
	{
		//�E�X�e�B�b�N�̓��͏���������
		bStickInput = false;//���͔���
		fFirstAngle = 0.0f;//���͂��ꂽ�ŏ��̊p�x
		fStickAngle = 0.0f;//���݂̃X�e�B�b�N�̊p�x
		fDistance = MIN_REFLECT_POWER;//���݂̊p�x�ƍŏ��̊p�x�̍��̍ő�l
	}

	//�E�X�e�B�b�N���|���ꂽ�ꍇ
	//�o���b�g�^�C�v���G�l�~�[�̏ꍇ
	if (((float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_UP] > 0.1f
		|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_DOWN] > 0.1f
		|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_RIGHT] > 0.1f
		|| (float)CManager::GetJoypad()->GetStick().abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_LEFT] > 0.1f))
	{
		//�X�e�B�b�N�̌��݂̊p�x��ۑ�
		fStickAngle = CManager::GetJoypad()->GetAngleR();

		//���͂��ꂽ�u�Ԃ̊p�x��ۑ�
		if (!bStickInput)
		{
			fFirstAngle = fStickAngle;//�ŏ��̃X�e�B�b�N�̊p�x��ۑ�
			nCommandTime = COMMAND_TIME;//�R�}���h��t�t���[����ݒ�
			bStickInput = true;//���͔����true�ɂ���
		}
	
		//�R�}���h���͎�t���̏ꍇ
		//�ő�p�x�����ݕۑ�����Ă���l���傫���ꍇ
		if (nCommandTime > 0
			&& abs(fStickAngle - fFirstAngle) > fDistance)
		{
			//���͒��ɓ��������ő�p�x���X�V
			fDistance = abs(fStickAngle - fFirstAngle);

			//�{�������߂��Ȃ��悤�ɒ���
			if (fDistance > MAX_REFLECT_POWER)
			{
				fDistance = MAX_REFLECT_POWER;
			}
		}
		
		//�����蔻�肪true�̃o���b�g�����擾
		CBullet* pBullet = pBulletManager->Collision(pos);

		//�o���b�g�^�C�v���G�l�~�[�̏ꍇ
		if (pBullet != nullptr
			&& (pBullet->GetBulletType() == CBullet::BOUND_ENEMY || pBullet->GetBulletType() == CBullet::LAUNCH_ENEMY))
		{
			//�A�N�V������Ԃɐݒ�
			SetState(CMotionCharacter::ACTION);

			//�v���C���[�̌����ɃX�e�B�b�N�̊p�x�𔽉f
			rot.y = fStickAngle;

			//�o���b�g�̏I������
			pBullet->Uninit();

			//�V������������v���C���[�o���b�g�̈ړ���
			BulletMove = D3DXVECTOR3(sinf(rot.y + D3DX_PI) * (fDistance + MIN_REFLECT_SPEED), 0.0f, cosf(rot.y + D3DX_PI) * (fDistance + MIN_REFLECT_SPEED));

			//SE�Đ�
			CManager::GetSound()->Play(CSound::SE_SMASH);

			//�J�����̗h���ݒ�
			CManager::GetCamera()->SetShake(10, int(fDistance));

			//�V�����v���C���[�o���b�g�𐶐�
			CBullet::Create(pos, BulletMove, CBullet::PLAYER);

			//�N���[���e�𐶐�
			for (int nCnt = 0; nCnt < int(fDistance); nCnt++)
			{
				CBullet::Create(pos,
					{ sinf(rot.y - DIFFUSION_RATE * (float)(nCnt + 1) + D3DX_PI) * (fDistance + MIN_REFLECT_SPEED), 0.0f, cosf(rot.y - DIFFUSION_RATE * (float)(nCnt + 1) + D3DX_PI) * (fDistance + MIN_REFLECT_SPEED) },
					CBullet::CLONE);

				CBullet::Create(pos,
					{ sinf(rot.y + DIFFUSION_RATE * (float)(nCnt + 1) + D3DX_PI) * (fDistance + MIN_REFLECT_SPEED), 0.0f, cosf(rot.y + DIFFUSION_RATE * (float)(nCnt + 1) + D3DX_PI) * (fDistance + MIN_REFLECT_SPEED) },
					CBullet::CLONE);
			}
		}
	}

	//�X�V���ꂽ����ݒ�
	SetRot(rot);//�p�x
	SetPos(pos);//�ʒu
}

//===========================================================================================================
// �]�[���Ƃ̓����蔻��
//===========================================================================================================
void CPlayer::CollisionZone(D3DXVECTOR3& pos, CObject*& pObj)
{
	//���[�J���ϐ��錾
	CZone* pZone = (CZone*)pObj;//�I�u�W�F�N�g�����]�[�����ɕϊ�
	D3DXVECTOR3 oldpos = GetOldPos();//�ߋ��̈ʒu���
	D3DXVECTOR3 size = GetSize();//�T�C�Y���

	//�]�[���^�C�v�����˃]�[���̏ꍇ
	if (pZone->GetZoneType() == CZone::REFLECT)
	{
		//�]�[���͈͓̔��ɂ���ꍇ
		if (pZone->Judge(pos))
		{
			//�v���C���[������X�e�[�W�̔ԍ���ۑ�����
			CGame::SetNumStage(pZone->GetID());

			//�Q�[���̏�Ԃ��ړ����̏ꍇ
			if (CGame::GetGameState() == CGame::STATE_MOVE)
			{
				//�Q�[�����̏�Ԃɐݒ�
				CGame::SetGameState(CGame::STATE_GAME);
			}
		}
		
		//�Q�[�����̏ꍇ
		if (CGame::GetGameState() == CGame::STATE_GAME
			|| CManager::GetScene()->GetMode() == CScene::MODE_TUTORIAL)
		{
			//�]�[���Ƃ̓����蔻��
			pZone->Collision(pos, oldpos, size);
		}
	}

	//�]�[���^�C�v���X�e�[�W�敪�]�[���̏ꍇ
	//�]�[���͈͓̔��ɂ���ꍇ
	else if (pZone->GetZoneType() == CZone::STAGE)
	{
		//�]�[���Ƃ̓����蔻��
		pZone->Collision(pos, oldpos, size);
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CPlayer::Draw()
{
	//���[�V�����L�����N�^�[�`�揈��
	CMotionCharacter::Draw();
}

//===========================================================================================================
// ��������
//===========================================================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	//�������𓮓I�m��
	CPlayer* pPlayer = NEW CPlayer();

	//�p�����[�^�ݒ�
	pPlayer->SetType(TYPE::PLAYER);//�I�u�W�F�N�g��ނ̐ݒ�
	pPlayer->SetPos(pos);//�����ʒu�ݒ�
	pPlayer->SetOldPos(pos);//�ߋ��̈ʒu

	//����������
	pPlayer->Init();

	return pPlayer;
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
bool CPlayer::Collision(D3DXVECTOR3& pos)
{
	//���[�J���ϐ��錾
	bool bCollision = false;//�����蔻��t���O
	D3DXVECTOR3 Pos = GetPos();//�ʒu���
	D3DXVECTOR3 size = GetSize();//�T�C�Y���

	//�͈͓��ɂ���ꍇ
	if (pos.x <= Pos.x + size.x * 0.5f && pos.x >= Pos.x - size.x * 0.5f
		&& pos.y <= Pos.y + size.y * 0.5f && pos.y >= Pos.y - size.y * 0.5f
		&& pos.z <= Pos.z + size.z * 0.5f && pos.z >= Pos.z - size.z * 0.5f)
	{
		//�����蔻��t���O��L���ɂ���
		bCollision = true;
	}

	return bCollision;
}
