//==============================================================================================================================================
//
// フィールドの処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "field.h"//フィールド

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CField::CField(int nPriority) : CObject3D(nPriority)
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CField::~CField()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CField::Init()
{	
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
	VERTEX_3D* pVtx;//頂点情報へのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファへのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * CProcess::MAX_VER,
		D3DUSAGE_WRITEONLY,
		CProcess::FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	//頂点バッファの設定
	SetVtxBuff(pVtxBuff);

	//テクスチャ生成
	CTexture* pTex = CManager::GetTexture();//取得
	int nTextureIdx = pTex->Regist("data\\TEXTURE\\field000.png");//登録
	BindTexture(pTex->GetAddress(nTextureIdx));//設定
	SetTextureIdx(nTextureIdx);//ID設定

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//情報の取得
	D3DXVECTOR3 pos = GetPos();//位置
	D3DXVECTOR3 size = GetSize();//サイズ

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, pos.y, size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(size.x, pos.y, size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, pos.y, -size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(size.x, pos.y, -size.z * 0.5f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCntVer = 0; nCntVer < CProcess::MAX_VER; nCntVer++)
	{
		//法線ベクトルの設定
		pVtx[nCntVer].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCntVer].col = GetColor();
	}

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();

	//オブジェクトの初期化処理
	CObject::Init();

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CField::Uninit()
{
	//オブジェクト終了処理
	CObject3D::Uninit();
}

//===========================================================================================================
// 削除処理
//===========================================================================================================
void CField::Release()
{
	//オブジェクト解放処理
	CObject3D::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CField::Update()
{
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CField::Draw()
{
	//オブジェクト描画処理
	CObject3D::Draw();
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CField* CField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CField* pField = NEW CField();

	pField->SetType(TYPE::FIELD);//オブジェクト種類の設定
	pField->SetPos(pos);//位置設定
	pField->SetSize(size);//サイズ
	pField->Init();//初期化処理

	return pField;
}
