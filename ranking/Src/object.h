//************************************************
//
// オブジェクト、ヘッダファイル[object.h]
// Author：福田歩希
//
//************************************************
#ifndef _OBJECT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _OBJECT_H_	//(二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

/*/ マクロ定義 /*/
#define AMOUNT_OBJECT 256			// 物の最大数
#define AMOUNT_MODEL_OBJECT	64		// 物の保持できる最大モデル種数

// 物用モデル情報
typedef struct
{
	LPD3DXMESH pMesh;						// メッシュ情報のポインタ
	LPD3DXBUFFER pBuffMat;					// マテリアルのポインタ
	DWORD NumMat;							// マテリアルの数
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// テクスチャのポインタ
}ObjectModel;

// 物情報
typedef struct
{
	int type;				// モデルの種類格納
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 size;		// サイズ
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	COLLISION_AABB aabb;	// AABB衝突判定用
	ObjectModel model;		// モデル情報格納
	int nIdxShadow;			// 一応影の番号格納用
}Object;

/*/ プロトタイプ宣言 /*/
void InitObject(void);					// オブジェクトの初期
void InitPreObject(void);				// 仮想のオブジェクトの初期
void InitGizmoObject(void);				// ギズモの初期
void ImportModelObject(void);			// オブジェクトモデル取得
void ImportGizmoModelObject(void);		// ギズモモデル取得
void ImportLayoutObject(FILE* pFile);	// モデル配置情報取得
void VerifyTypeObject(int id_Model);	// オブジェクト種類の照合
void VerifyTypePreObject(void);			// 仮想オブジェクト種類の照合
void ImportTexObject(void);				// モデルテクスチャを読込み
void UninitObject(void);				// オブジェクト破棄
void UninitGizmoObject(void);			// ギズモ破棄
void UpdateObject(bool LayoutEdit);		// 更新
int GetInfoMaxObject(void);				// 現在の配置モデル数を取得
void PrintInfoObject(void);				// デバッグ表示
void RotateObject(Object* pObject);		// オブジェクトの回転
void MoveObject(Object* pObject);		// オブジェクトの移動
void CalcMtxObject(void);				// 既存オブジェクト用マトリックスの計算
void CalcMtxPreObject(int mode);		// 仮想オブジェクト用マトリックスの計算
void DeleteObject(void);				// 既存オブジェクトを消去
void DrawObject(bool LayoutEdit);		// オブジェクトの描画
void DrawPreObject(int mode);			// 仮想のオブジェクトの描画(ギズモ含む)
Object* GetInfoObject(void);			// オブジェクトの情報を取得
Object* GetInfoGizmoObject(void);		// ギズモ情報を取得
void ExportLayoutObject(void);			// モデル配置情報保存

#endif