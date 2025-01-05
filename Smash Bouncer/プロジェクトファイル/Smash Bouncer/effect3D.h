#pragma once
//==============================================================================================================================================
//
// 3D�G�t�F�N�g�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _EFFECT3D_H_ //���̃}�N����`������Ȃ�������
#define _EFFECT3D_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "object3D.h"//3D�I�u�W�F�N�g

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CEffect3D : public CObject3D
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//�^�C�v
	typedef enum
	{
		NONE = 0,
		EFFECT_3D_TARGET,//�^�[�Q�b�g
		EFFECT_3D_SHOCKWAVE,//�Ռ��g
		EFFECT_3D_PILLAR,//��
		EFFECT_3D_MAX
	}EFFECT_3D_TYPE;

	//======================================
	// �֐�
	//======================================
	CEffect3D(int nPriority);//�R���X�g���N�^
	~CEffect3D() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Release() override;//�������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CEffect3D* Create(EFFECT_3D_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//��������

private:
	//======================================
	// �֐�
	//======================================

	//���̐ݒ菈��
	void SetEffect3DType(EFFECT_3D_TYPE type) { m_type = type; }//3D�G�t�F�N�g�^�C�v
	
	//======================================
	// �ϐ�
	//======================================
	static constexpr const char* TEXTURE_FILE[EFFECT_3D_MAX] =
	{
		"",
		"data/TEXTURE/EFFECT/Target000.png",//�^�[�Q�b�g
		"data/TEXTURE/EFFECT/shockwave000.png",//�Ռ��g
		"data/TEXTURE/EFFECT/EffectPillar000.png",//��
	};//�e�N�X�`���t�@�C��

	EFFECT_3D_TYPE m_type;//�^�C�v
};

#endif