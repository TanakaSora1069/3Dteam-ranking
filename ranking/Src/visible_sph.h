//************************************************
//
// ���`�̓����蔻��������A�w�b�_�t�@�C��[visible_sph.h]
// Author�F���c����
//
//************************************************
#ifndef _VISIBLE_SPH_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _VISIBLE_SPH_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

// �X�t�B�A�\����
typedef struct
{
	bool use;				// �g�p����
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3* pPos;		// �Ǐ]�Ώۂ̈ʒu
	D3DXCOLOR col;			// �F
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
}Sph;

/*/ �v���g�^�C�v�錾 /*/
void InitVisibleSph(void);					// ����
int CreateVisibleSph(const float rad,
	D3DXCOLOR col, D3DXVECTOR3* pPos);		// ����
void UninitVisibleSph(void);				// �j��
void UpdateVisibleSph(void);				// �X�V
void DeleteVisibleSph(int id);				// ����
void CalcMtxVisibleSph(void);				// �s��v�Z
void DrawVisibleSph(void);					// �`��

#endif