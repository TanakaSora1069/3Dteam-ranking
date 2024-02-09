//************************************************
//
// �I���W�i���G�t�F�N�g�A�w�b�_�t�@�C��[effect_hayu.h]
// Author�F���c����
//
//************************************************
#ifndef _EFFECT_HAYU_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EFFECT_HAYU_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

// �G�t�F�N�g�̎�ޕ���
typedef enum
{
	styleHeart = 0,		// �n�[�g�F�_���[�W�I��
	styleDeath,			// ���F���V����
	styleRing,			// �����O�F����
	Max_effectstyle
}EffectStyle;

// �e�N�X�`���T�C�Y�Ǘ��p
typedef struct
{
	D3DXVECTOR2 size[4];	// �T�C�Y���i�[�p
}TextureSize;

// �e�N�X�`���A�j���[�V�����p
typedef struct
{
	int row;		// �s����
	int column;		// �񑍐�
	int id_pattern;	// ���݂̃p�^�[��
	int dur_cnt;	// �p�^�[���J�ڊԊu
	int id_cnt;		// �J�ڃJ�E���^�[
}TextureAnimation;

// �G�t�F�N�g�p���
typedef struct
{
	bool use;				// �g�p�t���O
	int style;				// �X�^�C��
	int type;				// �^�C�v
	D3DXVECTOR3* pPos;		// �Ώۈʒu
	D3DXVECTOR3 pos_moved;	// �ϓ��ʒu
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR2 span;		// �傫���p
	float angle;			// �p�x
	float length;			// �Ίp���p
	D3DXCOLOR col;			// �F
	int remain;				// ����
	TextureAnimation anima;	// �A�j���[�V�����p
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
}Effect_Hayu;

//�v���g�^�C�v�錾
void InitEffect_Hayu(void);					// ����
void ImportTexEffect_Hayu(void);			// �e�N�X�`���擾
void CreateVtxBufferEffect_Hayu(void);		// ���_���𐶐�
void UninitEffect_Hayu(void);				// �j��
int CreateEffect_Hayu(int type,
	D3DXVECTOR3* pPos);						// ����
void UpdateEffect_Hayu(void);				// �X�V
void SetVtxEffect_Hayu(void);				// �W�J
TextureSize SetTexEffect_Hayu(int id);		// �e�N�X�`���Ǘ��p
void AnimationTex_Effect_Hayu(int id);		// �A�j���[�V�����p
void DeleteEffect_Hayu(int id);				// ����
void DrawEffect_Hayu(void);					// �`��

#endif