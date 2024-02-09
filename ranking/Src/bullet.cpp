//************************************************
//
// �e[bullet.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "bullet.h"
// ����
#include "input.h"
#include "sound.h"
// ������
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "effect.h"
#include "effect_sand.h"
#include "enemy.h"
#include "explosion.h"
#include "game.h"
#include "item.h"
#include "player.h"
#include "shadow.h"
// �f�o�b�O��
#ifdef _DEBUG
#include "visible_sph.h"
#endif	// _DEBUG

// �O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			// �e�N�X�`���ւ̃|�C���^
Bullet g_Bullet[AMOUNT_BULLET];						// �e���

//************************************************
// �e����
//************************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{ // �e��񃊃Z�b�g
		g_Bullet[i].use = false;							// �g�p�t���O
		g_Bullet[i].type = bulletPlayer;					// �S�ăv���C���[�̒e�Ƃ������Ƃɂ��Ă���
		g_Bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_Bullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_Bullet[i].rad = 0;								// ���a
		g_Bullet[i].id_shadow = -1;							// �e�̎��ʔԍ�
		g_Bullet[i].id_sph = -1;							// ��������̎��ʔԍ�
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cannon.png",
		&g_pTextureBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);
	
	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BULLET; i++, pVtx += AMOUNT_VTX)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_BULLET, -SPAN_BULLET, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_BULLET, -SPAN_BULLET, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//************************************************
// �e�j��
//************************************************
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	if (g_pVtxBuffBullet != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//************************************************
// �e����
//************************************************
void CreateBullet(int type, int id)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (g_Bullet[i].use)
		{ // �g�p���Ȃ�R���e�B�j���[
			continue;
		}

		// �e�Ƀ^�C�v��ݒ�
		g_Bullet[i].type = type;

		// ���������s������for�Ő���
		if (type == bulletPlayer)
		{
			Camera* pCamera = GetInfoCamera();	// �J�����ւ̃|�C���^
			Player* pPlayer = GetInfoPlayer();	// �v���C���[�ւ̃|�C���^

			// �K���Ƀp�����[�^�ݒ�
			g_Bullet[i].use = true;

			// �������J�����̕�����
			g_Bullet[i].rot = pCamera[id].rot;

			// ���펯�ʔԍ��i�[
			int weapon = pPlayer[id].param.weapon;

			switch (weapon)
			{
				// �e
			case styleGun:
				g_Bullet[i].pos =
				{
					pPlayer[id].offset_atk[weapon].mtx._41,
					pPlayer[id].offset_atk[weapon].mtx._42,
					pPlayer[id].offset_atk[weapon].mtx._43,
				};

				g_Bullet[i].rad = SPAN_BULLET;	// �傫���F�K��
				g_Bullet[i].remain = 25;		// �����F�K��

				// �g���v�\���̐�[���甭�˂����悤�ɁA�����O�i�����Ă���
				g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x);
				g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x);
				break;

				// RPG
			case styleRPG:
				g_Bullet[i].pos =
				{
					pPlayer[id].offset_atk[weapon].mtx._41,
					pPlayer[id].offset_atk[weapon].mtx._42,
					pPlayer[id].offset_atk[weapon].mtx._43,
				};

				g_Bullet[i].rad = SPAN_BULLET;	// �傫���F�K��
				g_Bullet[i].remain = 25;		// �����F�K��

				// RPG�̐�[���甭�˂����悤�ɁA�����O�i�����Ă���
				g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x);
				g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x);
				break;
			}

			/*---�y���L���Ă��镐��̈ʒu����o���F����g��Ȃ����ǎc���Ƃ��āz---*/
			//g_Bullet[i].pos =
			//{
			//	pPlayer[id].parts[weapon].mtxWorld._41,
			//	pPlayer[id].parts[weapon].mtxWorld._42 + 13.0f,
			//	pPlayer[id].parts[weapon].mtxWorld._43,
			//};

			//g_Bullet[i].rad = SPAN_BULLET;
			//g_Bullet[i].remain = 25;

			//// �v���C���[�̐�[���甭�˂����悤�ɁA�����O�i�����Ă���
			//g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x) * 15.0f;
			//g_Bullet[i].pos.y += (sinf(g_Bullet[i].rot.x) * 15.0f);
			//g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x) * 15.0f;

			// �e�𐶐�
			g_Bullet[i].id_shadow = CreateShadow(&g_Bullet[i].pos, 10.0f);

#ifdef _DEBUG

			// �����蔻�������
			g_Bullet[i].id_sph = CreateVisibleSph(g_Bullet[i].rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Bullet[i].pos);

#endif	// _DEBUG 
		}

		break;
	}
}

//************************************************
// �e�X�V
//************************************************
void UpdateBullet(void)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_Bullet[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ړ�
		g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x) * SPD_BULLET;
		g_Bullet[i].pos.y += sinf(g_Bullet[i].rot.x) * SPD_BULLET;
		g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * cosf(g_Bullet[i].rot.x) * SPD_BULLET;

		if (g_Bullet[i].type == bulletPlayer)
		{ // �G�t�F�N�g���o��
			SetEffect(g_Bullet[i].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 10.0f);
			//SetEffectSand(g_Bullet[i].pos, 1, 150);
			//SetEffectSand(g_Player[g_P_id].pos, 1, 30);
		}

		// �����蔻����s��
		CollisionBullet(i);

		// ���Ŕ�����s��
		DeleteBullet(i);
	}
}

//************************************************
// �e����
//************************************************
void DeleteBullet(int id)
{
	if (CntDuration(&g_Bullet[id].remain))
	{ // �c�����Ԃ������Ȃ��

		// �����G�t�F�N�g
		SetExplosion(g_Bullet[id].pos, { 1.0f, 1.0f, 1.0f, 1.0f }, 30.0f, 30.0f);

		/*---�y�����I�ɏ��Łz---*/
		g_Bullet[id].use = false;							// �g�p�t���O
		g_Bullet[id].type = bulletPlayer;					// �v���C���[�̒e�ɂ��Ă���
		g_Bullet[id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_Bullet[id].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_Bullet[id].rad = 0;								// ���a
		g_Bullet[id].remain = 0;							// ����

		// �e������
		DeleteShadow(g_Bullet[id].id_shadow);

#ifdef _DEBUG

		// �������������
		DeleteVisibleSph(g_Bullet[id].id_sph);

#endif	// _DEBUG

		// ��ڂ��I�������l�����Z�b�g
		g_Bullet[id].id_shadow = -1;	
		g_Bullet[id].id_sph = -1;

		// ����
	}
}

//************************************************
// �e�`��
//************************************************
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans, mtxView;				// �v�Z�p�}�g���b�N�X

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
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_Bullet[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Bullet[i].mtxWorld);

		// �r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// �|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&g_Bullet[i].mtxWorld, NULL, &mtxView);	// �t�s������߂�

		g_Bullet[i].mtxWorld._41 = 0.0f;
		g_Bullet[i].mtxWorld._42 = 0.0f;
		g_Bullet[i].mtxWorld._43 = 0.0f;

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Bullet[i].pos.x,
			g_Bullet[i].pos.y,
			g_Bullet[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Bullet[i].mtxWorld,
			&g_Bullet[i].mtxWorld,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[i].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

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

//************************************************
// �e�̓����蔻��
//************************************************
void CollisionBullet(int id)
{
	// switch����ł͐錾���s���Ȃ�����if�Ő���
	if (g_Bullet[id].type == bulletPlayer)
	{ // �e���v���C���[�^�C�v�Ȃ�
		Enemy* pEnemy = GetInfoEnemy();
		BOSS* pBoss = GetInfoBoss();
			
		for (int j = 0; j < AMOUNT_ENEMY; j++, pEnemy++)
		{ // �G�l�~�[�Ƃ̔�����s��
			if (!pEnemy->use)
			{ // ���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pEnemy->pos, pEnemy->param.rad))
			{ // �G�Ƀq�b�g�����

				g_Bullet[id].remain = 0;	// �g�p���Ԃ𖳂���

				// �G�ɔ�e����t�^
				if (pEnemy->param.state != stateRotate_e &&
					pEnemy->param.state != stateDamage_e &&
					pEnemy->param.state != stateDead_e)
				{ // ��]�F�����F���S��ԂłȂ��Ƃ��̂�
					HitEnemy(j);

					if (pEnemy->param.style == Dragonfly)
					{ // ��x�̂ݓ��ʂɃm�b�N�o�b�N��^����
						pEnemy->move *= -1.0f;
					}
				}
			}
		}

		for (int i = 0; i < MAX_BOSS; i++, pBoss++)
		{//�{�X�Ƃ̔�����s��
			if (!pBoss->use)
			{//���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pBoss->pos, pBoss->Param.Radius))
			{//�{�X�ɓ������

				g_Bullet[id].remain = 0;	// �g�p���Ԃ𖳂���

				// �G�ɔ�e����t�^
				if (pBoss->Param.state != stateDamage_b &&
					pBoss->Param.state != stateDead_b)
				{// ������ԂƎ��S��ԂłȂ��Ƃ��̂�
					HitBoss(i);
				}
			}
		}
	}
	else if	(g_Bullet[id].type == bulletEnemy)
	{ // �e���G�l�~�[�^�C�v�Ȃ�

	}
}

//************************************************
// �e�����擾
//************************************************
Bullet* GetInfoBullet(void)
{
	return &g_Bullet[0];
}