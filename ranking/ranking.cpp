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
#include "sound.h"
#include "title.h"
#include "game.h"
#include "fade.h"

int g_aHighScore[MAX_RANK * MAX_PLAYER];	// ハイスコア格納
int g_PlayerNum;							// プレイ人数
int g_Score;								// プレイスコア
int nRankingAlpha;
bool bSwitchRankAlpha;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRanking[5] = {};	// テクスチャへのポインタ
TEXT_RANKING g_aTextRanking[MAX_TEXT];

//========================================
// ランキング画面の初期化処理
//========================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.jp",
		&g_pTextureRanking[0]);	// 背景

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking\\score_title_demo.png",
		&g_pTextureRanking[1]);	// タイトル

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking\\score_player_demo.png",
		&g_pTextureRanking[2]);	// プレイヤ―人数

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking\\score_end_demo.png",
		&g_pTextureRanking[3]);	// 切り替え表示

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking\\score_number_demo.png",
		&g_pTextureRanking[4]);	// 数字

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

		pVtx[0].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);
		pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;	// 頂点データのポインタを4つ分進める
	}

	g_pVtxBuffRanking->Unlock();

	nRankingAlpha = 255;
	bSwitchRankAlpha = false;

	SetRankingText();
	SetFade(FADE_IN, MODE_MAX);
}

//========================================
// ランキング画面の終了処理
//========================================
void UninitRanking(void)
{
	for (int nCnt = 0; nCnt < 5; nCnt++)
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
	// 文字の点滅
	if (nRankingAlpha >= 255 || nRankingAlpha <= 105)
	{
		bSwitchRankAlpha = bSwitchRankAlpha ? false : true;
	}

	if (bSwitchRankAlpha == false)
	{
		nRankingAlpha += RANKING_FLASH;
	}
	else
	{
		nRankingAlpha -= RANKING_FLASH;
	}

	VERTEX_2D* pVtx;

	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TEXT; nCnt++)
	{
		if (g_aTextRanking[nCnt].bUse == true)
		{
			if (g_aTextRanking[nCnt].type == 3)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nRankingAlpha);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nRankingAlpha);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nRankingAlpha);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nRankingAlpha);
			}
		}
		pVtx += AMOUNT_VTX;
	}
	g_pVtxBuffRanking->Unlock();

	if (GetJoypadTrigger(JOYKEY_A, 0) == true || GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_TITLE);
	}
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
	int* score;		// 今回プレイのスコア
	int* player;	// 今回プレイのプレイヤー人数

	// ファイルを開く
	//pFile = fopen("", "r");

	//if (pFile != NULL)
	//{
	for (int nCnt = 0; nCnt < MAX_RANK * MAX_PLAYER; nCnt++)
	{
		// ファイルからスコアを読み込む
		//fscanf(pFile, "%n", g_aHighScore[nCnt]);
		g_aHighScore[nCnt] = 123400; // スコア（仮）
	}

	// ファイルを閉じる
	//fclose(pFile);
//}

	// 今回プレイのスコア取得
	//score = GetInfoScore();

	// 今回プレイのプレイヤー人数取得
	//player =

	// ランキング更新
	 
	//for (int nCnt = 0; nCnt <MAX_RANK; nCnt++)
	//{
	//	if (g_aHighScore[((*player-1) * MAX_RANK) + nCnt] < *score)
	//	{
		//for (int nScoreCnt = MAX_RANK - 1; nScoreCnt > nCnt; nScoreCnt--)
		//{
			// 順位を下げる
		//	g_aHighScore[((*player - 1) * MAX_RANK) + nScoreCnt] = g_aHighScore[((*player - 1) * MAX_RANK) + nScoreCnt - 1];
		//}
		// 新しいスコアを入れる
		//g_aHighScore[((*player - 1) * MAX_RANK) + nCnt] = *score;
	//	}
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

	// 背景
	g_aTextRanking[nCnt].type = 0;
	g_aTextRanking[nCnt].bUse = true;

	nCnt++;
	pVtx += AMOUNT_VTX;

	// タイトル
	g_aTextRanking[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 100, 0);
	g_aTextRanking[nCnt].type = 1;
	g_aTextRanking[nCnt].width = 800.0f;
	g_aTextRanking[nCnt].height = 350.0f;
	g_aTextRanking[nCnt].bUse = true;

	pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / -2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / 2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / -2, g_aTextRanking[nCnt].height / 2, 0);
	pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / 2, g_aTextRanking[nCnt].height / 2, 0);

	nCnt++;
	pVtx += AMOUNT_VTX;

	// プレイ人数
	for (int nPlayerCnt = 1; nPlayerCnt <= MAX_PLAYER; nPlayerCnt++)
	{
		g_aTextRanking[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH / 5 * (float)nPlayerCnt, 300.0f, 0);
		g_aTextRanking[nCnt].type = 2;
		g_aTextRanking[nCnt].width = 300.0f;
		g_aTextRanking[nCnt].height = 100.0f;
		g_aTextRanking[nCnt].bUse = true;

		pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / -2, g_aTextRanking[nCnt].height / -2, 0);
		pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / 2, g_aTextRanking[nCnt].height / -2, 0);
		pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / -2, g_aTextRanking[nCnt].height / 2, 0);
		pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / 2, g_aTextRanking[nCnt].height / 2, 0);

		nCnt++;
		pVtx += AMOUNT_VTX;
	}

	// ボタンでタイトルへ戻る
	g_aTextRanking[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 300, SCREEN_HEIGHT - 100, 0);
	g_aTextRanking[nCnt].type = 3;
	g_aTextRanking[nCnt].width = 400.0f;
	g_aTextRanking[nCnt].height = 200.0f;
	g_aTextRanking[nCnt].bUse = true;

	pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / -2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / 2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / -2, g_aTextRanking[nCnt].height / 2, 0);
	pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / 2, g_aTextRanking[nCnt].height / 2, 0);

	nCnt++;
	pVtx += AMOUNT_VTX;

	// 数字	
	///// プレイ人数
	//for (int nPlayerCnt = 0; nPlayerCnt < MAX_PLAYER; nPlayerCnt++)
	//{
	//	g_aTextRanking[nCnt].pos = D3DXVECTOR3(float(SCREEN_WIDTH / 5 * nPlayerCnt)-175.0f, 300, 0);
	//	g_aTextRanking[nCnt].type = 3;
	//	g_aTextRanking[nCnt].width = 50.0f;
	//	g_aTextRanking[nCnt].height = 100.0f;
	//	g_aTextRanking[nCnt].bUse = true;

	//	nCnt++;
	//	pVtx += AMOUNT_VTX;
	//}

	/// スコア
	int aScore[MAX_SCORE] = {};	// 表示用スコア格納
	int nScoreSto = 0;			// 計算用スコア格納

	GetScore();

	for (int nPlayerCnt = 1; nPlayerCnt <= MAX_PLAYER; nPlayerCnt++)
	{
		for (int nRankCnt = 0; nRankCnt < MAX_RANK; nRankCnt++)
		{
			nScoreSto = g_aHighScore[((nPlayerCnt - 1) * MAX_RANK) + nRankCnt];

			for (int nScoreCnt = 0; nScoreCnt < MAX_SCORE; nScoreCnt++)
			{
				aScore[MAX_SCORE - nScoreCnt - 1] = nScoreSto - ((nScoreSto / 10) * 10);
				nScoreSto /= 10;
			}

			for (int nScoreCnt = 0; nScoreCnt < MAX_SCORE; nScoreCnt++)
			{
				g_aTextRanking[nCnt].type = 4;
				g_aTextRanking[nCnt].width = 40.0f;
				g_aTextRanking[nCnt].height = 100.0f;
				g_aTextRanking[nCnt].pos = D3DXVECTOR3((SCREEN_WIDTH / 5 * nPlayerCnt) + (nScoreCnt * g_aTextRanking[nCnt].width) - (g_aTextRanking[nCnt].width * 3.5f),
					nRankCnt * 100.0f + 500, 0);

				g_aTextRanking[nCnt].bUse = true;

				pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / -2, g_aTextRanking[nCnt].height / -2, 0);
				pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / 2, g_aTextRanking[nCnt].height / -2, 0);
				pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / -2, g_aTextRanking[nCnt].height / 2, 0);
				pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].width / 2, g_aTextRanking[nCnt].height / 2, 0);

				pVtx[0].tex = D3DXVECTOR2(aScore[nScoreCnt] * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(aScore[nScoreCnt] * 0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(aScore[nScoreCnt] * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(aScore[nScoreCnt] * 0.1f + 0.1f, 1.0f);

				nCnt++;
				pVtx += AMOUNT_VTX;
			}
		}
	}
	g_pVtxBuffRanking->Unlock();
}