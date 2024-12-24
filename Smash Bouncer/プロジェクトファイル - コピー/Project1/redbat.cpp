//==============================================================================================================================================
//
// レッドバットの処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "redbat.h"//レッドバットヘッダー

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CRedBat::CRedBat(int nPriority) : CBat(nPriority)
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CRedBat::~CRedBat()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CRedBat::Init()
{
	//エネミー初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CRedBat::Uninit()
{
	//エネミー終了処理
	CEnemy::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CRedBat::Release()
{
	//エネミー解放処理
	CEnemy::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CRedBat::Update()
{
	//エディタモードの場合
	if (CManager::GetScene()->GetEditMode())
	{
		//更新せずに処理を抜ける
		return;
	}

	//現在のステージとエネミーのいるステージが一致しない場合
	if (CGame::GetNumStage() != GetPostStageID())
	{
		//更新せずに処理を抜ける
		return;
	}

	//ゴーストの更新処理
	CBat::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CRedBat::Draw()
{
	//エネミーの描画処理
	CEnemy::Draw();
}

//===========================================================================================================
// 当たり判定
//===========================================================================================================
bool CRedBat::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//エネミーの当たり判定
	return CEnemy::Collision(pos, size);
}

//===========================================================================================================
// ヒット処理
//===========================================================================================================
void CRedBat::Hit()
{
	//エネミーのヒット処理
	CEnemy::Hit();
}
