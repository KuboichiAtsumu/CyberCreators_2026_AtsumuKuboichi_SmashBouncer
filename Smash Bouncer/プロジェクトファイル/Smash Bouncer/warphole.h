#pragma once
//==============================================================================================================================================
//
// ワープホールに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _WARPHOLE_H_
#define _WARPHOLE_H_

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "gimmick.h"//ギミックヘッダー

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CWarpHole : public CGimmick
{
public:
	//======================================
	// 関数
	//======================================
	CWarpHole(int nPriority);//コンストラクタ
	~CWarpHole() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	bool Collision(D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXVECTOR3 size, D3DXVECTOR3& rot) override;//当たり判定

private:
	//======================================
	// 関数
	//======================================
	void Warp(D3DXVECTOR3& pos);//ワープ処理

	//======================================
	// 変数
	//======================================
	static int m_nCntUseWarp;//使用不可のカウント
	bool m_bUseWarp;//使用フラグ
};

#endif
