//==============================================================================================================================================
//
// ラケットの処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "racket.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CRacket::CRacket(int nPriority) : 
	CObjectX(nPriority),
	m_bDraw(false)
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CRacket::~CRacket()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CRacket::Init()
{
	//モデル生成
	CXfile* pModel = CManager::GetModel();//取得
	int nModelIdx = pModel->Regist("data/MODEL/racket.x");//登録
	BindModel(pModel->GetAddress(nModelIdx));//設定
	SetModelIdx(nModelIdx);//ID設定
	
	//Xファイルオブジェクト初期化処理
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CRacket::Uninit()
{
	//Xファイルオブジェクト終了処理
	CObjectX::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
#include "player.h"
void CRacket::Update()
{
	//ローカル変数宣言
	CInputJoypad* pJoypad = CManager::GetJoypad();//ジョイパッド情報
	CInputJoypad::STICKINPUT Stickinput = pJoypad->GetStick();//スティック入力情報

	//右スティック入力中
	if ((float)Stickinput.abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_UP] > 0.1f || 
		(float)Stickinput.abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_DOWN] > 0.1f || 
		(float)Stickinput.abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_RIGHT] > 0.1f || 
		(float)Stickinput.abAnglePress[CInputJoypad::STICKTYPE_RIGHT][CInputJoypad::STICKANGLE_LEFT] > 0.1f)
	{
		//スティックの現在の角度を取得
		float fStickAngle = pJoypad->GetAngleR();

		//自分自身の角度情報取得
		D3DXVECTOR3 rot = GetRot();

		//スティックの角度に合わせて回転させる
		rot.y = fStickAngle;

		//角度情報を設定
		SetRot(rot);

		//描画フラグをtrueに設定
		m_bDraw = true;
	}
	//右スティック未入力
	else
	{
		//描画フラグをfalseに設定
		m_bDraw = false;
	}

	//指定した順番にオブジェクト情報を取得する
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		//先頭のオブジェクト情報を取得
		CObject* pObj = CObject::GetTop(nCnt);

		//オブジェクト情報がnullptrになるまで繰り返す
		while (pObj != nullptr)
		{
			//次のオブジェクト情報を取得
			CObject* pNext = pObj->GetNext();

			//オブジェクトタイプ情報を取得
			CObject::TYPE type = pObj->GetType();

			//オブジェクトタイプがプレイヤー
			if (type == CObject::PLAYER)
			{
				//プレイヤークラスにダウンキャスト
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

				//プレイヤーの座標
				D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

				//更新座標設定
				D3DXVECTOR3 UpdatePos(PlayerPos.x, PlayerPos.y + pPlayer->GetSize().y, PlayerPos.z);
				SetPos(UpdatePos);
			}

			//オブジェクト情報を次の情報に変更する
			pObj = pNext;
		}
	}
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CRacket::Draw()
{
	//描画フラグがtrue
	if (m_bDraw)
	{
		//Xファイルオブジェクト描画処理
		CObjectX::Draw();
	}
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CRacket* CRacket::Create(D3DXVECTOR3 pos)
{
	//タイプごとに動的確保
	CRacket* pRacket = NEW CRacket();

	//パラメータ設定
	pRacket->SetPos(pos);//座標
	
	//初期化処理
	pRacket->Init();
	
	return pRacket;
}
