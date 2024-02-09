//==========================================================
//
//ゲーム画面の描画処理[game.h]
//Author:kasai keisuke
//
//==========================================================

#ifndef _GAME_H_
#define _GAME_H_

//include
#include "main.h"

//マクロ定義
#define MAX_ENEMY	(1024)		//敵の最大数
#define MAX_PATHWORD	(128)	//最大文字数
#define MAX_SYMBOL	(4)			//イコールなどを読み込む用

//敵のパラメーターの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//出現位置
	D3DXVECTOR3 rot;	//出現向き
	int nStyle;			//タイプ
	int nCntAppear;		//出現時間
	int nLife;			//ライフ
}EnemyInfo;

//プロトタイプ宣言
void InitGame(void);		//ゲーム画面の初期化処理
void UninitGame(void);		//ゲーム画面の終了処理
void UpdateGame(void);		//ゲーム画面の更新処理
void DrawGame(void);		//ゲーム画面の描画処理
bool GetLayoutEdit(void);	// 編集モードのフラグ取得
bool CntDuration(int* dur);	// 状態継続カウント用

#endif