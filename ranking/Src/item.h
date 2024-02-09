//************************************************
//
// �A�C�e���A�w�b�_�t�@�C��[item.h]
// Author�F���c����
//
//************************************************
#ifndef _ITEM_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ITEM_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

/*/ �}�N����` /*/
#define AMOUNT_ITEM 64			// ���̍ő吔
#define AMOUNT_MODEL_ITEM	4	// ���̕ێ��ł���ő僂�f���퐔

// �A�C�e���̎���
typedef enum
{
	styleGun = 0,	// �g���v�\��
	styleRPG,		// RPG
	Max_itemstyle
}ItemStyle;

// �A�C�e���p���f�����
typedef struct
{
	int style;								// �X�^�C��
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
	float rad;								// �ЂȌ`�ɂ����锻��T�C�Y
}ItemModel;

// �A�C�e���p���
typedef struct
{
	bool use;				// �g�p���Ă��邩�ǂ���
	int style;				// �X�^�C��
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ����
	ItemModel model;		// ���f�����
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	int id_effect;			// �G�t�F�N�g���ʔԍ��i�[
	int id_sph;				// ���莯�ʔԍ��i�[
}Item;

/*/ �v���g�^�C�v�錾 /*/
void InitItem(void);					// ����
void ImportModelItem(void);				// ���f���擾
void ImportParamItem(FILE* pFile,
	int AmountModel);					// �p�����[�^�擾
void ImportTexItem(int AmountModel);	// ���f���e�N�X�`���擾
void CreateItem(int style);				// ����
void VerifyStyleItem(int id);			// �X�^�C���ԍ����ƍ�
void UninitItem(void);					// �I��
void UpdateItem(void);					// �X�V
void RotateItem(int id);				// ��]
void MoveItem(int id);					// �ړ�
void CollisionItem(int id);				// �����蔻��
void CalcMtxItem(void);					// �s��v�Z
int GetItem(int id);					// �擾
void DrawItem(void);					// �`��
Item* GetInfoItem(void);				// �����擾

#endif