//==============================================================================================================================================
//
// タイトルロゴに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "logo.h"//タイトルロゴ

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CLogo::CLogo(int nPriority) : CObject3D(nPriority)
{
	//メンバ変数初期化
	m_nCnt = 0;//フラグ切り替えカウント
	m_bUp = false;//移動方向フラグ
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CLogo::~CLogo()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CLogo::Init()
{
	//パラメータ設定
	SetPos(POS);//位置
	SetRot(ROT);//角度
	SetSize(SIZE);//サイズ

	//テクスチャ生成
	CTexture* pTex = CManager::GetTexture();//取得
	int nTextureIdx = pTex->Regist(TEXTURE_FILE);//登録
	BindTexture(pTex->GetAddress(nTextureIdx));//設定
	SetTextureIdx(nTextureIdx);//ID設定

	//3Dオブジェクト初期化処理
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CLogo::Uninit()
{
	//3Dオブジェクト終了処理
	CObject3D::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CLogo::Update()
{
	//ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();//位置情報

	//カウントを加算
	m_nCnt++;

	//フラグがtrueの場合
	if (m_bUp)
	{
		//上昇させる
		pos.y += 0.1f;
	}
	//フラグがfalseの場合
	else
	{
		//下降させる
		pos.y -= 0.1f;
	}

	//更新された位置情報を設定
	SetPos(pos);

	//カウントが最大まで達した場合
	if (m_nCnt == 60)
	{
		//フラグを切り替える
		m_bUp = m_bUp ? false : true;

		//カウントリセット
		m_nCnt = 0;
	}

	//3Dオブジェクト更新処理
	CObject3D::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CLogo::Draw()
{
	//3Dオブジェクト描画処理
	CObject3D::Draw();
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CLogo* CLogo::Create()
{
	//メモリを動的確保
	CLogo* pLogo = NEW CLogo(4);

	//パラメータ設定
	pLogo->SetType(CObject::UI);//オブジェクトタイプ

	//初期化処理
	pLogo->Init();

	return pLogo;
}
