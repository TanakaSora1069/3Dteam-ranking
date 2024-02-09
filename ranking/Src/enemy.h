//************************************************
//
// �G�l�~�[�����A�w�b�_�t�@�C��[enemy.h]
// Author�F���c����
//
//************************************************
#ifndef _ENEMY_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� / */
#include "main.h"

/*/ �}�N����` /*/
#define AMOUNT_ENEMY 64				// �G�l�~�[�̍ő吔
#define AMOUNT_ENEMY_PARTS	32		// �G�l�~�[�ő僂�f���퐔
#define SPD_STOPMOVE_ENEMY	0.9f	// �u���[�L��

// �G�l�~�[�̎�ޕ���
typedef enum
{
	Dragonfly = 0,	// �g���{
	Ant,			// �a
	Max_enemystyle,
}EnemyStyle;

// �G�l�~�[��ԕ���
typedef enum
{
	stateNormal_e = 0,	// �ʏ�
	stateMove_e,		// �ړ�
	stateAtk_e,			// �U��
	stateCharge_e,		// ����
	stateRotate_e,		// ��]
	stateDamage_e,		// ����
	stateDead_e,		// ���S
	steteResurrect_e,	// ����
	Max_enemystate,
}EnemyState;

// �G�l�~�[�p�����[�^���
typedef struct
{
	int appear;		// �o���^�C�~���O
	int style;		// �X�^�C��
	int state;		// ���
	int dur;		// ��Ԍp��
	int target;		// �Ώ�
	int HP;			// �̗�
	float SPD;		// ���x
	float rad;		// ������T�C�Y
	int motion_now;	// �Đ����[�V����
	int motion_old;	// �ߋ����[�V����
}EnemyParam;

// �G�l�~�[�p���f�����
typedef struct
{
	int style;								// �X�^�C��
	LPD3DXMESH pMesh;						// ���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;					// �}�e���A���̃|�C���^
	DWORD NumMat;							// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 pos_offset;					// �ʒu�I�t�Z�b�g
	D3DXVECTOR3 pos_moved;					// ���[�V�������ȂǕϓ��ʒu
	D3DXVECTOR3 rot_offset;					// �����I�t�Z�b�g
	D3DXVECTOR3 rot_moved;					// ���[�V�������ȂǕϓ�����
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	int IdxParent;							// �e�p�[�c�̃C���f�b�N�X
}EnemyModel;

// ���[�V�������̃p�[�c�ڕW����p
typedef struct
{
	D3DXVECTOR3 pos;	// �ڕW�ʒu�i�[
	D3DXVECTOR3 rot;	// �ڕW�����i�[
}EnemyMotionDest;

// ���[�V�������̃L�[�p
typedef struct
{
	int amount_frame;							// �L�[�P�ʂ̑��t���[����
	EnemyMotionDest dest[AMOUNT_ENEMY_PARTS];	// �p�[�c�̓�����i�[
}EnemyMotionKey;

// �G�l�~�[���[�V�����p
typedef struct
{
	int loop;				// ���[�v�t���O
	int amount_key;			// ���[�V�����P�ʂ̑��L�[��
	int id_key;				// �Đ����̃L�[�ԍ����i�[
	int id_frame;			// �Đ����̃t���[���ԍ����i�[
	EnemyMotionKey key[16];	// �L�[�����i�[
}EnemyMotion;

// �G�l�~�[���
typedef struct
{
	bool use;								// �g�p���� 
	EnemyParam param;						// �p�����[�^
	D3DXVECTOR3 pos;						// ���[���h�ʒu
	D3DXVECTOR3 pos_old;					// �ߋ��̈ʒu
	D3DXVECTOR3 move;						// �ړ���
	D3DXVECTOR3 rot;						// ���݂̌���
	D3DXVECTOR3 rot_goal;					// �ڕW�̌���
	D3DXVECTOR3 size;						// �傫��
	D3DXCOLOR col;							// �F�ύX�p
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	EnemyModel parts[AMOUNT_ENEMY_PARTS];	// �G�l�~�[�̃p�[�c��
	EnemyMotion motion[8];					// ���[�V�������
	int id_shadow;							// �e���ʔԍ��i�[
	int id_sph;								// ���莯�ʔԍ��i�[
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);					// ����
void ImportModelEnemy(void);			// ���f���擾
void ImportOffsetEnemy(FILE* pFile,
	int AmountModel);					// ���f���I�t�Z�b�g�擾
void ImportTexEnemy(int AmountModel);	// ���f���e�N�X�`���擾
void VerifyStyleEnemy(int id);			// �X�^�C���ԍ����ƍ�
void ImportMotionEnemy(void);			// ���[�V�����擾
void ImportParamEnemy(void);			// �p�����[�^�擾
void UninitEnemy(void);					// �j��
void UpdateEnemy(void);					// �X�V
void AppearEnemy(int id);				// �o��
void RotateEnemy(int id);				// ��]
void MoveEnemy(int id);					// �ړ�
int SetTargetEnemy(int id);				// �Ώۂ����߂�
void AtkEnemy(int id);					// �U��
void HitEnemy(int id);					// ��e��
void DamageEnemy(int id);				// ����
void DeadEnemy(int id);					// ���S
void ResurrectEnemy(int id);			// ����
void MotionEnemy(int id);				// ���[�V�����Ǘ�
void ChangeMotionEnemy(int id,
	int* pNow, int* pOld);				// ���[�V�����ύX���m
void MoveMotionEnemy(int id,
	EnemyMotion* pMotion);				// ���[�V��������p
void CntMotionEnemy(int id,
	EnemyMotion* pMotion);				// ���[�V�����J�E���g�p
void DeleteEnemy(int id);				// ����
void CalcMtxEnemy(void);				// �s��v�Z
void DrawEnemy(void);					// �`��
Enemy* GetInfoEnemy(void);				// �G�l�~�[�����擾

#endif