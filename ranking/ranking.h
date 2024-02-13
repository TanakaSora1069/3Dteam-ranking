//************************************************
// 
// �����L���O[ranking.h]
// Auther:SORA TANAKA
// 
//************************************************

#ifndef _RANKING_H_
#define _RANKING_H_

// �C���N���[�h�t�@�C��
#include "main.h"

// �}�N����`
#define MAX_RANK	(5) // �\������X�R�A�̏��ʂ̐�
#define MAX_SCORE	(8)	// �\������X�R�A�̌���
#define MAX_TEXT	(256)	// �`�悷��e�L�X�g�̍ő吔

typedef struct
{
	D3DXVECTOR3 pos;	// ���W
	int type;			// �e�N�X�`���̎��
	float whith;		// ����
	float height;		// �c��
	bool bUse;			// �g�p����Ă��邩
}TEXT_RANKING;	// �����L���O��ʂ̃e�L�X�g

// �v���g�^�C�v�錾
void InitRanking(void);		// �����L���O��ʂ̏���������
void UninitRanking(void);	// �����L���O��ʂ̏I������
void UpdateRanking(void);	// �����L���O��ʂ̍X�V����
void DrawRanking(void);		// �����L���O��ʂ̕`�揈��
void GetScore(void);		// �X�R�A�擾
void SetRankingText(void);	// �e�L�X�g�̐ݒ�


#endif // !_RANKING_H_
