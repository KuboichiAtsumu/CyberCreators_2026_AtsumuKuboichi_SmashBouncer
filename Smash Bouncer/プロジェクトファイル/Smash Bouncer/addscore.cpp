//==============================================================================================================================================
//
// 加算スコア表示に関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "addscore.h"//加算スコア表示

//===========================================================================================================
// 静的メンバ変数初期化
//===========================================================================================================
//CAddScore* CAddScore::m_apNumber[MAX_NUMBER] = {};//各数字情報

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CAddScore::CAddScore(int nPriority) : CBillboard(nPriority)
{
	//メンバー変数初期化
	m_nAddScore = 0;//加算されたスコア情報
	m_nIdx = 0;//ID
	m_bLightUp = true;//ライトアップフラグ
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CAddScore::~CAddScore()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CAddScore::Init()
{
	//テクスチャ生成
	CTexture* pTex = CManager::GetTexture();//取得
	int nTextureIdx = 0;//テクスチャID

	//数字テクスチャ
	if (m_nIdx < MAX_NUMBER - 1)
	{
		nTextureIdx = pTex->Regist("data/TEXTURE/number000.png");//登録
	}
	//＋マークテクスチャ
	else
	{
		nTextureIdx = pTex->Regist("data/TEXTURE/EFFECT/plusmark000.png");//登録
	}

	BindTexture(pTex->GetAddress(nTextureIdx));//設定
	SetTextureIdx(nTextureIdx);//ID設定

	//パラメータ設定
	SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

	//ビルボード初期化処理
	if (FAILED(CBillboard::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CAddScore::Uninit()
{
	//ビルボード終了処理
	CBillboard::Uninit();

	////IDを保存
	//int nID = m_nIdx;

	////データが存在する場合
	//if (m_apNumber[nID] != nullptr)
	//{
	//	m_apNumber[nID] = nullptr;
	//}
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CAddScore::Update()
{
	//ビルボード更新処理
	CBillboard::Update();

	//頂点情報更新処理
	UpdateVtx();
}

//===========================================================================================================
// 移動処理
//===========================================================================================================
void CAddScore::Move()
{
	//ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();//位置情報

	//上に動かす
	pos.y += UP_SPEED;

	//更新された位置情報を設定
	SetPos(pos);
}

//===========================================================================================================
// 頂点情報更新処理
//===========================================================================================================
void CAddScore::UpdateVtx()
{
	//ローカル変数宣言
	VERTEX_3D* pVtx;//頂点情報へのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファへのポインタ
	D3DXCOLOR col = GetColor();//カラー情報
	int aPosTexU[MAX_NUMBER];//各桁の数字を格納用
	int nMulti = 10;//各桁の倍数

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//最後のポリゴン以外のみ更新
	if (m_nIdx < MAX_NUMBER - 1)
	{
		//各桁の数字を求める
		for (int nCnt = 0; nCnt < m_nIdx; nCnt++)
		{
			//何桁目かを求める
			nMulti *= 10;
		}

		//数字に合わせてテクスチャ座標を変更
		aPosTexU[m_nIdx] = (m_nAddScore % nMulti) / (nMulti / 10);

		//テクスチャ座標の更新
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[m_nIdx] / 10.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[m_nIdx] + 1) / 10.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[m_nIdx] / 10.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[m_nIdx] + 1) / 10.0f, 1.0f);
	}

	//ライトアップフラグがtrueの場合
	if (m_bLightUp)
	{
		//明るくする
		col.a += COLOR_ASCENT;
	}
	//ライトアップフラグがfalseの場合
	else
	{
		//暗くする
		col.a -= COLOR_ASCENT;
	}

	//α値が最大ではない場合
	if (col.a <= 0.00f || col.a >= 1.00f)
	{
		//ライトアップフラグを切り替える
		m_bLightUp = m_bLightUp ? false : true;
	}

	//更新されたカラー情報を設定
	SetColor(col);

	//ビルボード更新処理
	CBillboard::Update();

	//α値が０の場合
	if (col.a <= 0.00f)
	{
		//終了処理
		Uninit();
	}

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CAddScore::Draw()
{
	//ビルボード描画処理
	CBillboard::Draw();
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CAddScore* CAddScore::Create(int nIdx, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAddScore)
{
	//メモリを動的確保
	CAddScore* pAddScore = NEW CAddScore(4);

	//パラメータ設定
	pAddScore->SetType(TYPE::UI);//オブジェクトタイプ
	pAddScore->SetIndex(nIdx);//番号
	pAddScore->SetSize(size);//サイズ
	pAddScore->SetPos(pos);//生成位置
	pAddScore->SetAddScore(nAddScore);//加算されたスコア数
	
	//初期化処理
	pAddScore->Init();

	return pAddScore;
}

//===========================================================================================================
// 生成位置設定処理
//===========================================================================================================
void CAddScore::SetPos(D3DXVECTOR3 pos)
{
	//ローカル変数宣言
	D3DXVECTOR3 size = GetSize();//サイズ情報

	//右から順番に生成していく
	CObject3D::SetPos({ pos.x - size.x * m_nIdx, pos.y, pos.z });
}
