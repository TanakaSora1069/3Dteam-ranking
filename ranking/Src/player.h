//************************************************
//
// �v���C���[�����A�w�b�_�t�@�C��[player.h]
// Author�F���c����, kasai keisuke
//
//************************************************
#ifndef _PLAYER_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PLAYER_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� / */
#include "main.h"

#include "item.h"	// ���߂�Ȃ���

/*/ �}�N����` /*/
#define AMOUNT_PLAYER_PARTS	16		// �v���C���[�ő僂�f���퐔
#define SPD_STOPMOVE_PLAYER	0.9f	// �u���[�L��
#define SPD_MOVE_PLAYER	0.3f		// �ړ����x

// �v���C���[�̏�ԕ���
typedef enum
{
	stateNormal_p = 0,	// �ʏ�
	stateMove_p,		// �ړ�
	stateAtk_p,			// �U��
	stateDamage_p,		// ����
	stateDead_p,		// ���S
	steteResurrect_p,	// ����
	Max_playerstate,
}PlayerState;

// �v���C���[�p�����[�^���
typedef struct
{
	int style;		// �X�^�C��
	int state;		// ���
	int dur;		// ��Ԍp��
	int HP;			// �̗�
	float SPD;		// ���x
	float rad;		// ������T�C�Y
	int weapon;		// ���펯��
	int motion_now;	// �Đ����[�V����
	int motion_old;	// �ߋ����[�V����
}PlayerParam;

// �v���C���[���U������ʒu��ۑ��c
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXMATRIX mtx;		// ���[���h�}�g���b�N�X
}OffsetPosAtk;

// �v���C���[�p���f�����
typedef struct
{
	int style;								// �X�^�C��
	int weapon;								// ���펯��
	LPD3DXMESH pMesh;						// ���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;					// �}�e���A���̃|�C���^
	DWORD NumMat;							// �}�e���A���̐�
	D3DXCOLOR ColMat_offset[AMOUNT_MAT];	// �}�e���A���̐F�I�t�Z�b�g
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 pos_offset;					// �ʒu�I�t�Z�b�g
	D3DXVECTOR3 pos_moved;					// ���[�V������̕ϓ��ʒu
	D3DXVECTOR3 rot_offset;					// �����I�t�Z�b�g
	D3DXVECTOR3 rot_moved;					// ���[�V������̕ϓ�����
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	int IdxParent;							// �e�p�[�c�̃C���f�b�N�X
}PlayerModel;

// ���[�V�������̃p�[�c�ڕW����p
typedef struct
{
	D3DXVECTOR3 pos;	// �ڕW�ʒu�i�[
	D3DXVECTOR3 rot;	// �ڕW�����i�[
}PlayerMotionDest;

// ���[�V�������̃L�[�p
typedef struct
{
	int amount_frame;							// �L�[�P�ʂ̑��t���[����
	PlayerMotionDest dest[AMOUNT_PLAYER_PARTS];	// �p�[�c�̓�����i�[
}PlayerMotionKey;

// �v���C���[���[�V�����p
typedef struct
{
	int loop;					// ���[�v�t���O
	int amount_key;				// ���[�V�����P�ʂ̑��L�[��
	int id_key;					// �Đ����̃L�[�ԍ����i�[
	int id_frame;				// �Đ����̃t���[���ԍ����i�[
	PlayerMotionKey key[16];	// �L�[�����i�[
}PlayerMotion;

// �v���C���[���
typedef struct
{
	bool use;								// �g�p�t���O
	PlayerParam param;						// �p�����[�^
	D3DXVECTOR3 pos;						// ���[���h�ʒu
	D3DXVECTOR3 pos_old;					// �ߋ��̈ʒu
	D3DXVECTOR3 move;						// �ړ���
	D3DXVECTOR3 rot;						// ���݂̌���
	D3DXVECTOR3 rot_goal;					// �ڕW�̌���
	D3DXCOLOR col;							// �F�ύX�p
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	OffsetPosAtk offset_atk[Max_itemstyle];	// �U������ʒu���i�[
	PlayerModel parts[AMOUNT_PLAYER_PARTS];	// ���f���p�[�c
	PlayerMotion motion[8];					// ���[�V�������
	int id_shadow;							// �e���ʔԍ�
	int id_sph;								// ���莯�ʔԍ��i�[
}Player;

/*/ �v���g�^�C�v�錾 /*/
void InitPlayer(void);								// ����
void ImportModelPlayer(void);						// ���f���擾
void ImportOffsetPlayer(FILE* pFile,
	int AmountModel);								// ���f���I�t�Z�b�g�擾
void ImportOffsetAtkPlayer(FILE* pFile);			// �U���ʒu�̃I�t�Z�b�g�擾
void ImportTexPlayer(int AmountModel);				// ���f���e�N�X�`���擾
void VerifyStylePlayer(int id);						// �X�^�C���ԍ����ƍ�
void ImportMotionPlayer(void);						// ���[�V�����擾
void UninitPlayer(void);							// �j��
void UpdatePlayer(int id);							// �X�V
void RotatePlayer(int id);							// ��]
void AdjustTurret(int id);							// �C������
void MovePlayer(int id);							// �ړ�
void DEBUG_MovePlayer(void);						// �f�o�b�O�ړ�
void AtkPlayer(int id);								// �U��
void HitPlayer(int id);								// ��e��
void DamagePlayer(int id);							// ����
void DeadPlayer(int id);							// ���S
void ResurrectPlayer(int id);						// ����
void MotionPlayer(int id);							// ���[�V�����Ǘ�
void ChangeMotionPlayer(int id,
	int* pNow, int* pOld);							// ���[�V�����ύX���m
void MoveMotionPlayer(int id,
	PlayerMotion* pMotion);							// ���[�V��������p
void CntMotionPlayer(int id,
	PlayerMotion* pMotion);							// ���[�V�����J�E���g�p
void CalcMtxPlayer(void);							// �s��v�Z
void DrawPlayer(void);								// �`��
void ChangeDiffuseColPlayer(int player_id,
	int parts_id, int mat_id, D3DXMATERIAL* pMat);	// �g�U���̕ύX(�S������)
Player* GetInfoPlayer(void);						// �v���C���[�����擾

#endif