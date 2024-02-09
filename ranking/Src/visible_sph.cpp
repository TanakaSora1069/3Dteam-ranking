//************************************************
//
// ���`�̓����蔻�������[visible_sph.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "visible_sph.h"
// ������
#include "player.h"

/*/ �}�N����` /*/
#define AMOUNT_SPHERE 64	// �X�t�B�A�̍ő吔
#define COLUMN_SPHERE 11	// ��(���̕�)
#define LINE_SPHERE	11		// �s(��������)

/*/ �O���[�o���ϐ� /*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSphere = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Sph g_Sph[AMOUNT_SPHERE] = {};						// �X�t�B�A���
static const float g_F = 1.0f;						// 1.0f
// ����̌v�Z�p
static const int g_AmountVtx = (COLUMN_SPHERE * LINE_SPHERE);			// ���_�̐�
static const int g_AmountPrimitive = (((COLUMN_SPHERE - 1) * (LINE_SPHERE - 1)) * 2) + ((LINE_SPHERE - 2) * 4);	// �ʂ̐�
static const int g_AmountIdx = g_AmountPrimitive + 2;					// �C���f�b�N�X�̐�
static const float g_COLUMN = g_F / (COLUMN_SPHERE - 1);				// ���񕪂�1
static const float g_LINE = g_F / (LINE_SPHERE - 1);					// ���s����1
static const float g_COLUMNr = (D3DX_PI * 2.0f) / (COLUMN_SPHERE - 1);	// ���񕪂�1�̊p�x
static const float g_LINEr = D3DX_PI / (LINE_SPHERE - 1);				// ���s����1�̊p�x

//************************************************
// �X�t�B�A����
//************************************************
void InitVisibleSph(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_SPHERE; i++)
	{ // �X�t�B�A�������Z�b�g
		g_Sph[i].use = false;
		g_Sph[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Sph[i].pPos = NULL;
		g_Sph[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	/*--------------------------------------------*/

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_AmountVtx * AMOUNT_SPHERE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < g_AmountVtx; i++)
	{
		// ���_���W�̐ݒ�
		pVtx[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̏����ݒ�
		pVtx[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		// �e�N�X�`�����W�̏����ݒ�
		pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSphere->Unlock();

	/*--------------------------------------------*/

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_AmountIdx * AMOUNT_SPHERE,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphere,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	// �s���J�E���g�p

	while (1)	// ���[�v�񐔂͏k�ރ��[�v��
	{
		// �s�̋N�_������W�J����
		for (int X = 0; X < COLUMN_SPHERE; X++, pIdx += 2)
		{ // 2���_�Z�b�g�ŗ񂪂���Ă���
			pIdx[0] = (WORD)(COLUMN_SPHERE + X + (Z * COLUMN_SPHERE));	// �񐔎��̂��N�_�̃C���f�b�N�X�ɂȂ�
			pIdx[1] = (WORD)(X + (Z * COLUMN_SPHERE));
		}


		if (Z >= LINE_SPHERE - 2)
		{ // �k�ރ��[�v���o���Ȃ��Ȃ�΃��[�v�𔲂���
			break;
		}

		pIdx[0] = (WORD)((COLUMN_SPHERE * (Z + 1)) - 1);	// (�� * (�Y���s + 1)) - 1�ł��̍s�̉E��̊p
		pIdx[1] = (WORD)((Z + 2) * COLUMN_SPHERE);	// (�Y���s + 2) * �񐔂ŋN�_�̂����1�s����

		pIdx += 2;
		Z++;	// �s�̋N�_��1�i������
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffSphere->Unlock();
}

//************************************************
// �X�t�B�A����
//************************************************
int CreateVisibleSph(const float rad, D3DXCOLOR col, D3DXVECTOR3* pPos)
{
	VERTEX_3D* pVtx;	// ���_���̃|�C���^
	int id = -1;		// ���ʔԍ��i�[

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SPHERE; i++, pVtx += g_AmountVtx)
	{
		if (g_Sph[i].use)
		{ // �g�p����Ă���΃R���e�B�j���[
			continue;
		}

		float yaw = 0.0f;					// ���p
		float pitch = -(D3DX_PI * 0.5f);	// ��

		for (int j = 0; j < g_AmountVtx; j++, yaw += g_COLUMNr)
		{
			// �p�x�̒���
			if (yaw >= (D3DX_PI * 2.0f))
			{
				yaw = 0.0f;
				pitch += g_LINEr;
			}

			// ���_���W�̐ݒ�
			pVtx[j].pos =
			{
				(rad * cosf(yaw) * cosf(pitch)),
				(rad * sinf(pitch)),
				(rad * sinf(yaw) * cosf(pitch))
			};

			// �F�̔��f
			pVtx[j].col = col;
		}

		g_Sph[i].use = true;	// �g�p
		g_Sph[i].pPos = pPos;	// �Ώە��̈ʒu�����i�[
		id = i;					// ���ʔԍ����R�s�[

		break;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSphere->Unlock();

	return id;	// ���ʔԍ���Ԃ�
}

//************************************************
// �X�t�B�A�j��
//************************************************
void UninitVisibleSph(void)
{
	if (g_pVtxBuffSphere != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}

	if (g_pIdxBuffSphere != NULL)
	{ // �C���f�b�N�X�o�b�t�@�̔j��
		g_pIdxBuffSphere->Release();
		g_pIdxBuffSphere = NULL;
	}
}

//************************************************
// �X�t�B�A�X�V
//************************************************
void UpdateVisibleSph(void)
{
	for (int i = 0; i < AMOUNT_SPHERE; i++)
	{
		if (!g_Sph[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �Ώە��ƈʒu�𓯊�����
		g_Sph[i].pos = *g_Sph[i].pPos;
	}

	// �s��v�Z
	CalcMtxVisibleSph();
}

//************************************************
// �X�t�B�A�p�̍s����v�Z
//************************************************
void CalcMtxVisibleSph(void)
{
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_SPHERE; i++)
	{
		if (!g_Sph[i].use)
		{ //  ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Sph[i].mtxWorld);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Sph[i].pos.x,
			g_Sph[i].pos.y,
			g_Sph[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Sph[i].mtxWorld,
			&g_Sph[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// �X�t�B�A�폜
//************************************************
void DeleteVisibleSph(int id)
{
	// �������Z�b�g
	g_Sph[id].use = false;
	g_Sph[id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Sph[id].pPos = NULL;
	g_Sph[id].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//************************************************
// �X�t�B�A�`��
//************************************************
void DrawVisibleSph(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffSphere);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_SPHERE; i++)
	{
		if (!g_Sph[i].use)
		{ //  ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		pDevice->SetTransform(D3DTS_WORLD, &g_Sph[i].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// �X�t�B�A�̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, i * g_AmountVtx, 0, g_AmountVtx,
			0, g_AmountPrimitive);
	}

	// ���C�g���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}