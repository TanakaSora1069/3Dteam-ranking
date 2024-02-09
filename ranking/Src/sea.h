//************************************************
//
// �C���������A�w�b�_�t�@�C��[sea.h]
// Author�F���c����
//
//************************************************
#ifndef _SEA_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SEA_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

// �C�p�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXCOLOR col;			// �F
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
}Sea;

/*/ �v���g�^�C�v�錾 /*/
void InitSea(void);		// ����
void UninitSea(void);	// �j��
void UpdateSea(void);	// �X�V
void CalcMtxSea(void);	// �s��v�Z
void DrawSea(void);		// �`��

#endif