//==============================================================================================================================================
//
// x�t�@�C���Ɋւ���Ǘ��̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _XFILE_H_ //���̃}�N����`������Ȃ�������
#define _XFILE_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "main.h"

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CXfile
{
public:
	//======================================
	// �ϐ�
	//======================================
	static const int MAX_MAT = 100;//�}�e���A���ő吔
	static constexpr int MAX_NUM_OBJECT = 100;//��ނ̍ő吔

	//======================================
	// �񋓌^��`
	//======================================
	struct CModel
	{
		//�֐�
		void Release();//�폜����

		//�ϐ�
		static const int MAX_MAT = 100;//�}�e���A���ő吔
		char aTextureFile[CProcess::MAX_TEXT];//�t�@�C���p�X
		char aModelFile[CProcess::MAX_TEXT];//�t�@�C���p�X
		LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���ւ̃|�C���^
		LPD3DXMESH pMesh;//���b�V�����
		LPD3DXBUFFER pBuffMat;//�}�e���A�����
		DWORD dwNumMat;//�}�e���A���̐�
		D3DCOLORVALUE Diffuse[MAX_MAT];//�F�������
		D3DCOLORVALUE FirstDiffuse[MAX_MAT];//�F������񏉊��l
	};

	//======================================
	// �J�e�S���[
	//======================================
	typedef enum
	{
		BLOCK,//�I�u�W�F�N�g
		ENEMY,//�G
		ITEM,//�A�C�e��
		POINT,//�|�C���g
		GIMMICK,//�M�~�b�N
		MAX_CATEGORY
	}CATEGORY;

	//======================================
	// �֐�
	//======================================
	CXfile();//�R���X�g���N�^
	~CXfile();//�f�X�g���N�^
	void Unload();//�e�N�X�`���j��
	int Regist(const char* pModelName);//���f���o�^
	static void BindModel(int nCategory, int nType, CXfile::CModel* aModelInfo);//���f����񊄂蓖��
	static void BindTexture(int nCategory, int nType, LPDIRECT3DTEXTURE9 pTexture) { m_apSaveModel[nCategory][nType].m_pTexture = pTexture; }//�e�N�X�`�����蓖��
	static void LoadModelFile();//���f���t�@�C���p�X�Ǎ�
	static void LoadTextureFile();//�e�N�X�`���t�@�C���p�X�Ǎ�
	static void Regist();//�o�^����
	static CModel* GetSaveModelInfo(int nCategory, int nType) { return &m_apSaveModel[nCategory][nType]; }//���f���ۑ����擾
	CModel* GetAddress(int nIdx) { return m_aModel[nIdx]; }//���f�����擾

private:
	//======================================
	// �ϐ�
	//======================================
	static constexpr const char* MODEL_FILE = "data/ModelFile.txt";//���f���p�X�ۑ��t�@�C��
	static constexpr const char* TEXTURE_FILE = "data/TextureFile.txt";//�e�N�X�`���p�X�ۑ��t�@�C��
	static const int MAX_MODEL = 1000;//���f�����ő吔
	static CModel m_apSaveModel[MAX_CATEGORY][MAX_NUM_OBJECT];//�ۑ��p���f�����
	const char* m_ModelFileName[MAX_MODEL];//�쐬�ς�X�t�@�C���p�X�ۊǗp
	CModel* m_aModel[MAX_MODEL];//���f�����
	int m_nAllModel = 0;//���f������
};

#endif
