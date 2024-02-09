//************************************************
//
// �{�X�A�w�b�_�t�@�C��[boss.h]
// Author�F�����h��
//
//************************************************

#ifndef _BOSS_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BOSS_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� / */
#include "main.h"

/*/ �}�N����` /*/
#define MAX_BOSS			(2)		// �{�X�̐�
#define AMOUNT_BOSS_PARTS	(16)	// �{�X�ő僂�f���퐔
#define SPD_STOPMOVE_BOSS	(0.9f)	// �u���[�L��
#define NUM_MOTION			(9)		//���[�V�����̎�ސ�

// �{�X�̎�ޕ���
typedef enum
{
	BOSSTYPE_MID = 0,	//���{�X
	BOSSTYPE_BIG,		//��{�X
	BOSSTYPE_MAX
}BOSSTYPE;

// �{�X��ԕ���
typedef enum
{
	stateNormal_b = 0,	// �ʏ�
	stateMove_b,		// �ړ�
	stateAtk_b,			// �U��
	stateDamage_b,		// ��e
	stateDead_b,		// ���S
	steteResurrect_b,	// ����
	Max_bossstate,
}BOSSState;

//���[�V������ޕ���
typedef enum
{
	motion_neutral = 0,	// �j���[�g�������[�V����
	motion_move,		// �ړ����[�V����
	motion_action,		// �U�����[�V����
	motion_jump,		// �W�����v���[�V����
	motion_landing,		// ���n���[�V����
	motion_blownaway,	// ������у��[�V����
	motion_fall,		// �|��r�����[�V����
	motion_collapse,	// �|��j���[�g�������[�V����
	motion_Resurrect,	// �N���オ�胂�[�V����
	motion_max,
}BossMotionType;

// �{�X�p�����[�^���
typedef struct
{
	int appear;			// �o���^�C�~���O
	int style;			// �X�^�C��
	int state;			// ���
	int dur;			// ��Ԍp��
	float HP;			// �̗�
	D3DXVECTOR3 SPD;	// ���x
	float Radius;		// ���̔���ɕK�v�Ȕ��a
	int motion_now;		// �Đ����[�V����
	int motion_old;		// �ߋ����[�V����
	bool bMove;			// �ړ����Ă��邩�ǂ���

}BOSSParam;

// �{�X�p���f�����
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
}BOSSModel;

// ���[�V�������̃p�[�c�ڕW����p
typedef struct
{
	D3DXVECTOR3 pos;	// �ڕW�ʒu�i�[
	D3DXVECTOR3 rot;	// �ڕW�����i�[
}BossMotionDest;

// ���[�V�������̃L�[�p
typedef struct
{
	int amount_frame;							// �L�[�P�ʂ̑��t���[����
	BossMotionDest dest[AMOUNT_BOSS_PARTS];		// �p�[�c�̓�����i�[
}BossMotionKey;

// �{�X���[�V�����p
typedef struct
{
	int loop;				// ���[�v�t���O
	int amount_key;			// ���[�V�����P�ʂ̑��L�[��
	int id_key;				// �Đ����̃L�[�ԍ����i�[
	int id_frame;			// �Đ����̃t���[���ԍ����i�[
	BossMotionKey key[16];	// �L�[�����i�[
}BossMotion;

// �{�X���
typedef struct
{
	bool use;								// �g�p���� 
	D3DXVECTOR3 pos;						// ���[���h�ʒu
	D3DXVECTOR3 pos_old;					// �ߋ��̈ʒu
	D3DXVECTOR3 move;						// �ړ���
	D3DXVECTOR3 rot;						// ���݂̌���
	D3DXVECTOR3 rot_goal;					// �ڕW�̌���
	D3DXCOLOR col;							// �F�ύX�p
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	BOSSModel parts[AMOUNT_BOSS_PARTS];		// �G�l�~�[�̃p�[�c��
	BOSSTYPE type;							// �{�X�̎��
	BOSSState State;						// �{�X�̏��
	BOSSParam Param;						// �{�X�̃p�����[�^�[
	int id_sph;								// ���莯�ʔԍ��i�[
	BossMotion motion[8];					// ���[�V�������
}BOSS;

//�v���g�^�C�v�錾
void InitBoss(void);									// ����
void ImportModelBoss(void);								// ���f���擾
void ImportOffsetBoss(FILE* pFile, int AmountModel);	// ���f���I�t�Z�b�g�擾
void ImportTexBoss(int AmountModel);					// ���f���e�N�X�`����Ǎ���
void ImportMotionBoss(void);							// ���[�V�����擾
//void GenerateBOSS(void);								// �o���ݒ�
void AppearBoss(int id);								// �o��
void ImportParamBoss(void);								// �p�����[�^�擾
void VerifyStyleBoss(int id);							// �X�^�C���ԍ����ƍ�
void UninitBoss(void);									// �j��
void UpdateBoss(void);									// �X�V
void RotateBoss(int id);								// ��]
void MoveBoss(int id);									// �ړ�
void CalcMtxBoss(void);									// �s��v�Z
void DrawBoss(void);									// �`��
BOSS* GetInfoBoss(void);								// �G�l�~�[�����擾
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	int nStyle, float fLife);							// �G�̃p�����[�^�[��ݒ肷��
void MidBossBehavior(int id);							// ���{�X�̋���
void BigBossBehavior(int id);							// ��{�X�̋���
void HitBoss(int id);									// �{�X�ƒe�̓����蔻��
void DamageBoss(int id);								// ����
void DeadBoss(int id);									// ���S
void ResurrectBoss(int id);								// ����
void MotionBoss(int id);								// ���[�V�����Ǘ�
void ChangeMotionBoss(int id,int* pNow, int* pOld);		// ���[�V�����ύX���m
void MoveMotionBoss(int id,BossMotion* pMotion);		// ���[�V��������p
void CntMotionBoss(int id,BossMotion* pMotion);			// ���[�V�����J�E���g�p


#endif
