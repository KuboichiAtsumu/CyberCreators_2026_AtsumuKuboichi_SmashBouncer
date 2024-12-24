#pragma once
//==============================================================================================================================================
//
// PUSHに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _PUSH_H_ //このマクロ定義がされなかったら
#define _PUSH_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "object3D.h"//3Dオブジェクト

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CPush : public CObject3D
{
public:
	//======================================
	// 列挙型定義
	//======================================

	//状態
	typedef enum
	{
		STAND_BY,//待機中
		BLINKING,//点滅
	}STATE;

	//======================================
	// 関数
	//======================================
	CPush(int nPriority);//コンストラクタ
	~CPush() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CPush* Create();//生成処理

private:
	//======================================
	// 変数
	//======================================
	static constexpr const char* TEXTURE_FILE = "data/TEXTURE/Title/PushUI000.png";//テクスチャファイル
	const D3DXVECTOR3 POS = { 80.0f, 20.0f, -50.0f };//生成位置
	const D3DXVECTOR3 ROT = { 0.0f, 0.3f, 0.0f };//生成角度
	const D3DXVECTOR3 SIZE = { 200.0f, 0.0f, 50.0f };//生成サイズ
	const float STAND_SPEED = 0.02f;//待機中の点滅速度
	STATE m_state;//状態
	bool m_bLightUp;//ライトアップフラグ
};

#endif
