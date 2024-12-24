//==============================================================================================================================================
//
// �|�C���g�Ǘ�
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "pointmanager.h"//�|�C���g�}�l�[�W���[

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CPointManager::CPointManager() : CObjectManager()
{
	//�ÓI�����o�ϐ�������
	m_pTop = nullptr;//�擪�A�h���X
	m_pCur = nullptr;//�I�[�A�h���X
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CPointManager::~CPointManager()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CPointManager::Init()
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
			if (nCategory == CXfile::POINT)
			{
				//�u���b�N�𐶐�
				CPoint* pPoint = CPoint::Create(pos, rot);

				//�擪�A�h���X�����݂��Ȃ��ꍇ
				if (m_pTop == nullptr)
				{
					//���������u���b�N����擪�A�h���X�ɑ��
					m_pTop = pPoint;

					//�O�̃I�u�W�F�N�g����nullptr����
					pPoint->SetPrevPoint(nullptr);
				}

				//�擪�A�h���X�����݂���ꍇ
				else
				{
					//�擪�A�h���X���擾
					CPoint* pAllPoint = m_pTop;

					//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
					while (pAllPoint != nullptr)
					{
						//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
						if (pAllPoint->GetNextPoint() == nullptr)
						{
							//���̃I�u�W�F�N�g���ɐ��������u���b�N����ۑ�
							pAllPoint->SetNextPoint(pPoint);

							//���������u���b�N���̑O�̃I�u�W�F�N�g����ۑ�
							pPoint->SetPrevPoint(pAllPoint);

							break;
						}

						//�I�u�W�F�N�g�������̏��ɕύX����
						pAllPoint = pAllPoint->GetNextPoint();
					}
				}

				//���g�̎��̃I�u�W�F�N�g����nullptr����
				pPoint->SetNextPoint(nullptr);

				//�I�[�A�h���X����
				m_pCur = pPoint;
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
void CPointManager::Uninit()
{
	//�I�u�W�F�N�g�}�l�[�W���[�I������
	CObjectManager::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CPointManager::Update()
{
	//�擪�A�h���X���擾����
	CPoint* pPoint = m_pTop;

	//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
	while (pPoint != nullptr)
	{
		//���̃I�u�W�F�N�g�����擾
		CPoint* pNext = pPoint->GetNextPoint();

		//�폜�t���O��true�̏ꍇ
		if (pPoint->GetDeleteFlag())
		{
			//�O�̃I�u�W�F�N�g�����擾
			CPoint* pPrev = pPoint->GetPrevPoint();

			//�O�̃I�u�W�F�N�g��񂪑��݂���ꍇ
			if (pPrev != nullptr)
			{
				//���̃I�u�W�F�N�g�����q��
				pPrev->SetNextPoint(pNext);
			}
			//�O�̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			else
			{
				//���̂̃I�u�W�F�N�g���̑O�̃I�u�W�F�N�g����nullptr�ɐݒ�
				pNext->SetPrevPoint(nullptr);

				//�擪�A�h���X��ύX
				m_pTop = pNext;
			}

			//���̃I�u�W�F�N�g��񂪑��݂���ꍇ
			if (pNext != nullptr)
			{
				//�O�̃I�u�W�F�N�g�����q��
				pNext->SetPrevPoint(pPrev);
			}
			//���̃I�u�W�F�N�g��񂪑��݂��Ȃ��ꍇ
			else
			{
				//�O�̃I�u�W�F�N�g���̎��̃I�u�W�F�N�g����nullptr�ɐݒ�
				pPrev->SetNextPoint(nullptr);

				//�I�[�A�h���X��ύX
				m_pCur = pPrev;
			}
		}

		//�I�u�W�F�N�g�������̏��ɕύX����
		pPoint = pNext;
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CPointManager::Draw()
{

}
