//************************************************
//
// �ҏW�J�����A�w�b�_�t�@�C��[editcamera.h]
// Author�F���c����
//
//************************************************
#ifndef _EDITCAMERA_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EDITCAMERA_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

// �ҏW�J�������p
typedef struct
{
	D3DXVECTOR3 posV;			// �J�����̍��W
	D3DXVECTOR3 posR;			// �����_�̍��W
	D3DXVECTOR3 rot;			// ���݂̌���
	D3DXVECTOR3 rot_goal;		// �ڕW�̌���
	float distance;				// ���_�ƒ����_�̋���
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DVIEWPORT9 viewport;		// �r���[�|�[�g
}EditCamera;

/*/ �v���g�^�C�v�錾 /*/
void InitEditCamera(void);						// ����
void UpdateEditCamera(void);					// �X�V
void CalcEditPosV(const D3DXVECTOR3 target);	// ���_���Z�o
void CalcEditPosR(const D3DXVECTOR3 target);	// �����_���Z�o
void SetInfoEditCamera(void);					// �J�����Z�b�g
EditCamera* GetInfoEditCamera(void);			// �J�������擾

#endif