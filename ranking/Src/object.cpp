//************************************************
//
// オブジェクト[object.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "object.h"
// 諸処理
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"
#include "input.h"
#include <assert.h>
#endif	// _DEBUG

/*/ グローバル変数 /*/
ObjectModel g_ObjectModel[AMOUNT_MODEL_OBJECT];	// オブジェクトモデル情報のひな形
Object g_Object[AMOUNT_OBJECT];					// オブジェクト情報
Object g_PreObject;								// 仮想のオブジェクト情報
Object g_GizmoObject;							// ギズモモデル用
int g_MaxModel = 0;								// モデル総種類数格納
int g_MaxObject = 0;							// 既存モデル総数格納
bool g_TrackAA = true;							// 移動モード識別
bool g_Overwrite = false;						// 編集モード識別
int g_obj_id = 0;								// 選択している既存オブジェクト識別

//************************************************
// オブジェクト初期
//************************************************
void InitObject(void)
{
	g_MaxModel = 0;			// モデル総種類数リセット
	g_MaxObject = 0;		// 既存モデル数リセット
	g_TrackAA = true;		// 移動モード：平行
	g_Overwrite = false;	// 編集モード：通常
	g_obj_id = 0;

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{ // オブジェクト用モデル情報のひな形のリセット
		g_ObjectModel[i].pMesh = NULL;
		g_ObjectModel[i].pBuffMat = NULL;
		g_ObjectModel[i].NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // テクスチャの情報のリセット
			g_ObjectModel[i].pTex[j] = NULL;
		}
	}

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{ // オブジェクトの情報のリセット
		g_Object[i].type = 0;
		g_Object[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[i].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[i].aabb = {};
		g_Object[i].model.pMesh = NULL;
		g_Object[i].model.pBuffMat = NULL;
		g_Object[i].model.NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // テクスチャ情報のリセット
			g_ObjectModel[i].pTex[j] = NULL;
		}
		g_Object[i].nIdxShadow = 0;	//!< 現在未使用
	}

#ifdef _DEBUG

	// 仮想のオブジェクトの情報のリセット
	InitPreObject();

	// ギズモ情報をリセット
	InitGizmoObject();

#endif // _DEBUG

	// オブジェクト用のモデル情報を取得
	ImportModelObject();	//!< 関数を呼ぶ順番が非常重要

#ifdef _DEBUG

	g_PreObject.model = g_ObjectModel[0];	//!< 仮想のオブジェクト情報にモデル情報を1つセット(描画エラー回避)

#endif // _DEBUG
}

//************************************************
// 仮想のオブジェクト初期
//************************************************
void InitPreObject(void)
{
	// 仮想のオブジェクトの情報のリセット
	g_PreObject.type = 0;
	g_PreObject.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PreObject.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PreObject.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PreObject.aabb = {};
	g_PreObject.model.pMesh = NULL;
	g_PreObject.model.pBuffMat = NULL;
	g_PreObject.model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // テクスチャ情報をリセット
		g_PreObject.model.pTex[i] = NULL;
	}
	g_PreObject.nIdxShadow = 0;	//!< 現在未使用
}

//************************************************
// ギズモ初期
//************************************************
void InitGizmoObject(void)
{
	// ギズモ情報のリセット
	g_GizmoObject.type = 0;
	g_GizmoObject.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_GizmoObject.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_GizmoObject.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_GizmoObject.aabb = {};
	g_GizmoObject.model.pMesh = NULL;
	g_GizmoObject.model.pBuffMat = NULL;
	g_GizmoObject.model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // テクスチャ情報をリセット
		g_GizmoObject.model.pTex[i] = NULL;
	}
	g_GizmoObject.nIdxShadow = 0;	//!< 現在未使用
}

//************************************************
// オブジェクトモデル情報を読み込む
//************************************************
void ImportModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int id_Model = 0;			// モデルの識別用

	/*--------------------------------------------*/

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_import.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "オブジェクトモデル情報の展開に失敗");

#endif	// _DEBUG
	}

	/*--------------------------------------------*/

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// 読み込むモデル数を取得する
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &g_MaxModel);
		}

#ifdef _DEBUG

		// エラー
		assert(g_MaxModel < AMOUNT_MODEL_OBJECT && "オブジェクトモデル情報が最大量を越えました");

#endif	// _DEBUG

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
				&g_ObjectModel[id_Model].pBuffMat,
				NULL,
				&g_ObjectModel[id_Model].NumMat,
				&g_ObjectModel[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == g_MaxModel)
			{ // 総モデル種類数分読み取り終わると終了
				break;
			}
		}
	}

	/*--------------------------------------------*/

	// 各モデルのテクスチャ情報を取得
	ImportTexObject();

	// 各モデルの配置情報を取得
	ImportLayoutObject(pFile);

	// ファイルを閉じる
	fclose(pFile);

#ifdef _DEBUG

	// ギズモモデルを読み込む
	ImportGizmoModelObject();

#endif
}

//************************************************
// ギズモモデル情報を読み込む
//************************************************
void ImportGizmoModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXLoadMeshFromX("data\\MODEL\\OBJECT\\Gizmo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_GizmoObject.model.pBuffMat,
		NULL,
		&g_GizmoObject.model.NumMat,
		&g_GizmoObject.model.pMesh);
}

//************************************************
// モデルテクスチャ情報を読み込む
//************************************************
void ImportTexObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int i = 0; i < g_MaxModel; i++)
	{
		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_ObjectModel[i].pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int j = 0; j < (int)g_ObjectModel[i].NumMat; j++)
		{
			// マテリアルにテクスチャが設定されていれば読込み
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_ObjectModel[i].pTex[j]);
			}
			else
			{
				g_ObjectModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// モデル配置情報を読み込む
//************************************************
void ImportLayoutObject(FILE* pFile)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int Type = -1;				// モデルの種類格納
	D3DXVECTOR3 pos = {};		// 位置を格納
	D3DXVECTOR3 rot = {};		// 向き格納
	int id_Model = 0;			// モデルの識別用

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "TYPE") == 0)
		{ // このモデルの種類を取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &Type);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置を取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);

			// 度数を弧度に変換
			rot = (rot * D3DX_PI) / 180.0f;
		}

		if (strcmp(&FileString[0], "END_MODELSET") == 0)
		{
#ifdef _DEBUG

			// エラー
			assert(Type != -1 && "オブジェクトモデルの種類情報の読込みに失敗");

#endif	// _DEBUG

			// 読み込んだ配置情報を該当順番のオブジェクトへコピーする
			g_Object[id_Model].type = Type;
			g_Object[id_Model].pos = pos;
			g_Object[id_Model].rot = rot;

			VerifyTypeObject(id_Model);	// 種類の照合

			id_Model++; // コピーしたら次へ
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // 終了
			break;
		}
	}
}

//************************************************
// 種類の照合
//************************************************
void VerifyTypeObject(int id_Model)
{
	for (int i = 0; i < g_MaxModel; i++)
	{
		if (g_Object[id_Model].type == i)
		{ // 各オブジェクトの種類を照合
			g_Object[id_Model].model = g_ObjectModel[i];	//!< 番号の一致しているモデル情報をコピー
		}
	}
}

//************************************************
// 種類の照合(仮想)
//************************************************
void VerifyTypePreObject(void)
{
	for (int i = 0; i < g_MaxModel; i++)
	{
		if (g_PreObject.type == i)
		{ // 各仮想オブジェクトの種類を照合
			g_PreObject.model = g_ObjectModel[i];	//!< 番号の一致しているモデル情報をコピー
		}
	}
}

//************************************************
// オブジェクト破棄
//************************************************
void UninitObject(void)
{
	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_ObjectModel[i].pTex[j] != NULL)
			{ // テクスチャの破棄
				g_ObjectModel[i].pTex[j]->Release();
				g_ObjectModel[i].pTex[j] = NULL;
			}
		}

		if (g_ObjectModel[i].pMesh != NULL)
		{ // メッシュの破棄
			g_ObjectModel[i].pMesh->Release();
			g_ObjectModel[i].pMesh = NULL;
		}

		if (g_ObjectModel[i].pBuffMat != NULL)
		{ // マテリアルの破棄
			g_ObjectModel[i].pBuffMat->Release();
			g_ObjectModel[i].pBuffMat = NULL;
		}
	}

	// ギズモ破棄
	UninitGizmoObject();
}

//************************************************
// ギズモ破棄
//************************************************
void UninitGizmoObject(void)
{
	if (g_GizmoObject.model.pMesh != NULL)
	{ // メッシュの破棄
		g_GizmoObject.model.pMesh->Release();
		g_GizmoObject.model.pMesh = NULL;
	}

	if (g_GizmoObject.model.pBuffMat != NULL)
	{ // マテリアルの破棄
		g_GizmoObject.model.pBuffMat->Release();
		g_GizmoObject.model.pBuffMat = NULL;
	}
}

//************************************************
// オブジェクト更新
//************************************************
void UpdateObject(bool LayoutEdit)
{
#ifdef _DEBUG

	if (LayoutEdit)
	{ // 編集モードでなければ処理を行わない

		EditCamera* pEditCamera = GetInfoEditCamera();	// 編集カメラ情報取得
		Object* pObject = nullptr;						// 仮想・既存オブジェクト識別用
		int Loop = 1;									// 汎用ループ回数

		/*--------------------------------------------*/

		// モデルの配置情報を保存する
		if (GetKeyboardTrigger(DIK_F3))
		{
			ExportLayoutObject();
		}

		// 移動モードを変更する
		if (GetKeyboardTrigger(DIK_F4))
		{
			g_TrackAA = !g_TrackAA;
		}

		// 編集モードを変更する
		if (GetKeyboardTrigger(DIK_F5))
		{
			g_Overwrite = !g_Overwrite;
		}

		// 現在の配置モデル数を取得
		g_MaxObject = GetInfoMaxObject();

		if (GetKeyboardPress(DIK_SPACE))
		{ // 押下で移動や回転の速度上昇
			Loop = 4;
		}

		// オブジェクトの情報をデバッグ表示
		PrintInfoObject();

		/*--------------------------------------------*/

		// モードに応じて取得するオブジェクトを識別する
		if (g_Overwrite)
		{
			pObject = &g_Object[g_obj_id];
		}
		else
		{
			pObject = &g_PreObject;
		}

		/*--------------------------------------------*/

		// 番号の変更 (最小、最大になった時に逆側へ回る用に修正予定)
		if (g_Overwrite)
		{ // 上書きモード時のみ
			if (GetKeyboardTrigger(DIK_PERIOD) || GetKeyboardPress(DIK_X))
			{
				for (int i = g_obj_id + 1; i < AMOUNT_OBJECT; i++)
				{
					if (g_Object[i].model.pMesh != NULL)
					{ // モデル情報を持つ番に当たるとその番へ変更
						g_obj_id = i;

						break;
					}
				}
			}
			else if (GetKeyboardTrigger(DIK_COMMA) || GetKeyboardPress(DIK_Z))
			{
				for (int i = g_obj_id - 1; i >= 0; i--)
				{
					if (g_Object[i].model.pMesh != NULL)
					{ // モデル情報を持つ番に当たるとその番へ変更
						g_obj_id = i;

						break;
					}
				}
			}
		}

		// 種類の変更
		if (GetKeyboardTrigger(DIK_RSHIFT))
		{
			pObject->type < g_MaxModel - 1 ? pObject->type++ : pObject->type = 0;

			g_Overwrite ? VerifyTypeObject(g_obj_id) : VerifyTypePreObject();
		}
		else if (GetKeyboardTrigger(DIK_LSHIFT))
		{
			pObject->type > 0 ? pObject->type-- : pObject->type = g_MaxModel - 1;

			g_Overwrite ? VerifyTypeObject(g_obj_id) : VerifyTypePreObject();
		}

		// エラー
		assert(pObject->type >= 0 && pObject->type < g_MaxModel && "オブジェクトモデルの種類の変更失敗");

		/*--------------------------------------------*/

		// 移動系
		for (int i = 0; i < Loop; i++)
		{
			// オブジェクトの回転
			RotateObject(pObject);

			// オブジェクトの移動
			MoveObject(pObject);
		}

		// 仮想のオブジェクトを、通常オブジェクトとして配置
		if (!g_Overwrite && GetKeyboardTrigger(DIK_RETURN))
		{
			for (int i = 0; i < AMOUNT_OBJECT; i++)
			{
				// 既に保存情報があればコンティニュー
				if (g_Object[i].model.pMesh != NULL)
				{
					continue;
				}

				g_Object[i] = g_PreObject;	// 新たに情報を保存

				break;
			}
		}

		// 既存のオブジェクトを削除
		if (g_Overwrite && GetKeyboardTrigger(DIK_BACK))
		{
			DeleteObject();	// 情報を削除
		}

		/*--------------------------------------------*/

		// 既存位置にギズモを付属
		g_GizmoObject.pos = pObject->pos;

		// 既存向きにギズモを付属
		if (!g_TrackAA)
		{ // 直交モード時のみ
			g_GizmoObject.rot.y = pEditCamera->rot.y;
		}
		else
		{
			if (g_GizmoObject.rot.y != 0.0f)
			{
				g_GizmoObject.rot.y = 0.0f;
			}
		}

		/*--------------------------------------------*/

		// 最後に行列算
		CalcMtxPreObject(0);	//!< 仮想オブジェクト
		CalcMtxPreObject(1);	//!< ギズモ
	}	// if(LayoutEdit)

#endif	// _DEBUG

	// モードに関わらず既存オブジェクトは最後に行列計算
	CalcMtxObject();
}

//************************************************
// 現在の配置モデル数を取得
//************************************************
int GetInfoMaxObject(void)
{
	int Cnt = 0;

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (g_Object[i].model.pMesh != NULL)
		{
			Cnt++;	// 既に保存情報があればカウント増加
		}
	}

	return Cnt;
}

//************************************************
// オブジェクトの情報をデバッグ表示
//************************************************
void PrintInfoObject(void)
{
#ifdef _DEBUG

	char Test[32] = {};	// 汎用文字列

	if (!g_Overwrite)
	{
		PrintDebugProc("【現在の仮想オブジェクト情報】\nモデルの配置数：%d\n種類：%d\n位置：%f %f %f\n向き：%f %f %f\n"
			, g_MaxObject, g_PreObject.type, g_PreObject.pos.x, g_PreObject.pos.y, g_PreObject.pos.z, g_PreObject.rot.x, g_PreObject.rot.y, g_PreObject.rot.z);
	}
	else
	{
		PrintDebugProc("【現在の既存オブジェクト情報】\n現在の選択：%d / %d番目\n種類：%d\n位置：%f %f %f\n向き：%f %f %f\n"
			, g_obj_id, g_MaxObject, g_Object[g_obj_id].type, g_Object[g_obj_id].pos.x, g_Object[g_obj_id].pos.y, g_Object[g_obj_id].pos.z, g_Object[g_obj_id].rot.x, g_Object[g_obj_id].rot.y, g_Object[g_obj_id].rot.z);
	}

	g_TrackAA ? sprintf(Test, "平行") : sprintf(Test, "直交");

	PrintDebugProc("移動モード：%s\n", &Test[0]);

	g_Overwrite ? sprintf(Test, "上書き") : sprintf(Test, "通常");

	PrintDebugProc("編集モード：%s\n", &Test[0]);

#endif	// _DEBUG
}

//************************************************
// オブジェクトの回転
//************************************************
void RotateObject(Object* pObject)
{
#ifdef _DEBUG

	// X軸に回転
	if (GetKeyboardPress(DIK_R))
	{
		pObject->rot.x += 0.01f;
	}
	else if (GetKeyboardPress(DIK_F))
	{
		pObject->rot.x -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_V))
	{
		pObject->rot.x = 0.0f;
	}

	// Y軸に回転
	if (GetKeyboardPress(DIK_T))
	{
		pObject->rot.y += 0.01f;
	}
	else if (GetKeyboardPress(DIK_G))
	{
		pObject->rot.y -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_B))
	{
		pObject->rot.y = 0.0f;
	}

	// Z軸に回転
	if (GetKeyboardPress(DIK_Y))
	{
		pObject->rot.z += 0.01f;
	}
	else if (GetKeyboardPress(DIK_H))
	{
		pObject->rot.z -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_N))
	{
		pObject->rot.z = 0.0f;
	}

	// X軸に一定値
	if (GetKeyboardTrigger(DIK_U))
	{
		pObject->rot.x += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_J))
	{
		pObject->rot.x -= D3DX_PI * 0.025f;
	}

	// Y軸に一定値
	if (GetKeyboardTrigger(DIK_I))
	{
		pObject->rot.y += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_K))
	{
		pObject->rot.y -= D3DX_PI * 0.025f;
	}

	// Z軸に一定値
	if (GetKeyboardTrigger(DIK_O))
	{
		pObject->rot.z += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_L))
	{
		pObject->rot.z -= D3DX_PI * 0.025f;
	}

#endif	// _DEBUG
}

//************************************************
// オブジェクトの移動
//************************************************
void MoveObject(Object* pObject)
{
#ifdef _DEBUG

	bool move = false;
	float X = 0.0f;
	float Z = 0.0f;
	const EditCamera* pCamera = GetInfoEditCamera();

	// 左右
	if (GetKeyboardPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (GetKeyboardPress(DIK_D))
	{
		X = 1.0f;
	}

	// 前後
	if (GetKeyboardPress(DIK_W))
	{
		Z = 1.0f;
	}
	else if (GetKeyboardPress(DIK_S))
	{
		Z = -1.0f;
	}

	// 上下
	if (GetKeyboardPress(DIK_LBRACKET))
	{
		pObject->pos.y += 1.0f;
	}
	else if (GetKeyboardPress(DIK_RBRACKET))
	{
		pObject->pos.y -= 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_YEN))
	{
		pObject->pos.y = 0.0f;
	}

	// intへのキャストを利用して小数部分を切り捨てるため警告無効化
#pragma warning(disable:4244)

	// 端数調整
	if (GetKeyboardTrigger(DIK_MINUS))
	{
		pObject->pos.x = (int)pObject->pos.x;
	}
	else if (GetKeyboardTrigger(DIK_CIRCUMFLEX))
	{
		pObject->pos.z = (int)pObject->pos.z;
	}

#pragma warning(default:4244)

	/*--- (消去予定) ---*/
	if (GetKeyboardTrigger(DIK_0))
	{
		pObject->pos =
		{
			0.0f,
			300.0f,
			0.0f
		};
	}

	// 左右一定値
	if (GetKeyboardTrigger(DIK_NUMPAD4))
	{
		X = -1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD6))
	{
		X = 1.0f;
	}

	// 前後一定値
	if (GetKeyboardTrigger(DIK_NUMPAD8))
	{
		Z = 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD5))
	{
		Z = -1.0f;
	}

	// 上下一定値
	if (GetKeyboardTrigger(DIK_NUMPAD2))
	{
		pObject->pos.y += 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD0))
	{
		pObject->pos.y -= 1.0f;
	}

	if (X != 0.0f || Z != 0.0f)
	{ // 何かを入力していれば移動している判定
		move = true;
	}

	if (move)
	{
		// 移動量と目標方角を設定
		if (g_TrackAA)
		{
			pObject->pos.x += sinf(atan2f(X, Z));
			pObject->pos.z += cosf(atan2f(X, Z));
		}
		else
		{
			pObject->pos.x += sinf(atan2f(X, Z) + pCamera->rot.y);
			pObject->pos.z += cosf(atan2f(X, Z) + pCamera->rot.y);
		}
	}

#endif	// _DEBUG
}

//************************************************
// 既存のオブジェクトを消去（消したオブジェクト番号を埋めるようにソートする予定。←これが出来れば番号の変更を以前のもので使いまわせる。）
//************************************************
void DeleteObject(void)
{
	// オブジェクトの情報のリセット
	g_Object[g_obj_id].type = 0;
	g_Object[g_obj_id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object[g_obj_id].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object[g_obj_id].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object[g_obj_id].aabb = {};
	g_Object[g_obj_id].model.pMesh = NULL;
	g_Object[g_obj_id].model.pBuffMat = NULL;
	g_Object[g_obj_id].model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // テクスチャ情報のリセット
		g_ObjectModel[g_obj_id].pTex[i] = NULL;
	}
	g_Object[g_obj_id].nIdxShadow = 0;	//!< 現在未使用
}

//************************************************
// 既存オブジェクト用マトリックスの計算
//************************************************
void CalcMtxObject(void)
{
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (g_Object[i].model.pMesh == NULL)
		{ // なんらかの理由で空っぽならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Object[i].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Object[i].rot.y,
			g_Object[i].rot.x,
			g_Object[i].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_Object[i].mtxWorld,
			&g_Object[i].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Object[i].pos.x,
			g_Object[i].pos.y,
			g_Object[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Object[i].mtxWorld,
			&g_Object[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// 仮想オブジェクト用マトリックスの計算
//************************************************
void CalcMtxPreObject(int mode)
{
#ifdef _DEBUG

	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;		// 計算用マトリックス
	Object* pObject = nullptr;

	switch (mode)
	{
	case 0:
		// 仮想オブジェクト
		pObject = &g_PreObject;
		break;

	case 1:
		// ギズモ
		pObject = &g_GizmoObject;

		break;

	default:

		// エラー
		assert(false && "仮想オブジェクトのマトリックス計算異常");

		break;
	}

	/*--------------------------------------------*/

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&pObject->mtxWorld);

	if (mode == 1)
	{ // ギズモモードの場合ズーム率に合わせて拡縮
		EditCamera* pEditCamera = GetInfoEditCamera();	// 編集カメラ情報取得

		// 距離を取得
		float DistanceSize = (pEditCamera->distance * 0.005f);

		//スケールを変更1
		D3DXMatrixScaling(&mtxScale,
			pObject->size.x + DistanceSize,
			pObject->size.y + DistanceSize,
			pObject->size.z + DistanceSize);

		//スケールを変更2
		D3DXMatrixMultiply(&pObject->mtxWorld,
			&pObject->mtxWorld,
			&mtxScale);
	}

	// 向きを反映1
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		pObject->rot.y,
		pObject->rot.x,
		pObject->rot.z);

	// 向きを反映2
	D3DXMatrixMultiply(&pObject->mtxWorld,
		&pObject->mtxWorld,
		&mtxRot);

	// 位置を反映1
	D3DXMatrixTranslation(&mtxTrans,
		pObject->pos.x,
		pObject->pos.y,
		pObject->pos.z);

	// 位置を反映2
	D3DXMatrixMultiply(&pObject->mtxWorld,
		&pObject->mtxWorld,
		&mtxTrans);

#endif // _DEBUG
}

//************************************************
// オブジェクト描画
//************************************************
void DrawObject(bool LayoutEdit)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	for (int obj_id = 0; obj_id < AMOUNT_OBJECT; obj_id++)
	{
		if (g_Object[obj_id].model.pMesh == NULL)
		{ // なんらかの理由で空っぽならコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[obj_id].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Object[obj_id].model.pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int mat_id = 0; mat_id < (int)g_Object[obj_id].model.NumMat; mat_id++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[mat_id].MatD3D);

			//テクスチャの設定
			if (g_Object[obj_id].model.pTex[mat_id] != NULL)
			{
				pDevice->SetTexture(0, g_Object[obj_id].model.pTex[mat_id]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			// オブジェクトパーツの描画
			g_Object[obj_id].model.pMesh->DrawSubset(mat_id);
		}

		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

#ifdef _DEBUG

	if (LayoutEdit)
	{
		// 仮想オブジェクトを描画
		if (!g_Overwrite)
		{
			DrawPreObject(0);
		}

		// ギズモを描画
		DrawPreObject(1);
	}

#endif	// _DEBUG
}

//************************************************
// 仮想のオブジェクト描画
//************************************************
void DrawPreObject(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	Object* pObject = nullptr;

	switch (mode)
	{
	case 0:
		// 仮想オブジェクト
		pObject = &g_PreObject;
		break;

	case 1:
		// ギズモ
		pObject = &g_GizmoObject;

		//Z位置の比較方法の変更
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// 常に深度テストに合格
		break;

	default:

#ifdef _DEBUG

		// エラー
		assert(false && "仮想オブジェクトの描画モード異常");

#endif	// _DEBUG

		break;
	}

	/*--------------------------------------------*/

	D3DMATERIAL9 matDef;							// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;								// マテリアルデータへのポインタ

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &pObject->mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pObject->model.pBuffMat->GetBufferPointer();

	// そのパーツの持つマテリアル分回す
	for (int i = 0; i < (int)pObject->model.NumMat; i++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//テクスチャの設定
		if (pObject->model.pTex[i] != NULL)
		{
			pDevice->SetTexture(0, pObject->model.pTex[i]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// オブジェクトパーツの描画
		pObject->model.pMesh->DrawSubset(i);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	if (mode == 1)
	{ // ギズモ描画モードの場合
		//Z位置の比較方法の修正
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}

//************************************************
// オブジェクト情報を取得
//************************************************
Object* GetInfoObject(void)
{
	return &g_Object[0];
}

//************************************************
// ギズモ情報を取得
//************************************************
Object* GetInfoGizmoObject(void)
{
	return &g_GizmoObject;
}

//************************************************
// モデル配置情報を保存する
//************************************************
void ExportLayoutObject(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 rot = {};	// 計算用

	// 保存するファイルを用意
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_export.txt", "w") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "オブジェクトモデル配置保存用のファイルの用意に失敗");

#else

		return;

#endif	// _DEBUG
	}

	// ビューワーで使いまわしやすいフォーマットで書き出しておく…
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# モデル配置情報\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");

	// モデルの種類、位置、向きを、置いた分だけ書き出す
	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (g_Object[i].model.pMesh == NULL)
		{ // モデル情報が無ければこの番はコンティニュー
			continue;
		}

		// 弧度を度数に変換
		rot = (g_Object[i].rot * 180.0f) / D3DX_PI;

		fprintf(pFile, "MODELSET\n");
		fprintf(pFile, "	TYPE = %d\n", g_Object[i].type);
		fprintf(pFile, "	POS = %.1f %.1f %.1f\n", g_Object[i].pos.x, g_Object[i].pos.y, g_Object[i].pos.z);
		fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", rot.x, rot.y, rot.z);
		fprintf(pFile, "END_MODELSET\n\n");
	}

	// 終了
	fprintf(pFile, "END_SCRIPT\n");

	// ファイルを閉じる
	fclose(pFile);
}
