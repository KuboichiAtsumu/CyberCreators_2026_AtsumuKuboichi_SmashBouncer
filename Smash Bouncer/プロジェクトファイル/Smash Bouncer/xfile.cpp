//==============================================================================================================================================
//
// x�t�@�C���ꊇ�Ǘ��Ɋւ���Ǘ�
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "xfile.h"//x�t�@�C���ꊇ�Ǘ�
#include "manager.h"//�}�l�[�W���[
#include "renderer.h"//�����_���[
#include "objectX.h"//x�t�@�C���I�u�W�F�N�g

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
CXfile::CModel CXfile::m_apSaveModel[MAX_CATEGORY][MAX_NUM_OBJECT] = {};

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CXfile::CXfile()
{
	//�����o�ϐ�������
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		m_aModel[nCnt] = nullptr;//X�t�@�C���z��
		m_ModelFileName[nCnt] = nullptr;//�쐬�ς�X�t�@�C���ۊǔz��
	}

	//X�t�@�C������
	m_nAllModel = 0;
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CXfile::~CXfile()
{
}

//===========================================================================================================
// X�t�@�C���j��
//===========================================================================================================
void CXfile::Unload()
{
	//�����o�ϐ�������
	for (int nCnt = 0; nCnt < m_nAllModel; nCnt++)
	{
		if (m_aModel[nCnt] != nullptr)
		{
			m_aModel[nCnt]->Release();
			delete m_aModel[nCnt];
			m_aModel[nCnt] = nullptr;//X�t�@�C���z��
			m_ModelFileName[nCnt] = nullptr;//�쐬�ς�X�t�@�C���ۊǔz��
		}
	}

	m_nAllModel = 0;
}

//===========================================================================================================
// ���f���\���̃f�X�g���N�^
//===========================================================================================================
void CXfile::CModel::Release()
{
	//���b�V����񂪑��݂���ꍇ
	if (pMesh != nullptr)
	{
		//���b�V���������
		pMesh->Release();
		pMesh = nullptr;
	}

	//�}�e���A����񂪑��݂���ꍇ
	if (pBuffMat != nullptr)
	{
		//�}�e���A���������
		pBuffMat->Release();
		pBuffMat = nullptr;
	}

	//�F�����������Z�b�g
	for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
	{
		Diffuse[nCntMat] = {};
		FirstDiffuse[nCntMat] = {};
	}

	//�}�e���A���������Z�b�g
	dwNumMat = {};
}

//===========================================================================================================
// X�t�@�C���o�^
//===========================================================================================================
int CXfile::Regist(const char* pModelName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̎擾
	int nIdx = 0;//ID

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		nIdx = nCnt;//ID�ݒ�

		//��񂪑��݂��Ȃ��ꍇ
		if (m_aModel[nIdx] == nullptr)
		{
			//���ۑ��p
			m_aModel[nIdx] = NEW CModel();

			//���ۊ�
			strcpy(m_aModel[nIdx]->aModelFile, pModelName);

			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(m_aModel[nIdx]->aModelFile, D3DXMESH_SYSTEMMEM, pDevice, nullptr, &m_aModel[nIdx]->pBuffMat, nullptr, &m_aModel[nIdx]->dwNumMat, &m_aModel[nIdx]->pMesh);

			//�}�e���A����񂪑��݂���ꍇ
			if (m_aModel[nIdx]->pBuffMat != nullptr)
			{
				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_aModel[nIdx]->pBuffMat->GetBufferPointer();

				//�F��������ۑ�
				for (int nCntMat = 0; nCntMat < (int)m_aModel[nIdx]->dwNumMat; nCntMat++)
				{
					m_aModel[nIdx]->Diffuse[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
					m_aModel[nIdx]->FirstDiffuse[nCntMat] = m_aModel[nCnt]->Diffuse[nCntMat];
				}
			}

			//X�t�@�C���������Z
			m_nAllModel++;
			break;
		}

		//�t�@�C�������ɓo�^����Ă���ꍇ
		else if (strcmp(pModelName, m_aModel[nIdx]->aModelFile) == 0)
		{
			break;
		}
	}

	return nIdx;//ID��Ԃ�
}

//===========================================================================================================
// ���f���t�@�C���p�X�Ǎ�
//===========================================================================================================
void CXfile::LoadModelFile()
{
	//���[�J���ϐ��錾
	int nNumCategory = -1;//�J�e�S���[��
	int nNumFile = 0;//�^�C�v��
	char aDataSearch[CProcess::MAX_TEXT];//�t�@�C�������p

	//�t�@�C�����J��
	FILE* pFile = fopen(MODEL_FILE, "r");

	//�t�@�C�����J���Ȃ��ꍇ
	if (pFile == nullptr)
	{
		//�����𔲂���
		return;
	}

	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		//����
		int nResult = fscanf(pFile, "%s", aDataSearch);

		//EOF�����������ꍇ
		if (nResult == EOF)
		{//�ǂݍ��ݏI��
			fclose(pFile);
			break;
		}
		//FILE_SET�����������ꍇ
		else if (!strcmp(aDataSearch, "FILE_SET"))
		{
			//�J�e�S���[�������Z
			nNumCategory++;

			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				//����
				fscanf(pFile, "%s", aDataSearch);

				//END_FILE�����������ꍇ
				if (!strcmp(aDataSearch, "END_FILE"))
				{
					//�t�@�C���p�X�̓ǂݍ��݂��I��
					CObjectX::m_nNumType[nNumCategory] = nNumFile + 1;
					break;
				}
				//FILE�����������ꍇ
				else if (!strcmp(aDataSearch, "FILE"))
				{
					//�^�C�v��ǂݍ���
					fscanf(pFile, "%d", &nNumFile);

					//�t�@�C���p�X��ǂݍ���
					fscanf(pFile, "%s", &m_apSaveModel[nNumCategory][nNumFile].aModelFile);
				}
			}
		}
		//��L�ȊO�����������ꍇ
		else
		{
			//��΂��Č����𑱂���
			continue;
		}
	}
}

//===========================================================================================================
// �e�N�X�`���t�@�C���p�X�Ǎ�
//===========================================================================================================
void CXfile::LoadTextureFile()
{
	int nNumCategory = 0;
	int nNumFile = 0;
	char aDataSearch[CProcess::MAX_TEXT];

	//�t�@�C�����J��
	FILE* pFile = fopen(TEXTURE_FILE, "r");

	//�t�@�C�����J���Ȃ��ꍇ
	if (pFile == nullptr)
	{
		return;
	}

	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		int nResult = fscanf(pFile, "%s", aDataSearch);	//����

		//EOF�����������ꍇ
		if (nResult == EOF)
		{//�ǂݍ��ݏI��
			fclose(pFile);
			break;
		}
		//BLOCK�����������ꍇ
		else if (!strcmp(aDataSearch, "FILE_SET"))
		{
			//�J�e�S���[�ԍ���ǂݍ���
			fscanf(pFile, "%d", &nNumCategory);

			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				//����
				fscanf(pFile, "%s", aDataSearch);

				//END_BLOCK�����������ꍇ
				if (!strcmp(aDataSearch, "END_FILE"))
				{//�ǂݍ��݂��I��
					break;
				}
				//�f�[�^�̓ǂݍ���
				else if (!strcmp(aDataSearch, "FILE"))
				{//�t�@�C���p�X
					fscanf(pFile, "%d", &nNumFile);//�t�@�C���p�X�ԍ�
					fscanf(pFile, "%s", &m_apSaveModel[nNumCategory][nNumFile].aTextureFile);//�t�@�C���p�X
				}
			}
		}
		//��L�ȊO�����������ꍇ
		else
		{
			continue;
		}
	}
}

//===========================================================================================================
// �o�^����
//===========================================================================================================
void CXfile::Regist()
{
	//���[�J���ϐ��錾
	CTexture* pTex = CManager::GetTexture();
	CXfile* pModel = CManager::GetModel();
	int nTextureIdx = 0;//�e�N�X�`���ԍ�
	int nModelIdx = 0;//���f���ԍ�

	//�o�^
	for (int nCntCategory = 0; nCntCategory < MAX_CATEGORY; nCntCategory++)
	{
		for (int nCntType = 0; nCntType < CObjectX::m_nNumType[nCntCategory] + 1; nCntType++)
		{
			//���f��
			nModelIdx = pModel->Regist(m_apSaveModel[nCntCategory][nCntType].aModelFile);
			BindModel(nCntCategory, nCntType, pModel->GetAddress(nModelIdx));

			//�e�N�X�`��
			nTextureIdx = pTex->Regist(m_apSaveModel[nCntCategory][nCntType].aTextureFile);
			BindTexture(nCntCategory, nCntType, pTex->GetAddress(nTextureIdx));
		}
	}
}

//===========================================================================================================
// ���f�����ݒ菈��
//===========================================================================================================
void CXfile::BindModel(int nCategory, int nType, CXfile::CModel* aModelInfo)
{
	strcpy(m_apSaveModel[nCategory][nType].aModelFile, aModelInfo->aModelFile);//�t�@�C���p�X
	m_apSaveModel[nCategory][nType].pMesh = aModelInfo->pMesh;//���b�V�����
	m_apSaveModel[nCategory][nType].pBuffMat = aModelInfo->pBuffMat;//�}�e���A�����
	m_apSaveModel[nCategory][nType].dwNumMat = aModelInfo->dwNumMat;//�}�e���A����

	//�F����
	for (int nCntMat = 0; nCntMat < (int)m_apSaveModel[nCategory][nType].dwNumMat; nCntMat++)
	{
		m_apSaveModel[nCategory][nType].Diffuse[nCntMat] = aModelInfo->Diffuse[nCntMat];
		m_apSaveModel[nCategory][nType].FirstDiffuse[nCntMat] = m_apSaveModel[nCategory][nType].Diffuse[nCntMat];
	}
}