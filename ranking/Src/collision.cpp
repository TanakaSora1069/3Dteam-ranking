//************************************************
//
// 衝突判定[collision.cpp]
// Author：福田歩希
//
//************************************************
/*/ インクルードファイル /*/
#include "collision.h"
// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif	// _DEBUG

/*/ マクロ定義 /*/
#define SPH_AABB_VERIFY 0  // 衝突判定の取り方を変更

//************************************************
// 球同士の衝突判定
//************************************************
bool CollisionSph(const D3DXVECTOR3 sph1, const float r1, const D3DXVECTOR3 sph2, const float r2)
{
    // 球体1から球体2へのベクトルを算出
    D3DXVECTOR3 vec = sph2 - sph1;

    // 球体間の距離を算出
    float dist = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    // 球体間距離が互いの半径の合計以下であれば接触
    return (dist <= r1 + r2);
}

//************************************************
// 球とAABBの衝突判定
//************************************************
#pragma warning(disable:4100)
bool CollisionSph(const D3DXVECTOR3 sph, const float r, const COLLISION_AABB box)
#pragma warning(default:4100)
{
#if SPH_AABB_VERIFY
    
    // これはウソです
    return (sph.x < box.max.x &&
        sph.x > box.min.x &&
        sph.y < box.max.y &&
        sph.y > box.min.y &&
        sph.z < box.max.z &&
        sph.z > box.min.z);

#else
    return false;
#endif
}

//************************************************
// AABB同士の衝突判定
//************************************************
bool CollisionAABB(const COLLISION_AABB box1, const COLLISION_AABB box2)
{
    // 各軸でお互いの最大・最小を結ぶ線分が重なれば接触
    return (box1.min.x < box2.max.x &&
        box1.max.x > box2.min.x &&
        box1.min.y < box2.max.y &&
        box1.max.y > box2.min.y &&
        box1.min.z < box2.max.z &&
        box1.max.z > box2.min.z);
}