#pragma once
//==============================================================================================================================================
//
// ビルボードに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _BILLBOARD_H_ //このマクロ定義がされなかったら
#define _BILLBOARD_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "object3D.h"//メイン処理

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CBillboard : public CObject3D
{
public:
	//======================================
	// 列挙型定義
	//======================================

	//タイプ
	typedef enum
	{
		BILLBOARD_EXPLOSION,//爆発
		BILLBOARD_SCORE,//スコア
		BILLBOARD_MAX
	}BILLBOARD_TYPE;

	//======================================
	// 関数
	//======================================
	CBillboard(int nPriority = 3);//コンストラクタ
	~CBillboard() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBillboard* Create(BILLBOARD_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size);//生成処理
};

#endif