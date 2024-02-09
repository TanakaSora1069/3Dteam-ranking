//************************************************
//
// ボス処理[boss.cpp]
// Author：葛西敬介
//
//************************************************

/*/ インクルードファイル /*/
#include "boss.h"
#include "collision.h"
#include "player.h"
#include "visible_sph.h"
// 中枢
#include "game.h"
#include "input.h"
#include "sound.h"

#include <stdlib.h>
#include <time.h>

// 諸処理
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif	// _DEBUG

/*/ グローバル変数 /*/
BOSSModel g_BossModel[AMOUNT_BOSS_PARTS];	// ボス用モデル情報のひな形
BossMotion g_BossMotion[NUM_MOTION];		// ボスモーション情報のひな形
BOSS g_aBoss[MAX_BOSS];						// ボス情報
int g_nCntStop = 0;							// 動かなくさせる時間
D3DXVECTOR3 g_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//ボスの移動量


//************************************************
// ボス初期
//************************************************
void InitBoss(void)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{ // ボス用モデル情報のひな形のリセット
		BOSSModel* pModel = &g_BossModel[i];

		// スタイル
		pModel->style = 0;

		// モデル
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // マテリアル
			pModel->pTex[j] = NULL;
		}

		// モデル座標
		pModel->pos_offset = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 親インデックス
		pModel->IdxParent = -1;
	}

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_BOSS; i++)
	{ // ボス情報のリセット
		BOSS* pBoss = &g_aBoss[i];

		// 使用フラグ
		pBoss->use = false;

		// パラメータ
		pBoss->Param.style = 0;								//番号
		pBoss->Param.state = stateNormal_b;					//状態
		pBoss->Param.dur = 0;								//HPがなくなってから描画されなくなるまでの時間
		pBoss->Param.HP = 0;								//ライフ
		pBoss->Param.SPD = D3DXVECTOR3(0.0f,0.0f,0.0f);		//移動量
		pBoss->Param.Radius = 0.0f;							//当たり判定の半径
		pBoss->Param.motion_now = 0;						//今再生中のモーション
		pBoss->Param.motion_old = 0;						//1つ前に再生されていたモーション
		//pBoss->Param.bMove = true;							//移動しているかどうか

		// 座標
		pBoss->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 色
		pBoss->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		// 判定識別番号
		pBoss->id_sph = -1;


		for (int j = 0; j < AMOUNT_BOSS_PARTS; j++)
		{ // 各パーツ情報をリセット
			BOSSModel* pModel = &pBoss->parts[j];

			// モデル
			pModel->pMesh = NULL;
			pModel->pBuffMat = NULL;
			pModel->NumMat = 0;

			for (int k = 0; k < AMOUNT_MAT; k++)
			{ // マテリアル
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
	}

	/*--------------------------------------------*/

	// ボス用のモデル情報を取得
	ImportModelBoss();

	// ボス用のモーション情報を取得
	ImportMotionBoss();

	// ボス用のパラメータ情報を取得
	ImportParamBoss();

	/*---【モーション情報をコピー(修正予定)】---*/
	for (int i = 0; i < MAX_BOSS; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (g_BossMotion[j].amount_key == 0)
			{ // 未使用ならコンティニュー
				continue;
			}

			// モーション情報をコピー
			g_aBoss[i].motion[j] = g_BossMotion[j];
		}

		g_aBoss[i].Param.bMove = true;	//移動しているかどうか

	}
	//グローバル変数の初期化
	g_nCntStop = 0;	//敵のスタン時間
	g_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ローカル変数宣言
	D3DXVECTOR3 KeepMove = D3DXVECTOR3(0.0f,0.0f,0.0f);
	float fNumberx = 0.0f;
	float fNumberz = 0.0f;
	float fKeepNumx = 0.0f;
	float fKeepNumz = 0.0f;

	//敵の挙動の算出
	srand((unsigned int)time(NULL));
	fNumberx = rand() % 50 + 1;
	fNumberz = rand() % 50 + 1;

	fKeepNumx = fNumberx / 10;
	fKeepNumz = fNumberz / 10;

	KeepMove = D3DXVECTOR3(fKeepNumx / 10, 0.0f, fKeepNumz / 10);

	g_Move = D3DXVECTOR3(KeepMove.x, KeepMove.y, KeepMove.z);


	
	/******************************/

	/*---【試験的に敵を配置(消去予定)】---*/

	//DEBUG_GenerateEnemy();

	/******************************/
}

//************************************************
// モデル情報を読み込む
//************************************************
void ImportModelBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int AmountModel = 0;		// モデルの数を格納
	int id_Model = 0;			// モデルの識別用

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "ボスモデル情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// 読み込むモデル数を取得する
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &AmountModel);
		}

#ifdef _DEBUG

		// エラー
		assert(AmountModel < AMOUNT_BOSS_PARTS && "ボスモデルモデル情報が最大量を越えました");

#endif

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// 読み込むモデル名を取得する
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%s", &FileString[0], 128);

			// 読み込んだ情報をひな形にのみコピーする
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_BossModel[id_Model].pBuffMat,
				NULL,
				&g_BossModel[id_Model].NumMat,
				&g_BossModel[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// 各モデルのオフセット情報を取得
	ImportOffsetBoss(pFile, AmountModel);

	// 各モデルのテクスチャ情報を取得
	ImportTexBoss(AmountModel);

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// モデルオフセット情報を読み込む
//************************************************
void ImportOffsetBoss(FILE* pFile, int AmountModel)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int Style = -1;				// このパーツのスタイルを格納
	int IdxParent = -1;			// 親のインデックスを格納
	D3DXVECTOR3 pos = {};		// 位置のオフセットを格納
	D3DXVECTOR3 rot = {};		// 向きのオフセットを格納
	int id_Model = 0;			// モデルの識別用

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // このパーツのスタイルを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &Style);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // 親のインデックスを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置のオフセットを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きのオフセットを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// 読み込んだ情報をひな形にのみコピーする
			g_BossModel[id_Model].style = Style;
			g_BossModel[id_Model].IdxParent = IdxParent;
			g_BossModel[id_Model].pos_offset = pos;
			g_BossModel[id_Model].rot_offset = rot;

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}
}

//************************************************
// モデルテクスチャ情報を読み込む
//************************************************
void ImportTexBoss(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int i = 0; i < AmountModel; i++)
	{
		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_BossModel[i].pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int j = 0; j < (int)g_BossModel[i].NumMat; j++)
		{
			// マテリアルにテクスチャが設定されていれば読込み
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_BossModel[i].pTex[j]);
			}
			else
			{
				g_BossModel[i].pTex[j] = NULL;
			}
		}
	}
}

//************************************************
// 敵のパラメータ情報の読込み
//************************************************
void ImportParamBoss(void)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};		// 文章を格納
	int i = 0;						// 汎用整数
	int appear = 0;					// 出現タイミングを格納
	int style = 0;					// スタイルを格納
	float hp = 0.0f;				// ライフを格納
	float radius = 0.0f;			// 半径を格納(当たり判定用)
	//float spd = 0;				// 速度を格納
	D3DXVECTOR3 pos, rot, spd;		// 位置と向きを格納

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_param.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "ボスパラメータ情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (i >= MAX_BOSS)
		{ // 敵の最大数を越えると強制終了
			break;
		}

		if (strcmp(&FileString[0], "APPEAR") == 0)
		{ // 出現タイミングを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 64, &appear);
		}

		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // スタイルを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 64, &style);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // ライフを取得
			fscanf_s(pFile, "%s %f", &FileString[0], 64, &hp);
		}

		if (strcmp(&FileString[0], "SPD") == 0)
		{ // 速度を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &spd.x,&spd.y,&spd.z);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きを取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "RADIUS") == 0)
		{ // 向きを取得
			fscanf_s(pFile, "%s %f", &FileString[0], 64, &radius);
		}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // 取得した情報を反映
			g_aBoss[i].Param =
			{
				appear, style, 0, 0, hp,spd,radius
			};

			g_aBoss[i].pos = pos;
			g_aBoss[i].rot = rot;

			i++;	// 次の番号へ
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{
			break;	// 終了
		}
	}
}

////************************************************
//// 敵の出現設定
////************************************************
//void DEBUG_GenerateEnemy(void)
//{
//	/*---【現在、試験的に敵の情報設定(修正予定)】---*/
//	for (int i = 0; i < MAX_BOSS; i++)
//	{
//		// パラメータ
//		g_aBoss[i].Param.style = 0;
//		g_aBoss[i].Param.SPD = 0.1f + i * 0.1f;
//
//		g_aBoss[i].use = true;
//		g_aBoss[i].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
//
//		// スタイル番号を照合
//		VerifyStyleBOSS(i);
//
//		break;	// 1体のみ
//	}
//}

//************************************************
// スタイル番号の照合
//************************************************
void VerifyStyleBoss(int id)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		if (g_aBoss[id].Param.style == g_BossModel[i].style)
		{ // 各ボスのスタイルと全パーツのスタイルを照合
			g_aBoss[id].parts[i] = g_BossModel[i];	//!< 番号の一致しているパーツのみ有効化
		}
	}
}

//************************************************
// モーション情報を読み込む
//************************************************
void ImportMotionBoss(void)
{
	 //ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int i = 0, j = 0, k = 0;	// 汎用整数
	int Loop = 0;				// ループフラグを格納
	int AmountKey = 0;			// 総キー数を取得
	int AmountFrame = 0;		// 総フレーム数を取得
	D3DXVECTOR3 pos, rot;		// 位置と向きを格納

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_motion.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "エネミーモーション情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "LOOP") == 0)
		{ // ループフラグを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &Loop);
		}

		if (strcmp(&FileString[0], "NUM_KEY") == 0)
		{ // 総キー数を取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountKey);
		}

		if (strcmp(&FileString[0], "FRAME") == 0)
		{ // フレーム数を取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountFrame);
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
			g_BossMotion[i].key[j].dest[k].pos = pos;
			g_BossMotion[i].key[j].dest[k].rot = rot;

			k++;	// パーツ番号を進める
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // キー情報を保存
			g_BossMotion[i].key[j].amount_frame = AmountFrame;

			k = 0;	// パーツ番号をリセット
			j++;	// キー番号を進める
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // モーション情報を保存
			g_BossMotion[i].loop = Loop;
			g_BossMotion[i].amount_key = AmountKey;

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
// ボス破棄
//************************************************
void UninitBoss(void)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_BossModel[i].pTex[j] != NULL)
			{ // テクスチャの破棄
				g_BossModel[i].pTex[j]->Release();
				g_BossModel[i].pTex[j] = NULL;
			}
		}

		if (g_BossModel[i].pMesh != NULL)
		{ // メッシュの破棄
			g_BossModel[i].pMesh->Release();
			g_BossModel[i].pMesh = NULL;
		}

		if (g_BossModel[i].pBuffMat != NULL)
		{ // マテリアルの破棄
			g_BossModel[i].pBuffMat->Release();
			g_BossModel[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// ボス更新
//************************************************
void UpdateBoss(void)
{
	for (int i = 0; i < MAX_BOSS; i++)
	{
		// 出現
		AppearBoss(i);

		// 過去の位置を記録
		g_aBoss[i].pos_old = g_aBoss[i].pos;

		// 回転
		RotateBoss(i);

		//移動
		MoveBoss(i);

		//被弾
		DamageBoss(i);

		//死亡
		DeadBoss(i);

		// モーション
		MotionBoss(i);

	}

	// 最後に行列計算
	CalcMtxBoss();
#ifdef _DEBUG

	PrintDebugProc("ボスの座標 : %f %f %f\n", g_aBoss[0].pos.x, g_aBoss[0].pos.y, g_aBoss[0].pos.z);
	PrintDebugProc("ボスの向き : %f %f %f\n", g_aBoss[0].rot.x, g_aBoss[0].rot.y, g_aBoss[0].rot.z);
#endif

#ifdef _DEBUG

	for (int i = 0; i < 1; i++)
	{
		BOSS* pBoss = &g_aBoss[i];
		char pStr[8];

		switch (pBoss->Param.state)
		{
		case stateNormal_b:
			snprintf(&pStr[0], 8, "通常");
			break;

		case stateMove_b:
			snprintf(&pStr[0], 8, "移動");
			break;

		case stateAtk_b:
			snprintf(&pStr[0], 8, "攻撃");
			break;

		case stateDamage_b:
			snprintf(&pStr[0], 8, "被弾");
			break;

		case stateDead_b:
			snprintf(&pStr[0], 8, "死亡");
			break;

		default:

			// エラー
			assert(false && "いずれかのエネミー状態にエラー");

			break;
		}

		PrintDebugProc("【%dB】\nstate : %s\n", i + 1, &pStr[0]);	// ステータス
		PrintDebugProc("HP : %f\n", pBoss->Param.HP);				// ライフ
		PrintDebugProc("SPD : %f\n", pBoss->Param.SPD);				// 速度
	}
#endif
}

//************************************************
// ボス出現
//************************************************
void AppearBoss(int id)
{
	if (g_aBoss[id].Param.appear > 0)
	{ // 出現タイミングが設定されていれば
		g_aBoss[id].Param.appear--;

		if (g_aBoss[id].Param.appear <= 0)
		{ // 出現タイミング時間に到達で
			g_aBoss[id].use = true;

			// スタイル番号を照合
			VerifyStyleBoss(id);
#ifdef _DEBUG
			// このとき当たり判定を可視化
			g_aBoss[id].id_sph = CreateVisibleSph(g_aBoss[id].Param.Radius, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_aBoss[id].pos);
#endif
		}
	}
}

//************************************************
// ボス回転
//************************************************
void RotateBoss(int id)
{
	// ブレーキ力
	float StopEnergy = 0.1f;

	// 回転ブレーキ
	if (g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y > D3DX_PI)
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y < -D3DX_PI)
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy);
	}
}

//************************************************
// ボス移動
//************************************************
void MoveBoss(int id)
{
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{

		switch (g_aBoss[nCntBoss].Param.style)
		{
		case 0:
			MidBossBehavior(nCntBoss);	//中ボスの挙動
			break;
		case 1:
			BigBossBehavior(nCntBoss);	//大ボスの挙動
			break;
		default:
			break;
		}
	}
}

//************************************************
// 中ボスの挙動
//************************************************
void MidBossBehavior(int id)
{
	if (g_aBoss[id].use && g_aBoss[id].Param.state != stateDamage_b && g_aBoss[id].Param.state != stateDead_b)
	{
		g_aBoss[id].Param.state = stateMove_b;		// 移動状態

		//向きを決める
		g_aBoss[id].rot_goal.y = atan2f(-g_aBoss[id].Param.SPD.x - g_Move.x , -g_aBoss[id].Param.SPD.z - g_Move.z);

		if (g_aBoss[id].Param.bMove)
		{
			//位置を動かす
			g_aBoss[id].pos += g_Move + g_aBoss[id].Param.SPD;
		}

	}

}

//************************************************
// 大ボスの挙動
//************************************************
void BigBossBehavior(int id)
{

}

//************************************************
// ボスの当たり判定
//************************************************
void HitBoss(int id)
{
	g_aBoss[id].Param.state = stateDamage_b;	// 負傷状態に
	g_aBoss[id].Param.dur = 20;				// 継続時間を付与
	g_aBoss[id].Param.HP--;						// HPを減らす

}

//************************************************
// ボスの負傷判定
//************************************************
void DamageBoss(int id)
{
	if (g_aBoss[id].Param.state != stateDamage_b)
	{ // 負傷状態でなければ終了
		return;
	}

	/*---【以下負傷状態時のみ】---*/

	// 点滅
	g_aBoss[id].col.a *= -1.0f;


	if (CntDuration(&g_aBoss[id].Param.dur))
	{
		g_aBoss[id].Param.state = stateNormal_b;	// 通常状態に
		g_aBoss[id].col.a = 1.0f;					// 通常色に

			//ローカル変数宣言
		D3DXVECTOR3 KeepMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float fNumberx = 0.0f;
		float fNumberz = 0.0f;
		float fKeepNumx = 0.0f;
		float fKeepNumz = 0.0f;

		//敵の挙動の算出
		srand((unsigned int)time(NULL));
		fNumberx = rand() % 50 + 1;
		fNumberz = rand() % 50 + 1;

		fKeepNumx = fNumberx / 10;
		fKeepNumz = fNumberz / 10;

		KeepMove = D3DXVECTOR3(fKeepNumx / 10, 0.0f, fKeepNumz / 10);

		g_Move = D3DXVECTOR3(KeepMove.x, KeepMove.y, KeepMove.z);

	}

}

//************************************************
// ボスの死亡判定
//************************************************
void DeadBoss(int id)
{
	if (g_aBoss[id].Param.state == stateDamage_b && g_aBoss[id].Param.HP <= 0.0f)
	{ // 負傷状態で体力が無いときのみ
		g_aBoss[id].Param.state = stateDead_b;	// 死亡状態に
		g_aBoss[id].Param.dur = 180;			// 継続時間付与
		g_aBoss[id].col.a = 0.5f;				// 半透明に
	}


	if (g_aBoss[id].Param.state != stateDead_b)
	{ // 死亡状態でなければ終了
		return;
	}

	/*---【以下死亡状態時のみ】---*/

	if (CntDuration(&g_aBoss[id].Param.dur))
	{
		/*---【無限に現れず、かつ復活の予定もあるためこれで】---*/
		g_aBoss[id].use = false;	// 使用フラグ

#ifdef _DEBUG

		// 判定可視化のみ邪魔なので消去
		DeleteVisibleSph(g_aBoss[id].id_sph);

#endif	// _DEBUG

		g_aBoss[id].id_sph = -1;	// 役目を終えた数値もリセット
	}
}



//************************************************
// ボスの復活判定
//************************************************
void ResurrectBoss(int id)
{
	if (g_aBoss[id].Param.state == stateDead_b)
	{ // 死亡状態であれば
		g_aBoss[id].Param.state = stateNormal_b;
		g_aBoss[id].Param.HP = 3;	//!< 現段階では適当に設定
	}				

}

//************************************************
// モーション管理処理
//************************************************
void MotionBoss(int id)
{
	if (!g_aBoss[id].use)
	{ // 未使用ならリターン
		return;
	}

	// 再生情報格納用
	int* pNow = &g_aBoss[id].Param.motion_now;			// 現在のモーション種類
	int* pOld = &g_aBoss[id].Param.motion_old;			// 過去のモーション種類
	BossMotion* pMotion = &g_aBoss[id].motion[*pNow];	// 各エネミーのモーション情報

	switch (g_aBoss[id].Param.state)
	{
	case stateNormal_b:
		g_aBoss[id].Param.motion_now = motion_neutral;		//ニュートラルモーション
		break;
	case stateMove_b:
		g_aBoss[id].Param.motion_now = motion_move;			//移動モーション
		break;
	case stateAtk_b:
		g_aBoss[id].Param.motion_now = motion_action;		//攻撃モーション
		break;
	case stateDamage_b:
		g_aBoss[id].Param.motion_now = motion_neutral;		//被弾モーション
		break;
	case stateDead_b:
		g_aBoss[id].Param.motion_now = motion_collapse;		//死亡モーション
		break;
	case steteResurrect_b:
		g_aBoss[id].Param.motion_now = motion_Resurrect;	//復活モーション
		break;

	}

	// 変更を検知
	ChangeMotionBoss(id, pNow, pOld);

	// パーツの動作
	MoveMotionBoss(id, pMotion);

	// フレームカウント
	CntMotionBoss(id, pMotion);

}

//************************************************
// モーション変更処理
//************************************************
void ChangeMotionBoss(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // 過去と現在の再生モーションが同じならリターン
		return;
	}

	// 過去のモーションのキーとフレームをリセット
	g_aBoss[id].motion[*pOld].id_key = 0;
	g_aBoss[id].motion[*pOld].id_frame = 0;

	// 新しいモーションへ移ったことを保存
	*pOld = *pNow;

}

//************************************************
// モーション動作処理
//************************************************
void MoveMotionBoss(int id, BossMotion* pMotion)
{
	// 再生中のキーの総フレーム数から現在のフレーム番号を差し引く
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---【試験的に、使用されているパーツの数分】---*/
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		{ // パーツが未使用ならコンティニュー
			if (g_aBoss[id].parts[i].pMesh == NULL)
				continue;
		}

		g_aBoss[id].parts[i].pos_moved += (pMotion->key[pMotion->id_key].dest[i].pos - g_aBoss[id].parts[i].pos_moved) / dest;
		g_aBoss[id].parts[i].rot_moved += (pMotion->key[pMotion->id_key].dest[i].rot - g_aBoss[id].parts[i].rot_moved) / dest;
	}

}

//************************************************
// モーションカウント用
//************************************************
void CntMotionBoss(int id, BossMotion* pMotion)
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
			g_aBoss[id].Param.motion_now = 0;
		}
	}

}

//************************************************
// ボス用のワールドマトリックスを計算
//************************************************
void CalcMtxBoss(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	for (int enemy_id = 0; enemy_id < MAX_BOSS; enemy_id++)
	{
		if (!g_aBoss[enemy_id].use)
		{ // この番の使用フラグが無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBoss[enemy_id].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aBoss[enemy_id].rot.y,
			g_aBoss[enemy_id].rot.x,
			g_aBoss[enemy_id].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_aBoss[enemy_id].mtxWorld,
			&g_aBoss[enemy_id].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aBoss[enemy_id].pos.x,
			g_aBoss[enemy_id].pos.y,
			g_aBoss[enemy_id].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_aBoss[enemy_id].mtxWorld,
			&g_aBoss[enemy_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_BOSS_PARTS; Ps_id++)
		{
			if (g_aBoss[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // 空っぽならコンティニュー
				continue;
			}

			// この番パーツの「親パーツ」のインデックスを保存
			int IdxParent = g_aBoss[enemy_id].parts[Ps_id].IdxParent;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld);

			// モーション向きの反映
			D3DXVECTOR3 PartsRot =
			{
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.x + g_aBoss[enemy_id].parts[Ps_id].rot_moved.x,
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.y + g_aBoss[enemy_id].parts[Ps_id].rot_moved.y,
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.z + g_aBoss[enemy_id].parts[Ps_id].rot_moved.z
			};

			// 向きを反映1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// 向きを反映2
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// モーション位置の反映
			D3DXVECTOR3 PartsPos =
			{
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.x + g_aBoss[enemy_id].parts[Ps_id].pos_moved.x,
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.y + g_aBoss[enemy_id].parts[Ps_id].pos_moved.y,
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.z + g_aBoss[enemy_id].parts[Ps_id].pos_moved.z
			};

			// 位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// 位置を反映
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// 親のワールドマトリックスを取得
			if (IdxParent == -1)
			{ //メインパーツのみワールド座標に直結
				mtxParent = g_aBoss[enemy_id].mtxWorld;
			}
			else
			{ //その他パーツはそれぞれの親パーツへ付随
				mtxParent = g_aBoss[enemy_id].parts[IdxParent].mtxWorld;
			}

			// パーツごとのワールドマトリックスを算出
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}
	}
}

//************************************************
// ボス描画
//************************************************
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	for (int enemy_id = 0; enemy_id < MAX_BOSS; enemy_id++)
	{
		if (!g_aBoss[enemy_id].use)
		{ // この番の使用フラグが無しでコンティニュー
			continue;
		}
		 
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[enemy_id].mtxWorld);

		for (int Ps_id = 0; Ps_id < AMOUNT_BOSS_PARTS; Ps_id++)
		{
			if (g_aBoss[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // 空っぽならコンティニュー
				continue;
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[enemy_id].parts[Ps_id].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aBoss[enemy_id].parts[Ps_id].pBuffMat->GetBufferPointer();

			for (int mat_id = 0; mat_id < (int)g_aBoss[enemy_id].parts[Ps_id].NumMat; mat_id++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[mat_id].MatD3D);

				// テクスチャの設定
				if (g_aBoss[enemy_id].parts[Ps_id].pTex[mat_id] != NULL)
				{
					pDevice->SetTexture(0, g_aBoss[enemy_id].parts[Ps_id].pTex[mat_id]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// モデルパーツの描画
				g_aBoss[enemy_id].parts[Ps_id].pMesh->DrawSubset(mat_id);
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}

	}
}

//************************************************
// ボス情報を取得
//************************************************
BOSS* GetInfoBoss(void)
{
	return g_aBoss;
}	

