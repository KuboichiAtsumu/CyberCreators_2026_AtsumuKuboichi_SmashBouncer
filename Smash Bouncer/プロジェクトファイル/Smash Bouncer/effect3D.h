#pragma once
//==============================================================================================================================================
//
// 3Dエフェクトに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _EFFECT3D_H_ //このマクロ定義がされなかったら
#define _EFFECT3D_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "object3D.h"//3Dオブジェクト

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CEffect3D : public CObject3D
{
public:
	//======================================
	// 列挙型定義
	//======================================

	//タイプ
	typedef enum
	{
		NONE = 0,
		EFFECT_3D_TARGET,//ターゲット
		EFFECT_3D_SHOCKWAVE,//衝撃波
		EFFECT_3D_PILLAR,//柱
		EFFECT_3D_MAX
	}EFFECT_3D_TYPE;

	//======================================
	// 関数
	//======================================
	CEffect3D(int nPriority);//コンストラクタ
	~CEffect3D() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Release() override;//解放処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CEffect3D* Create(EFFECT_3D_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//生成処理

private:
	//======================================
	// 関数
	//======================================

	//情報の設定処理
	void SetEffect3DType(EFFECT_3D_TYPE type) { m_type = type; }//3Dエフェクトタイプ
	
	//======================================
	// 変数
	//======================================
	static constexpr const char* TEXTURE_FILE[EFFECT_3D_MAX] =
	{
		"",
		"data/TEXTURE/EFFECT/Target000.png",//ターゲット
		"data/TEXTURE/EFFECT/shockwave000.png",//衝撃波
		"data/TEXTURE/EFFECT/EffectPillar000.png",//柱
	};//テクスチャファイル

	EFFECT_3D_TYPE m_type;//タイプ
};

#endif