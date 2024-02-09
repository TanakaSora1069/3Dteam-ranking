////************************************************
////
//// 立方体の判定を可視化、ヘッダファイル[visible_box.h]
//// Author：福田歩希
////
////************************************************
//#ifndef _VISIBLE_BOX_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
//#define _VISIBLE_BOX_H_	// (二重インクルード防止、マクロ定義する)
//
///*/ インクルードファイル /*/
//#include "main.h"
//
//// 判定表示用
//struct Box
//{
//	D3DXVECTOR3 pos;		// 判定表示の位置
//	D3DXVECTOR3* pPos;		// 対象物の位置のアドレス格納
//	D3DXCOLOR col;			// 表示カラー
//	D3DXMATRIX mtxWorld;	// ワールドマトリックス
//};
//
////プロトタイプ宣言
//void InitVisible_Box(void);			// 初期
//void UninitVisible_Box(void);		// 破棄
//void UpdateVisible_Box(void);		// 更新
//void CreateVisible_Box(const COLLISION_AABB box, D3DXCOLOR col, D3DXVECTOR3* pPos);	// 生成
//void DeleteVisible_Box(int Box_id);	// 消去
//void DrawVisible_Box(void);			// 描画
//
//#endif