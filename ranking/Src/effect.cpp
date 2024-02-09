//************************************************
//
// �G�t�F�N�g[effect.cpp]
// Author�F�����h��
//
//************************************************

//include
#include "main.h"
#include "effect.h"

//�O���[�o���ϐ��錾
EFFECT g_aEffect[MAX_EFFECT];	//�G�t�F�N�g�̏��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;		//�e�N�X�`���ւ̃|�C���^

//************************************************
// �G�t�F�N�g�̏���������
//************************************************
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();  //�f�o�C�X�ւ̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureEffect);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL);

	VERTEX_3D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
		g_aEffect[nCntEffect].fRadius = 0.0f;							//���a
		g_aEffect[nCntEffect].fLife = 0.0f;								//���C�t
		g_aEffect[nCntEffect].bUse = false;								//�g�p���Ă��邩�ǂ���


		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

}

//************************************************
// �G�t�F�N�g�̏I������
//************************************************
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

}

//************************************************
// �G�t�F�N�g�̍X�V����
//************************************************
void UpdateEffect(void)
{
	VERTEX_3D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		EFFECT* pEffect = &g_aEffect[nCntEffect];
		if (pEffect->bUse)
		{
			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//�G�t�F�N�g�̐F������������������
			pEffect->col.a -= 0.01f;
			if (pEffect->col.a <= 0.0f)
			{
				pEffect->col.a = 0.0f;

			}

			//�G�t�F�N�g�̑傫��������������������
			pEffect->fRadius -= 0.5f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = pEffect->col;
			pVtx[1].col = pEffect->col;
			pVtx[2].col = pEffect->col;
			pVtx[3].col = pEffect->col;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-pEffect->fRadius, +pEffect->fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+pEffect->fRadius, +pEffect->fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-pEffect->fRadius, -pEffect->fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+pEffect->fRadius, -pEffect->fRadius, 0.0f);

			pEffect->fLife--;
			if (pEffect->fLife <= 0.0f)
			{
				pEffect->bUse = false;
			}
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();

}

//************************************************
// �G�t�F�N�g�̕`�揈��
//************************************************
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	/*---�y1�x�ōςސݒ��for���̊O�Ɉڂ��܂����F���c�z---*/

	// �G�t�F�N�g���̃|�C���^
	EFFECT* pEffect = &g_aEffect[0];

	// ���C�g���f�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	// �[�x�e�X�g�̔�r���@�̕ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// �[�x�o�b�t�@�ɕ`�悵�Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	/*----------------------------------------------------*/

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pEffect->mtxworld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pEffect->mtxworld, NULL, &mtxView);

			//�t�s������߂�
			pEffect->mtxworld._41 = 0.0f;
			pEffect->mtxworld._42 = 0.0f;
			pEffect->mtxworld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pEffect->pos.x, pEffect->pos.y, pEffect->pos.z);

			D3DXMatrixMultiply(&pEffect->mtxworld, &pEffect->mtxworld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxworld);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�G�t�F�N�g�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}

	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	/*---�y1�x�ōςސݒ��for���̊O�Ɉڂ��܂����F���c�z---*/

	// ���C�g���f��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �[�x�o�b�t�@�̔�r���@�̕ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �[�x�o�b�t�@�ɕ`�悷��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	/*----------------------------------------------------*/
}

//************************************************
// �G�t�F�N�g�̐ݒ菈��
//************************************************
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float fLife)
{
	VERTEX_3D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (!g_aEffect[nCntEffect].bUse)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].fLife = fLife;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, +g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius, +g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].bUse = true;

			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();

}

//************************************************
// �G�t�F�N�g�̏����擾���鏈��
//************************************************
EFFECT* GetEffect(void)
{
	return g_aEffect;
}
