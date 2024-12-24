//==============================================================================================================================================
//
// �G�l�~�[�}�l�[�W���[�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "enemymanager.h"//�G�l�~�[�}�l�[�W���[

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CEnemyManager::CEnemyManager(int nPriority) : CObjectManager(nPriority)
{
	//�ÓI�����o�ϐ�������
	m_pTop = nullptr;//�擪�A�h���X
	m_pCur = nullptr;//�I�[�A�h���X
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CEnemyManager::~CEnemyManager()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CEnemyManager::Init()
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };//�ʒu
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };//����
	D3DXVECTOR3 scale = { 1.0f,1.0f,1.0f };//�g�嗦
	int nNumAll = 0;//����
	int nCategory = 0;//�J�e�S���[
	int nType = 0;//���
	const char* StageFile = "";//�X�e�[�W���t�@�C���p�X

	//�V�[���ɉ����ăt�@�C����ύX
	switch (CManager::GetScene()->GetMode())
	{
		//�`���[�g���A��
	case CScene::MODE_TUTORIAL:
		StageFile = CManager::TUTORIAL_STAGE;
		break;

		//�Q�[��
	case CScene::MODE_GAME:
		StageFile = CManager::GAME_STAGE;
		break;

	default:
		break;
	}

	//�t�@�C�����J��
	FILE* pFile = fopen(StageFile, "rb");

	//�I�u�W�F�N�g�f�[�^�̓ǂݍ���
	if (pFile != nullptr)
	{
		//�t�@�C���̓ǂݍ���
		fread(&nNumAll, sizeof(int), 1, pFile);

		for (int nCnt = 0; nCnt < nNumAll; nCnt++)
		{
			//�f�[�^�̎擾
			fread(&pos, sizeof(D3DXVECTOR3), 1, pFile);//�ʒu
			fread(&rot, sizeof(D3DXVECTOR3), 1, pFile);//����
			fread(&scale, sizeof(D3DXVECTOR3), 1, pFile);//�g�嗦
			fread(&nCategory, sizeof(int), 1, pFile);//�J�e�S���[
			fread(&nType, sizeof(int), 1, pFile);//���

			//�J�e�S���[���G�l�~�[�̏ꍇ
			if (nCategory == CXfile::ENEMY)
			{
				//�G�l�~�[�𐶐�
				CEnemy* pEnemy = CEnemy::Create(pos, rot, nType);
				
				//�擪�A�h���X�����݂��Ȃ��ꍇ
				if (m_pTop == nullptr)
				{
					//���������G�l�~�[����擪�A�h���X�ɑ��
					m_pTop = pEnemy;

					//�O�̃I�u�W�F�N�g����nullptr����
					pEnemy->SetPrevEnemy(nullptr);
				}

				//�擪�A�h���X�����݂���ꍇ
				else
				{
					//�擪�A�h���X���擾
					CEnemy* pAllEnemy = m_pTop;

					//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
					while (pAllEnemy != nullptr)
					{
						//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
						if (pAllEnemy->GetNextEnemy() == nullptr)
						{
							//���̃I�u�W�F�N�g���ɐ��������G�l�~�[����ۑ�
							pAllEnemy->SetNextEnemy(pEnemy);

							//���������G�l�~�[���̑O�̃I�u�W�F�N�g����ۑ�
							pEnemy->SetPrevEnemy(pAllEnemy);

							break;
						}

						//�I�u�W�F�N�g�������̏��ɕύX����
						pAllEnemy = pAllEnemy->GetNextEnemy();
					}
				}

				//���g�̎��̃I�u�W�F�N�g����nullptr����
				pEnemy->SetNextEnemy(nullptr);

				//�I�[�A�h���X����
				m_pCur = pEnemy;
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}

	//�I�u�W�F�N�g�}�l�[�W���[����������
	if (FAILED(CObjectManager::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CEnemyManager::Uninit()
{
	//�I�u�W�F�N�g�}�l�[�W���[�I������
	CObjectManager::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CEnemyManager::Update()
{
	//�擪�A�h���X���擾����
	CEnemy* pEnemy = m_pTop;

	//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
	while (pEnemy != nullptr)
	{
		//���̃I�u�W�F�N�g�����擾
		CEnemy* pNext = pEnemy->GetNextEnemy();

		//�폜�t���O��true�̏ꍇ
		if (pEnemy->GetDeleteFlag())
		{
			//�O�̃I�u�W�F�N�g�����擾
			CEnemy* pPrev = pEnemy->GetPrevEnemy();

			//�O�̃I�u�W�F�N�g��񂪑��݂���ꍇ
			if (pPrev != nullptr)
			{
				//���̃I�u�W�F�N�g�����q��
				pPrev->SetNextEnemy(pNext);
			}
			//�O�̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			else
			{
				//���̃I�u�W�F�N�g��񂪑��݂���ꍇ
				if (pNext != nullptr)
				{
					//���̃I�u�W�F�N�g���̑O�̃I�u�W�F�N�g����nullptr�ɐݒ�
					pNext->SetPrevEnemy(nullptr);
				}

				//�擪�A�h���X��ύX
				m_pTop = pNext;
			}

			//���̃I�u�W�F�N�g��񂪑��݂���ꍇ
			if (pNext != nullptr)
			{
				//�O�̃I�u�W�F�N�g�����q��
				pNext->SetPrevEnemy(pPrev);
			}
			//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			else
			{
				//�O�̃I�u�W�F�N�g��񂪑��݂���ꍇ
				if (pPrev != nullptr)
				{
					//�O�̃I�u�W�F�N�g���̎��̃I�u�W�F�N�g����nullptr�ɐݒ�
					pPrev->SetNextEnemy(nullptr);
				}

				//�I�[�A�h���X��ύX
				m_pCur = pPrev;
			}
		}

		//�I�u�W�F�N�g�������̏��ɕύX����
		pEnemy = pNext;
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CEnemyManager::Draw()
{
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
bool CEnemyManager::Collision(D3DXVECTOR3& pos, D3DXVECTOR3& size)
{
	//���[�J���ϐ��錾
	bool bCollsion = false;//�����蔻��t���O

	//�擪�A�h���X���擾����
	CEnemy* pEnemy = m_pTop;

	//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
	while (pEnemy != nullptr)
	{
		//���̃I�u�W�F�N�g�����擾
		CEnemy* pNext = pEnemy->GetNextEnemy();

		//�G�ɓ��������ꍇ
		if (!pEnemy->GetDeleteFlag() && pEnemy->Collision(pos, size))
		{
			//�q�b�g����
			pEnemy->Hit();

			//�����蔻��t���O��true�ɂ���
			bCollsion = true;
		}

		//�I�u�W�F�N�g�������̏��ɕύX����
		pEnemy = pNext;
	}

	return bCollsion;
}

//===========================================================================================================
// �o�^����
//===========================================================================================================
void CEnemyManager::Regist(CEnemy* pEnemy)
{
	//�擪�A�h���X�����݂��Ȃ��ꍇ
	if (m_pTop == nullptr)
	{
		//���������o���b�g����擪�A�h���X�ɑ��
		m_pTop = pEnemy;

		//�O�̃I�u�W�F�N�g����nullptr����
		m_pTop->SetPrevEnemy(nullptr);
	}

	//�擪�A�h���X�����݂���ꍇ
	else
	{
		//�擪�A�h���X���擾
		CEnemy* pAllEnemy = m_pTop;

		//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
		while (pAllEnemy != nullptr)
		{
			//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			if (pAllEnemy->GetNextEnemy() == nullptr)
			{
				//���̃I�u�W�F�N�g���ɐ��������o���b�g����ۑ�
				pAllEnemy->SetNextEnemy(pEnemy);

				//���������o���b�g���̑O�̃I�u�W�F�N�g����ۑ�
				pEnemy->SetPrevEnemy(pAllEnemy);

				break;
			}

			//�I�u�W�F�N�g�������̏��ɕύX����
			pAllEnemy = pAllEnemy->GetNextEnemy();
		}
	}

	//���g�̎��̃I�u�W�F�N�g����nullptr����
	pEnemy->SetNextEnemy(nullptr);

	//�I�[�A�h���X����
	m_pCur = pEnemy;
}
