//************************************************
//
// エネミー処理[enemy.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "enemy.h"
// 中枢
#include "input.h"
#include "sound.h"
// 諸処理
#include "collision.h"
#include "game.h"
#include "player.h"
#include "shadow.h"
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*/ グローバル変数 /*/
EnemyModel g_EnemyModel[AMOUNT_ENEMY_PARTS];	// エネミー用モデル情報のひな形
EnemyMotion g_EnemyMotion[8];					// エネミーモーション情報のひな形
Enemy g_Enemy[AMOUNT_ENEMY];					// エネミー情報

float g_movePower = 0.0f;

//************************************************
// エネミー初期
//************************************************
void InitEnemy(void)
{
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{ // エネミー用モデル情報のひな形のリセット
		EnemyModel* pModel = &g_EnemyModel[i];

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
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 親インデックス
		pModel->IdxParent = -1;
	}

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{ // エネミー情報のリセット
		Enemy* pEnemy = &g_Enemy[i];

		// 使用フラグ
		pEnemy->use = false;

		// パラメータ
		pEnemy->param =
		{
			0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0		// メンバー情報はヘッダファイルを確認して下さい
		};

		// 座標系
		pEnemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 色
		pEnemy->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
		{ // 各パーツ情報をリセット
			EnemyModel* pModel = &pEnemy->parts[j];

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

		// 識別番号
		pEnemy->id_shadow = -1;
		pEnemy->id_sph = -1;
	}

	/*--------------------------------------------*/

	// エネミー用のモデル情報を取得
	ImportModelEnemy();

	// エネミー用のモーション情報を取得
	ImportMotionEnemy();

	// エネミー用のパラメータ情報を取得
	ImportParamEnemy();

	/*---【モーション情報をコピー(修正予定)】---*/
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (g_EnemyMotion[j].amount_key == 0)
			{ // 未使用ならコンティニュー
				continue;
			}

			// モーション情報をコピー
			g_Enemy[i].motion[j] = g_EnemyMotion[j];
		}
	}
}

//************************************************
// モデル情報を読み込む
//************************************************
void ImportModelEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int AmountModel = 0;		// モデルの数を格納
	int id_Model = 0;			// モデルの識別用

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "エネミーモデル情報の展開に失敗");

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
		assert(AmountModel < AMOUNT_ENEMY_PARTS && "エネミーモデルモデル情報が最大量を越えました");

#endif

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// 読み込むモデル名を取得する
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// 読み込んだ情報をひな形にのみコピーする
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_EnemyModel[id_Model].pBuffMat,
				NULL,
				&g_EnemyModel[id_Model].NumMat,
				&g_EnemyModel[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// 各モデルのオフセット情報を取得
	ImportOffsetEnemy(pFile, AmountModel);

	// 各モデルのテクスチャ情報を取得
	ImportTexEnemy(AmountModel);

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// モデルオフセット情報を読み込む
//************************************************
void ImportOffsetEnemy(FILE* pFile, int AmountModel)
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
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &Style);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // 親のインデックスを取得	
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
			g_EnemyModel[id_Model].style = Style;
			g_EnemyModel[id_Model].IdxParent = IdxParent;
			g_EnemyModel[id_Model].pos_offset = pos;
			g_EnemyModel[id_Model].rot_offset = rot;

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
void ImportTexEnemy(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int i = 0; i < AmountModel; i++)
	{
		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_EnemyModel[i].pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int j = 0; j < (int)g_EnemyModel[i].NumMat; j++)
		{
			// マテリアルにテクスチャが設定されていれば読込み
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_EnemyModel[i].pTex[j]);
			}
			else
			{
				g_EnemyModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// 敵のパラメータ情報の読込み
//************************************************
void ImportParamEnemy(void)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int i = 0;					// 汎用整数
	int appear = 0;				// 出現タイミングを格納
	int style = 0;				// スタイルを格納
	int hp = 0;					// ライフを格納
	float spd = 0;				// 速度を格納
	float rad = 0;				// 判定サイズを格納
	D3DXVECTOR3 pos, rot;		// 位置と向きを格納

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_param.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "エネミーパラメータ情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "APPEAR") == 0)
		{ // 出現タイミングを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &appear);
		}

		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // スタイルを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // ライフを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &hp);
		}

		if (strcmp(&FileString[0], "SPD") == 0)
		{ // 速度を取得
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &spd);
		}

		if (strcmp(&FileString[0], "RAD") == 0)
		{ // 判定サイズを取得
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &rad);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きを取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // 取得した情報を反映
			g_Enemy[i].param =
			{
				appear, style, 0, 0, -1, hp, spd, rad, 0, 0
			};
			g_Enemy[i].pos = pos;
			g_Enemy[i].rot = rot;

			i++;	// 次の番号へ

			if (i >= AMOUNT_ENEMY)
			{ // 敵の最大数を越えると強制終了
				break;
			}
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{
			break;	// 終了
		}
	}
}

//************************************************
// スタイル番号の照合
//************************************************
void VerifyStyleEnemy(int id)
{
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		if (g_Enemy[id].param.style == g_EnemyModel[i].style)
		{ // 各エネミーのスタイルと全パーツのスタイルを照合
			g_Enemy[id].parts[i] = g_EnemyModel[i];	//!< 番号の一致しているパーツのみ有効化
		}
	}
}

//************************************************
// モーション情報を読み込む
//************************************************
void ImportMotionEnemy(void)
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
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_motion.txt", "r") != 0)
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
			g_EnemyMotion[i].key[j].dest[k].pos = pos;
			g_EnemyMotion[i].key[j].dest[k].rot = rot;

			k++;	// パーツ番号を進める
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // キー情報を保存
			g_EnemyMotion[i].key[j].amount_frame = amountFrame;

			k = 0;	// パーツ番号をリセット
			j++;	// キー番号を進める
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // モーション情報を保存
			g_EnemyMotion[i].loop = loop;
			g_EnemyMotion[i].amount_key = amountKey;

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
// エネミー破棄
//************************************************
void UninitEnemy(void)
{
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_EnemyModel[i].pTex[j] != NULL)
			{ // テクスチャの破棄
				g_EnemyModel[i].pTex[j]->Release();
				g_EnemyModel[i].pTex[j] = NULL;
			}
		}

		if (g_EnemyModel[i].pMesh != NULL)
		{ // メッシュの破棄
			g_EnemyModel[i].pMesh->Release();
			g_EnemyModel[i].pMesh = NULL;
		}

		if (g_EnemyModel[i].pBuffMat != NULL)
		{ // マテリアルの破棄
			g_EnemyModel[i].pBuffMat->Release();
			g_EnemyModel[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// エネミー更新
//************************************************
void UpdateEnemy(void)
{
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		// 出現：使用状況に関わらない
		AppearEnemy(i);

		// 過去の位置を記録
		g_Enemy[i].pos_old = g_Enemy[i].pos;

		// 回転
		RotateEnemy(i);

		// 移動
		MoveEnemy(i);

		// 攻撃
		AtkEnemy(i);

		// 負傷
		DamageEnemy(i);

		// 死亡
		DeadEnemy(i);

		// モーション
		MotionEnemy(i);
	}

	// 最後に行列計算
	CalcMtxEnemy();

#ifdef _DEBUG

	for (int i = 0; i < 3; i++)
	{
		Enemy* pEnemy = &g_Enemy[i];
		char pStr[8];

		switch (pEnemy->param.state)
		{
		case stateNormal_e:
			snprintf(&pStr[0], 8, "通常");
			break;

		case stateMove_e:
			snprintf(&pStr[0], 8, "移動");
			break;

		case stateAtk_e:
			snprintf(&pStr[0], 8, "攻撃");
			break;

		case stateCharge_e:
			snprintf(&pStr[0], 8, "溜め");
			break;

		case stateRotate_e:
			snprintf(&pStr[0], 8, "回転");
			break;

		case stateDamage_e:
			snprintf(&pStr[0], 8, "被弾");
			break;

		case stateDead_e:
			snprintf(&pStr[0], 8, "死亡");
			break;

		default:

			// エラー
			assert(false && "いずれかのエネミー状態にエラー");

			break;
		}

		PrintDebugProc("【%dE】\nstate : %s\n", i + 1, &pStr[0]);	// ステータス
		PrintDebugProc("HP : %d\n", pEnemy->param.HP);				// ライフ
		PrintDebugProc("SPD : %f\n", pEnemy->param.SPD);			// 速度
	}

#endif	// _DEBUG

}

//************************************************
// エネミー出現
//************************************************
void AppearEnemy(int id)
{
	if (g_Enemy[id].param.appear > 0 && !g_Enemy[id].use)
	{ // 未使用のもので出現タイミングが設定されていれば

		g_Enemy[id].param.appear--;

		if (g_Enemy[id].param.appear <= 0)
		{ // 出現タイミング時間に到達で
			g_Enemy[id].use = true;

			// 追跡対象となるプレイヤーを決める
			g_Enemy[id].param.target = SetTargetEnemy(id);

			// スタイル番号を照合
			VerifyStyleEnemy(id);

			// 影を生成
			g_Enemy[id].id_shadow = CreateShadow(&g_Enemy[id].pos, 40.0f);

#ifdef _DEBUG

			// このとき当たり判定を可視化
			g_Enemy[id].id_sph = CreateVisibleSph(g_Enemy[id].param.rad, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_Enemy[id].pos);

#endif	// _DEBUG 
		}
	}
}

//************************************************
// エネミー回転
//************************************************
void RotateEnemy(int id)
{
	// ブレーキ力
	float StopEnergy = 0.1f;

	// 回転ブレーキ
	if (g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y > D3DX_PI)
	{
		g_Enemy[id].rot.y += ((g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y < -D3DX_PI)
	{
		g_Enemy[id].rot.y += ((g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_Enemy[id].rot.y += ((g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y) * StopEnergy);
	}

	// ピッチ調整
	g_Enemy[id].rot.x += ((g_Enemy[id].rot_goal.x - g_Enemy[id].rot.x) * StopEnergy);
}

//************************************************
// エネミー移動
//************************************************
void MoveEnemy(int id)
{
	if (g_Enemy[id].param.state != stateAtk_e &&
		g_Enemy[id].param.state != stateCharge_e &&
		g_Enemy[id].param.state != stateRotate_e &&
		g_Enemy[id].param.state != stateDamage_e &&
		g_Enemy[id].param.state != stateDead_e)
	{ // 攻撃：溜め：回転：負傷：死亡状態でなければ
		if (g_Enemy[id].param.style == Dragonfly)
		{ // スタイル：蜻蛉

			Player* pPlayer = GetInfoPlayer();							// プレイヤーへのポインタ
			int target = g_Enemy[id].param.target;						// 追跡対象の識別
			D3DXVECTOR3 vec = pPlayer[target].pos - g_Enemy[id].pos;	// 追跡対象へのベクトル

			if (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z) < pPlayer[target].param.rad + 70.0f)
			{ // 一定範囲内に近づくと強制終了し攻撃状態へ
			
				g_Enemy[id].param.state = stateAtk_e;	// 攻撃状態に
				g_Enemy[id].param.motion_now = 1;		// 攻撃の代わりに通常モーションを再生

				return; // 以降の処理を全て行わない
			}

			// 移動量の付与
			if (g_Enemy[id].pos.y > 20.0f)
			{
				g_Enemy[id].move =
				{
					sinf(atan2f(vec.x, vec.z)),
					sinf(atan2f(vec.y, vec.z)),
					cosf(atan2f(vec.x, vec.z))
				};
			}
			else
			{
				g_Enemy[id].move =
				{
					sinf(atan2f(vec.x, vec.z)),
					-sinf(atan2f(vec.y, vec.z)),
					cosf(atan2f(vec.x, vec.z))
				};
			}

			// 向きを付与	
			g_Enemy[id].rot_goal.y = atan2f(-vec.x, -vec.z);											// ヨー
			g_Enemy[id].rot_goal.x = atan2f(-g_Enemy[id].pos.y, sqrtf(vec.x * vec.x + vec.z * vec.z));	// ピッチ

			// 移動量反映
			g_Enemy[id].pos += g_Enemy[id].move * g_Enemy[id].param.SPD * 2.5f; 

			g_Enemy[id].param.state = stateMove_e;	// 移動状態に  
			g_Enemy[id].param.motion_now = 1;		// 移動モーションを再生
		}
		else if (g_Enemy[id].param.style == Ant)
		{ // スタイル：蟻

		}
	}
}

//************************************************
// エネミー攻撃
//************************************************
void AtkEnemy(int id)
{
	if (g_Enemy[id].param.state != stateAtk_e &&
		g_Enemy[id].param.state != stateCharge_e &&
		g_Enemy[id].param.state != stateRotate_e)
	{ // 攻撃：溜め状態で無ければリターン
		return;
	}

	if (g_Enemy[id].param.style == Dragonfly)
	{ // スタイル：蜻蛉

		if (g_Enemy[id].param.state == stateAtk_e)
		{ // 攻撃状態のとき

			g_Enemy[id].param.state = stateCharge_e;		// 溜め状態に遷移
			g_Enemy[id].param.dur = 40;						// 期間
		}
		else if (g_Enemy[id].param.state == stateCharge_e)
		{ // 溜め状態の時

			if (g_Enemy[id].param.dur > 35)
			{
				Player* pPlayer = GetInfoPlayer();
				int target = g_Enemy[id].param.target;						// 追跡対象の識別
				D3DXVECTOR3 vec = pPlayer[target].pos - g_Enemy[id].pos;	// 追跡対象へのベクトル

				// 特別な移動量の付与
				g_Enemy[id].move =
				{
					-sinf(atan2f(vec.x, vec.z)),	
					0.75f,							// 上空へ
					-cosf(atan2f(vec.x, vec.z))
				};

				// 移動量を反映
				g_Enemy[id].pos += g_Enemy[id].move * 10.0f;	// 素早くうごく

				// 特別な向き
				g_Enemy[id].rot_goal.y -= 0.2f;	// ヨー：少しひねる
				g_Enemy[id].rot_goal.x = 0.0f;	// ピッチ：どうしよう
			}

			if (CntDuration(&g_Enemy[id].param.dur))
			{ // 期間終了で
				g_Enemy[id].param.state = stateRotate_e;	// 回転状態に遷移
				g_Enemy[id].param.dur = 120;				// 期間
			}
		}
		else if (g_Enemy[id].param.state == stateRotate_e)
		{ // 回転状態のとき

			Player* pPlayer = GetInfoPlayer();							// プレイヤーへのポインタ
			int target = g_Enemy[id].param.target;						// 追跡対象の識別
			D3DXVECTOR3 vec = pPlayer[target].pos - g_Enemy[id].pos;	// 追跡対象へのベクトル

			// 移動量の付与
			if (g_Enemy[id].pos.y > 20.0f)
			{
				g_Enemy[id].move =
				{
					sinf(atan2f(vec.x, vec.z)),
					sinf(atan2f(vec.y, vec.z)),
					cosf(atan2f(vec.x, vec.z))
				};
			}
			else
			{
				g_Enemy[id].move =
				{
					sinf(atan2f(vec.x, vec.z)),
					-sinf(atan2f(vec.y, vec.z)),
					cosf(atan2f(vec.x, vec.z))
				};
			}

			// 向きを付与
			g_Enemy[id].rot_goal.y = atan2f(-vec.x, -vec.z);	// ヨー
			g_Enemy[id].rot_goal.x = 0.0f;						// ピッチ

			// 移動量反映
			g_Enemy[id].pos += g_Enemy[id].move * g_Enemy[id].param.SPD * 2.5f;

			g_Enemy[id].param.motion_now = 0;	// 通常モーションを再生

			// 回転を続ける
			g_Enemy[id].rot.y += 1.0f;

			// プレイヤーとの当たり判定
			if (pPlayer[target].param.state != stateDamage_p &&
				CollisionSph(g_Enemy[id].pos, g_Enemy[id].param.rad, pPlayer[target].pos, pPlayer[target].param.rad))
			{
				// 被弾の処理
				HitPlayer(target);

				// 特別にノックバックを与える
				pPlayer[target].move.x = g_Enemy[id].move.x * g_Enemy[id].param.SPD * 80.0f;
				pPlayer[target].move.z = g_Enemy[id].move.z * g_Enemy[id].param.SPD * 80.0f;
			}

			if (CntDuration(&g_Enemy[id].param.dur))
			{ // 期間終了で
				g_Enemy[id].param.state = stateNormal_e;	// 通常状態に遷移
			}
		}
	}
	else if (g_Enemy[id].param.style == Ant)
	{ // スタイル：蟻

	}
}

//************************************************
// エネミーの追跡対象を決める
//************************************************
int SetTargetEnemy(int id)
{
	int target = -1;					// 追跡対象の識別番号を格納
	Player* pPlayer = GetInfoPlayer();	// プレイヤーへのポインタ
	float dist[MAX_PLAYER] = {};		// プレイヤーとの距離
	int max_dist = 0;					// 算出した距離の総数を格納

	for (int i = 0; i < MAX_PLAYER; i++, max_dist++)
	{ // 全てのプレイヤーとの距離を算出

		if (!pPlayer[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		D3DXVECTOR3 vec = pPlayer[i].pos - g_Enemy[id].pos;
		dist[i] = sqrtf(vec.x * vec.x + vec.z * vec.z);
	}

	float min = FLT_MAX;	// 浮動小数の最大値

	for (int i = 0; i < max_dist; i++)
	{ // 算出した距離の中で一番小さいものを算出

		if (min > dist[i])
		{ // より数値を格納しているものと交換
			min = dist[i];
			target = i;	// その時の識別番号を格納
		}
	}

	return target;
}

//************************************************
// エネミー被弾時
//************************************************
void HitEnemy(int id)
{
	g_Enemy[id].param.state = stateDamage_e;	// 負傷状態に
	g_Enemy[id].param.motion_now = 1;			// なんかのモーション
	g_Enemy[id].param.dur = 45;					// 継続時間を付与
	g_Enemy[id].param.HP--;
}

//************************************************
// エネミー負傷
//************************************************
void DamageEnemy(int id)
{
	if (g_Enemy[id].param.state != stateDamage_e)
	{ // 負傷状態でなければ終了
		return;
	}

	/*---【以下負傷状態時のみ】---*/

	// 点滅
	g_Enemy[id].col.a *= -1.0f;

	if (g_Enemy[id].param.style == Dragonfly)
	{ // 蜻蛉のみ特別に移動
		g_Enemy[id].pos += g_Enemy[id].move;
		g_Enemy[id].pos.y += 1.0f;
		g_Enemy[id].rot.x += 0.05f;
	}

	if (CntDuration(&g_Enemy[id].param.dur))
	{
		g_Enemy[id].param.state = stateNormal_e;	// 通常状態に
		g_Enemy[id].param.motion_now = 0;			// 通常モーション
		g_Enemy[id].col.a = 1.0f;					// 通常色に
	}
}

//************************************************
// エネミー死亡
//************************************************
void DeadEnemy(int id)
{
	// 死亡状態を付与
	if (g_Enemy[id].param.state == stateDamage_e && g_Enemy[id].param.HP <= 0)
	{ // 負傷状態で体力が無いときのみ
		g_Enemy[id].param.state = stateDead_e;	// 死亡状態に
		g_Enemy[id].param.dur = 25;				// 継続時間付与
		g_Enemy[id].param.motion_now = 2;		// 死亡モーション
		g_Enemy[id].col.a = 0.5f;				// 半透明に
	}

	if (g_Enemy[id].param.state != stateDead_e)
	{ // 死亡状態でなければ終了
		return;
	}

	/*---【以下死亡状態時のみ】---*/

	// 縮小
	g_Enemy[id].size -= { 0.035f, 0.035f, 0.035f };

	if (CntDuration(&g_Enemy[id].param.dur))
	{
#ifdef _DEBUG

		// 判定可視化のみ邪魔なので消去
		DeleteVisibleSph(g_Enemy[id].id_sph);

#endif	// _DEBUG

		// 影を消去
		DeleteShadow(g_Enemy[id].id_shadow);

		// 消去
		DeleteEnemy(id);
	}
}

//************************************************
// エネミー復活
//************************************************
void ResurrectEnemy(int id)
{
	if (g_Enemy[id].param.state == stateDead_e)
	{ // 死亡状態であれば
		g_Enemy[id].param.state = stateNormal_e;
		g_Enemy[id].param.HP = 3;	//!< 現段階では適当に設定
	}
}

//************************************************
// エネミーのモーション管理
//************************************************
void MotionEnemy(int id)
{
	if (!g_Enemy[id].use)
	{ // 未使用ならリターン
		return;
	}

	// 再生情報格納用
	int* pNow = &g_Enemy[id].param.motion_now;			// 現在のモーション種類
	int* pOld = &g_Enemy[id].param.motion_old;			// 過去のモーション種類
	EnemyMotion* pMotion = &g_Enemy[id].motion[*pNow];	// 各エネミーのモーション情報

	// 変更を検知
	ChangeMotionEnemy(id, pNow, pOld);

	// パーツの動作
	MoveMotionEnemy(id, pMotion);

	// フレームカウント
	if (g_Enemy[id].param.state != stateCharge_e)
	{ // 溜め状態でないときのみ
		CntMotionEnemy(id, pMotion);
	}
}

//************************************************
// エネミーのモーション変更検知
//************************************************
void ChangeMotionEnemy(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // 過去と現在の再生モーションが同じならリターン
		return;
	}

	// 過去のモーションのキーとフレームをリセット
	g_Enemy[id].motion[*pOld].id_key = 0;
	g_Enemy[id].motion[*pOld].id_frame = 0;

	// 新しいモーションへ移ったことを保存
	*pOld = *pNow;
}

//************************************************
// エネミーのモーション動作用
//************************************************
void MoveMotionEnemy(int id, EnemyMotion* pMotion)
{
	// 再生中のキーの総フレーム数から現在のフレーム番号を差し引く
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---【試験的に、使用されているパーツの数分】---*/
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		{ // パーツが未使用ならコンティニュー
		if (g_Enemy[id].parts[i].pMesh == NULL)
			continue;
		}

		g_Enemy[id].parts[i].pos_moved += (pMotion->key[pMotion->id_key].dest[i].pos - g_Enemy[id].parts[i].pos_moved) / dest;
		g_Enemy[id].parts[i].rot_moved += (pMotion->key[pMotion->id_key].dest[i].rot - g_Enemy[id].parts[i].rot_moved) / dest;
	}
}

//************************************************
// エネミーのモーションカウント用
//************************************************
void CntMotionEnemy(int id, EnemyMotion* pMotion)
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
			g_Enemy[id].param.motion_now = 0;
		}
	}
}

//************************************************
// エネミー消去
//************************************************
void DeleteEnemy(int id)
{
	Enemy* pEnemy = &g_Enemy[id];

	// 使用フラグ
	pEnemy->use = false;

	// パラメータ
	pEnemy->param =
	{
		0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0		// メンバー情報はヘッダファイルを確認して下さい
	};

	// 座標系
	pEnemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 色
	pEnemy->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
	{ // 各パーツ情報をリセット
		EnemyModel* pModel = &pEnemy->parts[j];

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

	// 判定識別番号
	pEnemy->id_sph = -1;
}

//************************************************
// エネミー用のワールドマトリックスを計算
//************************************************
void CalcMtxEnemy(void)
{
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;	// 計算用マトリックス

	for (int enemy_id = 0; enemy_id < AMOUNT_ENEMY; enemy_id++)
	{
		if (!g_Enemy[enemy_id].use)
		{ // この番の使用フラグが無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Enemy[enemy_id].mtxWorld);

		if (g_Enemy[enemy_id].param.state == stateDead_e)
		{ // 死亡時のみ

			// 大きさを反映1
			D3DXMatrixScaling(&mtxScale,
				1.0f + g_Enemy[enemy_id].size.x,
				1.0f + g_Enemy[enemy_id].size.y,
				1.0f + g_Enemy[enemy_id].size.z);

			// 大きさを反映2
			D3DXMatrixMultiply(&g_Enemy[enemy_id].mtxWorld,
				&g_Enemy[enemy_id].mtxWorld,
				&mtxScale);
		}

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Enemy[enemy_id].rot.y,
			g_Enemy[enemy_id].rot.x,
			g_Enemy[enemy_id].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_Enemy[enemy_id].mtxWorld,
			&g_Enemy[enemy_id].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Enemy[enemy_id].pos.x,
			g_Enemy[enemy_id].pos.y,
			g_Enemy[enemy_id].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Enemy[enemy_id].mtxWorld,
			&g_Enemy[enemy_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_ENEMY_PARTS; Ps_id++)
		{
			if (g_Enemy[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // 空っぽならコンティニュー
				continue;
			}

			// この番パーツの「親パーツ」のインデックスを保存
			int IdxParent = g_Enemy[enemy_id].parts[Ps_id].IdxParent;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[enemy_id].parts[Ps_id].mtxWorld);

			// モーション向きの反映
			D3DXVECTOR3 PartsRot =
			{
				g_Enemy[enemy_id].parts[Ps_id].rot_offset.x + g_Enemy[enemy_id].parts[Ps_id].rot_moved.x,
				g_Enemy[enemy_id].parts[Ps_id].rot_offset.y + g_Enemy[enemy_id].parts[Ps_id].rot_moved.y,
				g_Enemy[enemy_id].parts[Ps_id].rot_offset.z + g_Enemy[enemy_id].parts[Ps_id].rot_moved.z
			};

			// 向きを反映1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// 向きを反映2
			D3DXMatrixMultiply(&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// モーション位置の反映
			D3DXVECTOR3 PartsPos =
			{
				g_Enemy[enemy_id].parts[Ps_id].pos_offset.x + g_Enemy[enemy_id].parts[Ps_id].pos_moved.x,
				g_Enemy[enemy_id].parts[Ps_id].pos_offset.y + g_Enemy[enemy_id].parts[Ps_id].pos_moved.y,
				g_Enemy[enemy_id].parts[Ps_id].pos_offset.z + g_Enemy[enemy_id].parts[Ps_id].pos_moved.z
			};

			// 位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// 位置を反映
			D3DXMatrixMultiply(&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// 親のワールドマトリックスを取得
			if (IdxParent == -1)
			{ //メインパーツのみワールド座標に直結
				mtxParent = g_Enemy[enemy_id].mtxWorld;
			}
			else
			{ //その他パーツはそれぞれの親パーツへ付随
				mtxParent = g_Enemy[enemy_id].parts[IdxParent].mtxWorld;
			}

			// パーツごとのワールドマトリックスを算出
			D3DXMatrixMultiply(&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}
	}
}

//************************************************
// エネミー描画
//************************************************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	for (int id_enemy = 0; id_enemy < AMOUNT_ENEMY; id_enemy++)
	{
		if (!g_Enemy[id_enemy].use)
		{ // この番の使用フラグが無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[id_enemy].mtxWorld);

		for (int id_Ps = 0; id_Ps < AMOUNT_ENEMY_PARTS; id_Ps++)
		{
			if (g_Enemy[id_enemy].parts[id_Ps].pMesh == NULL)
			{ // パーツが未使用ならコンティニュー
				continue;
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[id_enemy].parts[id_Ps].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Enemy[id_enemy].parts[id_Ps].pBuffMat->GetBufferPointer();

			for (int id_mat = 0; id_mat < (int)g_Enemy[id_enemy].parts[id_Ps].NumMat; id_mat++)
			{
				// カラーA値反映
				pMat[id_mat].MatD3D.Diffuse.a = g_Enemy[id_enemy].col.a;

				// マテリアルの設定
				pDevice->SetMaterial(&pMat[id_mat].MatD3D);

				// テクスチャの設定
				if (g_Enemy[id_enemy].parts[id_Ps].pTex[id_mat] != NULL)
				{
					pDevice->SetTexture(0, g_Enemy[id_enemy].parts[id_Ps].pTex[id_mat]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// モデルパーツの描画
				g_Enemy[id_enemy].parts[id_Ps].pMesh->DrawSubset(id_mat);
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//************************************************
// エネミー情報を取得
//************************************************
Enemy* GetInfoEnemy(void)
{
	return &g_Enemy[0];
}