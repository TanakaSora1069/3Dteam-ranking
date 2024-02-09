//===============================================================================
//
//  3D�Q�[����b(EffectSand.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "effect_sand.h"
#include "stdlib.h"
#include "debugproc.h"
#include "input.h"
#include <time.h>

//�}�N����`
//�}�N����`
#define MAX_EFFECT_SAND	(1024)
#define EFFECT_SAND_COOLTIME	(7)
#define NUM_EffectSand	(6)
#define MAX_EFFECT_EMUTTER	(3)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float nSize;
	float fLength;
	float fAngle;
	int nType;
	bool bUse;
	int nAlpha;
}EffectSand;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEffectSand[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffectSand = NULL;
D3DXMATRIX g_mtxWorldEffectSand;
EffectSand g_EffectSand[MAX_EFFECT_SAND];

int effectfrag[MAX_EFFECT_EMUTTER];
//======================================
//���G�t�F�N�g�̏���������
//======================================
void InitEffectSand(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT_SAND,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffectSand,
		NULL);
	//�e�N�X�`���̓ǂݍ���
	VERTEX_3D* pVtx;	//���_���̃|�C���^
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\s_effect.png",	
		&g_apTextureEffectSand[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\s_effect_a.png",
		&g_apTextureEffectSand[1]);
	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{
		g_EffectSand[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EffectSand[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EffectSand[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_EffectSand[nCnt].nSize = 50;
		g_EffectSand[nCnt].fLength = sqrtf(g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize + g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize) / 2.0f;
		g_EffectSand[nCnt].fAngle = atan2f(g_EffectSand[nCnt].nSize, g_EffectSand[nCnt].nSize);
		g_EffectSand[nCnt].nType = 0;
		g_EffectSand[nCnt].bUse = false;
		g_EffectSand[nCnt].nAlpha = 255;

	}

	g_pVtxBuffEffectSand->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{


		//���_���W�̐ݒ�
		pVtx[0].pos.x = sinf(g_EffectSand[nCnt].rot.z - (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
		pVtx[0].pos.z = cosf(g_EffectSand[nCnt].rot.z - (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
		pVtx[0].pos.y = 50.0f;
		pVtx[1].pos.x = sinf(g_EffectSand[nCnt].rot.z + (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
		pVtx[1].pos.z = cosf(g_EffectSand[nCnt].rot.z + (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
		pVtx[1].pos.y = 50.0f;
		pVtx[2].pos.x = sinf(g_EffectSand[nCnt].rot.z - g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
		pVtx[2].pos.z = cosf(g_EffectSand[nCnt].rot.z - g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
		pVtx[2].pos.y = -50.0f;
		pVtx[3].pos.x = sinf(g_EffectSand[nCnt].rot.z + g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
		pVtx[3].pos.z = cosf(g_EffectSand[nCnt].rot.z + g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
		pVtx[3].pos.y = -50.0f;

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffEffectSand->Unlock();

	for (int i = 0; i < MAX_EFFECT_EMUTTER; i++)
	{
		effectfrag[i] = 0;
	}
}

//======================================
//���G�t�F�N�g�̏I������
//======================================

void UninitEffectSand(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureEffectSand[nCnt] != NULL)
		{
			g_apTextureEffectSand[nCnt]->Release();
			g_apTextureEffectSand[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffectSand != NULL)
	{
		g_pVtxBuffEffectSand->Release();
		g_pVtxBuffEffectSand = NULL;
	}
}
//======================================
//���G�t�F�N�g�̍X�V����
//======================================

void UpdateEffectSand(void)
{

	VERTEX_3D* pVtx;	//���_���̃|�C���^
	g_pVtxBuffEffectSand->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{
		if (g_EffectSand[nCnt].bUse == true)
		{
			g_EffectSand[nCnt].nSize -= 0.6f;

			g_EffectSand[nCnt].fLength = sqrtf(g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize + g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize) / 2.0f;
			g_EffectSand[nCnt].fAngle = atan2f(g_EffectSand[nCnt].nSize, g_EffectSand[nCnt].nSize);
			g_EffectSand[nCnt].nAlpha -= 5;
			//���_���W�̐ݒ�
			pVtx[0].pos.x = sinf(g_EffectSand[nCnt].rot.z - (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
			pVtx[0].pos.y = -cosf(g_EffectSand[nCnt].rot.z - (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
			pVtx[0].pos.z = 0;
			pVtx[1].pos.x = sinf(g_EffectSand[nCnt].rot.z + (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
			pVtx[1].pos.y = -cosf(g_EffectSand[nCnt].rot.z + (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
			pVtx[1].pos.z = -0;
			pVtx[2].pos.x = sinf(g_EffectSand[nCnt].rot.z - g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
			pVtx[2].pos.y = -cosf(g_EffectSand[nCnt].rot.z - g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
			pVtx[2].pos.z = 0;
			pVtx[3].pos.x = sinf(g_EffectSand[nCnt].rot.z + g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
			pVtx[3].pos.y = -cosf(g_EffectSand[nCnt].rot.z + g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
			pVtx[3].pos.z = -0;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_EffectSand[nCnt].nAlpha);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_EffectSand[nCnt].nAlpha);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_EffectSand[nCnt].nAlpha);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_EffectSand[nCnt].nAlpha);

			if (g_EffectSand[nCnt].nType == 0)
			{
				g_EffectSand[nCnt].rot.z -= 0.6f;
			}
			else
			{
				g_EffectSand[nCnt].rot.z += 0.6f;
			}
			if (g_EffectSand[nCnt].nSize < 10)
			{
				g_EffectSand[nCnt].bUse = false;
			}
	

		}
		pVtx += 4;
	}
	g_pVtxBuffEffectSand->Unlock();
	int Used = 0;
	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{
		if (g_EffectSand[nCnt].bUse == true)
		{
			Used++;
		}
	}
	for (int i = 0; i < MAX_EFFECT_EMUTTER; i++)
	{
		if (effectfrag[i] <= EFFECT_SAND_COOLTIME)
		{
			effectfrag[i]++;
		}
	}

	//PrintDebugProc("�g�p���Ă���G�t�F�N�g���F%d / %d\n", Used, MAX_EFFECT_SAND);
}


//======================================
//���G�t�F�N�g�̕`�揈��
//======================================
void DrawEffectSand(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxView;

	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Z�A���t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	/*---�y1�x�ōςސݒ��for���̊O�Ɉڂ��܂����F���c�z---*/

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffectSand, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	/*----------------------------------------------------*/

	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{
		if (g_EffectSand[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X
			D3DXMatrixIdentity(&g_mtxWorldEffectSand);

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂ�������
			D3DXMatrixInverse(&g_mtxWorldEffectSand, NULL, &mtxView);//�t�s������߂�
			g_mtxWorldEffectSand._41 = 0.0f;
			g_mtxWorldEffectSand._42 = 0.0f;
			g_mtxWorldEffectSand._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_EffectSand[nCnt].pos.x,
				g_EffectSand[nCnt].pos.y,
				g_EffectSand[nCnt].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffectSand,
				&g_mtxWorldEffectSand,
				&mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&g_mtxWorldEffectSand);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEffectSand[g_EffectSand[nCnt].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
	//�ʏ�̍����ɖ߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�A���t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
//======================================
//���G�t�F�N�g�̐ݒu
//======================================
void SetEffectSand(D3DXVECTOR3 pos,int nType, float nSize,int nID)
{
	VERTEX_3D* pVtx;	//���_���̃|�C���^
	g_pVtxBuffEffectSand->Lock(0, 0, (void**)&pVtx, 0);
	if (effectfrag[nID] > EFFECT_SAND_COOLTIME)
	{
		effectfrag[nID] = 0;
		for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
		{
			if (g_EffectSand[nCnt].bUse == false)
			{
				g_EffectSand[nCnt].bUse = true;
				g_EffectSand[nCnt].pos = pos;
				g_EffectSand[nCnt].nType = nType;
				g_EffectSand[nCnt].nSize = nSize;
				g_EffectSand[nCnt].nAlpha = 255;

				g_EffectSand[nCnt].fLength = sqrtf(g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize + g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize) / 2.0f;
				g_EffectSand[nCnt].fAngle = atan2f(g_EffectSand[nCnt].nSize, g_EffectSand[nCnt].nSize);

				break;
			}
			pVtx += 4;

		}
	}

	g_pVtxBuffEffectSand->Unlock();

}
