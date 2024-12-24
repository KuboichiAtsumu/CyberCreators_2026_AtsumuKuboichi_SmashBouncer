//==============================================================================================================================================
//
// �A�C�e���}�l�[�W���[�̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "itemmanager.h"//�A�C�e���}�l�[�W���[

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CItemManager::CItemManager(int nPriority) : CObjectManager(nPriority)
{
	//�ÓI�����o�ϐ�������
	m_pTop = nullptr;//�擪�A�h���X
	m_pCur = nullptr;//�I�[�A�h���X
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CItemManager::~CItemManager()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CItemManager::Init()
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

			//�J�e�S���[���u���b�N�̏ꍇ
			if (nCategory == CXfile::ITEM)
			{
				//�u���b�N�𐶐�
				CItem* pItem = CItem::Create(pos, rot, nType);
				
				//�擪�A�h���X�����݂��Ȃ��ꍇ
				if (m_pTop == nullptr)
				{
					//���������G�l�~�[����擪�A�h���X�ɑ��
					m_pTop = pItem;

					//�O�̃I�u�W�F�N�g����nullptr����
					pItem->SetPrevItem(nullptr);
				}

				//�擪�A�h���X�����݂���ꍇ
				else
				{
					//�擪�A�h���X���擾
					CItem* pAllItem = m_pTop;

					//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
					while (pAllItem != nullptr)
					{
						//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
						if (pAllItem->GetNextItem() == nullptr)
						{
							//���̃I�u�W�F�N�g���ɐ��������G�l�~�[����ۑ�
							pAllItem->SetNextItem(pItem);

							//���������G�l�~�[���̑O�̃I�u�W�F�N�g����ۑ�
							pItem->SetPrevItem(pAllItem);

							break;
						}

						//�I�u�W�F�N�g�������̏��ɕύX����
						pAllItem = pAllItem->GetNextItem();
					}
				}

				//���g�̎��̃I�u�W�F�N�g����nullptr����
				pItem->SetNextItem(nullptr);

				//�I�[�A�h���X����
				m_pCur = pItem;
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
void CItemManager::Uninit()
{
	//�I�u�W�F�N�g�}�l�[�W���[�I������
	CObjectManager::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CItemManager::Update()
{
	//�擪�A�h���X���擾����
	CItem* pItem = m_pTop;

	//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
	while (pItem != nullptr)
	{
		//���̃I�u�W�F�N�g�����擾
		CItem* pNext = pItem->GetNextItem();

		//�폜�t���O��true�̏ꍇ
		if (pItem->GetDeleteFlag())
		{
			//�O�̃I�u�W�F�N�g�����擾
			CItem* pPrev = pItem->GetPrevItem();

			//�O�̃I�u�W�F�N�g��񂪑��݂���ꍇ
			if (pPrev != nullptr)
			{
				//���̃I�u�W�F�N�g�����q��
				pPrev->SetNextItem(pNext);
			}
			//�O�̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			else
			{
				//���̂̃I�u�W�F�N�g���̑O�̃I�u�W�F�N�g����nullptr�ɐݒ�
				pNext->SetPrevItem(nullptr);

				//�擪�A�h���X��ύX
				m_pTop = pNext;
			}

			//���̃I�u�W�F�N�g��񂪑��݂���ꍇ
			if (pNext != nullptr)
			{
				//�O�̃I�u�W�F�N�g�����q��
				pNext->SetPrevItem(pPrev);
			}
			//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			else
			{
				//�O�̃I�u�W�F�N�g���̎��̃I�u�W�F�N�g����nullptr�ɐݒ�
				pPrev->SetNextItem(nullptr);

				//�I�[�A�h���X��ύX
				m_pCur = pPrev;
			}
		}

		//�I�u�W�F�N�g�������̏��ɕύX����
		pItem = pNext;
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CItemManager::Draw()
{
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
void CItemManager::Collision(D3DXVECTOR3& pos, D3DXVECTOR3 size, int& nLife)
{
	//�擪�A�h���X���擾����
	CItem* pItem = m_pTop;

	//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
	while (pItem != nullptr)
	{
		//���̃I�u�W�F�N�g�����擾
		CItem* pNext = pItem->GetNextItem();

		//�����蔻��
		pItem->Collision(pos, size, nLife);

		//�I�u�W�F�N�g�������̏��ɕύX����
		pItem = pNext;
	}
}
