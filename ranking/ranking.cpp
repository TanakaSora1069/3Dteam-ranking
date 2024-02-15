//************************************************
// 
// �����L���O[ranking.cpp]
// Auther:SORA TANAKA
// 
//************************************************

/* �C���N���[�h�t�@�C�� */
#include "ranking.h"

// �g�p����t�@�C��
#include "input.h"
#include "main.h"
#include "sound.h"
//#include "title.h"

int g_aHighScore[MAX_RANK * MAX_PLAYER];	// �n�C�X�R�A�i�[
int g_PlayerNum;							// �v���C�l��
int g_Score;								// �v���C�X�R�A
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRanking[4] = {};	// �e�N�X�`���ւ̃|�C���^
TEXT_RANKING g_aTextRanking[MAX_TEXT];

//========================================
// �����L���O��ʂ̏���������
//========================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\title\\score_title_demo.png", &g_pTextureRanking[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\title\\score_player_demo.png", &g_pTextureRanking[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\title\\score_end_demo.png", &g_pTextureRanking[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\title\\score_number_demo.png", &g_pTextureRanking[3]);

	for (int nCnt = 0; nCnt < MAX_RANK * MAX_PLAYER; nCnt++)
	{
		g_aHighScore[nCnt] = 0;
	}
	g_PlayerNum = 0;
	g_Score = 0;



	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D* pVtx;

	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TEXT; nCnt++)
	{
		g_aTextRanking[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTextRanking[nCnt].type = 0;
		g_aTextRanking[nCnt].bUse = false;

		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;	// ���_�f�[�^�̃|�C���^��4���i�߂�
	}

	g_pVtxBuffRanking->Unlock();
}

//========================================
// �����L���O��ʂ̏I������
//========================================
void UninitRanking(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (g_pTextureRanking[nCnt] != NULL)
		{
			g_pTextureRanking[nCnt]->Release();
			g_pTextureRanking[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//========================================
// �����L���O��ʂ̍X�V����
//========================================
void UpdateRanking(void)
{
	// START�{�^���������ꂽ��^�C�g����
	if (GetJoypadPress(JOYKEY_START, 0))
	{
		//SetMode(MODE_RANKING);
	}

	// �����̓_��
}

//========================================
// �����L���O��ʂ̕`�揈��
//========================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEXT; nCnt++)
	{
		// �g�p����Ă���
		if (g_aTextRanking[nCnt].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRanking[g_aTextRanking[nCnt].type]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, 2);
		}
	}

}

//========================================
// �X�R�A�̎擾
//========================================
void GetScore(void)
{
	FILE* pFile;	// �t�@�C���|�C���^

	// �t�@�C�����J��
	//pFile = fopen("", "r");

	//if (pFile != NULL)
	//{
		for (int nCnt = 0; nCnt < MAX_RANK * MAX_PLAYER; nCnt++)
		{
			// �t�@�C������X�R�A��ǂݍ���
			g_aHighScore[nCnt] = int(123400); // �X�R�A�i���j
		}

		// �t�@�C�������
		//fclose(pFile);
	//}
}

//========================================
// �e�L�X�g�̐ݒ�
//========================================
void SetRankingText(void)
{
	int nCnt = 0;
	VERTEX_2D* pVtx;

	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	// �^�C�g��
	g_aTextRanking[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 100, 0);
	g_aTextRanking[nCnt].type = 0;
	g_aTextRanking[nCnt].whith = 800.0f;
	g_aTextRanking[nCnt].height = 150.0f;
	g_aTextRanking[nCnt].bUse = true;

	pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / 2, 0);
	pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / 2, 0);

	nCnt++;
	pVtx += AMOUNT_VTX;

	// �v���C�l��
	for (int nPlayerCnt = 0; nPlayerCnt < MAX_PLAYER; nPlayerCnt++)
	{
		g_aTextRanking[nCnt].pos = D3DXVECTOR3(float(SCREEN_WIDTH / 4 * nPlayerCnt), 300, 0);
		g_aTextRanking[nCnt].type = 1;
		g_aTextRanking[nCnt].whith = 300.0f;
		g_aTextRanking[nCnt].height = 100.0f;
		g_aTextRanking[nCnt].bUse = true;

		pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / -2, 0);
		pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / -2, 0);
		pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / 2, 0);
		pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / 2, 0);

		nCnt++;
		pVtx += AMOUNT_VTX;
	}

	// �{�^���Ń^�C�g���֖߂�
	g_aTextRanking[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 0);
	g_aTextRanking[nCnt].type = 2;
	g_aTextRanking[nCnt].whith = 400.0f;
	g_aTextRanking[nCnt].height = 80.0f;
	g_aTextRanking[nCnt].bUse = true;

	pVtx[0].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[1].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / -2, 0);
	pVtx[2].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / -2, g_aTextRanking[nCnt].height / 2, 0);
	pVtx[3].pos = g_aTextRanking[nCnt].pos + D3DXVECTOR3(g_aTextRanking[nCnt].whith / 2, g_aTextRanking[nCnt].height / 2, 0);

	nCnt++;
	pVtx += AMOUNT_VTX;

	// ����	
	/// �v���C�l��
	for (int nPlayerCnt = 0; nPlayerCnt < MAX_PLAYER; nPlayerCnt++)
	{
		g_aTextRanking[nCnt].pos = D3DXVECTOR3(float(SCREEN_WIDTH / 4 * nPlayerCnt)-175.0f, 300, 0);
		g_aTextRanking[nCnt].type = 3;
		g_aTextRanking[nCnt].whith = 50.0f;
		g_aTextRanking[nCnt].height = 100.0f;
		g_aTextRanking[nCnt].bUse = true;

		nCnt++;
		pVtx += AMOUNT_VTX;
	}

	/// �X�R�A
	for (int nScoreCnt = 0; nScoreCnt < MAX_SCORE * MAX_RANK * MAX_PLAYER; nScoreCnt++)
	{
		//g_aTextRanking[nCnt].pos = D3DXVECTOR3(0, 0, 0);
		g_aTextRanking[nCnt].type = 3;
		g_aTextRanking[nCnt].whith = 40.0f;
		g_aTextRanking[nCnt].height = 80.0f;
		g_aTextRanking[nCnt].bUse = true;

		nCnt++;
		pVtx += AMOUNT_VTX;
	}
}