//************************************************
//
// �e[shadow.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "shadow.h"

/*/ �}�N����` /*/
#define AMOUNT_SHADOW 256	// �e�̍ő吔

// �O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;				// �e�N�X�`���ւ̃|�C���^
Shadow g_Shadow[AMOUNT_SHADOW];						// �e���

//************************************************
// �e����
//************************************************
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{ // �e��񃊃Z�b�g
		g_Shadow[i].use = false;				// �g�p�t���O
		g_Shadow[i].pPos = nullptr;				// �Ώۈʒu
		g_Shadow[i].pos = { 0.0f, 0.0f, 0.0f };	// �ʒu
		g_Shadow[i].rot = { 0.0f, 0.0f, 0.0f };	// ����
		g_Shadow[i].span = { 0.0f, 0.0f };		// �傫���p
		g_Shadow[i].angle = 0.0f;				// �p�x
		g_Shadow[i].length = 0.0f;				// �Ίp���p
	}
	
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureShadow);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SHADOW; i++, pVtx += AMOUNT_VTX)
	{ // ���_���̃��Z�b�g

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffShadow->Unlock();

	//// �e�N�X�`�������擾
	//ImportTexShadow();

	//// ���_���𐶐�
	//CreateVtxBufferShadow();
}

//************************************************
// �e�N�X�`������ǂݍ���
//************************************************
void ImportTexShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureShadow);
}

//************************************************
// ���_���𐶐�
//************************************************
void CreateVtxBufferShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SHADOW; i++, pVtx += AMOUNT_VTX)
	{ // ���_���̃��Z�b�g

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffShadow->Unlock();
}

//************************************************
// �e�j��
//************************************************
void UninitShadow(void)
{
	if (g_pTextureShadow != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	if (g_pVtxBuffShadow != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//************************************************
// �e����
//************************************************
int CreateShadow(D3DXVECTOR3* pPos, float rad)
{
	int id = -1;	// ���ʔԍ��p

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (g_Shadow[i].use)
		{ // �g�p���Ȃ�R���e�B�j���[
			continue;
		}

		g_Shadow[i].use = true;
		g_Shadow[i].pPos = pPos;			// �Ώۈʒu���擾
		g_Shadow[i].span = { rad, rad };	// �傫�����f

		// �p�x���Z�o
		g_Shadow[i].angle = atan2f(g_Shadow[i].span.x, g_Shadow[i].span.y);

		// �Ίp�����Z�o
		g_Shadow[i].length = sqrtf(g_Shadow[i].span.x * g_Shadow[i].span.x +
			g_Shadow[i].span.y * g_Shadow[i].span.y);

		id = i;	// ���ʔԍ��i�[

		break;	// �I��
	}

	return id;	// �ꉞ���ʔԍ���n��
}

//************************************************
// �e�X�V
//************************************************
void UpdateShadow(void)
{
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{ // �����X�V

		if (!g_Shadow[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �Ώۈʒu�ɒǏ]
		g_Shadow[i].pos = *g_Shadow[i].pPos;

		// �n�ʂɒ���t��
		g_Shadow[i].pos.y = 1.0f;
	}

	// �|���S����W�J
	SetVtxShadow();

	// �s��v�Z
	CalcMatrixShadow();
}

//************************************************
// �e�W�J
//************************************************
void SetVtxShadow(void)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SHADOW; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_Shadow[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ��
		pVtx[0].pos =
		{
			sinf(g_Shadow[i].rot.z - (D3DX_PI - g_Shadow[i].angle)) * g_Shadow[i].length,
			0.0f,
			-cosf(g_Shadow[i].rot.z - (D3DX_PI - g_Shadow[i].angle)) * g_Shadow[i].length
		};

		pVtx[1].pos =
		{
			sinf(g_Shadow[i].rot.z + (D3DX_PI - g_Shadow[i].angle)) * g_Shadow[i].length,
			0.0f,
			-cosf(g_Shadow[i].rot.z + (D3DX_PI - g_Shadow[i].angle)) * g_Shadow[i].length
		};

		pVtx[2].pos =
		{
			sinf(g_Shadow[i].rot.z - g_Shadow[i].angle) * g_Shadow[i].length,
			0.0f,
			-cosf(g_Shadow[i].rot.z - g_Shadow[i].angle) * g_Shadow[i].length
		};

		pVtx[3].pos =
		{
			sinf(g_Shadow[i].rot.z + g_Shadow[i].angle) * g_Shadow[i].length,
			0.0f,
			-cosf(g_Shadow[i].rot.z + g_Shadow[i].angle) * g_Shadow[i].length
		};
	}

	g_pVtxBuffShadow->Unlock();
}

//************************************************
// �e����
//************************************************
void DeleteShadow(int id)
{
	g_Shadow[id].use = false;					// �g�p�t���O
	g_Shadow[id].pPos = nullptr;				// �Ώۈʒu
	g_Shadow[id].pos = { 0.0f, 0.0f, 0.0f };	// �ʒu
	g_Shadow[id].rot = { 0.0f, 0.0f, 0.0f };	// ����
	g_Shadow[id].span = { 0.0f, 0.0f };			// �傫���p
	g_Shadow[id].angle = 0.0f;					// �p�x
	g_Shadow[id].length = 0.0f;					// �Ίp���p
}

//************************************************
// �e�p�̍s����v�Z
//************************************************
void CalcMatrixShadow(void)
{
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (!g_Shadow[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Shadow[i].mtxWorld);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Shadow[i].pos.x,
			g_Shadow[i].pos.y,
			g_Shadow[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Shadow[i].mtxWorld,
			&g_Shadow[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// �e�`��
//************************************************
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;						// �v�Z�p�}�g���b�N�X

	// �A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���C�g���f�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (!g_Shadow[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[i].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureShadow);

		// �r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// �A���t�@�u�����f�B���O��߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�g���f��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}