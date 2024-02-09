//************************************************
//
// �G�t�F�N�g�A�w�b�_�t�@�C��[effect.h]
// Author�F�����h��
//
//************************************************

#ifndef _EFFECT_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EFFECT_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

//include
#include "main.h"

//�}�N����`
#define MAX_EFFECT	(4096)	//�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	D3DXMATRIX mtxworld;	//���[���h�}�g���b�N�X
	float fLife;			//���C�t
	float fRadius;			//���a
	bool bUse;				//�g�p���Ă��邩�ǂ���							
}EFFECT;

//�v���g�^�C�v�錾
void InitEffect(void);														//����������
void UninitEffect(void);													//�I������
void UpdateEffect(void);													//�X�V����
void DrawEffect(void);														//�`�揈��
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float fLife);	//�ݒ菈��
EFFECT* GetEffect(void);													//�����擾
#endif