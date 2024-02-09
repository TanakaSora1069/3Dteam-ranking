//************************************************
//
// プレイヤー処理[player.cpp]
// Author：福田歩希, kasai keisuke
//
//************************************************

/*/ インクルードファイル /*/
#include "player.h"
// 中枢
#include "input.h"
#include "sound.h"
// 諸処理
#include "bullet.h"
#include "camera.h"
#include "collision.h"
#include "effect_hayu.h"
#include "effect_sand.h"
#include "game.h"
#include "shadow.h"
// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*/ グローバル変数 /*/
PlayerModel g_PlayerModel[AMOUNT_PLAYER_PARTS];	// プレイヤーモデル情報のひな形
PlayerMotion g_PlayerMotion[8];					// プレイヤーモーション情報のひな形
Player g_Player[MAX_PLAYER];					// プレイヤー情報

/*---【キーボードでデバッグ操作するプレイヤーを識別】---*/
int g_P_id = 0;

//************************************************
// プレイヤー初期
//************************************************
void InitPlayer(void)
{
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{ // プレイヤーモデル情報のひな形のリセット
		PlayerModel* pModel = &g_PlayerModel[i];

		// スタイル
		pModel->style = -1;
		pModel->weapon = -1;

		// モデル
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // マテリアル
			pModel->ColMat_offset[j] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pModel->pTex[j] = NULL;
		}

		// モデル座標
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 親インデックス
		pModel->IdxParent = -1;
	}

	/*--------------------------------------------*/

	for (int i = 0; i < 8; i++)
	{ // モーション
		PlayerMotion* pMotion = &g_PlayerMotion[i];

		pMotion->loop = 0;
		pMotion->amount_key = 0;
		pMotion->id_key = 0;
		pMotion->id_frame = 0;

		for (int j = 0; j < 16; j++)
		{ // キー
			PlayerMotionKey* pKey = &pMotion->key[j];

			pKey->amount_frame = 0;

			for (int k = 0; k < AMOUNT_PLAYER_PARTS; k++)
			{ // 目標動作
				PlayerMotionDest* pDest = &pKey->dest[k];

				pDest->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pDest->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_PLAYER; i++)
	{ // プレイヤー情報のリセット
		Player* pPlayer = &g_Player[i];

		// 使用フラグ
		pPlayer->use = false;

		// パラメータ
		pPlayer->param =
		{
			0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 0		// メンバー情報はヘッダファイルを確認して下さい
		};

		// 座標
		pPlayer->pos = D3DXVECTOR3(-200.0f + i * 100.0f, 0.0f, -100.0f);	// 修正予定
		pPlayer->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pPlayer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pPlayer->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 色
		pPlayer->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int j = 0; j < Max_itemstyle; j++)
		{ // 攻撃位置をリセット
			pPlayer->offset_atk[j].pos = {};
		}

		for (int j = 0; j < AMOUNT_PLAYER_PARTS; j++)
		{ // 各パーツ情報をリセット
			PlayerModel* pModel = &pPlayer->parts[j];

			// スタイル番号
			pModel->style = -1;
			pModel->weapon = -1;

			// モデル
			pModel->pMesh = NULL;
			pModel->pBuffMat = NULL;
			pModel->NumMat = 0;

			for (int k = 0; k < AMOUNT_MAT; k++)
			{ // マテリアル
				pModel->ColMat_offset[k] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				pModel->pTex[k] = NULL;
			}

			// モデル座標
			pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 親インデックス
			pModel->IdxParent = -1;
		}

		// 判定識別番号
		pPlayer->id_shadow = -1;
		pPlayer->id_sph = -1;
	}

	// プレイヤー用のモデル情報を取得
	ImportModelPlayer();

	// プレイヤー用のモーション情報を取得
	ImportMotionPlayer();

	/******************************/
		
	/*---【試験的にプレイヤーに必要な情報を設定(消去予定)】---*/
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		/*---【モーション情報をコピー(修正予定)】---*/
		for (int j = 0; j < 8; j++)
		{
			if (g_PlayerMotion[j].amount_key == 0)
			{ // 未使用ならコンティニュー
				continue;
			}

			g_Player[i].motion[j] = g_PlayerMotion[j];
		}

		g_Player[i].use = true;	// 使用

		// ステータス
		g_Player[i].param.style = i;				// スタイル番号
		g_Player[i].param.state = stateNormal_p;	// 状態
		g_Player[i].param.HP = 3;					// 体力
		g_Player[i].param.SPD = 10.0f;				// 速度
		g_Player[i].param.rad = 30.0f;				// 判定サイズ
		g_Player[i].param.motion_now = styleGun;	// 武器
		g_Player[i].param.motion_now = 0;
		g_Player[i].param.motion_old = 0;

		// スタイル番号を照合
		VerifyStylePlayer(i);

		// 影を生成
		g_Player[i].id_shadow = CreateShadow(&g_Player[i].pos, 40.0f);

#ifdef _DEBUG

		// 当たり判定を可視化
		CreateVisibleSph(g_Player[i].param.rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Player[i].pos);

#endif
	}
	/******************************/
}

//************************************************
// モデル情報を読み込む
//************************************************
void ImportModelPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int AmountModel = 0;		// モデルの数を格納
	int id_Model = 0;			// モデルの識別用

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\PLAYER\\player_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "プレイヤーモデル情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// 読み込むモデル数を取得する
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountModel);
		}

#ifdef _DEBUG

		// エラー
		assert(AmountModel < AMOUNT_PLAYER_PARTS && "プレイヤーモデルモデル情報が最大量を越えました");

#endif	// _DEBUG

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// 読み込むモデル名を取得する
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// 読み込んだ情報をひな形にのみコピーする
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_PlayerModel[id_Model].pBuffMat,
				NULL,
				&g_PlayerModel[id_Model].NumMat,
				&g_PlayerModel[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// 各モデルのオフセット情報を取得
	ImportOffsetPlayer(pFile, AmountModel);

	// 各モデルのテクスチャ情報を取得
	ImportTexPlayer(AmountModel);

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// モデルオフセット情報を読み込む
//************************************************
void ImportOffsetPlayer(FILE* pFile, int AmountModel)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int style = -1;				// このパーツのスタイルを格納
	int weapon = -1;			// このパーツの武器スタイルを格納
	int IdxParent = -1;			// 親のインデックスを格納
	D3DXVECTOR3 pos = {};		// 位置のオフセットを格納
	D3DXVECTOR3 rot = {};		// 向きのオフセットを格納
	int id_Model = 0;			// モデルの識別用

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // このパーツのスタイルを取得	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "WEAPON") == 0)
		{ // このパーツのスタイルを取得	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &weapon);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // 親パーツとなるものの番を取得	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置のオフセットを取得	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きのオフセットを取得	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// 読み込んだ情報をひな形にのみコピーする
			g_PlayerModel[id_Model].style = style;
			g_PlayerModel[id_Model].weapon = weapon;
			g_PlayerModel[id_Model].IdxParent = IdxParent;
			g_PlayerModel[id_Model].pos_offset = pos;
			g_PlayerModel[id_Model].rot_offset = rot;

			weapon = -1;	// 武器スタイルをリセット
			id_Model++;		// パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// 攻撃位置のオフセット情報を取得
	ImportOffsetAtkPlayer(pFile);
}

//************************************************
// (強引に) 攻撃位置のオフセット情報を読み込む
//************************************************
void ImportOffsetAtkPlayer(FILE* pFile)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int i = 0;					// 汎用整数
	D3DXVECTOR3 pos = {};		// 位置のオフセットを格納

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{ 
		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置のオフセットを反映

			// 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
			
			for (int j = 0; j < MAX_PLAYER; j++)
			{ // (無理やり) 全てのプレイヤーに反映
				g_Player[j].offset_atk[i].pos = pos;
			}

			i++;	// 次の番へ
		}

		if (i >= Max_itemstyle)
		{ // 武器の最大数に到達すると終了
			break;
		}
	}
}

//************************************************
// モデルテクスチャ情報を読み込む
//************************************************
void ImportTexPlayer(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int i = 0; i < AmountModel; i++)
	{
		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_PlayerModel[i].pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int j = 0; j < (int)g_PlayerModel[i].NumMat; j++)
		{
			// マテリアルの色オフセット
			g_PlayerModel[i].ColMat_offset[j] = pMat[j].MatD3D.Diffuse;

			// マテリアルにテクスチャが設定されていれば読込み
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_PlayerModel[i].pTex[j]);
			}
			else
			{
				g_PlayerModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// スタイル番号の照合
//************************************************
void VerifyStylePlayer(int id)
{
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		// 各プレイヤーのスタイル番号と各パーツのスタイル番号を照合
		if (g_PlayerModel[i].style == g_Player[id].param.style || g_PlayerModel[i].style == 99)
		{ // スタイル番号の一致しているパーツ及びユニパーツを有効化する
			g_Player[id].parts[i] = g_PlayerModel[i];
		}
	}
}

//************************************************
// モーション情報を読み込む
//************************************************
void ImportMotionPlayer(void)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int i = 0, j = 0, k = 0;	// 汎用整数
	int loop = 0;				// ループフラグを格納
	int amountKey = 0;			// 総キー数を取得
	int amountFrame = 0;		// 総フレーム数を取得
	D3DXVECTOR3 pos, rot;		// 位置と向きを格納

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\PLAYER\\player_motion.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "プレイヤーモーション情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "LOOP") == 0)
		{ // ループフラグを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &loop);
		}

		if (strcmp(&FileString[0], "NUM_KEY") == 0)
		{ // 総キー数を取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &amountKey);
		}

		if (strcmp(&FileString[0], "FRAME") == 0)
		{ // フレーム数を取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &amountFrame);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 動作位置を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 動作向きを取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_KEY") == 0)
		{ // パーツ動作情報を保存
			g_PlayerMotion[i].key[j].dest[k].pos = pos;
			g_PlayerMotion[i].key[j].dest[k].rot = rot;

			k++;	// パーツ番号を進める
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // キー情報を保存
			g_PlayerMotion[i].key[j].amount_frame = amountFrame;

			k = 0;	// パーツ番号をリセット
			j++;	// キー番号を進める
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // モーション情報を保存
			g_PlayerMotion[i].loop = loop;
			g_PlayerMotion[i].amount_key = amountKey;

			j = 0;	// キー番号をリセット
			i++;	// モーション番号を進める
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // 終了
			break;
		}
	}
}

//************************************************
// プレイヤー破棄
//************************************************
void UninitPlayer(void)
{
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_PlayerModel[i].pTex[j] != NULL)
			{ // テクスチャの破棄
				g_PlayerModel[i].pTex[j]->Release();
				g_PlayerModel[i].pTex[j] = NULL;
			}
		}

		if (g_PlayerModel[i].pMesh != NULL)
		{ // メッシュの破棄
			g_PlayerModel[i].pMesh->Release();
			g_PlayerModel[i].pMesh = NULL;
		}

		if (g_PlayerModel[i].pBuffMat != NULL)
		{ // マテリアルの破棄
			g_PlayerModel[i].pBuffMat->Release();
			g_PlayerModel[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// プレイヤー更新
//************************************************
void UpdatePlayer(int joined)
{
	for (int i = 0; i < joined; i++)
	{
		// 過去の位置を記録
		g_Player[i].pos_old = g_Player[i].pos;

		// 回転
		RotatePlayer(i);

		// 砲塔調整
		AdjustTurret(i);

		// 移動
		MovePlayer(i);

#ifdef _DEBUG

		// デバッグ移動
		if (i == g_P_id)
		{ // 選択している番号のみ
			DEBUG_MovePlayer();
		}

#endif	// _DEBUG

		// 攻撃
		AtkPlayer(i);

		// 負傷
		DamagePlayer(i);

		// 死亡
		//DeadPlayer(i);

		// モーション
		MotionPlayer(i);
	}

	// 最後に行列計算
	CalcMtxPlayer();

	/*---【以下デバッグ表示用】---*/
#ifdef _DEBUG

	Player* pPlayer;
	char pStr[8];

	if (GetKeyboardTrigger(DIK_BACK))
	{
		// 復活
		ResurrectPlayer(g_P_id);
	}

	pPlayer = &g_Player[g_P_id];

	switch (pPlayer->param.state)
	{
	case stateNormal_p:
		snprintf(&pStr[0], 8, "通常");
		break;

	case stateMove_p:
		snprintf(&pStr[0], 8, "移動");
		break;

	case stateAtk_p:
		snprintf(&pStr[0], 8, "攻撃");
		break;

	case stateDamage_p:
		snprintf(&pStr[0], 8, "被弾");
		break;

	case stateDead_p:
		snprintf(&pStr[0], 8, "死亡");
		break;

	default:

		// エラー
		assert(false && "いずれかのプレイヤー状態にエラー");

		break;
	}

	PrintDebugProc("【%dP】\nstate : %s\n", g_P_id + 1, &pStr[0]);	// ステータス
	PrintDebugProc("HP : %d\n", pPlayer->param.HP);					// 体力
	PrintDebugProc("SPD : %f\n", pPlayer->param.SPD);				// 速度

#endif	// _DEBUG
}

//************************************************
// プレイヤー回転
//************************************************
void RotatePlayer(int id)
{
	// ブレーキ力
	float StopEnergy = 0.1f;

	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	// 回転ブレーキ
	if (g_Player[id].rot_goal.y - g_Player[id].rot.y > D3DX_PI)
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_Player[id].rot_goal.y - g_Player[id].rot.y < -D3DX_PI)
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy);
	}
}

//************************************************
// 砲塔を視点方向へ向ける
//************************************************
void AdjustTurret(int id)
{
	// カメラ情報を取得
	Camera* pCamera = GetInfoCamera();

	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	for (int j = 0; j < AMOUNT_PLAYER_PARTS; j++)
	{ // 装備の変更を考慮し、描画のないパーツにも情報を与える

		// この番パーツの「親パーツ」のインデックスを保存
		int IdxParent = g_Player[id].parts[j].IdxParent;

#if OFFSET_VERIFY

		if (g_Player[id].parts[j].IdxParent == -1)
		{ // この番のパーツが土台パーツであるならスキップ
			continue;
		}

#else

		if (IdxParent != 0)
		{ // この番のパーツの親のモデル種類が土台パーツでないならスキップ
			continue;
		}

#endif	// OFFSET_VERIFY

		// 向きを視点正面方向へ
		g_Player[id].parts[j].rot_moved.y = pCamera[id].rot.y;
	}
}

//************************************************
// プレイヤー移動
//************************************************
void MovePlayer(int id)
{
	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	if (g_Player[id].param.state != stateDamage_p)
	{ // 被弾状態でなければ

		// カメラ情報を取得
		const Camera* pCamera = GetInfoCamera();

		if (GetJoyStickL(id))
		{ // 左スティックで移動
			const XINPUT_GAMEPAD GamePad = GetGamePad(id);

			// 移動量と目的の向きを付与
			g_Player[id].move.x += sinf(atan2f((float)(GamePad.sThumbLX * 0.00001), (float)(GamePad.sThumbLY * 0.00001)) + pCamera[id].rot.y);
			g_Player[id].move.z += cosf(atan2f((float)(GamePad.sThumbLX * 0.00001), (float)(GamePad.sThumbLY * 0.00001)) + pCamera[id].rot.y);
			g_Player[id].rot_goal.y = atan2f((float)(GamePad.sThumbLX * -0.000001), (float)(GamePad.sThumbLY * -0.000001)) + pCamera[id].rot.y;

			// 移動状態に
			g_Player[id].param.state = stateMove_p;

			// 砂エフェクト
			SetEffectSand(g_Player[id].pos, 0, 30.0f, id);
			SetEffectSand(g_Player[id].pos, 1, 30.0f, id);

			// 移動モーションを再生
			g_Player[id].param.motion_now = 1;
		}
		else
		{ // 移動していないので

			// 通常状態に
			g_Player[id].param.state = stateNormal_p;

			// 通常モーションを再生
			g_Player[id].param.motion_now = 0;
		}
	}

	g_Player[id].move *= SPD_STOPMOVE_PLAYER;	// ブレーキ

	// ある程度移動量が少ないと0を入れておく
	if (g_Player[id].move.x < EPSILON && g_Player[id].move.x > -EPSILON)
	{
		g_Player[id].move.x = 0.0f;
	}

	if (g_Player[id].move.z < EPSILON && g_Player[id].move.z > -EPSILON)
	{
		g_Player[id].move.z = 0.0f;
	}

	g_Player[id].pos += g_Player[id].move * SPD_MOVE_PLAYER;	// 移動
}

//************************************************
// デバッグ移動
//************************************************
void DEBUG_MovePlayer(void)
{
	if (g_Player[g_P_id].param.state != stateDamage_p)
	{ // 被弾状態でなければ

		// カメラ情報を取得
		const Camera* pCamera = GetInfoCamera();

		// デバッグ時はキーボード入力で移動可能
		float X = 0.0f;
		float Z = 0.0f;
		bool move = false;

		if (GetKeyboardTrigger(DIK_1))
		{
			g_P_id = 0;
		}
		else if (GetKeyboardTrigger(DIK_2))
		{
			g_P_id = 1;
		}
		else if (GetKeyboardTrigger(DIK_3))
		{
			g_P_id = 2;
		}
		else if (GetKeyboardTrigger(DIK_4))
		{
			g_P_id = 3;
		}

		if (GetKeyboardPress(DIK_A))
		{
			X = -1.0f;
		}
		else if (GetKeyboardPress(DIK_D))
		{
			X = 1.0f;
		}

		if (GetKeyboardPress(DIK_W))
		{
			Z = 1.0f;
		}
		else if (GetKeyboardPress(DIK_S))
		{
			Z = -1.0f;
		}

		if (X != 0.0f || Z != 0.0f)
		{ // 何かを入力していれば移動している判定
			move = true;
		}

		if (move)
		{
			// 移動量と目標向きを設定
			g_Player[g_P_id].move.x += sinf(atan2f(X, Z) + pCamera[g_P_id].rot.y);
			g_Player[g_P_id].move.z += cosf(atan2f(X, Z) + pCamera[g_P_id].rot.y);
			g_Player[g_P_id].rot_goal.y = atan2f(-X, -Z) + pCamera[g_P_id].rot.y;

			// 移動状態に
			g_Player[g_P_id].param.state = stateMove_p;

			// 砂エフェクト
			SetEffectSand(g_Player[g_P_id].pos, 0, 30.0f, g_P_id);
			SetEffectSand(g_Player[g_P_id].pos, 1, 30.0f, g_P_id);

			// 移動モーションを再生
			g_Player[g_P_id].param.motion_now = 1;
		}
		else
		{ // 移動していないので
			// 通常状態に
			g_Player[g_P_id].param.state = stateNormal_p;

			// 通常モーションを再生
			g_Player[g_P_id].param.motion_now = 0;
		}
	}

	g_Player[g_P_id].move *= SPD_STOPMOVE_PLAYER;	// ブレーキ

	g_Player[g_P_id].pos += g_Player[g_P_id].move * SPD_MOVE_PLAYER;	// 移動
}

//************************************************
// プレイヤーの攻撃
//************************************************
void AtkPlayer(int id)
{
	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	if (GetTriggerTriggerButtonR(id))
	{
		const XINPUT_GAMEPAD GamePad = GetGamePad(id);

		CreateBullet(bulletPlayer, id);
	}

#ifdef _DEBUG

	if (id == g_P_id)
	{
		if (GetKeyboardPress(DIK_SPACE))
		{
			CreateBullet(bulletPlayer, id);
		}
		else if (GetKeyboardTrigger(DIK_RETURN))
		{
			CreateBullet(bulletPlayer, id);
		}
	}

#endif	// _DEBUG
}

//************************************************
// プレイヤーの被弾時
//************************************************
void HitPlayer(int id)
{
	// 被弾状態でなければ被弾
	g_Player[id].param.state = stateDamage_p;	// 負傷状態に
	g_Player[id].param.motion_now = 3;			// 被弾モーション
	g_Player[id].motion[3].id_frame = 0;		// フレームをリセット
	g_Player[id].motion[3].id_key = 0;			// キーをリセット
	g_Player[id].param.dur = 45;				// 継続時間
	g_Player[id].param.HP--;

	/*---【お試し被弾エフェクト】---*/
	CreateEffect_Hayu(styleHeart, &g_Player[id].pos);
}

//************************************************
// プレイヤー負傷
//************************************************
void DamagePlayer(int id)
{
	if (g_Player[id].param.state != stateDamage_p)
	{ // 負傷状態でなければ終了
		return;
	}

	/*---【以下負傷状態時のみ】---*/

	// 点滅
	g_Player[id].col.a *= -1.0f;

	if(CntDuration(&g_Player[id].param.dur))
	{
		g_Player[id].param.state = stateNormal_p;	// 通常状態に戻す
		g_Player[id].col.a = 1.0f;					// 通常色に
	}
}

//************************************************
// プレイヤー死亡判定
//************************************************
void DeadPlayer(int id)
{
	if (g_Player[id].param.HP <= 0)
	{ // ライフが無くなると
		g_Player[id].param.state = stateDead_p;	// 死亡状態に
	}
}

//************************************************
// プレイヤー復活
//************************************************
void ResurrectPlayer(int id)
{
	if (g_Player[id].param.state == stateDead_p)
	{ // 死亡状態であれば
		g_Player[id].param.state = stateNormal_p;
		g_Player[id].param.HP = 3;	//!< 現段階では適当に設定
	}
}

//************************************************
// プレイヤーのモーション管理
//************************************************
void MotionPlayer(int id)
{
	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	// 再生情報格納用
	int* pNow = &g_Player[id].param.motion_now;				// 現在のモーション種類
	int* pOld = &g_Player[id].param.motion_old;				// 過去のモーション種類
	PlayerMotion* pMotion = &g_Player[id].motion[*pNow];	// 各プレイヤーのモーション情報

	// 変更を検知
	ChangeMotionPlayer(id, pNow, pOld);

	// パーツの動作
	MoveMotionPlayer(id, pMotion);

	// フレームカウント
	CntMotionPlayer(id, pMotion);
}

//************************************************
// プレイヤーのモーション変更検知
//************************************************
void ChangeMotionPlayer(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // 過去と現在の再生モーションが同じならリターン
		return;
	}

	// 過去のモーションのキーとフレームをリセット
	g_Player[id].motion[*pOld].id_key = 0;
	g_Player[id].motion[*pOld].id_frame = 0;

	// 新しいモーションへ移ったことを保存
	*pOld = *pNow;
}

//************************************************
// プレイヤーのモーション動作用
//************************************************
void MoveMotionPlayer(int id, PlayerMotion* pMotion)
{
	// 再生中のキーの総フレーム数から現在のフレーム番号を差し引く
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---【動作が必要な土台パーツのみモーションを反映】---*/
	g_Player[id].parts[0].pos_moved += (pMotion->key[pMotion->id_key].dest[0].pos - g_Player[id].parts[0].pos_moved) / dest;
	g_Player[id].parts[0].rot_moved += (pMotion->key[pMotion->id_key].dest[0].rot - g_Player[id].parts[0].rot_moved) / dest;
}

//************************************************
// プレイヤーのモーションカウント用
//************************************************
void CntMotionPlayer(int id, PlayerMotion* pMotion)
{		
	// フレームカウント
	pMotion->id_frame++;

	if (pMotion->id_frame >= pMotion->key[pMotion->id_key].amount_frame)
	{ // 再生中のキーの総フレーム分経過で

		// フレーム番号をリセットし
		pMotion->id_frame = 0;
		
		// キーカウント
		pMotion->id_key++;

		if (pMotion->id_key >= pMotion->amount_key)
		{ // 再生中のモーションの総キー数経過で

			if (pMotion->loop == 1)
			{ // ループフラグが有るなら

				// キー番号リセットしリターン
				pMotion->id_key = 0;
				return;
			}

			/*---【未定、試験的に待機モーション戻す】---*/
			g_Player[id].param.motion_now = 0;
		}
	}
}

//************************************************
// プレイヤー用のワールドマトリックスを計算
//************************************************
void CalcMtxPlayer(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	for (int P_id = 0; P_id < MAX_PLAYER; P_id++)
	{
		if (!g_Player[P_id].use)
		{ // この番使用フラグ無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player[P_id].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player[P_id].rot.y,
			g_Player[P_id].rot.x,
			g_Player[P_id].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_Player[P_id].mtxWorld,
			&g_Player[P_id].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Player[P_id].pos.x,
			g_Player[P_id].pos.y,
			g_Player[P_id].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Player[P_id].mtxWorld,
			&g_Player[P_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_PLAYER_PARTS; Ps_id++)
		{
			if (g_Player[P_id].parts[Ps_id].pMesh == NULL)
			{ // 未使用ならコンティニュー
				continue;
			}

			// この番パーツの「親パーツ」のインデックスを保存
			int IdxParent = g_Player[P_id].parts[Ps_id].IdxParent;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player[P_id].parts[Ps_id].mtxWorld);

			// モーション向きの反映
			D3DXVECTOR3 PartsRot =
			{
				g_Player[P_id].parts[Ps_id].rot_offset.x + g_Player[P_id].parts[Ps_id].rot_moved.x,
				g_Player[P_id].parts[Ps_id].rot_offset.y + g_Player[P_id].parts[Ps_id].rot_moved.y,
				g_Player[P_id].parts[Ps_id].rot_offset.z + g_Player[P_id].parts[Ps_id].rot_moved.z
			};

			if (IdxParent == 0)
			{ // この番の親パーツが「土台パーツ」であれば、移動方向への回転を打ち消す(砲塔が常に視点方向を向くため)
				PartsRot -= g_Player[P_id].rot;
			}

			// 向きを反映1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// 向きを反映2
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// モーション位置の反映
			D3DXVECTOR3 PartsPos =
			{
				g_Player[P_id].parts[Ps_id].pos_offset.x + g_Player[P_id].parts[Ps_id].pos_moved.x,
				g_Player[P_id].parts[Ps_id].pos_offset.y + g_Player[P_id].parts[Ps_id].pos_moved.y,
				g_Player[P_id].parts[Ps_id].pos_offset.z + g_Player[P_id].parts[Ps_id].pos_moved.z
			};

			// 位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// 位置を反映
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// 親のワールドマトリックスを取得
			if (IdxParent == -1)
			{ // 土台パーツのみワールド座標に直結
				mtxParent = g_Player[P_id].mtxWorld;
			}
			else if (IdxParent == 99)
			{ // ユニパーツは各プレイヤーの体のパーツに付随
				mtxParent = g_Player[P_id].parts[P_id + 1].mtxWorld;
			}
			else
			{ // 体のパーツは土台に付随
				mtxParent = g_Player[P_id].parts[IdxParent].mtxWorld;
			}

			// パーツごとのワールドマトリックスを算出
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}

		// (かなり無理のある) 攻撃位置の設定 (仮)
		for (int weapon_id = 0; weapon_id < Max_itemstyle; weapon_id++)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player[P_id].offset_atk[weapon_id].mtx);

			// 位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				g_Player[P_id].offset_atk[weapon_id].pos.x,
				g_Player[P_id].offset_atk[weapon_id].pos.y,
				g_Player[P_id].offset_atk[weapon_id].pos.z);

			// 位置を反映
			D3DXMatrixMultiply(&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].offset_atk[weapon_id].mtx,
				&mtxTrans);

			// 付随するであろう武器のマトリックスと強引にかけ合わせる…
			D3DXMatrixMultiply(&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].parts[weapon_id + 5].mtxWorld);
		}
	}
}

//************************************************
// プレイヤー描画
//************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	for (int id_P = 0; id_P < MAX_PLAYER; id_P++)
	{
		if (!g_Player[id_P].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player[id_P].mtxWorld);

		for (int id_Ps = 0; id_Ps < AMOUNT_PLAYER_PARTS; id_Ps++)
		{
			if (g_Player[id_P].parts[id_Ps].pMesh == NULL)
			{ // 空っぽならコンティニュー
				continue;
			}

			if (g_Player[id_P].parts[id_Ps].style == 99 &&
				g_Player[id_P].parts[id_Ps].IdxParent == 99 &&
				g_Player[id_P].param.weapon != g_PlayerModel[id_Ps].weapon)
			{ // ユニパーツの場合、武器の識別をスタイルが異なるとコンティニュー
				continue;
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player[id_P].parts[id_Ps].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player[id_P].parts[id_Ps].pBuffMat->GetBufferPointer();

			for (int id_mat = 0; id_mat < (int)g_Player[id_P].parts[id_Ps].NumMat; id_mat++)
			{
				// カラーA値反映
				pMat[id_mat].MatD3D.Diffuse.a = g_Player[id_P].col.a;

				// マテリアルの設定
				pDevice->SetMaterial(&pMat[id_mat].MatD3D);

				// テクスチャの設定
				if (g_Player[id_P].parts[id_Ps].pTex[id_mat] != NULL)
				{
					pDevice->SetTexture(0, g_Player[id_P].parts[id_Ps].pTex[id_mat]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// モデルパーツの描画
				g_Player[id_P].parts[id_Ps].pMesh->DrawSubset(id_mat);
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//************************************************
// 拡散光を変更
//************************************************
void ChangeDiffuseColPlayer(int player_id, int parts_id, int mat_id, D3DXMATERIAL * pMat)
{
	if (parts_id == 0)
	{ // プレイヤー本体のキャタピラパーツの色を変える…？
		switch (player_id)
		{
			// 緑
		case 0:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			break;

			// 赤
		case 1:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			break;

			// 青
		case 2:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			break
				;
			// 黄
		case 3:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			break;
		}
	}
}

//************************************************
// プレイヤー情報を取得
//************************************************
Player* GetInfoPlayer(void)
{
	return &g_Player[0];
}