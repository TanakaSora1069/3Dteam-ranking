//************************************************
//
// 弾、ヘッダファイル[bullet.h]
// Author：福田歩希
//
//************************************************
#ifndef _BULLET_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BULLET_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

/*/ マクロ定義 /*/
#define AMOUNT_BULLET 256	// 弾数
#define SPAN_BULLET 10.0f	// 弾の大きさ
#define SPD_BULLET 7.5f	// 弾の速さ

// 弾の種類分け
typedef enum
{
	bulletPlayer = 0,	// プレイヤー
	bulletEnemy = 0,	// エネミー
	Max_bullettype
}BulletType;

// 弾用情報
struct Bullet
{
	bool use;				// 使用フラグ
	int type;				// タイプ識別
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	float rad;				// 球判定サイズ
	int remain;				// 寿命
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	int id_shadow;			// 影識別番号格納
	int id_sph;				// 判定識別番号格納
};

//プロトタイプ宣言
void InitBullet(void);			// 初期
void UninitBullet(void);		// 破棄
void CreateBullet(int type,
	int id);					// 生成
//void AdjustBullet(void);		// 弾道強化
void UpdateBullet(void);		// 更新
void DeleteBullet(int id);		// 消去
void DrawBullet(void);			// 描画
void CollisionBullet(int id);	// 当たり判定
Bullet* GetInfoBullet(void);	// 弾情報を取得

#endif