//==============================================================================================================================================
//
// �u���b�N�Ǘ�
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "blockmanager.h"//�u���b�N�}�l�[�W���[

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CBlockManager::CBlockManager(int nPriority) : CObjectManager(nPriority)
{
	//�ÓI�����o�ϐ�������
	m_pTop = nullptr;//�擪�A�h���X
	m_pCur = nullptr;//�I�[�A�h���X
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CBlockManager::~CBlockManager()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CBlockManager::Init()
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
		//�^�C�g���A�`���[�g���A��
	case CScene::MODE_TITLE:
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

			//�J�e�S���[���u���b�N�̏ꍇ
			if (nCategory == CXfile::BLOCK)
			{
				//�u���b�N�𐶐�
				CBlock* pBlock = CBlock::Create(pos, rot, scale, nType);

				//�擪�A�h���X�����݂��Ȃ��ꍇ
				if (m_pTop == nullptr)
				{
					//���������u���b�N����擪�A�h���X�ɑ��
					m_pTop = pBlock;

					//�O�̃I�u�W�F�N�g����nullptr����
					pBlock->SetPrevBlock(nullptr);
				}

				//�擪�A�h���X�����݂���ꍇ
				else
				{
					//�擪�A�h���X���擾
					CBlock* pAllBlock = m_pTop;

					//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
					while (pAllBlock != nullptr)
					{
						//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
						if (pAllBlock->GetNextBlock() == nullptr)
						{
							//���̃I�u�W�F�N�g���ɐ��������u���b�N����ۑ�
							pAllBlock->SetNextBlock(pBlock);

							//���������u���b�N���̑O�̃I�u�W�F�N�g����ۑ�
							pBlock->SetPrevBlock(pAllBlock);

							break;
						}

						//�I�u�W�F�N�g�������̏��ɕύX����
						pAllBlock = pAllBlock->GetNextBlock();
					}
				}

				//���g�̎��̃I�u�W�F�N�g����nullptr����
				pBlock->SetNextBlock(nullptr);
				
				//�I�[�A�h���X����
				m_pCur = pBlock;
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
void CBlockManager::Uninit()
{
	//�I�u�W�F�N�g�}�l�[�W���[�I������
	CObjectManager::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CBlockManager::Update()
{
	//�擪�A�h���X���擾����
	CBlock* pBlock = m_pTop;

	//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
	while (pBlock != nullptr)
	{
		//���̃I�u�W�F�N�g�����擾
		CBlock* pNext = pBlock->GetNextBlock();

		//�u���b�N��񂪑��݂���ꍇ
		//�폜�t���O��true�̏ꍇ
		if (pBlock != nullptr && pBlock->GetDeleteFlag())
		{
			//�O�̃I�u�W�F�N�g�����擾
			CBlock* pPrev = pBlock->GetPrevBlock();

			//�O�̃I�u�W�F�N�g��񂪑��݂���ꍇ
			if (pPrev != nullptr)
			{
				//���̃I�u�W�F�N�g�����q��
				pPrev->SetNextBlock(pNext);
			}
			//�O�̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			else
			{
				//���̂̃I�u�W�F�N�g���̑O�̃I�u�W�F�N�g����nullptr�ɐݒ�
				pNext->SetPrevBlock(nullptr);

				//�擪�A�h���X��ύX
				m_pTop = pNext;
			}

			//���̃I�u�W�F�N�g��񂪑��݂���ꍇ
			if (pNext != nullptr)
			{
				//�O�̃I�u�W�F�N�g�����q��
				pNext->SetPrevBlock(pPrev);
			}
			//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			else
			{
				//�O�̃I�u�W�F�N�g���̎��̃I�u�W�F�N�g����nullptr�ɐݒ�
				pPrev->SetNextBlock(nullptr);

				//�I�[�A�h���X��ύX
				m_pCur = pPrev;
			}
		}

		//�I�u�W�F�N�g�������̏��ɕύX����
		pBlock = pNext;
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CBlockManager::Draw()
{
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
void CBlockManager::Collision(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& size)
{
	//�擪�A�h���X���擾����
	CBlock* pBlock = m_pTop;

	//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
	while (pBlock != nullptr)
	{
		//���̃I�u�W�F�N�g�����擾
		CBlock* pNext = pBlock->GetNextBlock();

		//�u���b�N��񂪑��݂���ꍇ
		if (pBlock != nullptr)
		{
			//�����蔻�菈��
			pBlock->Collision(pos, oldpos, size);
		}

		//�I�u�W�F�N�g�������̏��ɕύX����
		pBlock = pNext;
	}
}

//===========================================================================================================
// ���ˏ���
//===========================================================================================================
bool CBlockManager::Reflection(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& move, D3DXVECTOR3& rot, D3DXVECTOR3& size)
{
	//���[�J���ϐ��錾
	bool bReflect = false;//���˔���

	//�擪�A�h���X���擾����
	CBlock* pBlock = m_pTop;

	//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
	while (pBlock != nullptr)
	{
		//���̃I�u�W�F�N�g�����擾
		CBlock* pNext = pBlock->GetNextBlock();

		//�u���b�N��񂪑��݂���ꍇ
		if (pBlock != nullptr)
		{
			//�����蔻�菈��
			bReflect = pBlock->Reflection(pos, oldpos, move, rot, size);
		}
	
		//���˔��肾�����ꍇ
		if (bReflect)
		{
			//���ˏ����𔲂���
			break;
		}

		//�I�u�W�F�N�g�������̏��ɕύX����
		pBlock = pNext;
	}

	//���˔����Ԃ�
	return bReflect;
}
