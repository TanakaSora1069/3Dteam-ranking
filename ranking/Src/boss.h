//************************************************
//
// ボス、ヘッダファイル[boss.h]
// Author：葛西敬介
//
//************************************************

#ifndef _BOSS_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BOSS_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル / */
#include "main.h"

/*/ マクロ定義 /*/
#define MAX_BOSS			(2)		// ボスの数
#define AMOUNT_BOSS_PARTS	(16)	// ボス最大モデル種数
#define SPD_STOPMOVE_BOSS	(0.9f)	// ブレーキ力
#define NUM_MOTION			(9)		//モーションの種類数

// ボスの種類分け
typedef enum
{
	BOSSTYPE_MID = 0,	//中ボス
	BOSSTYPE_BIG,		//大ボス
	BOSSTYPE_MAX
}BOSSTYPE;

// ボス状態分け
typedef enum
{
	stateNormal_b = 0,	// 通常
	stateMove_b,		// 移動
	stateAtk_b,			// 攻撃
	stateDamage_b,		// 被弾
	stateDead_b,		// 死亡
	steteResurrect_b,	// 復活
	Max_bossstate,
}BOSSState;

//モーション種類分け
typedef enum
{
	motion_neutral = 0,	// ニュートラルモーション
	motion_move,		// 移動モーション
	motion_action,		// 攻撃モーション
	motion_jump,		// ジャンプモーション
	motion_landing,		// 着地モーション
	motion_blownaway,	// 吹っ飛びモーション
	motion_fall,		// 倒れ途中モーション
	motion_collapse,	// 倒れニュートラルモーション
	motion_Resurrect,	// 起き上がりモーション
	motion_max,
}BossMotionType;

// ボスパラメータ情報
typedef struct
{
	int appear;			// 出現タイミング
	int style;			// スタイル
	int state;			// 状態
	int dur;			// 状態継続
	float HP;			// 体力
	D3DXVECTOR3 SPD;	// 速度
	float Radius;		// 球の判定に必要な半径
	int motion_now;		// 再生モーション
	int motion_old;		// 過去モーション
	bool bMove;			// 移動しているかどうか

}BOSSParam;

// ボス用モデル情報
typedef struct
{
	int style;								// スタイル
	LPD3DXMESH pMesh;						// メッシュのポインタ
	LPD3DXBUFFER pBuffMat;					// マテリアルのポインタ
	DWORD NumMat;							// マテリアルの数
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// テクスチャのポインタ
	D3DXVECTOR3 pos_offset;					// 位置オフセット
	D3DXVECTOR3 pos_moved;					// モーション時など変動位置
	D3DXVECTOR3 rot_offset;					// 向きオフセット
	D3DXVECTOR3 rot_moved;					// モーション時など変動向き
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	int IdxParent;							// 親パーツのインデックス
}BOSSModel;

// モーション時のパーツ目標動作用
typedef struct
{
	D3DXVECTOR3 pos;	// 目標位置格納
	D3DXVECTOR3 rot;	// 目標向き格納
}BossMotionDest;

// モーション時のキー用
typedef struct
{
	int amount_frame;							// キー単位の総フレーム数
	BossMotionDest dest[AMOUNT_BOSS_PARTS];		// パーツの動作情報格納
}BossMotionKey;

// ボスモーション用
typedef struct
{
	int loop;				// ループフラグ
	int amount_key;			// モーション単位の総キー数
	int id_key;				// 再生中のキー番号を格納
	int id_frame;			// 再生中のフレーム番号を格納
	BossMotionKey key[16];	// キー情報を格納
}BossMotion;

// ボス情報
typedef struct
{
	bool use;								// 使用判定 
	D3DXVECTOR3 pos;						// ワールド位置
	D3DXVECTOR3 pos_old;					// 過去の位置
	D3DXVECTOR3 move;						// 移動量
	D3DXVECTOR3 rot;						// 現在の向き
	D3DXVECTOR3 rot_goal;					// 目標の向き
	D3DXCOLOR col;							// 色変更用
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	BOSSModel parts[AMOUNT_BOSS_PARTS];		// エネミーのパーツ数
	BOSSTYPE type;							// ボスの種類
	BOSSState State;						// ボスの状態
	BOSSParam Param;						// ボスのパラメーター
	int id_sph;								// 判定識別番号格納
	BossMotion motion[8];					// モーション情報
}BOSS;

//プロトタイプ宣言
void InitBoss(void);									// 初期
void ImportModelBoss(void);								// モデル取得
void ImportOffsetBoss(FILE* pFile, int AmountModel);	// モデルオフセット取得
void ImportTexBoss(int AmountModel);					// モデルテクスチャを読込み
void ImportMotionBoss(void);							// モーション取得
//void GenerateBOSS(void);								// 出現設定
void AppearBoss(int id);								// 出現
void ImportParamBoss(void);								// パラメータ取得
void VerifyStyleBoss(int id);							// スタイル番号を照合
void UninitBoss(void);									// 破棄
void UpdateBoss(void);									// 更新
void RotateBoss(int id);								// 回転
void MoveBoss(int id);									// 移動
void CalcMtxBoss(void);									// 行列計算
void DrawBoss(void);									// 描画
BOSS* GetInfoBoss(void);								// エネミー情報を取得
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	int nStyle, float fLife);							// 敵のパラメーターを設定する
void MidBossBehavior(int id);							// 中ボスの挙動
void BigBossBehavior(int id);							// 大ボスの挙動
void HitBoss(int id);									// ボスと弾の当たり判定
void DamageBoss(int id);								// 負傷
void DeadBoss(int id);									// 死亡
void ResurrectBoss(int id);								// 復活
void MotionBoss(int id);								// モーション管理
void ChangeMotionBoss(int id,int* pNow, int* pOld);		// モーション変更検知
void MoveMotionBoss(int id,BossMotion* pMotion);		// モーション動作用
void CntMotionBoss(int id,BossMotion* pMotion);			// モーションカウント用


#endif
