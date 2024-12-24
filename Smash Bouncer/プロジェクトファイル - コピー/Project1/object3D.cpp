//==============================================================================================================================================
//
// 3D�I�u�W�F�N�g�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "object3D.h"//3D�I�u�W�F�N�g
#include "zone.h"//�]�[��

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
int CObject3D::m_nAllEachStageID[CGame::MAX_STAGE][MAX_OBJECT_TYPE]{};//�e�X�e�[�W�̊e�I�u�W�F�N�g�̍��v��

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	//�����o�ϐ�������
	m_pos = { 0.0f, 0.0f, 0.0f };//�ʒu
	m_move = { 0.0f, 0.0f, 0.0f };//�ړ���
	m_rot = { 0.0f, 0.0f, 0.0f };//����
	m_size = { 0.0f, 0.0f, 0.0f };//�T�C�Y
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�F
	m_nLife = 0;//����
	m_nPostStageID = 0;//�ΏۃI�u�W�F�N�g������X�e�[�W��ID
	m_nEachStageID = 0;//�ΏۃI�u�W�F�N�g������X�e�[�W�̃I�u�W�F�N�gID
	m_nDivisionWidth = 1;//���̃e�N�X�`��������
	m_nDivisionHeight = 1;//�c�̃e�N�X�`��������
	m_nDelayAnim = 1;//�A�j���[�V�����x��
	m_nPatternAnimWidth = 1;//���̃A�j���[�V�����p�^�[��
	m_nPatternAnimHeight = 1;//�c�̃A�j���[�V�����p�^�[��
	m_nCounterAnim = 0;//�A�j���[�V�����J�E���^
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CObject3D::~CObject3D()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CObject3D::Init()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * CProcess::MAX_VER,
		D3DUSAGE_WRITEONLY,
		CProcess::FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	//���_�o�b�t�@�̐ݒ�
	SetVtxBuff(pVtxBuff);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / (float)m_nDivisionWidth, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / (float)m_nDivisionHeight);
	pVtx[3].tex = D3DXVECTOR2(1.0f / (float)m_nDivisionWidth, 1.0f / (float)m_nDivisionHeight);

	for (int nCntVer = 0; nCntVer < CProcess::MAX_VER; nCntVer++)
	{
		//�@���x�N�g���̐ݒ�
		pVtx[nCntVer].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCntVer].col = m_col;
	}

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	//�I�u�W�F�N�g�̏���������
	if (FAILED(CObject::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CObject3D::Uninit()
{
	//�폜�t���O��true�ɐݒ�
	SetDeleteFlag(true);
}

//===========================================================================================================
// �������
//===========================================================================================================
void CObject3D::Release()
{
	//�Y���X�e�[�W�̊Y���^�C�v�̃I�u�W�F�N�g���������Z
	m_nAllEachStageID[m_nPostStageID][GetType()]--;

	//�I�u�W�F�N�g�������
	CObject::Release();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CObject3D::Update()
{
	//���[�J���ϐ��錾
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);

	for (int nCntVer = 0; nCntVer < CProcess::MAX_VER; nCntVer++)
	{
		//���_�J���[�̐ݒ�
		pVtx[nCntVer].col = m_col;
	}

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//===========================================================================================================
// �A�j���[�V��������
//===========================================================================================================
void CObject3D::UpdateAnim()
{
	//���[�J���ϐ��錾
	VERTEX_3D* pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�A�j���[�V�����J�E���^�����Z
	m_nCounterAnim++;

	//�e�N�X�`���X�V����
	if (m_nCounterAnim % m_nDelayAnim == 0)
	{
		//���̃A�j���[�V�����p�^�[�������Z
		m_nPatternAnimWidth++;

		//���̃e�N�X�`���p�^�[�����ő�܂ŒB�����ꍇ
		if (m_nPatternAnimWidth > m_nDivisionWidth)
		{
			//���̃A�j���[�V�����p�^�[�������Z�b�g
			m_nPatternAnimWidth = 1;

			//�c�̃A�j���[�V�����p�^�[�������Z
			m_nPatternAnimHeight++;

			//�c�̃A�j���[�V����
			if (m_nPatternAnimHeight > m_nDivisionHeight)
			{
				//�c�̃A�j���[�V�����p�^�[�������Z�b�g
				m_nPatternAnimHeight = 1;
			}
		}

		//�e�N�X�`�����W���ړ�
		pVtx[0].tex.x = 1.0f / (float)(m_nDivisionWidth) * (float)(m_nPatternAnimWidth - 1);
		pVtx[1].tex.x = 1.0f / (float)(m_nDivisionWidth) * (float)m_nPatternAnimWidth;
		pVtx[2].tex.x = 1.0f / (float)(m_nDivisionWidth) * (float)(m_nPatternAnimWidth - 1);
		pVtx[3].tex.x = 1.0f / (float)(m_nDivisionWidth) * (float)m_nPatternAnimWidth;

		pVtx[0].tex.y = 1.0f / (float)(m_nDivisionHeight) * (float)(m_nPatternAnimHeight - 1);
		pVtx[1].tex.y = 1.0f / (float)(m_nDivisionHeight) * (float)(m_nPatternAnimHeight - 1);
		pVtx[2].tex.y = 1.0f / (float)(m_nDivisionHeight) * (float)m_nPatternAnimHeight;
		pVtx[3].tex.y = 1.0f / (float)(m_nDivisionHeight) * (float)m_nPatternAnimHeight;

		//�A�j���[�V�����J�E���^�����Z�b�g
		m_nCounterAnim = 0;
	}

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CObject3D::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();//�e�N�X�`�����ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CProcess::FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===========================================================================================================
// ����������X�e�[�WID�̓o�^����
//===========================================================================================================
void CObject3D::SetPostStageID()
{
	//�w�肵�����ԂɃI�u�W�F�N�g�����擾����
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		//�擪�̃I�u�W�F�N�g�����擾
		CObject* pObj = CObject::GetTop(nCnt);

		//�I�u�W�F�N�g���nullptr�ɂȂ�܂ŌJ��Ԃ�
		while (pObj != nullptr)
		{
			//���̃I�u�W�F�N�g�����擾
			CObject* pNext = pObj->GetNext();

			//�I�u�W�F�N�g�^�C�v���]�[���̏ꍇ
			if (pObj->GetType() == CObject::ZONE)
			{
				//�I�u�W�F�N�g�����G�l�~�[���ɕϊ�
				CZone* pZone = (CZone*)pObj;

				//�ʒu�����擾
				D3DXVECTOR3 pos = GetPos();

				//�͈͓��������ꍇ
				if (pZone->Judge(pos) && pZone->GetZoneType() == CZone::STAGE)
				{
					//�v���C���[������X�e�[�W�̔ԍ���ۑ�����
					m_nPostStageID = pZone->GetID();

					//�Y���X�e�[�W�̊Y���I�u�W�F�N�gID��ݒ�
					m_nEachStageID = m_nAllEachStageID[m_nPostStageID][GetType()];

					//�Y���X�e�[�W�̊Y���I�u�W�F�N�g�̍��v�������Z
					m_nAllEachStageID[m_nPostStageID][GetType()]++;
				}
			}

			//�I�u�W�F�N�g�������̏��ɕύX����
			pObj = pNext;
		}
	}
}
