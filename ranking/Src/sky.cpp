//************************************************
//
// ��[sky.cpp]
// Author�F���c����
//
//**********************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "sky.h"

/*/ �}�N����` /*/
#define AMOUNT_SKY	(1)			// ��̐�
#define SPAN_SKY	(2000.0f)	// ��̍L��
#define HEIGHT_SKY	(4000.0f)	// ��̍���
#define COLUMN_SKY	(61)		// ��(���̕�)
#define LINE_SKY	(2)			// �s(��������)

// �O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSky = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSky = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSky = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Sky g_aSky[AMOUNT_SKY] = {};					// ����
static const float g_F = 1.0f;					// �萔1.0f
/* ����̌v�Z�p */
static const int g_nAmountVtx = (COLUMN_SKY * LINE_SKY);	// ���_�̐�
static const int g_nAmountPrimitive = (((COLUMN_SKY - 1) * (LINE_SKY - 1)) * 2) + ((LINE_SKY - 2) * 4);	//�ʂ̐�
static const int g_nAmountIdx = g_nAmountPrimitive + 2;		// �C���f�b�N�X�̐�
static const float g_COLUMN = g_F / (COLUMN_SKY - 1);		// ���񕪂�1
static const float g_LINE = g_F / (LINE_SKY - 1);			// ���s����1

//************************************************
// �󏉊�
//************************************************
void InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < AMOUNT_SKY; i++)
	{ // ��̏������Z�b�g
		g_aSky[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSky[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sky.jpg",
		&g_pTextureSky);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_SKY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSky,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffSky->Lock(0, 0, (void**)&pVtx, 0);

	float fP[3] = {};	/*/ [0]����A[1]���s�A[2]��texX (���W�p��tex�p���K�v�ȗ��R�v����) /*/
	for (int i = 0, j = 0; i < g_nAmountVtx; i++, j++)
	{
		// 1�񕪃��[�v���������ꍇ
		if (j >= COLUMN_SKY)
		{
			fP[1] += g_LINE;	/* ���s����1���� */
			j = 0;	/* ��J�E���g���Z�b�g */
			fP[0] = 0.0f;	/* �~���Ȃ̂ŗ�ʒu�����Z�b�g */
		}

		fP[2] = g_COLUMN * (float)j;	/* ��J�E���g���A���񕪂�1���� */

		// ���_���W�̐ݒ�
		pVtx[i].pos = D3DXVECTOR3(sinf(D3DX_PI - fP[0]) * SPAN_SKY,
			HEIGHT_SKY * (fP[1]),
			cosf(D3DX_PI - fP[0]) * SPAN_SKY);

		// ������c�H(�v����)
		fP[0] += D3DX_PI * (2.0f / (COLUMN_SKY - 1));

		// �@���x�N�g���̐ݒ�
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̏����ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

		// �e�N�X�`�����W�̏����ݒ�
		pVtx[i].tex = D3DXVECTOR2(-fP[2] * 2.0f, -fP[1]);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSky->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_SKY,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSky,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSky->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	// �s���J�E���g
	while (1)	/* ���[�v�񐔂͏k�ރ��[�v�� */
	{
		// �s�̋N�_������W�J����
		for (int X = 0; X < COLUMN_SKY; X++, pIdx += 2)	/* 2���_�Z�b�g�ŗ񂪂���Ă��� */
		{
			pIdx[0] = (WORD)(COLUMN_SKY + X + (Z * COLUMN_SKY));	/* �񐔎��̂��N�_�̃C���f�b�N�X�ɂȂ� */
			pIdx[1] = (WORD)(X + (Z * COLUMN_SKY));
		}

		// �k�ރ��[�v���o���Ȃ��Ȃ�΃��[�v�𔲂���
		if (Z >= LINE_SKY - 2) break;

		pIdx[0] = (WORD)((COLUMN_SKY * (Z + 1)) - 1);	/* (�� * (�Y���s + 1)) - 1�ł��̍s�̉E��̊p */
		pIdx[1] = (WORD)((Z + 2) * COLUMN_SKY);	/* (�Y���s + 2) * �񐔂ŋN�_�̂����1�s���� */

		pIdx += 2;
		Z++;	/* �s�̋N�_��1�i������ */
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffSky->Unlock();
}

//************************************************
// ��j��
//************************************************
void UninitSky(void)
{
	if (g_pTextureSky != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}

	if (g_pVtxBuffSky != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffSky->Release();
		g_pVtxBuffSky = NULL;
	}

	if (g_pIdxBuffSky != NULL)
	{ // �C���f�b�N�X�o�b�t�@�̔j��
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}
}

//************************************************
// ��X�V
//************************************************
void UpdateSky(void)
{
	// �s��v�Z
	CalcMtxSky();
}

//************************************************
// ��̍s��v�Z
//************************************************
void CalcMtxSky(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_SKY; i++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aSky[i].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aSky[i].rot.y,
			g_aSky[i].rot.x,
			g_aSky[i].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_aSky[i].mtxWorld,
			&g_aSky[i].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aSky[i].pos.x,
			g_aSky[i].pos.y,
			g_aSky[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aSky[i].mtxWorld,
			&g_aSky[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// ��`��
//************************************************
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < AMOUNT_SKY; i++)
	{
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aSky[i].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffSky, 0, sizeof(VERTEX_3D));

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffSky);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSky);

		// ��̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nAmountVtx,
			0, g_nAmountPrimitive);
	}
}