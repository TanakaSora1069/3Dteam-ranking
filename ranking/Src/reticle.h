//************************************************
//
// ���e�B�N���A�w�b�_�t�@�C��[reticle.h]
// Author�F���c����
//
//************************************************
#ifndef _RETICLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RETICLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

// ���e�B�N���p���
typedef struct
{
	bool use;				// �g�p�t���O
	D3DXVECTOR3 pos_moved;	// �ϓ��ʒu
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR2 span;		// �傫���p
	float angle;			// �p�x
	float length;			// �Ίp���p
	int remain;				// ����
	D3DXCOLOR col;			// �F
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
}Reticle;

//�v���g�^�C�v�錾
void InitReticle(void);				// ����
void CreateReticle(int joined);		// ����
void UninitReticle(void);			// �I��
void UpdateReticle(int joined);		// �X�V
void SetVtxReticle(int joined);		// �W�J
void DrawReticle(int id);			// �`��
Reticle* GetInfoReticle(void);		// �擾

#endif