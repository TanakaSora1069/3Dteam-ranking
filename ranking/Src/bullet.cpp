//************************************************
//
// 弾[bullet.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "bullet.h"
// 中枢
#include "input.h"
#include "sound.h"
// 諸処理
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "effect.h"
#include "effect_sand.h"
#include "enemy.h"
#include "explosion.h"
#include "game.h"
#include "item.h"
#include "player.h"
#include "shadow.h"
// デバッグ時
#ifdef _DEBUG
#include "visible_sph.h"
#endif	// _DEBUG

// グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			// テクスチャへのポインタ
Bullet g_Bullet[AMOUNT_BULLET];						// 弾情報

//************************************************
// 弾初期
//************************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{ // 弾情報リセット
		g_Bullet[i].use = false;							// 使用フラグ
		g_Bullet[i].type = bulletPlayer;					// 全てプレイヤーの弾ということにしておく
		g_Bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_Bullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_Bullet[i].rad = 0;								// 半径
		g_Bullet[i].id_shadow = -1;							// 影の識別番号
		g_Bullet[i].id_sph = -1;							// 判定可視化の識別番号
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cannon.png",
		&g_pTextureBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);
	
	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BULLET; i++, pVtx += AMOUNT_VTX)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_BULLET, -SPAN_BULLET, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_BULLET, -SPAN_BULLET, 0.0f);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//************************************************
// 弾破棄
//************************************************
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{ // テクスチャの破棄
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	if (g_pVtxBuffBullet != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//************************************************
// 弾生成
//************************************************
void CreateBullet(int type, int id)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (g_Bullet[i].use)
		{ // 使用中ならコンティニュー
			continue;
		}

		// 弾にタイプを設定
		g_Bullet[i].type = type;

		// 初期化を行うためforで制御
		if (type == bulletPlayer)
		{
			Camera* pCamera = GetInfoCamera();	// カメラへのポインタ
			Player* pPlayer = GetInfoPlayer();	// プレイヤーへのポインタ

			// 適当にパラメータ設定
			g_Bullet[i].use = true;

			// 向きをカメラの方向に
			g_Bullet[i].rot = pCamera[id].rot;

			// 武器識別番号格納
			int weapon = pPlayer[id].param.weapon;

			switch (weapon)
			{
				// 銃
			case styleGun:
				g_Bullet[i].pos =
				{
					pPlayer[id].offset_atk[weapon].mtx._41,
					pPlayer[id].offset_atk[weapon].mtx._42,
					pPlayer[id].offset_atk[weapon].mtx._43,
				};

				g_Bullet[i].rad = SPAN_BULLET;	// 大きさ：適量
				g_Bullet[i].remain = 25;		// 寿命：適量

				// トンプソンの先端から発射されるように、少し前進させておく
				g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x);
				g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x);
				break;

				// RPG
			case styleRPG:
				g_Bullet[i].pos =
				{
					pPlayer[id].offset_atk[weapon].mtx._41,
					pPlayer[id].offset_atk[weapon].mtx._42,
					pPlayer[id].offset_atk[weapon].mtx._43,
				};

				g_Bullet[i].rad = SPAN_BULLET;	// 大きさ：適量
				g_Bullet[i].remain = 25;		// 寿命：適量

				// RPGの先端から発射されるように、少し前進させておく
				g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x);
				g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x);
				break;
			}

			/*---【所有している武器の位置から出現：これ使わないけど残しといて】---*/
			//g_Bullet[i].pos =
			//{
			//	pPlayer[id].parts[weapon].mtxWorld._41,
			//	pPlayer[id].parts[weapon].mtxWorld._42 + 13.0f,
			//	pPlayer[id].parts[weapon].mtxWorld._43,
			//};

			//g_Bullet[i].rad = SPAN_BULLET;
			//g_Bullet[i].remain = 25;

			//// プレイヤーの先端から発射されるように、少し前進させておく
			//g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x) * 15.0f;
			//g_Bullet[i].pos.y += (sinf(g_Bullet[i].rot.x) * 15.0f);
			//g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x) * 15.0f;

			// 影を生成
			g_Bullet[i].id_shadow = CreateShadow(&g_Bullet[i].pos, 10.0f);

#ifdef _DEBUG

			// 当たり判定を可視化
			g_Bullet[i].id_sph = CreateVisibleSph(g_Bullet[i].rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Bullet[i].pos);

#endif	// _DEBUG 
		}

		break;
	}
}

//************************************************
// 弾更新
//************************************************
void UpdateBullet(void)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_Bullet[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 移動
		g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x) * SPD_BULLET;
		g_Bullet[i].pos.y += sinf(g_Bullet[i].rot.x) * SPD_BULLET;
		g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x) * SPD_BULLET;

		if (g_Bullet[i].type == bulletPlayer)
		{ // エフェクトを出す
			SetEffect(g_Bullet[i].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 10.0f);
			//SetEffectSand(g_Bullet[i].pos, 1, 150);
			//SetEffectSand(g_Player[g_P_id].pos, 1, 30);
		}

		// 当たり判定を行う
		CollisionBullet(i);

		// 消滅判定を行う
		DeleteBullet(i);
	}
}

//************************************************
// 弾消滅
//************************************************
void DeleteBullet(int id)
{
	if (CntDuration(&g_Bullet[id].remain))
	{ // 残存時間が無くなると

		// 爆発エフェクト
		SetExplosion(g_Bullet[id].pos, { 1.0f, 1.0f, 1.0f, 1.0f }, 30.0f, 30.0f);

		/*---【試験的に消滅】---*/
		g_Bullet[id].use = false;							// 使用フラグ
		g_Bullet[id].type = bulletPlayer;					// プレイヤーの弾にしておく
		g_Bullet[id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_Bullet[id].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_Bullet[id].rad = 0;								// 半径
		g_Bullet[id].remain = 0;							// 寿命

		// 影を消去
		DeleteShadow(g_Bullet[id].id_shadow);

#ifdef _DEBUG

		// 判定可視化を消去
		DeleteVisibleSph(g_Bullet[id].id_sph);

#endif	// _DEBUG

		// 役目を終えた数値もリセット
		g_Bullet[id].id_shadow = -1;	
		g_Bullet[id].id_sph = -1;

		// 爆発
	}
}

//************************************************
// 弾描画
//************************************************
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxTrans, mtxView;				// 計算用マトリックス

	// ライト反映を無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// 深度テストの比較方法の変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//// 深度バッファに描画しない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_Bullet[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Bullet[i].mtxWorld);

		// ビューマトリックス取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// ポリゴンをカメラの正面に向け続ける
		D3DXMatrixInverse(&g_Bullet[i].mtxWorld, NULL, &mtxView);	// 逆行列を求める

		g_Bullet[i].mtxWorld._41 = 0.0f;
		g_Bullet[i].mtxWorld._42 = 0.0f;
		g_Bullet[i].mtxWorld._43 = 0.0f;

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Bullet[i].pos.x,
			g_Bullet[i].pos.y,
			g_Bullet[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Bullet[i].mtxWorld,
			&g_Bullet[i].mtxWorld,
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[i].mtxWorld);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBullet);

		// ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ライト反映を有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// 深度テストの比較方法の変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//// 深度バッファに書き込む
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//************************************************
// 弾の当たり判定
//************************************************
void CollisionBullet(int id)
{
	// switch制御では宣言を行えないためifで制御
	if (g_Bullet[id].type == bulletPlayer)
	{ // 弾がプレイヤータイプなら
		Enemy* pEnemy = GetInfoEnemy();
		BOSS* pBoss = GetInfoBoss();
			
		for (int j = 0; j < AMOUNT_ENEMY; j++, pEnemy++)
		{ // エネミーとの判定を行う
			if (!pEnemy->use)
			{ // 未使用ならコンティニュー
				continue;
			}

			if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pEnemy->pos, pEnemy->param.rad))
			{ // 敵にヒットすると

				g_Bullet[id].remain = 0;	// 使用時間を無くす

				// 敵に被弾情報を付与
				if (pEnemy->param.state != stateRotate_e &&
					pEnemy->param.state != stateDamage_e &&
					pEnemy->param.state != stateDead_e)
				{ // 回転：負傷：死亡状態でないときのみ
					HitEnemy(j);

					if (pEnemy->param.style == Dragonfly)
					{ // 蜻蛉のみ特別にノックバックを与える
						pEnemy->move *= -1.0f;
					}
				}
			}
		}

		for (int i = 0; i < MAX_BOSS; i++, pBoss++)
		{//ボスとの判定を行う
			if (!pBoss->use)
			{//未使用ならコンティニュー
				continue;
			}

			if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pBoss->pos, pBoss->Param.Radius))
			{//ボスに当たると

				g_Bullet[id].remain = 0;	// 使用時間を無くす

				// 敵に被弾情報を付与
				if (pBoss->Param.state != stateDamage_b &&
					pBoss->Param.state != stateDead_b)
				{// 負傷状態と死亡状態でないときのみ
					HitBoss(i);
				}
			}
		}
	}
	else if	(g_Bullet[id].type == bulletEnemy)
	{ // 弾がエネミータイプなら

	}
}

//************************************************
// 弾情報を取得
//************************************************
Bullet* GetInfoBullet(void)
{
	return &g_Bullet[0];
}