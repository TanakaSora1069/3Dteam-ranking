//************************************************
//
// �I���W�i���G�t�F�N�g[effect_hayu.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "effect_hayu.h"
// ����
#include "sound.h"
// ������
#include "game.h"
#include "player.h"
// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif // _DEBUG

/*/ �}�N����` /*/
#define AMOUNT_EFFECT 256	// �G�t�F�N�g�̍ő吔

// �O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect_Hayu = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect_Hayu[Max_effectstyle];		// �e�N�X�`���ւ̃|�C���^
Effect_Hayu g_Effect[AMOUNT_EFFECT];							// �G�t�F�N�g���

//************************************************
// �G�t�F�N�g����
//************************************************
void InitEffect_Hayu(void)
{
	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{ // �G�t�F�N�g��񃊃Z�b�g
		g_Effect[i].use = false;								// �g�p�t���O
		g_Effect[i].style = -1;									// �X�^�C��
		g_Effect[i].type = -1;									// �^�C�v
		g_Effect[i].pPos = nullptr;								// �Ώۈʒu
		g_Effect[i].pos_moved = { 0.0f, 0.0f, 0.0f } ;			// �ϓ��ʒu
		g_Effect[i].pos = { 0.0f, 0.0f, 0.0f };					// �ʒu
		g_Effect[i].rot = { 0.0f, 0.0f, 0.0f };					// ����
		g_Effect[i].span = { 0.0f, 0.0f };						// �傫���p
		g_Effect[i].angle = 0.0f;								// �p�x
		g_Effect[i].length = 0.0f;								// �Ίp���p
		g_Effect[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
		g_Effect[i].remain = 0;									// ����
		g_Effect[i].anima.row = 0;								// �s
		g_Effect[i].anima.column = 0;							// ��
		g_Effect[i].anima.id_pattern = 0;						// ���݂̃p�^�[��
		g_Effect[i].anima.dur_cnt = 0;							// �p�^�[���J�ڊԊu
		g_Effect[i].anima.id_cnt = 0;							// �J�ڃJ�E���^�[
	}

	// �e�N�X�`�������擾
	ImportTexEffect_Hayu();

	// ���_���𐶐�
	CreateVtxBufferEffect_Hayu();
}

//************************************************
// �e�N�X�`������ǂݍ���
//************************************************
void ImportTexEffect_Hayu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ���
	const char* pFileName[Max_effectstyle] =
	{
		"data\\texture\\bullet001.png",
		"data\\texture\\bullet001.png",
		"data\\texture\\effect_ring.png",
	};

	for (int i = 0; i < Max_effectstyle; i++)
	{ // �e�N�X�`���̐���

		if (pFileName[i] == NULL)
		{ // �e�N�X�`���������Ȃ��Ă��I��
			break;
		}

		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureEffect_Hayu[i]);
	}
}

//************************************************
// ���_���𐶐�
//************************************************
void CreateVtxBufferEffect_Hayu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect_Hayu,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect_Hayu->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_EFFECT; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffEffect_Hayu->Unlock();
}

//************************************************
// �G�t�F�N�g�j��
//************************************************
void UninitEffect_Hayu(void)
{
	for (int i = 0; i < Max_effectstyle; i++)
	{
		if (g_pTextureEffect_Hayu[i] != NULL)
		{ // �e�N�X�`���̔j��
			g_pTextureEffect_Hayu[i]->Release();
			g_pTextureEffect_Hayu[i] = NULL;
		}
	}

	if (g_pVtxBuffEffect_Hayu != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffEffect_Hayu->Release();
		g_pVtxBuffEffect_Hayu = NULL;
	}
}

//************************************************
// �G�t�F�N�g����
//************************************************
int CreateEffect_Hayu(int style, D3DXVECTOR3* pPos)
{
	int id = -1;	// ���ʔԍ��p

	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		if (g_Effect[i].use)
		{ // �g�p���Ȃ�R���e�B�j���[
			continue;
		}

		g_Effect[i].use = true;
		g_Effect[i].style = style;	// �X�^�C���擾
		g_Effect[i].pPos = pPos;	// �Ώۈʒu���擾

		switch(g_Effect[i].style)
		{ //�X�^�C���ɉ����ăe�L�g�[�ɏ���t�^
		case styleHeart:

			g_Effect[i].type = 0;					// �c
			g_Effect[i].span = { 25.0f, 25.0f };	// �傫���F�K��
			g_Effect[i].remain = 45;				// �����F�K��

			break;

		case styleDeath:

			g_Effect[i].type = 0;					// �c
			g_Effect[i].span = { 50.0f, 50.0f };	// �傫���F�K��
			g_Effect[i].remain = 60;				// �����F�K��

			break;

		case styleRing:

			g_Effect[i].type = 1;					// ��
			g_Effect[i].span = { 50.0f, 50.0f };	// �傫���F�K��
			g_Effect[i].remain = -1;				// �����F����
			g_Effect[i].anima.row = 3;				// 3�s
			g_Effect[i].anima.column = 5;			// 5��
			g_Effect[i].anima.dur_cnt = 1;			// �J�ڊԊu�F�K��

			break;

		default:

#ifdef _DEBUG

			assert(false && "Hayu�G�t�F�N�g�X�^�C���擾�G���[");

#endif	// _DEBUG

			break;
		}

		// �p�x���Z�o
		g_Effect[i].angle = atan2f(g_Effect[i].span.x, g_Effect[i].span.y);

		// �Ίp�����Z�o
		g_Effect[i].length = sqrtf(g_Effect[i].span.x * g_Effect[i].span.x +
			g_Effect[i].span.y * g_Effect[i].span.y);

		id = i;	// ���ʔԍ��i�[

		break;	// �I��
	}

	return id;	// �ꉞ���ʔԍ���n��
}

//************************************************
// �G�t�F�N�g�X�V
//************************************************
void UpdateEffect_Hayu(void)
{
	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{ // �����X�V
		
		if (!g_Effect[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �Ώۈʒu�ɕϓ��ʒu�����Z
		g_Effect[i].pos = *g_Effect[i].pPos + g_Effect[i].pos_moved;

		if (g_Effect[i].type == 1)
		{ // ���^�C�v�Ȃ班��������
			g_Effect[i].pos.y = 1.0f;
		}

		if (g_Effect[i].remain != -1)
		{ // �����������łȂ����
			if (CntDuration(&g_Effect[i].remain))
			{ // ����
				DeleteEffect_Hayu(i);
			}
		}
	}

	// �|���S����W�J
	SetVtxEffect_Hayu();
}

//************************************************
// �G�t�F�N�g�W�J
//************************************************
void SetVtxEffect_Hayu(void)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	TextureSize tex = {};	// �e�N�X�`���T�C�Y�p

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect_Hayu->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_EFFECT; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_Effect[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���_�̓W�J���@��2����
		if (g_Effect[i].type == 0)
		{ // �c
			pVtx[0].pos =
			{
				sinf(g_Effect[i].rot.z - (D3DX_PI - g_Effect[i].angle)) * g_Effect[i].length,
				-cosf(g_Effect[i].rot.z - (D3DX_PI - g_Effect[i].angle)) * g_Effect[i].length,
				0.0f
			};

			pVtx[1].pos =
			{
				sinf(g_Effect[i].rot.z + (D3DX_PI - g_Effect[i].angle)) * g_Effect[i].length,
				-cosf(g_Effect[i].rot.z + (D3DX_PI - g_Effect[i].angle)) * g_Effect[i].length,
				0.0f
			};

			pVtx[2].pos =
			{
				sinf(g_Effect[i].rot.z - g_Effect[i].angle) * g_Effect[i].length,
				-cosf(g_Effect[i].rot.z - g_Effect[i].angle) * g_Effect[i].length,
				0.0f
			};

			pVtx[3].pos =
			{
				sinf(g_Effect[i].rot.z + g_Effect[i].angle) * g_Effect[i].length,
				-cosf(g_Effect[i].rot.z + g_Effect[i].angle) * g_Effect[i].length,
				0.0f
			};
		}
		else if (g_Effect[i].type == 1)
		{ // ��
			pVtx[0].pos =
			{
				sinf(g_Effect[i].rot.z - (D3DX_PI - g_Effect[i].angle)) * g_Effect[i].length,
				0.0f,
				-cosf(g_Effect[i].rot.z - (D3DX_PI - g_Effect[i].angle)) * g_Effect[i].length
			};

			pVtx[1].pos =
			{
				sinf(g_Effect[i].rot.z + (D3DX_PI - g_Effect[i].angle)) * g_Effect[i].length,
				0.0f,
				-cosf(g_Effect[i].rot.z + (D3DX_PI - g_Effect[i].angle)) * g_Effect[i].length
			};

			pVtx[2].pos =
			{
				sinf(g_Effect[i].rot.z - g_Effect[i].angle) * g_Effect[i].length,
				0.0f,
				-cosf(g_Effect[i].rot.z - g_Effect[i].angle) * g_Effect[i].length
			};

			pVtx[3].pos =
			{
				sinf(g_Effect[i].rot.z + g_Effect[i].angle) * g_Effect[i].length,
				0.0f,
				-cosf(g_Effect[i].rot.z + g_Effect[i].angle) * g_Effect[i].length
			};
		}

		// ���̃G�t�F�N�g�p�̃T�C�Y���Z�o
		tex = SetTexEffect_Hayu(i);

		// �e�N�X�`���T�C�Y���f
		pVtx[0].tex = tex.size[0];
		pVtx[1].tex = tex.size[1];
		pVtx[2].tex = tex.size[2];
		pVtx[3].tex = tex.size[3];
	}

	g_pVtxBuffEffect_Hayu->Unlock();
}

//************************************************
// �G�t�F�N�g�A�j���[�V�����Ǘ�
//************************************************
TextureSize SetTexEffect_Hayu(int id)
{
	TextureSize tex = {};	// �e�N�X�`���T�C�Y�i�[

	// switch����ł͐錾���s���Ȃ�����if�Ő��䂷��
	if (g_Effect[id].style == styleHeart)
	{
		// �n�[�g�F�Œ�
		tex = {
			D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f, 0.0f),
			D3DXVECTOR2(0.0f, 1.0f),
			D3DXVECTOR2(1.0f, 1.0f),
		};
	}
	else if (g_Effect[id].style == styleDeath)
	{
		// ���F�Œ�
		tex = {
			D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f, 0.0f),
			D3DXVECTOR2(0.0f, 1.0f),
			D3DXVECTOR2(1.0f, 1.0f),
		};
	}
	else if (g_Effect[id].style == styleRing)
	{
		// �����O�F5�� * 3�s�̃p�^�[���Ōv�Z
		float row = 1.0f / g_Effect[id].anima.row;			// 1������̍s�T�C�Y
		float column = 1.0f / g_Effect[id].anima.column;	// 1������̗�T�C�Y

		// �����e�N�X�`���A�j���[�V����
		AnimationTex_Effect_Hayu(id);

		float x = 1.0f + (g_Effect[id].anima.id_pattern * 1.0f);
		float y = 1.0f;

		if (g_Effect[id].anima.id_pattern >= 5 &&
			g_Effect[id].anima.id_pattern < 10)
		{
			y = 2.0f;
		}
		else if (g_Effect[id].anima.id_pattern >= 10)
		{
			y = 3.0f;
		}

		tex = {
			D3DXVECTOR2(column * (x - 1.0f), row * (y - 1.0f)),
			D3DXVECTOR2(column * x, row * (y - 1.0f)),
			D3DXVECTOR2(column * (x - 1.0f), row * y),
			D3DXVECTOR2(column * x, row * y),
		};
	}

	return tex;	// �e�N�X�`���T�C�Y��n��
}

//************************************************
// �e�N�X�`���A�j���[�V����
//************************************************
void AnimationTex_Effect_Hayu(int id)
{
	if (g_Effect[id].anima.id_cnt < g_Effect[id].anima.dur_cnt)
	{ // ����̊Ԋu�܂ŃJ�E���g
		g_Effect[id].anima.id_cnt++;
	}
	else
	{ // ����̊Ԋu�ɒB�����
		g_Effect[id].anima.id_cnt = 0;		// �J�E���g���Z�b�g
		g_Effect[id].anima.id_pattern++;	// �p�^�[����i�߂�

		if (g_Effect[id].anima.id_pattern >= 15)
		{ // 15�p�^�[���ɓ��B�Ń��Z�b�g�H
			g_Effect[id].anima.id_pattern = 0;
		}
	}
}

//************************************************
// �G�t�F�N�g����
//************************************************
void DeleteEffect_Hayu(int id)
{
	g_Effect[id].use = false;								// �g�p�t���O
	g_Effect[id].style = -1;								// �X�^�C��
	g_Effect[id].type = -1;									// �^�C�v
	g_Effect[id].pPos = nullptr;							// �Ώۈʒu
	g_Effect[id].pos_moved = { 0.0f, 0.0f, 0.0f };			// �ϓ��ʒu
	g_Effect[id].pos = { 0.0f, 0.0f, 0.0f };				// �ʒu
	g_Effect[id].rot = { 0.0f, 0.0f, 0.0f };				// ����
	g_Effect[id].span = { 0.0f, 0.0f };						// �傫���p
	g_Effect[id].angle = 0.0f;								// �p�x
	g_Effect[id].length = 0.0f;								// �Ίp���p
	g_Effect[id].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
	g_Effect[id].remain = 0;								// ����
	g_Effect[id].anima.row = 0;								// ���s��
	g_Effect[id].anima.column = 0;							// ����
	g_Effect[id].anima.id_pattern = 0;						// ���݂̃p�^�[��
	g_Effect[id].anima.dur_cnt = 0;							// �p�^�[���J�ڊԊu
	g_Effect[id].anima.id_cnt = 0;							// �J�ڃJ�E���^�[
}

//************************************************
// �G�t�F�N�g�`��
//************************************************
void DrawEffect_Hayu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans, mtxView;				// �v�Z�p�}�g���b�N�X
	LPDIRECT3DTEXTURE9 pTexture;				// �e�N�X�`���|�C���^

	// ���C�g���f�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// �[�x�e�X�g�̔�r���@�̕ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//// �[�x�o�b�t�@�ɕ`�悵�Ȃ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect_Hayu, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		if (!g_Effect[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Effect[i].mtxWorld);

		// �r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		if (g_Effect[i].type == 0)
		{
			// �|���S�����J�����̐��ʂɌ���������
			D3DXMatrixInverse(&g_Effect[i].mtxWorld, NULL, &mtxView);	// �t�s������߂�

			g_Effect[i].mtxWorld._41 = 0.0f;
			g_Effect[i].mtxWorld._42 = 0.0f;
			g_Effect[i].mtxWorld._43 = 0.0f;
		}

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Effect[i].pos.x,
			g_Effect[i].pos.y,
			g_Effect[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Effect[i].mtxWorld,
			&g_Effect[i].mtxWorld,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Effect[i].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pTexture = g_pTextureEffect_Hayu[g_Effect[i].style];

		pDevice->SetTexture(0, pTexture);

		// �r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ���C�g���f��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// �[�x�e�X�g�̔�r���@�̕ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//// �[�x�o�b�t�@�ɏ�������
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}