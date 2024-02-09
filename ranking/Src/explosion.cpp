//************************************************
//
// �v���C���[����[player.cpp]
// Author�F�����h��
//************************************************

//include
#include "explosion.h"

#include "main.h"

//�O���[�o���ϐ��錾
Explosion g_aExplosion[MAX_EXPLOSION];					//�����̏��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			//�e�N�X�`���ւ̃|�C���^

//=======================================================================
//�����̏���������
//=======================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�ւ̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion.png", &g_pTextureExplosion);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL);

	VERTEX_3D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		Explosion* pExplosion = &g_aExplosion[nCntExplosion]; //�z����|�C���^�ɓn��

		pExplosion->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		pExplosion->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
		pExplosion->fHeight = 0.0f;								//����
		pExplosion->fWidth = 0.0f;								//��
		pExplosion->fLength = 0.0f;								//�Ίp���̒���
		pExplosion->nCounterAnim = 0;							//�A�j���[�V�����J�E���^�[
		pExplosion->nPatternAnim = 0;							//�A�j���[�V�����p�^�[��No.
		pExplosion->bUse = false;								//�g�p���Ă��邩�ǂ���

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();

}

//=======================================================================
//�����̏I������
//=======================================================================
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}

//=======================================================================
//�����̍X�V����
//=======================================================================
void UpdateExplosion(void)
{
	VERTEX_3D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		Explosion* pExplosion = &g_aExplosion[nCntExplosion];

		if (pExplosion->bUse)
		{
			pExplosion->pos = pExplosion->pos;
			pExplosion->fWidth = pExplosion->fWidth;
			pExplosion->fHeight = pExplosion->fHeight;

			//�Ίp���̒��������߂�
			pExplosion->fLength = sqrtf(pExplosion->fWidth * pExplosion->fWidth + pExplosion->fHeight * pExplosion->fHeight) / 2.0f;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = -pExplosion->fLength;
			pVtx[0].pos.y = pExplosion->fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = pExplosion->fLength;
			pVtx[1].pos.y = pExplosion->fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -pExplosion->fLength;
			pVtx[2].pos.y = -pExplosion->fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = pExplosion->fLength;
			pVtx[3].pos.y = -pExplosion->fLength;
			pVtx[3].pos.z = 0.0f;

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

			g_aExplosion[nCntExplosion].nCounterAnim++;//�A�j���[�V�����J�E���^�[�̉��Z

			if (g_aExplosion[nCntExplosion].nCounterAnim >= 3)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;//�A�j���[�V�����p�^�[���̉��Z
				g_aExplosion[nCntExplosion].nCounterAnim = 0;
			}
			if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}

			//�X�V����
			pVtx[0].tex.x = g_aExplosion[nCntExplosion].nPatternAnim / 8.0f;
			pVtx[1].tex.x = (g_aExplosion[nCntExplosion].nPatternAnim + 1) / 8.0f;
			pVtx[2].tex.x = g_aExplosion[nCntExplosion].nPatternAnim / 8.0f;
			pVtx[3].tex.x = (g_aExplosion[nCntExplosion].nPatternAnim + 1) / 8.0f;

		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();

}

//=======================================================================
//�����̕`�揈��
//=======================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�ւ̃|�C���^

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p

	/*---�y1�x�ōςސݒ��for���̊O�Ɉڂ��܂����F���c�z---*/

	Explosion* pExplosion = &g_aExplosion[0];	// �������̃|�C���^

	// ���C�g���f�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// �[�x�e�X�g�̔�r���@�̕ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//// �[�x�o�b�t�@�ɏ������܂Ȃ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	/*----------------------------------------------------*/

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pExplosion->mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pExplosion->mtxWorld, NULL, &mtxView);

			//�t�s������߂�
			pExplosion->mtxWorld._41 = 0.0f;
			pExplosion->mtxWorld._42 = 0.0f;
			pExplosion->mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pExplosion->pos.x, pExplosion->pos.y, pExplosion->pos.z);

			D3DXMatrixMultiply(&pExplosion->mtxWorld, &pExplosion->mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pExplosion->mtxWorld);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			//�r���{�[�h�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);

		}

	}

	/*---�y1�x�ōςސݒ��for���̊O�Ɉڂ��܂����F���c�z---*/

	// ���C�g���f��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// �[�x�o�b�t�@�̔�r���@�̕ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//// �[�x�o�b�t�@�ɕ`�悷��
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	/*----------------------------------------------------*/
}

//=======================================================================
//�����̐ݒ菈��
//=======================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_3D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		Explosion* pExplosion = &g_aExplosion[nCntExplosion];
		if (!pExplosion->bUse)
		{
			pExplosion->pos = pos;			//�ʒu
			pExplosion->col = col;			//���_�J���[
			pExplosion->fWidth = fWidth;	//��
			pExplosion->fHeight = fHeight;	//����
			pExplosion->nPatternAnim = 0;	//�A�j���[�V�����p�^�[��No.
			pExplosion->nCounterAnim = 0;	//�A�j���[�V�����J�E���^�[
			pExplosion->bUse = true;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->fWidth, pExplosion->pos.y - pExplosion->fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->fWidth, pExplosion->pos.y - pExplosion->fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->fWidth, pExplosion->pos.y + pExplosion->fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->fWidth, pExplosion->pos.y + pExplosion->fHeight, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = pExplosion->col;
			pVtx[1].col = pExplosion->col;
			pVtx[2].col = pExplosion->col;
			pVtx[3].col = pExplosion->col;


			break;

		}

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();

}

//=======================================================================
//�����̏����擾
//=======================================================================
Explosion* GetExplosion(void)
{
	return g_aExplosion;
}
