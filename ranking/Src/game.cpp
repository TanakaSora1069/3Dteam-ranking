//==========================================================
//
//�Q�[����ʂ̕`�揈��[game.cpp]
//Author:kasai keisuke, ���c����
//
//==========================================================

/* �C���N���[�h�t�@�C�� */
#include "game.h"
// ����
#include "input.h"
#include "main.h"
#include "sound.h"
// ������
#include "boss.h"
#include "bullet.h"
#include "camera.h"
#include "effect.h"
#include "effect_hayu.h"
#include "effect_sand.h"
#include "enemy.h"
#include "explosion.h"
#include "item.h"
#include "light.h"
#include "object.h"
#include "player.h"
#include "reticle.h"
#include "sea.h"
#include "shadow.h"
#include "sky.h"
// �f�o�b�O��
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"
#include "TEST.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*/ �}�N����` /*/
#define JOIN_VERIFY 1	// �l���w��

/*/ �O���[�o���ϐ� /*/
int g_AmountPlayer = JOIN_VERIFY;	// �v���C�l���i�[
bool g_LayoutEdit = false;			// �z�u�ҏW���[�h�p�t���O
int g_nCnt = 0;						//�f�o�b�N�p�ϐ�(�R���g���[�������m�F�p)
bool g_Pause = false;				// �|�[�Y����p�t���O

//=======================================================================
//�Q�[����ʂ̏���������
//=======================================================================
void InitGame(void)
{
#ifndef JOIN_VERIFY

	// �l���w�肪������ΌŒ�
	g_AmountPlayer = 1;

#endif	// JOIN_VERIFY

	//�e��ϐ��̏�����
	g_LayoutEdit = false;	// �z�u�ҏW���[�h���I�t
	g_nCnt = 0;				//�f�o�b�N�p�ϐ�(�R���g���[�������m�F�p)�̏�����
	g_Pause = false;		// �|�[�Y�t���O�𖳂���

#ifdef _DEBUG

	// �l�������������ƏI��
	assert(g_AmountPlayer > 0 && g_AmountPlayer <= 4);

	// �ҏW�J�����̏���
	InitEditCamera();

	// �e�X�g�p�̏���
	InitTEST(g_AmountPlayer);

	// ���̔����������
	InitVisibleSph();

#endif	// _DEBUG

	// ���e�B�N���̏����F��s
	InitReticle();
	
	// �e�̏����F��s
	InitShadow();

	//�{�X�̏���������
	InitBoss();

	// �e�̏���
	InitBullet();

	// �J�����̏���
	InitCamera(g_AmountPlayer);

	//�G�t�F�N�g�̏���������
	InitEffect();

	// Hayu�G�t�F�N�g�̏���
	InitEffect_Hayu();

	// ���̃G�t�F�N�g�̏���
	InitEffectSand();

	// �G�̏���
	InitEnemy();

	// �����̏���
	InitExplosion();
	
	// �A�C�e���̏���
	InitItem();

	// ���C�g�̏���
	InitLight();

	// ���̏���
	InitObject();

	// �v���C���[�̏���
	InitPlayer();

	// �C�̏���
	InitSea();

	// ��̏���
	InitSky();
}

//=======================================================================
//�Q�[����ʂ̏I������
//=======================================================================
void UninitGame(void)
{
#ifdef _DEBUG

	// �e�X�g�p�̏I��
	UninitTEST();

	// ���̔�������I��
	UninitVisibleSph();

#endif	// _DEBUG

	//�{�X�̏I������
	UninitBoss();

	// �e�̏I��
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	// Hayu�G�t�F�N�g�̏I��
	UninitEffect_Hayu();

	// ���̃G�t�F�N�g�̏I��
	UninitEffectSand();

	// �G�̏I��
	UninitEnemy();

	// �����̏I��
	UninitExplosion();

	// �A�C�e���̏I��
	UninitItem();

	// ���̏I��
	UninitObject();

	// �v���C���[�̏I��
	UninitPlayer();

	// ���e�B�N���̏I��
	UninitReticle();

	// �C�̏I��
	UninitSea();

	// �e�̏I��
	UninitShadow();

	// ��̏I��
	UninitSky();
}

//=======================================================================
//�Q�[����ʂ̍X�V����
//=======================================================================
void UpdateGame(void)
{
	if (GetJoypadTrigger(JOYKEY_START, 0) || GetKeyboardTrigger(DIK_P))
	{
		g_Pause = !g_Pause;
	}

	if (g_Pause)
	{ // �|�[�Y���̂�

		/*---�y������UI�̏����z---*/

		return;	// �ȉ��̏����͍s��Ȃ�
	}

#if defined (_DEBUG)

	// �z�u�ҏW���[�h�؂�ւ�
	if (GetKeyboardTrigger(DIK_F2))
	{
		g_LayoutEdit = !g_LayoutEdit;
	}

	if (!g_LayoutEdit)
	{ // �z�u�ҏW���[�h�łȂ��Ƃ��̂�
		// �Q���l���𒼐ڕύX
		if (GetKeyboardTrigger(DIK_LBRACKET))
		{
			g_AmountPlayer < 4 ? g_AmountPlayer++ : g_AmountPlayer = 1;
		}
		else if (GetKeyboardTrigger(DIK_RBRACKET))
		{
			g_AmountPlayer > 1 ? g_AmountPlayer-- : g_AmountPlayer = 4;
		}
	}

	// �f�o�b�O�\���̍X�V(�z�z)
	UpdateDebugProc();

	// �J���� or �ҏW�J�����̍X�V
	g_LayoutEdit ? UpdateEditCamera() : UpdateCamera(g_AmountPlayer);

	// �e�X�g�p�̍X�V
	UpdateTEST(g_AmountPlayer);

#endif	// _DEBUG

#ifndef _DEBUG

	// �J�����̍X�V
	UpdateCamera(g_AmountPlayer);

#endif // _DEBUG �����[�X

	// �󋵂ɉ����ĕ��̍X�V
	UpdateObject(g_LayoutEdit);

	if (!g_LayoutEdit)
	{
		// �G�̍X�V
		UpdateEnemy();

		//�{�X�̍X�V����
		UpdateBoss();

		//�A�C�e���̍X�V
		UpdateItem();

		// ���C�g�̍X�V
		UpdateLight();

		// �v���C���[�̍X�V
		UpdatePlayer(g_AmountPlayer);

		// ���e�B�N���̍X�V
		UpdateReticle(g_AmountPlayer);

		// �e�̍X�V
		UpdateBullet();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		// Hayu�G�t�F�N�g�̍X�V
		UpdateEffect_Hayu();

		// �����̍X�V
		UpdateExplosion();

		// ���̃G�t�F�N�g�̍X�V
		UpdateEffectSand();

		// �C�̍X�V
		UpdateSea();

		// �e�̍X�V
		UpdateShadow();

		// ��̍X�V
		UpdateSky();

#ifdef _DEBUG	

		// ���̔�������X�V
		UpdateVisibleSph();

#endif // _DEBUG �����ꂱ���ɒu������
	}
}

//=======================================================================
//�Q�[����ʂ̕`�揈��
//=======================================================================
void DrawGame(void)
{
	// ���[�v��
	int Loop = 0;

	// �z�u�ҏW���[�h�ł���Η]���ȕ`���}��
	g_LayoutEdit ? Loop = 1 : Loop = g_AmountPlayer;

	for (int i = 0; i < Loop; i++)
	{
#ifdef _DEBUG

		// �J���� or �ҏW�J�����̐ݒ�
		g_LayoutEdit ? SetInfoEditCamera() : SetInfoCamera(i, g_AmountPlayer);

#else

		// �J�����̐ݒ�
		SetInfoCamera(i, g_AmountPlayer);

#endif	// _DEBUG �����[�X

		// ��̕`��
		DrawSky();

		// �C�̕`��
		DrawSea();

		// �󋵂ɉ����ĕ��̕`��
		DrawObject(g_LayoutEdit);

		// �G�̕`��
		DrawEnemy();

		// �{�X�̕`�揈��
		DrawBoss();

		// �A�C�e���̕`��
		DrawItem();

		// ���̃G�t�F�N�g�̕`��
		DrawEffectSand();

		// Hayu�G�t�F�N�g�̕`��
		DrawEffect_Hayu();

		// �����̕`��
		DrawExplosion();

		// �e�̕`��
		DrawShadow();

		//�G�t�F�N�g�̕`��
		DrawEffect();

		// ���e�B�N���̕`��
		DrawReticle(i);

		// �e�̕`��
		DrawBullet();

		// �v���C���[�̕`��
		DrawPlayer();

#ifdef _DEBUG

		// ���̔�������`��
		DrawVisibleSph();

#endif	// _DEBUG
	}

	// UI�p�|�[�g�̐ݒ�
	SetInfoUIport();

	/*---�y�Q�[����UI�̕\���͂������牺�ōs���܂��z---*/

#ifdef _DEBUG

	// �e�X�g�p�̕`��
	if (!g_LayoutEdit)
	{
		//DrawTEST();	//!< UI�n�̓|�[�g�ݒ肳��Ă��Ȃ��͈͂̕`��͍s���܂���B�͂ݏo��悤�Ȃ�V���Ƀ|�[�g�ݒ��ǉ����Ă��������B
	}

	// �f�o�b�O�p�\���̕`��(�z�z)
	DrawDebugProc();

#endif	// _DEBUG
}

/*---�y�ȉ��Q�[�����[�v�O�z---*/

//************************************************
// �ҏW���[�h�̃t���O�擾
//************************************************
bool GetLayoutEdit()
{
	return g_LayoutEdit;
}

//************************************************
// ��Ԍp���J�E���g�p
//************************************************
bool CntDuration(int* dur)
{
	bool finish = false;

	if (*dur > 0)
	{ // �p�����Ԍ���
		*dur -= 1;	// �Ȃ��f�N�������g��Ή��H
	}
	else
	{ // �p�����Ԃ������Ȃ��

		// ������Ԃ�
		finish = true;
	}

	return finish;
}