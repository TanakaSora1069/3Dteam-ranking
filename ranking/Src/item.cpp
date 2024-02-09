//************************************************
//
// �A�C�e��[item.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "item.h"
// ����
#include "input.h"
// ������
#include "collision.h"
#include "effect_hayu.h"
#include "player.h"
// �f�o�b�O��
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*/ �O���[�o���ϐ� /*/
ItemModel g_ItemModel[AMOUNT_MODEL_ITEM];	// �A�C�e�����f�����̂ЂȌ`
Item g_Item[AMOUNT_ITEM];					// �A�C�e�����

//************************************************
// �A�C�e������������
//************************************************
void InitItem(void)
{
	ItemModel* pModel = &g_ItemModel[0];	 // �A�C�e�����f���̂ЂȌ`�ւ̃|�C���^

	for (int i = 0; i < AMOUNT_MODEL_ITEM; i++, pModel++)
	{ // �A�C�e�����f�����̂ЂȌ`�̃��Z�b�g

		// �X�^�C��
		pModel->style = -1;

		// ���f��
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �}�e���A��
			pModel->ColMat_offset[j] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pModel->pTex[j] = NULL;
		}

		// ���f�����W
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/*--------------------------------------------*/

	Item* pItem = &g_Item[0];	// �A�C�e�����ւ̃|�C���^

	for (int i = 0; i < AMOUNT_ITEM; i++, pItem++)
	{ // �A�C�e�����̃��Z�b�g

		pItem->use = false;	// �g�p�t���O
		pItem->style = -1;	// �X�^�C��
		pItem->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���f��
		pItem->model.pMesh = NULL;
		pItem->model.pBuffMat = NULL;
		pItem->model.NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �}�e���A��
			pItem->model.ColMat_offset[j] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pItem->model.pTex[j] = NULL;
		}

		// ���f�����W
		pItem->model.pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->model.pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->model.rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->model.rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���ʔԍ����Z�b�g
		pItem->id_effect = -1;	
		pItem->id_sph = -1;
	}

	// �A�C�e���p�̃��f�������擾
	ImportModelItem();

	/*********************************************/

	/*---�y�����I�ɔz�u�z---*/
	CreateItem(styleGun);
	g_Item[0].pos = { -200.0f, 0.0f, 50.0f };	// �ʒu
	CreateItem(styleRPG);
	g_Item[1].pos = { -100.0f, 0.0f, 50.0f };	// �ʒu
	CreateItem(styleGun);
	g_Item[2].pos = { 0.0f, 0.0f, 50.0f };		// �ʒu
	CreateItem(styleRPG);
	g_Item[3].pos = { 100.0f, 0.0f, 50.0f };	// �ʒu
	CreateItem(styleGun);
	g_Item[4].pos = { 200.0f, 0.0f, 50.0f };	// �ʒu

	/*********************************************/
}

//************************************************
// ���f������ǂݍ���
//************************************************
void ImportModelItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int AmountModel = 0;		// ���f���̐����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\ITEM\\item_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�A�C�e�����f�����̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountModel);
		}

#ifdef _DEBUG

		// �G���[
		assert(AmountModel < AMOUNT_MODEL_ITEM && "�A�C�e�����f����񂪍ő�ʂ��z���܂���");

#endif	// _DEBUG

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ItemModel[id_Model].pBuffMat,
				NULL,
				&g_ItemModel[id_Model].NumMat,
				&g_ItemModel[id_Model].pMesh);

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}

	// ���łɃp�����[�^���擾
	ImportParamItem(pFile, AmountModel);

	// �t�@�C�������
	fclose(pFile);

	// �e���f���̃e�N�X�`�������擾
	ImportTexItem(AmountModel);
}

//************************************************
// �A�C�e���̃p�����[�^���̓Ǎ���
//************************************************
void ImportParamItem(FILE* pFile, int AmountModel)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	char FileString[128] = {};	// ���͂��i�[
	int i = 0;					// �ėp����
	int style = 0;				// �X�^�C�����i�[
	float rad = 0;				// ����T�C�Y���i�[

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // �X�^�C�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "RAD") == 0)
		{ // ����T�C�Y���擾
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &rad);
		}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // �擾�������𔽉f

			g_ItemModel[i].style = style;
			g_ItemModel[i].rad = rad;

			i++;	// ���̔ԍ���

			if (i >= AmountModel)
			{ // ���f���̍ő吔���z����Ƌ����I��
				break;
			}
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{
			break;	// �I��
		}
	}
}

//************************************************
// ���f���e�N�X�`������ǂݍ���
//************************************************
void ImportTexItem(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < AmountModel; i++)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_ItemModel[i].pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int j = 0; j < (int)g_ItemModel[i].NumMat; j++)
		{
			// �}�e���A���̐F�I�t�Z�b�g
			g_ItemModel[i].ColMat_offset[j] = pMat[j].MatD3D.Diffuse;

			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_ItemModel[i].pTex[j]);
			}
			else
			{
				g_ItemModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// �A�C�e������
//************************************************
void CreateItem(int style)
{
	for (int i = 0; i < AMOUNT_ITEM; i++)
	{
		if (g_Item[i].use)
		{ // �g�p���Ȃ�R���e�B�j���[
			continue;
		}

		g_Item[i].use = true;		// �g�p�t���O
		g_Item[i].style = style;	// �X�^�C��

		g_Item[i].pos = { 0.0f, 10.0f, 50.0f };	// �ʒu

		// �X�^�C���ƍ�
		VerifyStyleItem(i);

		// �G�t�F�N�g����
		g_Item[i].id_effect = CreateEffect_Hayu(styleRing, &g_Item[i].pos);

#ifdef _DEBUG

		// ���������
		g_Item[i].id_sph = CreateVisibleSph(g_Item[i].model.rad, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), &g_Item[i].pos);

#endif	// _DEBUG

		break; // �I��
	}
}

//************************************************
// �X�^�C���ԍ��̏ƍ�
//************************************************
void VerifyStyleItem(int id)
{
	for (int i = 0; i < AMOUNT_MODEL_ITEM; i++)
	{
		// �e�A�C�e���̃X�^�C���ԍ��Ɗe�p�[�c�̃X�^�C���ԍ����ƍ�
		if (g_ItemModel[i].style == g_Item[id].style)
		{ // �X�^�C���ԍ��̈�v���Ă��郂�f����L��������
			g_Item[id].model = g_ItemModel[i];
		}
	}
}

//************************************************
// �A�C�e���j��
//************************************************
void UninitItem(void)
{
	for (int i = 0; i < AMOUNT_MODEL_ITEM; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_ItemModel[i].pTex[j] != NULL)
			{ // �e�N�X�`���̔j��
				g_ItemModel[i].pTex[j]->Release();
				g_ItemModel[i].pTex[j] = NULL;
			}
		}

		if (g_ItemModel[i].pMesh != NULL)
		{ // ���b�V���̔j��
			g_ItemModel[i].pMesh->Release();
			g_ItemModel[i].pMesh = NULL;
		}

		if (g_ItemModel[i].pBuffMat != NULL)
		{ // �}�e���A���̔j��
			g_ItemModel[i].pBuffMat->Release();
			g_ItemModel[i].pBuffMat = NULL;
		}
	}
}
//************************************************
// �A�C�e���X�V����
//************************************************
void UpdateItem(void)
{
	for (int i = 0; i < AMOUNT_ITEM; i++)
	{
		if (!g_Item[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ��]
		RotateItem(i);

		// �ړ�
		MoveItem(i);

		// �����蔻��
		CollisionItem(i);
	}

	// �Ō�ɍs��v�Z
	CalcMtxItem();	//!< �o�O��h�����ߍŌ�ɍs�����ƁB
}

//************************************************
// ��]
//************************************************
void RotateItem(int id)
{
	g_Item[id].rot.y += 0.025f;	// �N���N��
}

//************************************************
// �ړ�
//************************************************
void MoveItem(int id)
{
	g_Item[id].pos.y = 5.0f + cosf(g_Item[id].rot.y) * 7.0f; // �㉺
}

//************************************************
// �����蔻��
//************************************************
void CollisionItem(int id)
{
	// �v���C���[�Ƃ̔�����s��
	if (!g_Item[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < MAX_PLAYER; i++, pPlayer++)
	{
		if (CollisionSph(g_Item[id].pos, g_Item[id].model.rad, pPlayer->pos, pPlayer->param.rad))
		{ // �v���C���[�Ƀq�b�g�����

			// �A�C�e�����擾
			pPlayer->param.weapon = GetItem(id);
		}
	}
}

//************************************************
// �A�C�e���̃��[���h�}�g���b�N�X���v�Z
//************************************************
void CalcMtxItem(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	Item* pItem = &g_Item[0];

	for (int i = 0; i < AMOUNT_ITEM; i++, pItem++)
	{
		if (!pItem->use)
		{ // ���g�p�Ȃ�ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&pItem->mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			pItem->rot.y,
			pItem->rot.x,
			pItem->rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&pItem->mtxWorld,
			&pItem->mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			pItem->pos.x,
			pItem->pos.y,
			pItem->pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&pItem->mtxWorld,
			&pItem->mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// �擾
//************************************************
int GetItem(int id)
{
	// �A�C�e�����̃��Z�b�g
	Item* pItem = &g_Item[id];	// �A�C�e�����ւ̃|�C���^
	int style = pItem->style;	// ���Z�b�g�O�ɃX�^�C�����i�[

	pItem->use = false;	// �g�p�t���O
	pItem->style = -1;	// �X�^�C��
	pItem->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���f��
	pItem->model.pMesh = NULL;
	pItem->model.pBuffMat = NULL;
	pItem->model.NumMat = 0;

	for (int j = 0; j < AMOUNT_MAT; j++)
	{ // �}�e���A��
		pItem->model.ColMat_offset[j] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pItem->model.pTex[j] = NULL;
	}

	// ���f�����W
	pItem->model.pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->model.pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->model.rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->model.rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �G�t�F�N�g������
	DeleteEffect_Hayu(pItem->id_effect);

#ifdef _DEBUG

	// ������폜
	DeleteVisibleSph(pItem->id_sph);

#endif	// _DEBUG

	pItem->id_effect = -1;
	pItem->id_sph = -1;

	return style;	// �擾�����A�C�e���̃X�^�C����Ԃ�
}

//************************************************
// �A�C�e���`��
//************************************************
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int id_item = 0; id_item < AMOUNT_ITEM; id_item++)
	{
		if (!g_Item[id_item].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Item[id_item].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Item[id_item].model.pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int id_mat = 0; id_mat < (int)g_Item[id_item].model.NumMat; id_mat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[id_mat].MatD3D);

			//�e�N�X�`���̐ݒ�
			if (g_Item[id_item].model.pTex[id_mat] != NULL)
			{
				pDevice->SetTexture(0, g_Item[id_item].model.pTex[id_mat]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			// �I�u�W�F�N�g�p�[�c�̕`��
			g_Item[id_item].model.pMesh->DrawSubset(id_mat);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}