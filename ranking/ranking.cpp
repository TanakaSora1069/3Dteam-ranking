//************************************************
// 
// ランキング[ranking.cpp]
// Auther:SORA TANAKA
// 
//************************************************

/* インクルードファイル */
#include "ranking.h"

// 使用するファイル
#include "input.h"
#include "main.h"
#include "sound.h"
//#include "title.h"

int g_aHighScore[MAX_RANK * MAX_PLAYER];	// ハイスコア格納
int g_PlayerNum;							// プレイ人数
int g_Score;								// プレイスコア
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRanking[4] = {};	// テクスチャへのポインタ
TEXT_RANKING g_aTextRanking[MAX_TEXT];

//========================================
// ランキング画面の初期化処理
//========================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\title\\score_title_demo.png", &g_pTextureRanking[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\title\\score_player_demo.png", &g_pTextureRanking[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\title\\score_end_demo.png", &g_pTextureRanking[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\title\\score_number_demo.png", &g_pTextureRanking[3]);

	for (int nCnt = 0; nCnt < MAX_RANK * MAX_PLAYER; nCnt++)
	{
		g_aHighScore[nCnt] = 0;
	}
	g_PlayerNum = 0;
	g_Score = 0;



	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D* pVtx;

	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TEXT; nCnt++)
	{
		g_aTextRanking[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTextRanking[nCnt].type = 0;
		g_aTextRanking[nCnt].bUse = false;

		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;	// 頂点データのポインタを4つ分進める
	}

	g_pVtxBuffRanking->Unlock();
}

//========================================
// ランキング画面の終了処理
//========================================
void UninitRanking(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (g_pTextureRanking[nCnt] != NULL)
		{
			g_pTextureRanking[nCnt]->Release();
			g_pTextureRanking[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//========================================
// ランキング画面の更新処理
//========================================
void UpdateRanking(void)
{
	// STARTボタンが押されたらタイトルへ
	if (GetJoypadPress(JOYKEY_START, 0))
	{
		//SetMode(MODE_RANKING);
	}

	// 文字の点滅
}

//========================================
// ランキング画面の描画処理
//========================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEXT; nCnt++)
	{
		// 使用されている
		if (g_aTextRanking[nCnt].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRanking[g_aTextRanking[nCnt].type]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, 2);
		}
	}

}

//========================================
// スコアの取得
//========================================
void GetScore(void)
{
	FILE* pFile;	// ファイルポインタ

	// ファイルを開く
	//pFile = fopen("", "r");

	//if (pFile != NULL)
	//{
		for (int nCnt = 0; nCnt < MAX_RANK * MAX_PLAYER; nCnt++)
		{
			// ファイルからスコアを読み込む
			g_aHighScore[nCnt] = int(123400); // スコア（仮）
		}

		// ファイルを閉じる
		//fclose(pFile);
	//}
}

//========================================
// テキストの設定
//========================================
void SetRankingText(void)
{
	int nCnt = 0;
	VERTEX_2D* pVtx;

	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	// タイトル
	g_aTextRanking[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 100, 0);
	g_aTextRanking[nCnt].type = 0;
	g_aTextRanking[nCnt].whith = 800.0f;
	g_aTextRanking[nCnt].height = 150.0f;
	g_aTextRanking[nCnt].bUse = true;

	pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / 2, 0);
	pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / 2, 0);

	nCnt++;
	pVtx += AMOUNT_VTX;

	// プレイ人数
	for (int nPlayerCnt = 0; nPlayerCnt < MAX_PLAYER; nPlayerCnt++)
	{
		g_aTextRanking[nCnt].pos = D3DXVECTOR3(float(SCREEN_WIDTH / 4 * nPlayerCnt), 300, 0);
		g_aTextRanking[nCnt].type = 1;
		g_aTextRanking[nCnt].whith = 300.0f;
		g_aTextRanking[nCnt].height = 100.0f;
		g_aTextRanking[nCnt].bUse = true;

		pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / -2, 0);
		pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / -2, 0);
		pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / 2, 0);
		pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / 2, 0);

		nCnt++;
		pVtx += AMOUNT_VTX;
	}

	// ボタンでタイトルへ戻る
	g_aTextRanking[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 0);
	g_aTextRanking[nCnt].type = 2;
	g_aTextRanking[nCnt].whith = 400.0f;
	g_aTextRanking[nCnt].height = 80.0f;
	g_aTextRanking[nCnt].bUse = true;

	pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / 2, 0);
	pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / 2, 0);

	nCnt++;
	pVtx += AMOUNT_VTX;

	// 数字	
	/// プレイ人数
	for (int nPlayerCnt = 0; nPlayerCnt < MAX_PLAYER; nPlayerCnt++)
	{
		g_aTextRanking[nCnt].pos = D3DXVECTOR3(float(SCREEN_WIDTH / 4 * nPlayerCnt)-175.0f, 300, 0);
		g_aTextRanking[nCnt].type = 3;
		g_aTextRanking[nCnt].whith = 50.0f;
		g_aTextRanking[nCnt].height = 100.0f;
		g_aTextRanking[nCnt].bUse = true;

		nCnt++;
		pVtx += AMOUNT_VTX;
	}

	/// スコア
	for (int nScoreCnt = 0; nScoreCnt < MAX_SCORE * MAX_RANK * MAX_PLAYER; nScoreCnt++)
	{
		//g_aTextRanking[nCnt].pos = D3DXVECTOR3(0, 0, 0);
		g_aTextRanking[nCnt].type = 3;
		g_aTextRanking[nCnt].whith = 40.0f;
		g_aTextRanking[nCnt].height = 80.0f;
		g_aTextRanking[nCnt].bUse = true;

		nCnt++;
		pVtx += AMOUNT_VTX;
	}
}