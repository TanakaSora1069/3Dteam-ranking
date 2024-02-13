//************************************************
// 
// ランキング[ranking.h]
// Auther:SORA TANAKA
// 
//************************************************

#ifndef _RANKING_H_
#define _RANKING_H_

// インクルードファイル
#include "main.h"

// マクロ定義
#define MAX_RANK	(5) // 表示するスコアの順位の数
#define MAX_SCORE	(8)	// 表示するスコアの桁数
#define MAX_TEXT	(256)	// 描画するテキストの最大数

typedef struct
{
	D3DXVECTOR3 pos;	// 座標
	int type;			// テクスチャの種類
	float whith;		// 横幅
	float height;		// 縦幅
	bool bUse;			// 使用されているか
}TEXT_RANKING;	// ランキング画面のテキスト

// プロトタイプ宣言
void InitRanking(void);		// ランキング画面の初期化処理
void UninitRanking(void);	// ランキング画面の終了処理
void UpdateRanking(void);	// ランキング画面の更新処理
void DrawRanking(void);		// ランキング画面の描画処理
void GetScore(void);		// スコア取得
void SetRankingText(void);	// テキストの設定


#endif // !_RANKING_H_
