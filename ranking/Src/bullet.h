//************************************************
//
// �e�A�w�b�_�t�@�C��[bullet.h]
// Author�F���c����
//
//************************************************
#ifndef _BULLET_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BULLET_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

/*/ �}�N����` /*/
#define AMOUNT_BULLET 256	// �e��
#define SPAN_BULLET 10.0f	// �e�̑傫��
#define SPD_BULLET 7.5f	// �e�̑���

// �e�̎�ޕ���
typedef enum
{
	bulletPlayer = 0,	// �v���C���[
	bulletEnemy = 0,	// �G�l�~�[
	Max_bullettype
}BulletType;

// �e�p���
struct Bullet
{
	bool use;				// �g�p�t���O
	int type;				// �^�C�v����
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	float rad;				// ������T�C�Y
	int remain;				// ����
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	int id_shadow;			// �e���ʔԍ��i�[
	int id_sph;				// ���莯�ʔԍ��i�[
};

//�v���g�^�C�v�錾
void InitBullet(void);			// ����
void UninitBullet(void);		// �j��
void CreateBullet(int type,
	int id);					// ����
//void AdjustBullet(void);		// �e������
void UpdateBullet(void);		// �X�V
void DeleteBullet(int id);		// ����
void DrawBullet(void);			// �`��
void CollisionBullet(int id);	// �����蔻��
Bullet* GetInfoBullet(void);	// �e�����擾

#endif