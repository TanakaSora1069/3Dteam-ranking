////************************************************
////
////矩形の当たり判定を可視化[visible_rect.cpp]
////author：福田歩希
////
////************************************************
//#include "visible_rect.h"
//
//#include "player.h"
//
////マクロ定義
//#define amount_rect	(128)	//レクトの最大数
//
////グローバル変数
//lpdirect3dvertexbuffer9 g_pvtxbuffrect = null;	//頂点バッファへのポインタ
//lpdirect3dindexbuffer9 g_pidxbuffrect = null;	//インデックスバッファへのポインタ
//rect g_arect[amount_rect] = {};	//レクト情報
///* 1レクト当たり */
//static const int g_namountvtx = 8;	//頂点の数
//static const int g_namountprimitive = 12;	//辺の数
//static const int g_namountidx = g_namountprimitive * 2;	//インデックスの数
//
////************************************************
////レクト初期
////************************************************
//void initvisible_rect(void)
//{
//	lpdirect3ddevice9 pdevice = getdevice();	//デバイスの取得
//
//	for (int i = 0; i < amount_rect; i++)
//	{
//		g_arect[i].buse = false;
//		g_arect[i].pos = d3dxvector3(0.0f, 0.0f, 0.0f);
//		g_arect[i].ppos = null;
//		g_arect[i].col = d3dxcolor(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//
//	//頂点バッファの生成
//	pdevice->createvertexbuffer(sizeof(vertex_3d) * g_namountvtx * amount_rect,
//		d3dusage_writeonly,
//		fvf_vertex_3d,
//		d3dpool_managed,
//		&g_pvtxbuffrect,
//		null);
//
//	//頂点情報のポインタ
//	vertex_3d* pvtx;
//
//	//頂点バッファをロックし頂点情報時へのポインタを取得
//	g_pvtxbuffrect->lock(0, 0, (void**)&pvtx, 0);
//
//	for (int i = 0; i < g_namountvtx * amount_rect; i++)
//	{
//		//頂点座標の設定
//		pvtx[i].pos = d3dxvector3(0.0f, 0.0f, 0.0f);
//
//		//法線ベクトルの設定
//		pvtx[i].nor = d3dxvector3(0.0f, 0.0f, 0.0f);
//
//		//頂点カラーの初期設定
//		pvtx[i].col = d3dxcolor(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//テクスチャ座標の初期設定
//		pvtx[i].tex = d3dxvector2(0.0f, 0.0f);
//	}
//
//	//頂点バッファをアンロック
//	g_pvtxbuffrect->unlock();
//
//	//インデックスバッファの生成
//	pdevice->createindexbuffer(sizeof(word) * g_namountidx * amount_rect,
//		d3dusage_writeonly,
//		d3dfmt_index16,
//		d3dpool_managed,
//		&g_pidxbuffrect,
//		null);
//
//	//インデックスバッファのポインタ
//	word* pidx;
//
//	//インデックスバッファをロック
//	g_pidxbuffrect->lock(0, 0, (void**)&pidx, 0);
//
//	for (int i = 0; i < amount_rect; i++)
//	{
//		/* x軸に平行な線を引く */
//		for (int j = 0; j < 8; j++, pidx++)
//		{
//			pidx[0] = (word)j;
//		}
//
//		/* y軸に平行な線を引く */
//		for (int j = 0, k = 0; j < 4; j++, pidx += 2)
//		{
//			if (j == 2) k += 2;	/* 0,1,4,5をレイの始点にするため3,4のインデックスを飛ばす */
//
//			pidx[0] = (word)(j + k);
//			pidx[1] = (word)(j + 2 + k);
//		}
//
//		/* z軸に平行な線を引く */
//		for (int j = 0; j < 4; j++, pidx += 2)
//		{
//			pidx[0] = (word)(j);
//			pidx[1] = (word)(j + 4);
//		}
//	}
//
//	//インデックスバッファをアンロック
//	g_pidxbuffrect->unlock();
//}
//
////************************************************
////レクト展開
////************************************************
//void setsizevisible_rect(const collision_aabb obj, d3dxcolor col, d3dxvector3* ppos)
//{
//	//頂点情報のポインタ
//	vertex_3d* pvtx;
//
//	//頂点バッファをロックし頂点情報時へのポインタを取得
//	g_pvtxbuffrect->lock(0, 0, (void**)&pvtx, 0);
//
//	for (int i = 0; i < amount_rect; i++, pvtx += g_namountvtx)
//	{
//		if (g_arect[i].buse) continue;
//
//		g_arect[i].buse = true;
//
//		/* 対象のワールド座標を相殺し頂点を展開する */
//		pvtx[0].pos = { obj.min.x - ppos->x, obj.max.y - ppos->y, obj.min.z - ppos->z };
//		pvtx[1].pos = { obj.max.x - ppos->x, obj.max.y - ppos->y, obj.min.z - ppos->z };
//		pvtx[2].pos = { obj.min.x - ppos->x, obj.min.y - ppos->y, obj.min.z - ppos->z };
//		pvtx[3].pos = { obj.max.x - ppos->x, obj.min.y - ppos->y, obj.min.z - ppos->z };
//		pvtx[4].pos = { obj.min.x - ppos->x, obj.max.y - ppos->y, obj.max.z - ppos->z };
//		pvtx[5].pos = { obj.max.x - ppos->x, obj.max.y - ppos->y, obj.max.z - ppos->z };
//		pvtx[6].pos = { obj.min.x - ppos->x, obj.min.y - ppos->y, obj.max.z - ppos->z };
//		pvtx[7].pos = { obj.max.x - ppos->x, obj.min.y - ppos->y, obj.max.z - ppos->z };
//
//		for (int j = 0; j < g_namountvtx; j++)
//		{
//			pvtx[j].col = col;
//		}
//
//		/* 対象のワールド座標に同期する */
//		g_arect[i].ppos = ppos;
//
//		break;
//	}
//
//	//頂点バッファをアンロック
//	g_pvtxbuffrect->unlock();
//}
//
////************************************************
////レクト破棄
////************************************************
//void uninitvisible_rect(void)
//{
//	//頂点バッファの破棄
//	if (g_pvtxbuffrect != null)
//	{
//		g_pvtxbuffrect->release();
//		g_pvtxbuffrect = null;
//	}
//
//	//インデックスバッファの破棄
//	if (g_pidxbuffrect != null)
//	{
//		g_pidxbuffrect->release();
//		g_pidxbuffrect = null;
//	}
//}
//
////************************************************
////レクト更新
////************************************************
//void updatevisible_rect(void)
//{
//	//対象物の中心に
//	for (int i = 0; i < amount_rect; i++)
//	{
//		if (!g_arect[i].buse) continue;
//
//		g_arect[i].pos = *g_arect[i].ppos;
//	}
//
//	///* 線を太くするため3軸方向に少しずつずらす */
//	//g_arect[1].pos.x += 0.15f;
//	//g_arect[2].pos.x += -0.15f;
//
//	//g_arect[3].pos.y += 0.15f;
//	//g_arect[4].pos.y += -0.15f;
//
//	//g_arect[5].pos.z += 0.15f;
//	//g_arect[6].pos.z += -0.15f;
//}
//
////************************************************
////レクト描画
////************************************************
//void drawvisible_rect(void)
//{
//	lpdirect3ddevice9 pdevice = getdevice();	//デバイスの取得
//
//	//ライトをオフ
//	pdevice->setrenderstate(d3drs_lighting, false);
//
//	d3dxmatrix mtxrot, mtxtrans;	//計算用マトリックス
//
//	for (int i = 0; i < amount_rect; i++)
//	{
//		if (!g_arect[i].buse) continue;
//
//		//ワールドマトリックスの初期化
//		d3dxmatrixidentity(&g_arect[i].mtxworld);
//
//		//位置を反映1
//		d3dxmatrixtranslation(&mtxtrans,
//			g_arect[i].pos.x,
//			g_arect[i].pos.y,
//			g_arect[i].pos.z);
//
//		//位置を反映2
//		d3dxmatrixmultiply(&g_arect[i].mtxworld,
//			&g_arect[i].mtxworld,
//			&mtxtrans);
//
//		//ワールドマトリックスの設定
//		pdevice->settransform(d3dts_world, &g_arect[i].mtxworld);
//
//		//頂点バッファをデータストリームに設定
//		pdevice->setstreamsource(0, g_pvtxbuffrect, 0, sizeof(vertex_3d));
//
//		//インデックスバッファをデータストリームに設定
//		pdevice->setindices(g_pidxbuffrect);
//
//		//頂点フォーマットの設定
//		pdevice->setfvf(fvf_vertex_3d);
//
//		//テクスチャの設定
//		//pdevice->settexture(0, null);
//
//		//レクトの描画
//		pdevice->drawindexedprimitive(d3dpt_linelist, i * g_namountvtx, 0, g_namountvtx,
//			0, g_namountprimitive);
//	}
//
//	//ライトをオン
//	pdevice->setrenderstate(d3drs_lighting, true);
//}