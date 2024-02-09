//************************************************
//
// �J�����A�w�b�_�t�@�C��[camera.h]
// Author�F���c����
//
//************************************************
#ifndef _CAMERA_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _CAMERA_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

/*/ �}�N����` /*/
#define AMOUNT_CAMERA 4			// �J�����̐�
#define UP_ADJUST_POSR 0.35f	// ������t�@�����X�W��
#define MIN_POSR 0.3927f		// �������t�@�����X�Œ�l

// �J�������p
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
}Camera;

// �r���[�|�[�g�T�C�Y�p
typedef struct
{
	DWORD Width;	// ����
	DWORD Height;	// �c��
}viewportSize;

// UI�|�[�g
typedef struct
{
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DVIEWPORT9 viewport;		// �r���[�|�[�g
}UIport;
/*/ �v���g�^�C�v�錾 /*/
void InitCamera(int joined);							// ����
viewportSize SetSizeViewport(int joined);				// �r���[�|�[�g�T�C�Y��ݒ�
void InitUIport(void);									// UI�|�[�g����
void UpdateCamera(int joined);							// �X�V
void CalcPosV(int id, const D3DXVECTOR3 target);		// ���_���Z�o
void CalcPosR(int id, const D3DXVECTOR3 target);		// �����_���Z�o
void SetInfoCamera(int id, int joined);					// �J�����Z�b�g
void CalcMatrixProjectionCamera(int id, int joined);	// �v���W�F�N�V�����}�g���b�N�X�v�Z
void CalcMatrixViewCamera(int id);						// �r���[�}�g���b�N�X�v�Z
void SetInfoUIport(void);								// UI�|�[�g�̐ݒ�
Camera* GetInfoCamera(void);							// �J�������擾

#endif