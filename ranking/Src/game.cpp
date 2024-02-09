//==========================================================
//
//ゲーム画面の描画処理[game.cpp]
//Author:kasai keisuke, 福田歩希
//
//==========================================================

/* インクルードファイル */
#include "game.h"
// 中枢
#include "input.h"
#include "main.h"
#include "sound.h"
// 諸処理
#include "boss.h"
#include "bullet.h"
#include "camera.h"
#include "effect.h"
#include "effect_hayu.h"
#include "effect_sand.h"
#include "enemy.h"
#include "explosion.h"
#include "item.h"
#include "light.h"
#include "object.h"
#include "player.h"
#include "reticle.h"
#include "sea.h"
#include "shadow.h"
#include "sky.h"
// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"
#include "TEST.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*/ マクロ定義 /*/
#define JOIN_VERIFY 1	// 人数指定

/*/ グローバル変数 /*/
int g_AmountPlayer = JOIN_VERIFY;	// プレイ人数格納
bool g_LayoutEdit = false;			// 配置編集モード用フラグ
int g_nCnt = 0;						//デバック用変数(コントローラ分離確認用)
bool g_Pause = false;				// ポーズ判定用フラグ

//=======================================================================
//ゲーム画面の初期化処理
//=======================================================================
void InitGame(void)
{
#ifndef JOIN_VERIFY

	// 人数指定が無ければ固定
	g_AmountPlayer = 1;

#endif	// JOIN_VERIFY

	//各種変数の初期化
	g_LayoutEdit = false;	// 配置編集モードをオフ
	g_nCnt = 0;				//デバック用変数(コントローラ分離確認用)の初期化
	g_Pause = false;		// ポーズフラグを無くす

#ifdef _DEBUG

	// 人数がおかしいと終了
	assert(g_AmountPlayer > 0 && g_AmountPlayer <= 4);

	// 編集カメラの初期
	InitEditCamera();

	// テスト用の初期
	InitTEST(g_AmountPlayer);

	// 球の判定可視化初期
	InitVisibleSph();

#endif	// _DEBUG

	// レティクルの初期：先行
	InitReticle();
	
	// 影の初期：先行
	InitShadow();

	//ボスの初期化処理
	InitBoss();

	// 弾の初期
	InitBullet();

	// カメラの初期
	InitCamera(g_AmountPlayer);

	//エフェクトの初期化処理
	InitEffect();

	// Hayuエフェクトの初期
	InitEffect_Hayu();

	// 砂のエフェクトの初期
	InitEffectSand();

	// 敵の初期
	InitEnemy();

	// 爆発の初期
	InitExplosion();
	
	// アイテムの初期
	InitItem();

	// ライトの初期
	InitLight();

	// 物の初期
	InitObject();

	// プレイヤーの初期
	InitPlayer();

	// 海の初期
	InitSea();

	// 空の初期
	InitSky();
}

//=======================================================================
//ゲーム画面の終了処理
//=======================================================================
void UninitGame(void)
{
#ifdef _DEBUG

	// テスト用の終了
	UninitTEST();

	// 球の判定可視化終了
	UninitVisibleSph();

#endif	// _DEBUG

	//ボスの終了処理
	UninitBoss();

	// 弾の終了
	UninitBullet();

	//エフェクトの終了処理
	UninitEffect();

	// Hayuエフェクトの終了
	UninitEffect_Hayu();

	// 砂のエフェクトの終了
	UninitEffectSand();

	// 敵の終了
	UninitEnemy();

	// 爆発の終了
	UninitExplosion();

	// アイテムの終了
	UninitItem();

	// 物の終了
	UninitObject();

	// プレイヤーの終了
	UninitPlayer();

	// レティクルの終了
	UninitReticle();

	// 海の終了
	UninitSea();

	// 影の終了
	UninitShadow();

	// 空の終了
	UninitSky();
}

//=======================================================================
//ゲーム画面の更新処理
//=======================================================================
void UpdateGame(void)
{
	if (GetJoypadTrigger(JOYKEY_START, 0) || GetKeyboardTrigger(DIK_P))
	{
		g_Pause = !g_Pause;
	}

	if (g_Pause)
	{ // ポーズ中のみ

		/*---【ここでUIの処理】---*/

		return;	// 以下の処理は行わない
	}

#if defined (_DEBUG)

	// 配置編集モード切り替え
	if (GetKeyboardTrigger(DIK_F2))
	{
		g_LayoutEdit = !g_LayoutEdit;
	}

	if (!g_LayoutEdit)
	{ // 配置編集モードでないときのみ
		// 参加人数を直接変更
		if (GetKeyboardTrigger(DIK_LBRACKET))
		{
			g_AmountPlayer < 4 ? g_AmountPlayer++ : g_AmountPlayer = 1;
		}
		else if (GetKeyboardTrigger(DIK_RBRACKET))
		{
			g_AmountPlayer > 1 ? g_AmountPlayer-- : g_AmountPlayer = 4;
		}
	}

	// デバッグ表示の更新(配布)
	UpdateDebugProc();

	// カメラ or 編集カメラの更新
	g_LayoutEdit ? UpdateEditCamera() : UpdateCamera(g_AmountPlayer);

	// テスト用の更新
	UpdateTEST(g_AmountPlayer);

#endif	// _DEBUG

#ifndef _DEBUG

	// カメラの更新
	UpdateCamera(g_AmountPlayer);

#endif // _DEBUG リリース

	// 状況に応じて物の更新
	UpdateObject(g_LayoutEdit);

	if (!g_LayoutEdit)
	{
		// 敵の更新
		UpdateEnemy();

		//ボスの更新処理
		UpdateBoss();

		//アイテムの更新
		UpdateItem();

		// ライトの更新
		UpdateLight();

		// プレイヤーの更新
		UpdatePlayer(g_AmountPlayer);

		// レティクルの更新
		UpdateReticle(g_AmountPlayer);

		// 弾の更新
		UpdateBullet();

		//エフェクトの更新処理
		UpdateEffect();

		// Hayuエフェクトの更新
		UpdateEffect_Hayu();

		// 爆発の更新
		UpdateExplosion();

		// 砂のエフェクトの更新
		UpdateEffectSand();

		// 海の更新
		UpdateSea();

		// 影の更新
		UpdateShadow();

		// 空の更新
		UpdateSky();

#ifdef _DEBUG	

		// 球の判定可視化更新
		UpdateVisibleSph();

#endif // _DEBUG ↑これここに置きたい
	}
}

//=======================================================================
//ゲーム画面の描画処理
//=======================================================================
void DrawGame(void)
{
	// ループ回数
	int Loop = 0;

	// 配置編集モードであれば余分な描画を抑制
	g_LayoutEdit ? Loop = 1 : Loop = g_AmountPlayer;

	for (int i = 0; i < Loop; i++)
	{
#ifdef _DEBUG

		// カメラ or 編集カメラの設定
		g_LayoutEdit ? SetInfoEditCamera() : SetInfoCamera(i, g_AmountPlayer);

#else

		// カメラの設定
		SetInfoCamera(i, g_AmountPlayer);

#endif	// _DEBUG リリース

		// 空の描画
		DrawSky();

		// 海の描画
		DrawSea();

		// 状況に応じて物の描画
		DrawObject(g_LayoutEdit);

		// 敵の描画
		DrawEnemy();

		// ボスの描画処理
		DrawBoss();

		// アイテムの描画
		DrawItem();

		// 砂のエフェクトの描画
		DrawEffectSand();

		// Hayuエフェクトの描画
		DrawEffect_Hayu();

		// 爆発の描画
		DrawExplosion();

		// 影の描画
		DrawShadow();

		//エフェクトの描画
		DrawEffect();

		// レティクルの描画
		DrawReticle(i);

		// 弾の描画
		DrawBullet();

		// プレイヤーの描画
		DrawPlayer();

#ifdef _DEBUG

		// 球の判定可視化描画
		DrawVisibleSph();

#endif	// _DEBUG
	}

	// UI用ポートの設定
	SetInfoUIport();

	/*---【ゲーム内UIの表示はここから下で行います】---*/

#ifdef _DEBUG

	// テスト用の描画
	if (!g_LayoutEdit)
	{
		//DrawTEST();	//!< UI系はポート設定されていない範囲の描画は行われません。はみ出るようなら新たにポート設定を追加してください。
	}

	// デバッグ用表示の描画(配布)
	DrawDebugProc();

#endif	// _DEBUG
}

/*---【以下ゲームループ外】---*/

//************************************************
// 編集モードのフラグ取得
//************************************************
bool GetLayoutEdit()
{
	return g_LayoutEdit;
}

//************************************************
// 状態継続カウント用
//************************************************
bool CntDuration(int* dur)
{
	bool finish = false;

	if (*dur > 0)
	{ // 継続時間減少
		*dur -= 1;	// なぜデクリメント非対応？
	}
	else
	{ // 継続時間が無くなると

		// 完了を返す
		finish = true;
	}

	return finish;
}