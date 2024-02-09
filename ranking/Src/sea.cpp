//************************************************
//
// �C����[sea.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "sea.h"

/*/ �}�N����` /*/
#define AMOUNT_MESHFIELD 1		// �C�̐�
#define SPAN_MESHFIELD 5000.0f	// �C�̑傫��

#define COLUMN_MESHFIELD 50	// ��(���̕�)
#define LINE_MESHFIELD 50	// �s(��������)

#define NOR_VERIFY 0
#define WAVE_VERIFY	0		// ���˂��ˌ^�ɂ�����
#define POINT_VERIFY	0	// 2�~2�̐^�񒆂̒��_���グ����

/*/ �O���[�o���ϐ� /*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSea = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSea = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSea = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Sea g_Sea[AMOUNT_MESHFIELD] = {};				// �C�p�\����
static const float g_F = 1.0f;					// �ėp�萔1.0f
// ����̌v�Z�p
static const int g_AmountVtx = (COLUMN_MESHFIELD * LINE_MESHFIELD);						// ���_�̐�
static const int g_AmountPrimitive = (((COLUMN_MESHFIELD - 1) * (LINE_MESHFIELD - 1)) * 2) + ((LINE_MESHFIELD - 2) * 4);	// �ʂ̐�
static const int g_AmountIdx = g_AmountPrimitive + 2;									// �C���f�b�N�X�̐�
static const float g_Column = g_F / (COLUMN_MESHFIELD - 1);								// ���񕪂�1
static const float g_Line = g_F / (LINE_MESHFIELD - 1);									// ���s����1
static const int g_VisiblePrimitive = g_AmountPrimitive - ((LINE_MESHFIELD - 2) * 4);	// ���ʂ̐�

//************************************************
// �C����
//************************************************
void InitSea(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{ // �C�p�\���̂̏����N���A
		g_Sea[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Sea[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/*--------------------------------------------*/

	// �e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\UV.jpg",
		&g_pTextureSea);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_AmountVtx * AMOUNT_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSea,
		NULL);

	VERTEX_3D* pVtx;	// ���_���̃|�C���^

	/*--------------------------------------------*/

#if 0

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffSea->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S�����Ƃ̊O�ς��擾���Ă���(�e�X�g)
	D3DXVECTOR3 N[g_VisiblePrimitive] = {};		// �ʖ@���x�N�g��
	D3DXVECTOR3 V1[g_VisiblePrimitive] = {};	// �x�N�g��1
	D3DXVECTOR3 V2[g_VisiblePrimitive] = {};	// �x�N�g��2

	for (int i = 0, vtx = 0; i < g_VisiblePrimitive; i++)
	{ // ���ʂ̖ʖ@���x�N�g���𐶐�
		switch (i % 2)
		{
		case 0:
			// ���v���̃|���S��
			V1[i] = pVtx[0 + vtx].pos - pVtx[3 + vtx].pos;
			V2[i] = pVtx[4 + vtx].pos - pVtx[3 + vtx].pos;
			D3DXVec3Cross(&N[i], &V1[i], &V2[i]);
			D3DXVec3Normalize(&N[i], &N[i]);
			break;

		case 1:
			// �����v���̃|���S��
			V1[i] = pVtx[4 + vtx].pos - pVtx[0 + vtx].pos;
			V2[i] = pVtx[1 + vtx].pos - pVtx[0 + vtx].pos;
			D3DXVec3Cross(&N[i], &V1[i], &V2[i]);
			D3DXVec3Normalize(&N[i], &N[i]);

			// �����Œ��_�ԍ������炷
			vtx++;
			break;
		}

		if (i == (COLUMN_MESHFIELD - 1))
		{
			vtx;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSea->Unlock();

#endif

	/*--------------------------------------------*/

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffSea->Lock(0, 0, (void**)&pVtx, 0);

	float fP[2] = {};	/*/ [0]����A[1]���s /*/
	for (int i = 0, j = 0; i < g_AmountVtx; i++, j++)
	{
		// 1�񕪃��[�v���������ꍇ
		if (j >= COLUMN_MESHFIELD)
		{
			fP[1] += g_Line;	/*/ ���s����1���� /*/
			j = 0;	/*/ ��J�E���g���Z�b�g /*/
		}

		fP[0] = g_Column * (float)j;	/*/ ��J�E���g���A���񕪂�1���� /*/

		// ���_���W�̐ݒ�
		pVtx[i].pos = D3DXVECTOR3((fP[0] * SPAN_MESHFIELD) - (SPAN_MESHFIELD * 0.5f),
			0.0f,
			(-fP[1] * SPAN_MESHFIELD) + (SPAN_MESHFIELD * 0.5f));

#if WAVE_VERIFY

		if (i != 0 && i % 2 != 0)
		{ // ��Ԓ��_����ɂ�����
			pVtx[i].pos.y = 30.0f;
		}

#elif POINT_VERIFY

		if (i == 4)
		{ // 2�~2�u���b�N�̒��S�̒��_����ɂ�����
			pVtx[i].pos.y = 50.0f;
		}

#endif // ���_�グ��V���[�Y

#if NOR_VERIFY

		// �@���x�N�g���̐ݒ�
		if (i == 0 || i == 3 || i == 4)
		{
			pVtx[i].nor = N[0];
		}
		else
		{
			pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}

#endif

		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̏����ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̏����ݒ�
		pVtx[i].tex = D3DXVECTOR2(fP[0], fP[1]);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSea->Unlock();

	/*--------------------------------------------*/

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_AmountIdx * AMOUNT_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSea,
		NULL);

	WORD* pIdx;	// �C���f�b�N�X�o�b�t�@�̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSea->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	// �s���J�E���g�p

	while (1)	// ���[�v�񐔂͏k�̃��[�v��
	{
		// �s�̋N�_������W�J����
		for (int X = 0; X < COLUMN_MESHFIELD; X++, pIdx += 2)	// 2���_�Z�b�g�ŗ񂪂���Ă���
		{
			pIdx[0] = (WORD)(COLUMN_MESHFIELD + X + (Z * COLUMN_MESHFIELD));	// �񐔎��̂��N�_�̃C���f�b�N�X�ɂȂ�
			pIdx[1] = (WORD)(X + (Z * COLUMN_MESHFIELD));
		}

		// �k�̃��[�v���o���Ȃ��Ȃ�΃��[�v�𔲂���
		if (Z >= LINE_MESHFIELD - 2) break;

		pIdx[0] = (WORD)((COLUMN_MESHFIELD * (Z + 1)) - 1);	// (�� * (�Y���s + 1)) - 1�ł��̍s�̉E��̊p
		pIdx[1] = (WORD)((Z + 2) * COLUMN_MESHFIELD);		// (�Y���s + 2) * �񐔂ŋN�_�̂����1�s����

		pIdx += 2;
		Z++;	// �s�̋N�_��1�i������
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffSea->Unlock();
}

//************************************************
// �C�j��
//************************************************
void UninitSea(void)
{
	if (g_pTextureSea != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureSea->Release();
		g_pTextureSea = NULL;
	}

	if (g_pVtxBuffSea != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffSea->Release();
		g_pVtxBuffSea = NULL;
	}

	if (g_pIdxBuffSea != NULL)
	{ // �C���f�b�N�X�o�b�t�@�̔j��
		g_pIdxBuffSea->Release();
		g_pIdxBuffSea = NULL;
	}
}

//************************************************
// �C�X�V
//************************************************
void UpdateSea(void)
{
	// �s��v�Z
	CalcMtxSea();
}

//************************************************
// �C�p�̃��[���h�}�g���b�N�X���v�Z
//************************************************
void CalcMtxSea(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Sea[i].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Sea[i].rot.y,
			g_Sea[i].rot.x,
			g_Sea[i].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_Sea[i].mtxWorld,
			&g_Sea[i].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Sea[i].pos.x,
			g_Sea[i].pos.y,
			g_Sea[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Sea[i].mtxWorld,
			&g_Sea[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// �C�`��
//************************************************
void DrawSea(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSea, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffSea);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Sea[i].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSea);

		// �C�̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_AmountVtx,
			0, g_AmountPrimitive);
	}
}