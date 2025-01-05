//==============================================================================================================================================
//
// ���[�V�����Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "motion.h"//���[�V����

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CMotionCharacter::CMotionCharacter(int nPriority) : CObjectX(nPriority)
{
	//�����o�ϐ�������
	m_State = NEUTRAL;//���
	m_nParts = 0;//�p�[�c��
	m_nMotion = -1;//���[�V������
	m_fSpeed = 0.0f;//���x�{��

	//�p�[�c���
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_aParts[nCnt] = {};
	}
	//���[�V�������
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_aMotion[nCnt] = {};
	}
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CMotionCharacter::~CMotionCharacter()
{
}

//===========================================================================================================
// �������
//===========================================================================================================
void CMotionCharacter::Release()
{
	//�p�[�c����j��
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		m_aParts[nCnt] = {};
	}
	//���[�V��������j��
	for (int nCnt = 0; nCnt < m_nMotion; nCnt++)
	{
		m_aMotion[nCnt] = {};
	}

	//X�t�@�C���I�u�W�F�N�g�������
	CObjectX::Release();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CMotionCharacter::Update()
{
	//���[�J���ϐ��錾
	MOTION_STATE State = {};//���݂̏��
	int nKeySet = 0;//���݂̃L�[

	for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
	{
		//�㔼�g�p�[�c�̏ꍇ
		if (m_aParts[nCntParts].nHalf == UP_BODY)
		{
			//���݂̏�Ԃ�ۑ�
			State = m_State;
		}

		//�����g�p�[�c�̏ꍇ
		else if (m_aParts[nCntParts].nHalf == DOWN_BODY)
		{
			//�ΏۃI�u�W�F�N�g�̈ړ��ʏ��擾
			D3DXVECTOR3 move = GetMove();

			//�����Ă��Ȃ��ꍇ
			if ((move.x <= MAX_JUDGE_MOVE && move.x >= -MAX_JUDGE_MOVE) && (move.z <= MAX_JUDGE_MOVE && move.z >= -MAX_JUDGE_MOVE))
			{
				//���݂̏�Ԃ�ۑ�
				State = m_State;
			}
			//�����Ă���ꍇ
			else
			{
				//�ړ����
				State = MOVE;
			}
		}

		//���݂̃L�[��ۑ�
		nKeySet = m_aMotion[State].nCntKeySet;

		//���[�V��������
		Motion(State, nCntParts, nKeySet);
	}

	//�J�E���g���w��̃t���[�����ɂȂ����ꍇ
	if (m_aMotion[State].nCntFrame >= m_aMotion[State].aKeyset[nKeySet].nMaxFrame)
	{
		//�t���[�����J�E���g��������
		m_aMotion[State].nCntFrame = 0;

		//�L�[�������Z
		m_aMotion[State].nCntKeySet++;

		//�L�[�����ő吔�ɂȂ���
		if (m_aMotion[State].nCntKeySet > m_aMotion[State].nMaxKeySet)
		{
			//���[�v���Ȃ��ꍇ
			if (!(bool)m_aMotion[State].nLoop)
			{
				//�j���[�g�������
				m_State = NEUTRAL;
			}

			//�L�[����������
			m_aMotion[State].nCntKeySet = 0;
		}
	}

	//�t���[�����X�V
	m_aMotion[State].nCntFrame++;
}

//===========================================================================================================
// ���[�V��������
//===========================================================================================================
void CMotionCharacter::Motion(MOTION_STATE state, int nParts, int nKeySet)
{
	//���[�J���ϐ��錾
	int nNextKeySet = (nKeySet + 1) % (m_aMotion[state].nMaxKeySet + 1);//���̃L�[
	float fFrame = (float)m_aMotion[state].nCntFrame / m_aMotion[state].aKeyset[nKeySet].nMaxFrame;//���݂̃t���[���ƑS�̃t���[���̊���

	//============================
	// ���̃L�[�܂ł̍��������߂�
	//============================

	//����
	float fRotx = m_aMotion[state].aKeyset[nNextKeySet].aKey[nParts].rot.x - m_aMotion[state].aKeyset[nKeySet].aKey[nParts].rot.x;//X��
	float fRoty = m_aMotion[state].aKeyset[nNextKeySet].aKey[nParts].rot.y - m_aMotion[state].aKeyset[nKeySet].aKey[nParts].rot.y;//Y��
	float fRotz = m_aMotion[state].aKeyset[nNextKeySet].aKey[nParts].rot.z - m_aMotion[state].aKeyset[nKeySet].aKey[nParts].rot.z;//Z��

	//�ʒu
	float fPosx = m_aMotion[state].aKeyset[nNextKeySet].aKey[nParts].pos.x - m_aMotion[state].aKeyset[nKeySet].aKey[nParts].pos.x;//X���W
	float fPosy = m_aMotion[state].aKeyset[nNextKeySet].aKey[nParts].pos.y - m_aMotion[state].aKeyset[nKeySet].aKey[nParts].pos.y;//Y���W
	float fPosz = m_aMotion[state].aKeyset[nNextKeySet].aKey[nParts].pos.z - m_aMotion[state].aKeyset[nKeySet].aKey[nParts].pos.z;//Z���W

	//============================
	// ���̃L�[�𔽉f
	//============================

	//�������X�V
	m_aParts[nParts].rot.x = m_aMotion[state].aKeyset[nKeySet].aKey[nParts].rot.x + fRotx * fFrame;//X��
	m_aParts[nParts].rot.y = m_aMotion[state].aKeyset[nKeySet].aKey[nParts].rot.y + fRoty * fFrame;//Y��
	m_aParts[nParts].rot.z = m_aMotion[state].aKeyset[nKeySet].aKey[nParts].rot.z + fRotz * fFrame;//Z��

	//�ʒu���X�V
	m_aParts[nParts].pos.x = m_aParts[nParts].pos.x + m_aMotion[state].aKeyset[nKeySet].aKey[nParts].pos.x + fPosx * fFrame;//X���W
	m_aParts[nParts].pos.y = m_aParts[nParts].pos.y + m_aMotion[state].aKeyset[nKeySet].aKey[nParts].pos.y + fPosy * fFrame;//Y���W
	m_aParts[nParts].pos.z = m_aParts[nParts].pos.z + m_aMotion[state].aKeyset[nKeySet].aKey[nParts].pos.z + fPosz * fFrame;//Z���W
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CMotionCharacter::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���̃f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxWorld = GetMatrix();//���[���h�}�g���b�N�X���
	D3DXVECTOR3 pos = GetPos();//�ʒu
	D3DXVECTOR3 rot = GetRot();//����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
	{
		//�e�p�[�c���f���̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_aParts[nCntParts].mtxWorld);

		//�e�p�[�c���f���̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aParts[nCntParts].rot.y, m_aParts[nCntParts].rot.x, m_aParts[nCntParts].rot.z);
		D3DXMatrixMultiply(&m_aParts[nCntParts].mtxWorld, &m_aParts[nCntParts].mtxWorld, &mtxRot);

		//�e�p�[�c���f���̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_aParts[nCntParts].pos.x, m_aParts[nCntParts].pos.y, m_aParts[nCntParts].pos.z);
		D3DXMatrixMultiply(&m_aParts[nCntParts].mtxWorld, &m_aParts[nCntParts].mtxWorld, &mtxTrans);

		//�e�̔ԍ���ۑ�
		int nParent = m_aParts[nCntParts].nParent;

		//�e�̃}�g���b�N�X�𔽉f
		if (nParent != -1)
		{//�e�̔ԍ������ꍇ
			mtxParent = m_aParts[nParent].mtxWorld;//�e���f���̃}�g���b�N�X
		}
		else
		{//�e�̔ԍ��������Ȃ��ꍇ
			mtxParent = mtxWorld;//�L�����N�^�[���g�̃}�g���b�N�X
		}

		//�e�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_aParts[nCntParts].mtxWorld, &m_aParts[nCntParts].mtxWorld, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_aParts[nCntParts].mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_aParts[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aParts[nCntParts].dwNumMat; nCntMat++)
		{
			//�}�e���A�����𔽉f
			pMat[nCntMat].MatD3D.Diffuse = m_aParts[nCntParts].Diffuse[nCntMat];

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nullptr);

			//���f��(�p�[�c)�̕`��
			m_aParts[nCntParts].pMesh->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//===========================================================================================================
// �p�[�c�t�@�C���Ǎ�����
//===========================================================================================================
void CMotionCharacter::LoadParts(MOTION_TYPE type)
{
	//���[�J���ϐ��錾
	int nIndex = 0;//�e�p�[�c�ԍ�
	char aDataSearch[MAX_TEXT];//�f�[�^�ǂݍ��ݗp

	//�t�@�C�����J��
	FILE* pFile = fopen(PARTS_FILE[type], "r");

	//�t�@�C�����J���Ȃ��ꍇ
	if (pFile == nullptr)
	{
		//�������I��
		return;
	}

	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		//����
		int nResult = fscanf(pFile, "%s", aDataSearch);

		//END_PARTS�����������ꍇ
		if (nResult == EOF)
		{
			//�t�@�C�������
			fclose(pFile);

			//�����I��
			break;
		}
		//PARTS_FILENAME�����������ꍇ
		else if (!strcmp(aDataSearch, "PARTS_FILENAME"))
		{
			//�p�[�c�̃t�@�C�����𔽉f
			fscanf(pFile, "%s", &m_aParts[m_nParts].aPartsFile);

			//�p�[�c���J�E���g�����Z
			m_nParts++;
		}
		//MOVE�����������ꍇ
		else if (!strcmp(aDataSearch, "MOVE"))
		{
			//�v���C���[�̑��x�𔽉f
			fscanf(pFile, "%f", &m_fSpeed);
		}
		//PARTSSET�����������ꍇ
		else if (!strcmp(aDataSearch, "PARTSSET"))
		{
			//�e�p�[�c�̃f�[�^������
			while (1)
			{
				//����
				fscanf(pFile, "%s", aDataSearch);

				//END_PARTSSET�����������ꍇ
				if (!strcmp(aDataSearch, "END_PARTSSET"))
				{
					//�e�p�[�c���Ƃ̃f�[�^���������I��
					break;
				}
				//INDEX�����������ꍇ
				else if (!strcmp(aDataSearch, "INDEX"))
				{
					//�ԍ���ۑ�
					fscanf(pFile, "%d", &nIndex);

					//�p�[�c�̔ԍ����p�[�c���𒴂��Ă���ꍇ
					if (nIndex > m_nParts)
					{//�e�p�[�c���Ƃ̃f�[�^�������I��
						break;
					}

					//�ԍ��𔽉f
					fscanf(pFile, "%d", &m_aParts[nIndex].nIndex);
				}
				//PARENT�����������ꍇ
				else if (!strcmp(aDataSearch, "PARENT"))
				{
					//�e�̔ԍ��𔽉f
					fscanf(pFile, "%d", &m_aParts[nIndex].nParent);
				}
				//HALF�����������ꍇ
				else if (!strcmp(aDataSearch, "HALF"))
				{
					//�㔼�g�������g���̔���𔽉f
					fscanf(pFile, "%d", &m_aParts[nIndex].nHalf);
				}
				//POS�����������ꍇ
				else if (!strcmp(aDataSearch, "POS"))
				{
					//�ʒu�𔽉f
					fscanf(pFile, "%f", &m_aParts[nIndex].pos.x);
					fscanf(pFile, "%f", &m_aParts[nIndex].pos.y);
					fscanf(pFile, "%f", &m_aParts[nIndex].pos.z);
				}
				//ROT�����������ꍇ
				else if (!strcmp(aDataSearch, "ROT"))
				{
					//�����𔽉f
					fscanf(pFile, "%f", &m_aParts[nIndex].rot.x);
					fscanf(pFile, "%f", &m_aParts[nIndex].rot.y);
					fscanf(pFile, "%f", &m_aParts[nIndex].rot.z);
				}
				//��L�ȊO�����������ꍇ
				else
				{
					//���̍s���X�L�b�v���ēǂݍ��݂𑱂���
					continue;
				}
			}
		}
		//��L�ȊO�����������ꍇ
		else
		{
			//���̍s���X�L�b�v���ēǂݍ��݂𑱂���
			continue;
		}
	}

	//���f������
	CXfile* pModel = CManager::GetModel();
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		int nModelIdx = pModel->Regist(m_aParts[nCnt].aPartsFile);//�o�^
		BindModel(pModel->GetAddress(nModelIdx));//�ݒ�
		SetModelIdx(nModelIdx);//ID�ݒ�
		SetSize();//�T�C�Y�ݒ�

		//�p�[�c���f�����ݒ菈��
		SetPartsInfo(GetModelInfo(), nCnt);
	}
}

//===========================================================================================================
// �p�[�c���f�����ݒ菈��
//===========================================================================================================
void CMotionCharacter::SetPartsInfo(CXfile::CModel aModelInfo, int nParts)
{
	//�}�e���A����
	m_aParts[nParts].dwNumMat = aModelInfo.dwNumMat;

	//�}�e���A���ւ̃|�C���^
	m_aParts[nParts].pBuffMat = aModelInfo.pBuffMat;

	//���b�V���̒��_���ւ̃|�C���^
	m_aParts[nParts].pMesh = aModelInfo.pMesh;

	//�F
	for (int nCntMat = 0; nCntMat < (int)m_aParts[nParts].dwNumMat; nCntMat++)
	{
		m_aParts[nParts].Diffuse[nCntMat] = aModelInfo.Diffuse[nCntMat];
		m_aParts[nParts].FirstDiffuse[nCntMat] = m_aParts[nParts].Diffuse[nCntMat];
	}
}

//===========================================================================================================
// ���[�V�������Ǎ�����
//===========================================================================================================
void CMotionCharacter::LoadMotion(MOTION_TYPE type)
{
	//���[�J���ϐ��錾
	int nCntParts = 0;//�p�[�c��
	char aDataSearch[MAX_TEXT];//�f�[�^�����p

	//�t�@�C�����J��
	FILE* pFile = fopen(PARTS_FILE[type], "r");

	//�t�@�C�����J���Ȃ��ꍇ
	if (pFile == nullptr)
	{
		//�ǂݍ��ݏ������I��
		return;
	}

	//EOF��������܂Ō������J��Ԃ�
	while (1)
	{
		//����
		int nResult = fscanf(pFile, "%s", aDataSearch);//�������ʂ�int�^�ɑ��

		//MOTIONSET�����������ꍇ
		if (!strcmp(aDataSearch, "MOTIONSET"))
		{
			//���[�V���������J�E���g
			m_nMotion++;
			m_aMotion[m_nMotion].nMaxKeySet = -1;

			//�e���[�V�����̃f�[�^������
			while (1)
			{
				//����
				fscanf(pFile, "%s", aDataSearch);

				//END_MOTIONSET�����������ꍇ
				if (!strcmp(aDataSearch, "END_MOTIONSET"))
				{
					//���[�V�����ǂݍ��ݏI��
					break;
				}

				//LOOP�����������ꍇ
				if (!strcmp(aDataSearch, "LOOP"))
				{
					//���[�v������擾
					fscanf(pFile, "%d", &m_aMotion[m_nMotion].nLoop);
				}

				//KEYSET�����������ꍇ
				if (!strcmp(aDataSearch, "KEYSET"))
				{
					//���v�L�[�������Z
					m_aMotion[m_nMotion].nMaxKeySet++;
					
					//�e�L�[�Z�b�g�̃f�[�^������
					while (1)
					{
						//����
						fscanf(pFile, "%s", aDataSearch);

						//KEY�����������ꍇ
						if (!strcmp(aDataSearch, "KEY"))
						{
							//�e�L�[�̃f�[�^������
							while (1)
							{
								//����
								fscanf(pFile, "%s", aDataSearch);

								//FRAME�����������ꍇ
								if (!strcmp(aDataSearch, "FRAME"))
								{
									//�t���[������ǂݍ���
									fscanf(pFile, "%d", &m_aMotion[m_nMotion].aKeyset[m_aMotion[m_nMotion].nMaxKeySet].nMaxFrame);
								}
								//POS�����������ꍇ
								else if (!strcmp(aDataSearch, "POS"))
								{
									//�ʒu����ǂݍ���
									fscanf(pFile, "%f", &m_aMotion[m_nMotion].aKeyset[m_aMotion[m_nMotion].nMaxKeySet].aKey[nCntParts].pos.x);	//X���W
									fscanf(pFile, "%f", &m_aMotion[m_nMotion].aKeyset[m_aMotion[m_nMotion].nMaxKeySet].aKey[nCntParts].pos.y);	//Y���W
									fscanf(pFile, "%f", &m_aMotion[m_nMotion].aKeyset[m_aMotion[m_nMotion].nMaxKeySet].aKey[nCntParts].pos.z);	//Z���W
								}
								//ROT�����������ꍇ
								else if (!strcmp(aDataSearch, "ROT"))
								{
									//��������ǂݍ���
									fscanf(pFile, "%f", &m_aMotion[m_nMotion].aKeyset[m_aMotion[m_nMotion].nMaxKeySet].aKey[nCntParts].rot.x);	//X��
									fscanf(pFile, "%f", &m_aMotion[m_nMotion].aKeyset[m_aMotion[m_nMotion].nMaxKeySet].aKey[nCntParts].rot.y);	//Y��
									fscanf(pFile, "%f", &m_aMotion[m_nMotion].aKeyset[m_aMotion[m_nMotion].nMaxKeySet].aKey[nCntParts].rot.z);	//Z��
								}
								//END_KEY�Z�b�g�����������ꍇ
								else if (!strcmp(aDataSearch, "END_KEY"))
								{
									//�p�[�c�������Z
									nCntParts++;

									//���[�V�����f�[�^�̓ǂݍ��݂��I��
									break;
								}
							}
						}
						//END_KEYSET�����������ꍇ
						else if (!strcmp(aDataSearch, "END_KEYSET"))
						{
							//�p�[�c���J�E���g�����Z�b�g
							nCntParts = 0;

							//�e�L�[�Z�b�g�̃f�[�^�̌������I������
							break;
						}
						//��L�ȊO�����������ꍇ
						else
						{
							//�X�L�b�v���ēǂݍ��݂𑱂���
							continue;
						}
					}
				}
				//��L�ȊO�����������ꍇ
				else
				{
					//�X�L�b�v���ēǂݍ��݂𑱂���
					continue;
				}
			}
		}
		//EOF�����������ꍇ
		else if (nResult == EOF)
		{
			//�t�@�C�������
			fclose(pFile);
			break;
		}
		//��L�ȊO�����������ꍇ
		else
		{
			//�����𑱂���
			continue;
		}
	}
}

//===========================================================================================================
// �p�[�c�̃J���[�ݒ菈��
//===========================================================================================================
void CMotionCharacter::SetPartsFlash(float a)
{
	//�p�[�c�����ݒ�
	for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
	{
		//�e�p�[�c�Ɏw�肳�ꂽ�J���[����ݒ�
		for (int nCntMat = 0; nCntMat < (int)m_aParts[nCntParts].dwNumMat; nCntMat++)
		{
			m_aParts[nCntParts].Diffuse[nCntMat].a = a;
		}
	}
}

//===========================================================================================================
// //�S�p�[�c�����킹���T�C�Y�ݒ菈��
//===========================================================================================================
void CMotionCharacter::SetAllPartsSize()
{
	//���[�J���ϐ��錾
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 size = { 0.0f, 0.0f, 0.0f };//���߂�ꂽ�T�C�Y
	D3DXVECTOR3 vtxMin = { 0.0f, 0.0f, 0.0f };//�e���W�̍ŏ��̒l
	D3DXVECTOR3 vtxMax = { 0.0f, 0.0f, 0.0f };//�e���W�̍ő�̒l

	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		//���_���̎擾
		int nNumVtx = m_aParts[nCnt].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		DWORD sizeFVF = D3DXGetFVFVertexSize(m_aParts[nCnt].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		m_aParts[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nIdxVtx = 0; nIdxVtx < nNumVtx; nIdxVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���f���̍ŏ��l�ƍő�l���擾
			if (vtx.x < vtxMin.x)
			{//X���W�̍ŏ��l
				vtxMin.x = vtx.x;
			}
			if (vtx.y < vtxMin.y)
			{//Y���W�̍ŏ��l
				vtxMin.y = vtx.y;
			}
			if (vtx.z < vtxMin.z)
			{//Z���W�̍ŏ��l
				vtxMin.z = vtx.z;
			}
			if (vtx.x > vtxMax.x)
			{//X���W�̍ő�l
				vtxMax.x = vtx.x;
			}
			if (vtx.y > vtxMax.y)
			{//Y���W�̍ő�l
				vtxMax.y = vtx.y;
			}
			if (vtx.z > vtxMax.z)
			{//Z���W�̍ő�l
				vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		m_aParts[nCnt].pMesh->UnlockVertexBuffer();
	}

	//�T�C�Y�����߂�
	size =
	{
		vtxMax.x - vtxMin.x,//x��
		vtxMax.y - vtxMin.y,//y��
		vtxMax.z - vtxMin.z//z��
	};

	//�T�C�Y����ݒ�
	SetUpdateSize(size);
}
