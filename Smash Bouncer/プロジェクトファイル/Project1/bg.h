#pragma once
//==============================================================================================================================================
//
// シーン背景に関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _BG_H_ //このマクロ定義がされなかったら
#define _BG_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "object2D.h"//2Dオブジェクト

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CBg : public CObject2D
{
public:
	//======================================
	// 列挙型定義
	//======================================

	//タイプ
	typedef enum
	{
		BG_TITLE,//タイトル
		BG_RESULT,//リザルト
		BG_MAX
	}BG_TYPE;

	//======================================
	// 関数
	//======================================
	CBg(int nPriority = 0);//コンストラクタ
	~CBg() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBg* Create(BG_TYPE type);//生成処理

	//パラメータ設定
	void SetBGType(BG_TYPE type) { m_type = type; }

private:
	//======================================
	// 変数
	//======================================
	static constexpr const char* BG_TEXTURE[BG_MAX] =
	{
		"data/TEXTURE/Title/TitleBG000.png",
		"data/TEXTURE/Result/ResultBG001.png",
	};//タイプごとのテクスチャファイル

	BG_TYPE m_type;//タイプ
};

#endif
