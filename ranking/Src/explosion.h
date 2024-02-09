//************************************************
//
// ���������A�w�b�_�t�@�C��[explosion.h]
// Author�F�����h��
//
//************************************************

#ifndef _EXPLOSION_H_     //���̃}�N����`������Ă��Ȃ�������
#define _EXPLOSION_H_    //2�d�C���N���[�h�h�~�̃}�N����`

//include
#include "main.h"

//�}�N����`
#define MAX_EXPLOSION	(1024)	//�����G�t�F�N�g�̍ő吔

//�����G�t�F�N�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��No.
	float fWidth;			//��
	float fHeight;			//����
	float fLength;			//�Ίp���̒���
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Explosion;

//�v���g�^�C�v�錾
void InitExplosion(void);														//�����̏���������
void UninitExplosion(void);														//�����̏I������
void UpdateExplosion(void);														//�����̍X�V����
void DrawExplosion(void);														//�����̕`�揈��
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);	//�����̐ݒ菈��
Explosion* GetExplosion(void);													//�����̏����擾
#endif