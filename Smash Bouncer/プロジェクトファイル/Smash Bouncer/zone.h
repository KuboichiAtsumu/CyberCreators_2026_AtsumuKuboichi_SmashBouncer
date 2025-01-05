//==============================================================================================================================================
//
// �X�e�[�W�ʃ]�[���Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _STAGEZONE_H_ //���̃}�N����`������Ȃ�������
#define _STAGEZONE_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "object3D.h"

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CZone : public CObject3D
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//���
	typedef enum
	{
		STAGE,//�X�e�[�W�敪
		REFLECT,//���˃]�[��
		MAX_ZONE_TYPE
	}ZONETYPE;

	//======================================
	// �֐�
	//======================================
	CZone(int nPriority = 3);//�R���X�g���N�^
	~CZone() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CZone* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ZONETYPE type);//��������
	static void LoadZoneTexFile();//�e�]�[���^�C�v�̃e�N�X�`���t�@�C���Ǎ�����
	bool Judge(D3DXVECTOR3& pos);//�Ώۂ�����X�e�[�W�̔���
	void Collision(D3DXVECTOR3& pos, D3DXVECTOR3& oldpos, D3DXVECTOR3& size);//�����蔻��

	//���̎擾
	int GetID() { return m_nStageID; }//�X�e�[�WID
	ZONETYPE GetZoneType() { return m_ZoneType; }//�]�[���^�C�v
	
	//���̐ݒ�
	void SetCollisionFlag(bool bCollision) { m_bCollision = bCollision; }//�����蔻��̗L�����t���O

	//======================================
	// �ϐ�
	//======================================
	static constexpr float STAGEZONE_WIDTH = 400.0f;//�X�e�[�W�]�[���̉���
	static constexpr float STAGEZONE_HEIGHT = 260.0f;//�X�e�[�W�]�[���̏c��

	static constexpr float REFLECTZONE_WIDTH = 60.0f;//���˃]�[���̉���
	static constexpr float REFLECTZONE_HEIGHT = 260.0f;//���˃]�[���̏c��

private:
	//======================================
	// �֐�
	//======================================
	void SetZoneType(ZONETYPE type) { m_ZoneType = type; }//�]�[���^�C�v�ݒ�

	//======================================
	// �ϐ�
	//======================================
	static constexpr const char* TEXTURE_FILE = "data\\ZoneTexture.txt";//�e�N�X�`���p�X�ۑ��t�@�C��
	static char m_aTextureFile[MAX_ZONE_TYPE][CProcess::MAX_TEXT];//�e�^�C�v�̃e�N�X�`���t�@�C��
	ZONETYPE m_ZoneType;//�]�[���^�C�v
	static int m_nAllNumZone;//�]�[���̐�
	static int m_nNumZone[MAX_ZONE_TYPE];//�e�]�[���̐�
	int m_nStageID;//�e�]�[���̃X�e�[�WID
	bool m_bCollision;//�]�[���̓����蔻��̗L�����t���O
	bool m_bUse;//�g�p�t���O
};

#endif

