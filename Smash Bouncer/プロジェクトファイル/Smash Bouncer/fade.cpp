//==============================================================================================================================================
//
// フェードに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "fade.h"//フェードヘッダー

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	//メンバ変数初期化
	m_fade = FADE_NONE;//現在の状態
	m_NextMode = CScene::MODE_TITLE;//次のモード
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CFade::~CFade()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CFade::Init()
{
	//サイズ設定
	float fWidth = (float)CProcess::SCREEN_WIDTH;//横幅
	float fHeigth = (float)CProcess::SCREEN_HEIGHT;//縦幅
	SetSize({ fWidth, fHeigth });

	//位置設定
	D3DXVECTOR2 pos = { fWidth * 0.5f, fHeigth * 0.5f };
	SetPos(pos);

	//色設定
	D3DXCOLOR col = { 1.0f, 1.0f, 1.0f, 0.0f };
	SetColor(col);

	//2Dオブジェクト初期化処理
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CFade::Uninit()
{
	//2Dオブジェクト終了処理
	CObject2D::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CFade::Release()
{
	//2Dオブジェクト解放処理
	CObject2D::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CFade::Update()
{
	//現在のカラー情報を取得
	D3DXCOLOR col = GetColor();

	//フェードイン
	if (m_fade == FADE_IN)
	{
		//ポリゴンを透明にしていく
		col.a -= FADE_SPEED;

		//更新したカラーを設定
		SetColor(col);

		//2Dオブジェクト更新処理
		CObject2D::Update();

		//α値が0.0f以下の場合
		if (col.a <= 0.0f)
		{
			//0.0f以下にならないように調整
			col.a = 0.0f;

			//フェードしない状態にする
			m_fade = FADE_NONE;
		}
	}

	//フェードアウト
	else if (m_fade == FADE_OUT)
	{
		//ポリゴンを不透明にする
		col.a += FADE_SPEED;

		//更新したカラーを設定
		SetColor(col);

		//2Dオブジェクト更新処理
		CObject2D::Update();

		//α値が1.0f以上の場合
		if (col.a >= 1.0f)
		{
			//1.0f以上にならないように調整
			col.a = 1.0f;

			//フェードイン状態にする
			m_fade = FADE_IN;

			//次の画面へ移行
			CManager::SetMode(m_NextMode);
		}
	}
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CFade::Draw()
{
	//2Dオブジェクト描画処理
	CObject2D::Draw();
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CFade* CFade::Create()
{
	CFade* pFade = NEW CFade();

	pFade->SetType(TYPE::FADE);//種類設定
	pFade->Init();//初期化処理

	return pFade;
}

//===========================================================================================================
// 状態設定処理
//===========================================================================================================
void CFade::SetFade(CScene::MODE mode)
{
	m_NextMode = mode;//次のモードを設定
	m_fade = FADE_OUT;
}
