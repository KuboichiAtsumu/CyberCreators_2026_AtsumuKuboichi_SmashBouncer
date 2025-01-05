//==============================================================================================================================================
//
// 3D�G�f�B�^�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _EDIT3D_H_
#define _EDIT3D_H_

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "manager.h"
#include "objectx.h"

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CEdit3D : public CObjectX
{
public:
	//======================================
	// �֐�
	//======================================
	CEdit3D(int nPriority = 0);//�R���X�g���N�^
	~CEdit3D();//�f�X�g���N�^
	HRESULT Init();//����������
	static void UninitAll();//�S�I�u�W�F�N�g�������
	void Uninit();//�I������
	void Release();//�������
	void Update();//�X�V����
	static void EditUpdate();//�G�f�B�^���X�V����
	void Draw();//�`�揈��
	static CEdit3D* Create();//��������
	static void LoadInfo(const char* FileName);//���[�h����
	
	//======================================
	// �ϐ�
	//======================================
	static constexpr int MAX_EDIT3D = 1000;//�I�u�W�F�N�g�̍ő吔

private:
	//======================================
	// �񋓌^��`
	//======================================

	//���샂�[�h
	typedef enum
	{
		MODE_MOVE,//�ړ�
		MODE_SCALE,//�g��
	}EDIT_MODE;

	//======================================
	// �֐�
	//======================================
	static void Save();//�Z�[�u����
	static void SetCameraPos();//�J�����̐ݒ�
	void Move();//�ړ�����
	void Scale();//�g�又��
	
	//======================================
	// �ϐ�
	//======================================

	//�ÓI�����o�ϐ�
	static constexpr int TURN_DIRECTION = 8;//��]����������
	static constexpr float MOVE = 5.0f;//�ړ���
	static constexpr float SCALE = 0.1f;//�g���
	static constexpr float TURN = D3DX_PI * (1.0f / (float)TURN_DIRECTION);//��]��
	static CEdit3D* m_apEditObj[MAX_EDIT3D];//�I�u�W�F�N�g���
	static EDIT_MODE m_mode;//���샂�[�h
	static int m_nTarget;//�ҏW�Ώ۔ԍ�
	static int m_nNumAll;//���v�f�[�^��
	static bool m_bTrigger;//�ړ����@���g���K�[���ǂ���

	//�����o�ϐ�
	CXfile::CModel* m_apModel;//���f���̏��
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_rot;//����
	D3DXVECTOR3 m_Scale;//�g�嗦
	int m_nCategory;//�J�e�S���[
	int m_nType;//���
	int m_nID;//�e�I�u�W�F�N�g�̃A�h���X
	bool m_bUse;//�g�p���Ă��邩�ǂ���
};

#endif
