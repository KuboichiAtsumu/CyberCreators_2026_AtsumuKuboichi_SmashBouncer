//==============================================================================================================================================
//
// �I�u�W�F�N�g�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _OBJECT_H_ //���̃}�N����`������Ȃ�������
#define _OBJECT_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "manager.h"//�}�l�[�W���[

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CObject
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//���
	typedef enum
	{
		NONE = 0,
		EDIT,//�G�f�B�^�I�u�W�F�N�g
		PLAYER,//�v���C���[
		ENEMY,//�G
		BULLET,//�e
		BILLBOARD,//�r���{�[�h
		SCORE,//�X�R�A
		BLOCK,//�u���b�N
		ITEM,//�A�C�e��
		FIELD,//�t�B�[���h
		FADE,//�t�F�[�h
		ZONE,//�]�[��
		SHOTPOINT,//�|�C���g
		GIMMICK,//�M�~�b�N
		UI,//UI
		EFFECT,//�G�t�F�N�g
		MAX_OBJECT_TYPE
	}TYPE;

	//======================================
	// �֐�
	//======================================
	CObject(int nPriority = 3);//�R���X�g���N�^
	virtual ~CObject();//�f�X�g���N�^
	virtual HRESULT Init();//����������
	virtual void Uninit() = 0;//�I������
	virtual void Release();//�������
	virtual void Update() = 0;//�X�V����
	virtual void Draw() = 0;//�`�揈��
	static void UninitAll();//�S�I�u�W�F�N�g�I������
	static void ReleaseAll();//�S�I�u�W�F�N�g�������
	static void UpdateAll();//�S�I�u�W�F�N�g�X�V����
	static void DrawAll();//�S�I�u�W�F�N�g�`�揈��

	//���̐ݒ�
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtxBuff) { m_pVtxBuff = pVtxBuff; }//���_�o�b�t�@
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }//�e�N�X�`�����蓖��
	void SetType(TYPE type) { m_type = type; }//���
	void SetTextureIdx(int nIdx) { m_nTextureIdx = nIdx; }//�e�N�X�`���ԍ�
	void SetDeleteFlag(bool bDelete) { m_bDelete = bDelete; }//�폜�t���O

	//���̎擾
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return m_pVtxBuff; }//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }//�e�N�X�`�����
	TYPE GetType() { return m_type; }//���
	static CObject* GetTop(int nPriority) { return m_pTop[nPriority]; }//�擪�I�u�W�F�N�g
	CObject* GetNext() { return m_pNext; }//���̃I�u�W�F�N�g���
	bool GetDeleteFlag() { return m_bDelete; }//�폜�t���O

private:
	//======================================
	// �ϐ�
	//======================================
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`�����ւ̃|�C���^
	static CObject* m_pTop[MAX_PRIORITY];//�擪�I�u�W�F�N�g�̃|�C���^
	static CObject* m_pCur[MAX_PRIORITY];//�I�[�I�u�W�F�N�g�̃|�C���^
	CObject* m_pPrev;//�O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;//���̃I�u�W�F�N�g�̃|�C���^
	TYPE m_type;//���
	int m_nPriority;//�`��D��x��
	int m_nTextureIdx;//�e�N�X�`��ID
	bool m_bDelete;//�폜�t���O
};

#endif