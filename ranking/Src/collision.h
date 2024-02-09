//************************************************
//
// 衝突判定、ヘッダファイル[collision.h]
// Author：福田歩希
//
//************************************************
#ifndef _COLLISION_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _COLLISION_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

/*/ プロトタイプ宣言 /*/
bool CollisionSph(const D3DXVECTOR3 sph1, const float r1,
	const D3DXVECTOR3 sph2, const float r2);								// 球同士の衝突判定
bool CollisionAABB(const COLLISION_AABB box1, const COLLISION_AABB box2);   // AABB同士の衝突判定

#endif