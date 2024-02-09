//************************************************
//
// �e�X�g�A�w�b�_�t�@�C��[test.h]
// Author�F���c����
//
//************************************************
#ifndef _TEST_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TEST_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

/*/ �}�N����` /*/
#define TEST_POS_Y 90.0f	// �e�X�g�\����Y���W���w��

// �e�X�g�\���p�\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���S���W
	D3DXVECTOR3 move;	// �ړ���
	D3DXVECTOR3 rot;	// ��]��
	D3DXVECTOR2 size;	// ���c��
	float angle;		// �p�x
	float length;		// �Ίp��
	D3DXCOLOR col;		// �F���
	float F;			// �ėp
}TEST;

/*/ �v���g�^�C�v�錾 /*/
void InitTEST(int joined);				// ����
void SetInfoTEST(int joined);			// �ݒ�
void UninitTEST(void);					// �I��
void UpdateTEST(int joined);			// �X�V
void SetSizeTEST(void);					// �W�J
void SetColTEST(void);					// �F�ύX
void DrawTEST(void);					// �`��

#endif