//==========================================================
//
//�Q�[����ʂ̕`�揈��[game.h]
//Author:kasai keisuke
//
//==========================================================

#ifndef _GAME_H_
#define _GAME_H_

//include
#include "main.h"

//�}�N����`
#define MAX_ENEMY	(1024)		//�G�̍ő吔
#define MAX_PATHWORD	(128)	//�ő啶����
#define MAX_SYMBOL	(4)			//�C�R�[���Ȃǂ�ǂݍ��ޗp

//�G�̃p�����[�^�[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�o���ʒu
	D3DXVECTOR3 rot;	//�o������
	int nStyle;			//�^�C�v
	int nCntAppear;		//�o������
	int nLife;			//���C�t
}EnemyInfo;

//�v���g�^�C�v�錾
void InitGame(void);		//�Q�[����ʂ̏���������
void UninitGame(void);		//�Q�[����ʂ̏I������
void UpdateGame(void);		//�Q�[����ʂ̍X�V����
void DrawGame(void);		//�Q�[����ʂ̕`�揈��
bool GetLayoutEdit(void);	// �ҏW���[�h�̃t���O�擾
bool CntDuration(int* dur);	// ��Ԍp���J�E���g�p

#endif