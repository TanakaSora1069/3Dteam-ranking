//************************************************
//
// �e�A�w�b�_�t�@�C��[shadow.h]
// Author�F���c����
//
//************************************************
#ifndef _SHADOW_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SHADOW_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

// �e�p���
typedef struct
{
	bool use;				// �g�p�t���O
	D3DXVECTOR3* pPos;		// �Ώۈʒu
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR2 span;		// �傫���p
	float angle;			// �p�x
	float length;			// �Ίp���p
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
}Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);					// ����
void ImportTexShadow(void);				// �e�N�X�`���擾
void CreateVtxBufferShadow(void);		// ���_���𐶐�
void UninitShadow(void);				// �j��
int CreateShadow(D3DXVECTOR3* pPos,
	float rad);							// ����
void UpdateShadow(void);				// �X�V
void SetVtxShadow(void);				// �W�J
void DeleteShadow(int id);				// ����
void CalcMatrixShadow(void);			// �s��v�Z
void DrawShadow(void);					// �`��

#endif