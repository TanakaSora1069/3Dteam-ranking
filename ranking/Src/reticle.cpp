//************************************************
//
// ���e�B�N��[reticle.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "reticle.h"
// ������
#include "camera.h"
 
/*/ �}�N����` /*/
#define AMOUNT_RETICLE 4	// ���e�B�N���ő吔

// �O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReticle = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureReticle = NULL;		// �e�N�X�`���ւ̃|�C���^
Reticle g_Reticle[MAX_PLAYER];						// ���e�B�N�����

//************************************************
// ���e�B�N������
//************************************************
void InitReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_RETICLE; i++)
	{ // ���e�B�N����񃊃Z�b�g
		g_Reticle[i].use = false;								// �g�p�t���O
		g_Reticle[i].pos_moved = { 0.0f, 0.0f, 0.0f };			// �ϓ��ʒu
		g_Reticle[i].pos = { 0.0f, 0.0f, 0.0f };				// �ʒu
		g_Reticle[i].rot = { 0.0f, 0.0f, 0.0f };				// ����
		g_Reticle[i].span = { 0.0f, 0.0f };						// �傫���p
		g_Reticle[i].angle = 0.0f;								// �p�x
		g_Reticle[i].length = 0.0f;								// �Ίp���p
		g_Reticle[i].remain = 0;								// ����
		g_Reticle[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
	}

	/*--------------------------------------------*/

	// �e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\reticle.png",
		&g_pTextureReticle);

	/*--------------------------------------------*/

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_RETICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReticle,
		NULL);

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_RETICLE; i++, pVtx += AMOUNT_VTX)
	{ // ���_���̃��Z�b�g

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
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffReticle->Unlock();
}

//************************************************
// ���e�B�N������
//************************************************
void CreateReticle(int joined)
{
	for (int i = 0, j = 0; i < joined; i++)
	{
		if (i == 2)
		{
			j++;
		}

		// �K���Ƀp�����[�^�ݒ�
		g_Reticle[i].use = true;

		if (joined == 1)
		{
			g_Reticle[i].pos =
			{
				SCREEN_HALFWIDTH, SCREEN_HALFHEIGHT, 0.0f
			};

			g_Reticle[i].span = { 30.0f, 30.0f };	// �傫���F�K��
		}
		else if (joined == 2)
		{
			g_Reticle[i].pos =
			{
				SCREEN_HALFWIDTH * 0.5f + i * (SCREEN_HALFWIDTH), SCREEN_HALFHEIGHT, 0.0f
			};

			g_Reticle[i].span = { 20.0f, 20.0f };	// �傫���F�K��
		}
		else
		{
			g_Reticle[i].pos =
			{
				SCREEN_HALFWIDTH * 0.5f + i * (SCREEN_HALFWIDTH)-j * SCREEN_WIDTH, (SCREEN_HALFHEIGHT * 0.5f) + j * SCREEN_HALFHEIGHT, 0.0f
			};

			g_Reticle[i].span = { 15.0f, 15.0f };	// �傫���F�K��
		}

		// �p�x���Z�o
		g_Reticle[i].angle = atan2f(g_Reticle[i].span.x, g_Reticle[i].span.y);

		// �Ίp�����Z�o
		g_Reticle[i].length = sqrtf(g_Reticle[i].span.x * g_Reticle[i].span.x +
			g_Reticle[i].span.y * g_Reticle[i].span.y);
	}
}

//************************************************
// ���e�B�N���j��
//************************************************
void UninitReticle(void)
{
	if (g_pTextureReticle != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureReticle->Release();
		g_pTextureReticle = NULL;
	}

	if (g_pVtxBuffReticle != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffReticle->Release();
		g_pVtxBuffReticle = NULL;
	}
}

//************************************************
// ���e�B�N���X�V
//************************************************
void UpdateReticle(int joined)
{
	// ����
	CreateReticle(joined);

	// �W�J
	SetVtxReticle(joined);
}

//************************************************
// ���e�B�N���W�J
//************************************************
void SetVtxReticle(int joined)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < joined; i++, pVtx += AMOUNT_VTX)
	{
		// �ό`�Ȃǂ���Δ��f
		pVtx[0].pos =
		{
			g_Reticle[i].pos.x + sinf(g_Reticle[i].rot.z - (D3DX_PI - g_Reticle[i].angle)) * g_Reticle[i].length,
			g_Reticle[i].pos.y + cosf(g_Reticle[i].rot.z - (D3DX_PI - g_Reticle[i].angle)) * g_Reticle[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Reticle[i].pos.x + sinf(g_Reticle[i].rot.z + (D3DX_PI - g_Reticle[i].angle)) * g_Reticle[i].length,
			g_Reticle[i].pos.y + cosf(g_Reticle[i].rot.z + (D3DX_PI - g_Reticle[i].angle)) * g_Reticle[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Reticle[i].pos.x + sinf(g_Reticle[i].rot.z - g_Reticle[i].angle) * g_Reticle[i].length,
			g_Reticle[i].pos.y + cosf(g_Reticle[i].rot.z - g_Reticle[i].angle) * g_Reticle[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Reticle[i].pos.x + sinf(g_Reticle[i].rot.z + g_Reticle[i].angle) * g_Reticle[i].length,
			g_Reticle[i].pos.y + cosf(g_Reticle[i].rot.z + g_Reticle[i].angle) * g_Reticle[i].length,
			0.0f
		};
	}

	g_pVtxBuffReticle->Unlock();
}

//************************************************
// ���e�B�N���`��
//************************************************
void DrawReticle(int id)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffReticle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureReticle);

	// ���e�B�N���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, id * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//************************************************
// ���e�B�N�������擾
//************************************************
Reticle* GetInfoReticle(void)
{
	return &g_Reticle[0];
}