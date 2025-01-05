//==============================================================================================================================================
//
// パーティクルに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "particle.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CParticle::CParticle() :
	CBillboard{},
	m_MaxSize{},
	m_type{ TYPE::NONE },
	m_nLife{ 30 },
	m_nMaxLife{ m_nLife }
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CParticle::~CParticle()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CParticle::Init()
{
	//テクスチャ生成
	CTexture* pTex = CManager::GetTexture();//取得
	int nTexIdx = pTex->Regist("data/TEXTURE/Effect/effect000.jpg");//登録
	BindTexture(pTex->GetAddress(nTexIdx));//設定

	//移動量設定
	SetMoveValue();

	//カラー設定
	SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	//基底クラス初期化処理
	if (FAILED(CBillboard::Init())) return E_FAIL;

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CParticle::Uninit()
{
	//基底クラス終了処理
	CBillboard::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CParticle::Release()
{
	//基底クラス解放処理
	CBillboard::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CParticle::Update()
{
	//座標更新
	SetPos(GetPos() + GetMove());

	//寿命減少
	m_nLife--;

	//寿命が0
	if (m_nLife <= 0)
	{
		//終了処理
		Uninit();
	}

	//寿命に合わせて薄くする
	D3DXVECTOR3 size = GetSize();
	size.x = m_MaxSize.x * (static_cast<float>(m_nLife) / static_cast<float>(m_nMaxLife));
	size.y = m_MaxSize.y * (static_cast<float>(m_nLife) / static_cast<float>(m_nMaxLife));
	SetSize(size);

	//基底クラス更新処理
	CBillboard::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CParticle::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxTrans;//計算用マトリックス
	D3DXMATRIX mtxView;//ビューマトリックス取得用
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();//テクスチャ情報へのポインタ
	D3DXMATRIX mtxWorld;//ワールドマトリックス情報
	D3DXVECTOR3 Pos = GetPos();//座標情報

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&mtxWorld, nullptr, &mtxView);//逆行列を求める
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//座標を反映
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//ライトを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zバッファ書き込み無効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテスト有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(CProcess::FVF_VERTEX_3D);

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//aブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ライトを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zバッファ書き込み有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//===========================================================================================================
// 移動量設定
//===========================================================================================================
void CParticle::SetMoveValue()
{
	//各座標の移動方向ベクトルを設定
	float fX = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;
	float fY = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;
	float fZ = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;

	//移動量設定
	SetMove({ fX, fY, fZ });
}
