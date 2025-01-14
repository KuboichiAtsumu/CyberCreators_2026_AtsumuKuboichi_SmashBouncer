#pragma once
//==============================================================================================================================================
//
// ゲームUIに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _GAMEUI_H_ //このマクロ定義がされなかったら
#define _GAMEUI_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "object2D.h"//2Dオブジェクト

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CGameUI : public CObject2D
{
public:
	//======================================
	// 列挙型定義
	//======================================

	//タイプ
	typedef enum
	{
		UI_ATTENTION,//警告
		UI_STAGE,//ステージ
		UI_ALLSTAGE,//全ステージ数
		UI_MAX
	}UI_TYPE;

	//======================================
	// 関数
	//======================================
	CGameUI(int nPriority);//コンストラクタ
	~CGameUI() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CGameUI* Create(UI_TYPE type, D3DXVECTOR2 pos, D3DXVECTOR2 size);//生成処理

private:
	//======================================
	// 関数
	//======================================
	void SetUIType(UI_TYPE type) { m_type = type; }//UIタイプ設定

	//======================================
	// 変数
	//======================================
	static constexpr const char* TEXTURE_FILE[UI_MAX] = 
	{
		"data/TEXTURE/Game/attention000.png",
		"data/TEXTURE/Game/Stage000.png",
		"data/TEXTURE/Game/Stage001.png",
	};//テクスチャファイル

	UI_TYPE m_type;//タイプ
};

#endif
