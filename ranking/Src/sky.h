//************************************************
//
// �󏈗��A�w�b�_�t�@�C��[sky.h]
// Author�F���c����
//
//************************************************
#ifndef _SKY_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SKY_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

// ��\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
}Sky;

/*/ �v���g�^�C�v�錾 /*/
void InitSky(void);		// ����
void UninitSky(void);	// �j��
void UpdateSky(void);	// �X�V
void CalcMtxSky(void);	// �s��v�Z
void DrawSky(void);		// �`��

#endif