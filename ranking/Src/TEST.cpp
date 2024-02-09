//************************************************
//
// �e�X�g[TEST.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "TEST.h"
// ����
#include "input.h"
#include "sound.h"
// �f�o�b�O��
#ifdef _DEBUG
#include "debugproc.h"
#endif

/*/ �}�N����` /*/
#define AMOUNT_TEST 4	// �e�X�g�\���̐�
#define SIZE_VERIFY	1

// �e�X�g�p�e�N�X�`��
typedef enum
{
	Tex00 = 0,
	TexMax
}TexType;

/*/ �O���[�o���ϐ� /*/
LPDIRECT3DTEXTURE9 g_pTextureTEST[TexMax] = {};	// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTEST = NULL;	// ���_�o�b�t�@�̃|�C���^
TEST g_TEST[AMOUNT_TEST];						// �e�X�g�\����

//************************************************
// �e�X�g����
//************************************************
void InitTEST(int joined)
{
	for (int i = 0; i < AMOUNT_TEST; i++)
	{ // �\���̂̏��̏�����
		g_TEST[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_TEST[i].size = { 0.0f,0.0f };
		g_TEST[i].angle = 0.0f;
		g_TEST[i].length = 0.0f;
		g_TEST[i].F = 1.0f;	// �ėp
	}

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	// �e�N�X�`���摜�̓Ǎ��ݗp
	const char* pFileName[TexMax] =
	{
		"data\\TEXTURE\\test.png",
	};

	for (int i = 0; i < TexMax; i++)
	{ // �e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureTEST[i]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_TEST,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTEST,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffTEST->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_TEST; i++)
	{
		// ���_���W�̏����ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ������̊g�嗦(?)�̏����ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTEST->Unlock();

	// �e�X�g����t�^
	SetInfoTEST(joined);
}

//************************************************
// �\���̂̏���ݒ肷��֐�
//************************************************
void SetInfoTEST(int joined)
{
	int adjust = 0;	// �l�������p

	for (int i = 0; i < AMOUNT_TEST; i++)
	{ // �\���̂̏��̏�����
		g_TEST[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_TEST[i].size = { 0.0f,0.0f };
		g_TEST[i].angle = 0.0f;
		g_TEST[i].length = 0.0f;
		g_TEST[i].F = 1.0f;	// �ėp
	}

	if (joined >= 3)
	{
		adjust++;	//<! �Q���l����3�l�ȏ�Œ����p�ɃJ�E���g���܂��B
	}	

	for (int i = 0, j = 0; i < joined; i++)
	{ //�e�X�g�\���ɏ���t�^

		if (i == 2) j++;	//!< 2���[�v���_�ŕK��1�J�E���g���܂��B

		if (joined == 1)
		{ // �Q���l����1�l�̎��̂ݓ��ʂɈʒu�A�T�C�Y���Œ�
			g_TEST[i].pos =
			{
				SCREEN_HALFWIDTH,
				100.0f,
				0.0f,
			};

			g_TEST[i].size = { 160.0f, 100.0f };
		}
		else
		{ // �Q���l������������ꍇ�A�����I�Ɉʒu�A�T�C�Y��ݒ�
			g_TEST[i].pos =
			{
				(SCREEN_HALFWIDTH * 0.5f) + (i * SCREEN_HALFWIDTH) - (j * SCREEN_WIDTH),
				TEST_POS_Y + (j * SCREEN_HALFHEIGHT) - (adjust * 10.0f),
				0.0f,
			};

			g_TEST[i].size = { 130.0f - (adjust * 30.0f), 80.0f - (adjust * 15.0f) };
		}

		g_TEST[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

//************************************************
// �e�X�g�I�������֐�
//************************************************
void UninitTEST(void)
{
	for (int i = 0; i < TexMax; i++)
	{ // �e�N�X�`���̔j��
		if (g_pTextureTEST[i] != NULL)
		{
			g_pTextureTEST[i]->Release();
			g_pTextureTEST[i] = NULL;
		}
	}

	if (g_pVtxBuffTEST != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffTEST->Release();
		g_pVtxBuffTEST = NULL;
	}
}

//************************************************
// �e�X�g�X�V
//************************************************
void UpdateTEST(int joined)
{
	/*---�y�����ĕt�^�z---*/
	SetInfoTEST(joined);

	// �W�J
	SetSizeTEST();

	// �F�ύX
	SetColTEST();
}

//************************************************
// �e�X�g�W�J
//************************************************
void SetSizeTEST(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffTEST->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_TEST; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�
#if SIZE_VERIFY
		pVtx[0].pos =
		{
			g_TEST[i].pos.x - g_TEST[i].size.x,
			g_TEST[i].pos.y - g_TEST[i].size.y,
			0.0f
		};

		pVtx[1].pos =
		{
			g_TEST[i].pos.x + g_TEST[i].size.x,
			g_TEST[i].pos.y - g_TEST[i].size.y,
			0.0f
		};

		pVtx[2].pos =
		{
			g_TEST[i].pos.x - g_TEST[i].size.x,
			g_TEST[i].pos.y + g_TEST[i].size.y,
			0.0f
		};

		pVtx[3].pos =
		{
			g_TEST[i].pos.x + g_TEST[i].size.x,
			g_TEST[i].pos.y + g_TEST[i].size.y,
			0.0f
		};
#else
		PrintDebugProc("length x : %f\n", g_TEST[0].length);
		PrintDebugProc("length y : %f\n", g_TEST[0].length);

		pVtx[0].pos =
		{
			g_TEST[i].pos.x + sinf(g_TEST[i].rot.z - (D3DX_PI - g_TEST[i].angle)) * g_TEST[i].length,
			g_TEST[i].pos.y + cosf(g_TEST[i].rot.z - (D3DX_PI - g_TEST[i].angle)) * g_TEST[i].length,
			0.0f
		};

		PrintDebugProc("0x : %f\n", pVtx[0].pos.x);
		PrintDebugProc("0y : %f\n", pVtx[0].pos.y);

		pVtx[1].pos =
		{
			g_TEST[i].pos.x + sinf(g_TEST[i].rot.z + (D3DX_PI - g_TEST[i].angle)) * g_TEST[i].length,
			g_TEST[i].pos.y + cosf(g_TEST[i].rot.z + (D3DX_PI - g_TEST[i].angle)) * g_TEST[i].length,
			0.0f
		};

		PrintDebugProc("1x : %f\n", pVtx[1].pos.x);
		PrintDebugProc("1y : %f\n", pVtx[1].pos.y);

		pVtx[2].pos =
		{
			g_TEST[i].pos.x + sinf(g_TEST[i].rot.z - g_TEST[i].angle) * g_TEST[i].length,
			g_TEST[i].pos.y + cosf(g_TEST[i].rot.z - g_TEST[i].angle) * g_TEST[i].length,
			0.0f
		};

		PrintDebugProc("2x : %f\n", pVtx[2].pos.x);
		PrintDebugProc("2y : %f\n", pVtx[2].pos.y);

		pVtx[3].pos =
		{
			g_TEST[i].pos.x + sinf(g_TEST[i].rot.z + g_TEST[i].angle) * g_TEST[i].length,
			g_TEST[i].pos.y + cosf(g_TEST[i].rot.z + g_TEST[i].angle) * g_TEST[i].length,
			0.0f
		};

		PrintDebugProc("3x : %f\n", pVtx[3].pos.x);
		PrintDebugProc("3y : %f\n", pVtx[3].pos.y);
#endif
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTEST->Unlock();
}

//************************************************
// �e�X�g�F�ύX
//************************************************
void SetColTEST(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffTEST->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_TEST; i++, pVtx += AMOUNT_VTX)
	{
		pVtx[0].col = g_TEST[i].col;
		pVtx[1].col = g_TEST[i].col;
		pVtx[2].col = g_TEST[i].col;
		pVtx[3].col = g_TEST[i].col;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTEST->Unlock();
}

//************************************************
// �e�X�g�`��
//************************************************
void DrawTEST(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTEST, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_TEST; i++)
	{
		pDevice->SetTexture(0, g_pTextureTEST[Tex00]);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}