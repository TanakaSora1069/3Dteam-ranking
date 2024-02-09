//************************************************
//
// �G�l�~�[����[enemy.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "enemy.h"
// ����
#include "input.h"
#include "sound.h"
// ������
#include "collision.h"
#include "game.h"
#include "player.h"
#include "shadow.h"
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*/ �O���[�o���ϐ� /*/
EnemyModel g_EnemyModel[AMOUNT_ENEMY_PARTS];	// �G�l�~�[�p���f�����̂ЂȌ`
EnemyMotion g_EnemyMotion[8];					// �G�l�~�[���[�V�������̂ЂȌ`
Enemy g_Enemy[AMOUNT_ENEMY];					// �G�l�~�[���

float g_movePower = 0.0f;

//************************************************
// �G�l�~�[����
//************************************************
void InitEnemy(void)
{
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{ // �G�l�~�[�p���f�����̂ЂȌ`�̃��Z�b�g
		EnemyModel* pModel = &g_EnemyModel[i];

		// �X�^�C��
		pModel->style = 0;

		// ���f��
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �}�e���A��
			pModel->pTex[j] = NULL;
		}

		// ���f�����W
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �e�C���f�b�N�X
		pModel->IdxParent = -1;
	}

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{ // �G�l�~�[���̃��Z�b�g
		Enemy* pEnemy = &g_Enemy[i];

		// �g�p�t���O
		pEnemy->use = false;

		// �p�����[�^
		pEnemy->param =
		{
			0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0		// �����o�[���̓w�b�_�t�@�C�����m�F���ĉ�����
		};

		// ���W�n
		pEnemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �F
		pEnemy->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
		{ // �e�p�[�c�������Z�b�g
			EnemyModel* pModel = &pEnemy->parts[j];

			// ���f��
			pModel->pMesh = NULL;
			pModel->pBuffMat = NULL;
			pModel->NumMat = 0;

			for (int k = 0; k < AMOUNT_MAT; k++)
			{ // �}�e���A��
				pModel->pTex[k] = NULL;
			}

			// ���f�����W
			pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �e�C���f�b�N�X
			pModel->IdxParent = -1;
		}

		// ���ʔԍ�
		pEnemy->id_shadow = -1;
		pEnemy->id_sph = -1;
	}

	/*--------------------------------------------*/

	// �G�l�~�[�p�̃��f�������擾
	ImportModelEnemy();

	// �G�l�~�[�p�̃��[�V���������擾
	ImportMotionEnemy();

	// �G�l�~�[�p�̃p�����[�^�����擾
	ImportParamEnemy();

	/*---�y���[�V���������R�s�[(�C���\��)�z---*/
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (g_EnemyMotion[j].amount_key == 0)
			{ // ���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			// ���[�V���������R�s�[
			g_Enemy[i].motion[j] = g_EnemyMotion[j];
		}
	}
}

//************************************************
// ���f������ǂݍ���
//************************************************
void ImportModelEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int AmountModel = 0;		// ���f���̐����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�G�l�~�[���f�����̓W�J�Ɏ��s");

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
		assert(AmountModel < AMOUNT_ENEMY_PARTS && "�G�l�~�[���f�����f����񂪍ő�ʂ��z���܂���");

#endif

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_EnemyModel[id_Model].pBuffMat,
				NULL,
				&g_EnemyModel[id_Model].NumMat,
				&g_EnemyModel[id_Model].pMesh);

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}

	// �e���f���̃I�t�Z�b�g�����擾
	ImportOffsetEnemy(pFile, AmountModel);

	// �e���f���̃e�N�X�`�������擾
	ImportTexEnemy(AmountModel);

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// ���f���I�t�Z�b�g����ǂݍ���
//************************************************
void ImportOffsetEnemy(FILE* pFile, int AmountModel)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	char FileString[128] = {};	// ���͂��i�[
	int Style = -1;				// ���̃p�[�c�̃X�^�C�����i�[
	int IdxParent = -1;			// �e�̃C���f�b�N�X���i�[
	D3DXVECTOR3 pos = {};		// �ʒu�̃I�t�Z�b�g���i�[
	D3DXVECTOR3 rot = {};		// �����̃I�t�Z�b�g���i�[
	int id_Model = 0;			// ���f���̎��ʗp

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // ���̃p�[�c�̃X�^�C�����擾	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &Style);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // �e�̃C���f�b�N�X���擾	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu�̃I�t�Z�b�g���擾	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �����̃I�t�Z�b�g���擾	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			g_EnemyModel[id_Model].style = Style;
			g_EnemyModel[id_Model].IdxParent = IdxParent;
			g_EnemyModel[id_Model].pos_offset = pos;
			g_EnemyModel[id_Model].rot_offset = rot;

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}
}

//************************************************
// ���f���e�N�X�`������ǂݍ���
//************************************************
void ImportTexEnemy(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < AmountModel; i++)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_EnemyModel[i].pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int j = 0; j < (int)g_EnemyModel[i].NumMat; j++)
		{
			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_EnemyModel[i].pTex[j]);
			}
			else
			{
				g_EnemyModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// �G�̃p�����[�^���̓Ǎ���
//************************************************
void ImportParamEnemy(void)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int i = 0;					// �ėp����
	int appear = 0;				// �o���^�C�~���O���i�[
	int style = 0;				// �X�^�C�����i�[
	int hp = 0;					// ���C�t���i�[
	float spd = 0;				// ���x���i�[
	float rad = 0;				// ����T�C�Y���i�[
	D3DXVECTOR3 pos, rot;		// �ʒu�ƌ������i�[

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_param.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�G�l�~�[�p�����[�^���̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "APPEAR") == 0)
		{ // �o���^�C�~���O���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &appear);
		}

		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // �X�^�C�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // ���C�t���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &hp);
		}

		if (strcmp(&FileString[0], "SPD") == 0)
		{ // ���x���擾
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &spd);
		}

		if (strcmp(&FileString[0], "RAD") == 0)
		{ // ����T�C�Y���擾
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &rad);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �������擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // �擾�������𔽉f
			g_Enemy[i].param =
			{
				appear, style, 0, 0, -1, hp, spd, rad, 0, 0
			};
			g_Enemy[i].pos = pos;
			g_Enemy[i].rot = rot;

			i++;	// ���̔ԍ���

			if (i >= AMOUNT_ENEMY)
			{ // �G�̍ő吔���z����Ƌ����I��
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
// �X�^�C���ԍ��̏ƍ�
//************************************************
void VerifyStyleEnemy(int id)
{
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		if (g_Enemy[id].param.style == g_EnemyModel[i].style)
		{ // �e�G�l�~�[�̃X�^�C���ƑS�p�[�c�̃X�^�C�����ƍ�
			g_Enemy[id].parts[i] = g_EnemyModel[i];	//!< �ԍ��̈�v���Ă���p�[�c�̂ݗL����
		}
	}
}

//************************************************
// ���[�V��������ǂݍ���
//************************************************
void ImportMotionEnemy(void)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int i = 0, j = 0, k = 0;	// �ėp����
	int loop = 0;				// ���[�v�t���O���i�[
	int amountKey = 0;			// ���L�[�����擾
	int amountFrame = 0;		// ���t���[�������擾
	D3DXVECTOR3 pos, rot;		// �ʒu�ƌ������i�[

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_motion.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�G�l�~�[���[�V�������̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "LOOP") == 0)
		{ // ���[�v�t���O���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &loop);
		}

		if (strcmp(&FileString[0], "NUM_KEY") == 0)
		{ // ���L�[�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &amountKey);
		}

		if (strcmp(&FileString[0], "FRAME") == 0)
		{ // �t���[�������擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &amountFrame);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // ����ʒu���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // ����������擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_KEY") == 0)
		{ // �p�[�c�������ۑ�
			g_EnemyMotion[i].key[j].dest[k].pos = pos;
			g_EnemyMotion[i].key[j].dest[k].rot = rot;

			k++;	// �p�[�c�ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // �L�[����ۑ�
			g_EnemyMotion[i].key[j].amount_frame = amountFrame;

			k = 0;	// �p�[�c�ԍ������Z�b�g
			j++;	// �L�[�ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // ���[�V��������ۑ�
			g_EnemyMotion[i].loop = loop;
			g_EnemyMotion[i].amount_key = amountKey;

			j = 0;	// �L�[�ԍ������Z�b�g
			i++;	// ���[�V�����ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // �I��
			break;
		}
	}
}

//************************************************
// �G�l�~�[�j��
//************************************************
void UninitEnemy(void)
{
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_EnemyModel[i].pTex[j] != NULL)
			{ // �e�N�X�`���̔j��
				g_EnemyModel[i].pTex[j]->Release();
				g_EnemyModel[i].pTex[j] = NULL;
			}
		}

		if (g_EnemyModel[i].pMesh != NULL)
		{ // ���b�V���̔j��
			g_EnemyModel[i].pMesh->Release();
			g_EnemyModel[i].pMesh = NULL;
		}

		if (g_EnemyModel[i].pBuffMat != NULL)
		{ // �}�e���A���̔j��
			g_EnemyModel[i].pBuffMat->Release();
			g_EnemyModel[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// �G�l�~�[�X�V
//************************************************
void UpdateEnemy(void)
{
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		// �o���F�g�p�󋵂Ɋւ��Ȃ�
		AppearEnemy(i);

		// �ߋ��̈ʒu���L�^
		g_Enemy[i].pos_old = g_Enemy[i].pos;

		// ��]
		RotateEnemy(i);

		// �ړ�
		MoveEnemy(i);

		// �U��
		AtkEnemy(i);

		// ����
		DamageEnemy(i);

		// ���S
		DeadEnemy(i);

		// ���[�V����
		MotionEnemy(i);
	}

	// �Ō�ɍs��v�Z
	CalcMtxEnemy();

#ifdef _DEBUG

	for (int i = 0; i < 3; i++)
	{
		Enemy* pEnemy = &g_Enemy[i];
		char pStr[8];

		switch (pEnemy->param.state)
		{
		case stateNormal_e:
			snprintf(&pStr[0], 8, "�ʏ�");
			break;

		case stateMove_e:
			snprintf(&pStr[0], 8, "�ړ�");
			break;

		case stateAtk_e:
			snprintf(&pStr[0], 8, "�U��");
			break;

		case stateCharge_e:
			snprintf(&pStr[0], 8, "����");
			break;

		case stateRotate_e:
			snprintf(&pStr[0], 8, "��]");
			break;

		case stateDamage_e:
			snprintf(&pStr[0], 8, "��e");
			break;

		case stateDead_e:
			snprintf(&pStr[0], 8, "���S");
			break;

		default:

			// �G���[
			assert(false && "�����ꂩ�̃G�l�~�[��ԂɃG���[");

			break;
		}

		PrintDebugProc("�y%dE�z\nstate : %s\n", i + 1, &pStr[0]);	// �X�e�[�^�X
		PrintDebugProc("HP : %d\n", pEnemy->param.HP);				// ���C�t
		PrintDebugProc("SPD : %f\n", pEnemy->param.SPD);			// ���x
	}

#endif	// _DEBUG

}

//************************************************
// �G�l�~�[�o��
//************************************************
void AppearEnemy(int id)
{
	if (g_Enemy[id].param.appear > 0 && !g_Enemy[id].use)
	{ // ���g�p�̂��̂ŏo���^�C�~���O���ݒ肳��Ă����

		g_Enemy[id].param.appear--;

		if (g_Enemy[id].param.appear <= 0)
		{ // �o���^�C�~���O���Ԃɓ��B��
			g_Enemy[id].use = true;

			// �ǐՑΏۂƂȂ�v���C���[�����߂�
			g_Enemy[id].param.target = SetTargetEnemy(id);

			// �X�^�C���ԍ����ƍ�
			VerifyStyleEnemy(id);

			// �e�𐶐�
			g_Enemy[id].id_shadow = CreateShadow(&g_Enemy[id].pos, 40.0f);

#ifdef _DEBUG

			// ���̂Ƃ������蔻�������
			g_Enemy[id].id_sph = CreateVisibleSph(g_Enemy[id].param.rad, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_Enemy[id].pos);

#endif	// _DEBUG 
		}
	}
}

//************************************************
// �G�l�~�[��]
//************************************************
void RotateEnemy(int id)
{
	// �u���[�L��
	float StopEnergy = 0.1f;

	// ��]�u���[�L
	if (g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y > D3DX_PI)
	{
		g_Enemy[id].rot.y += ((g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y < -D3DX_PI)
	{
		g_Enemy[id].rot.y += ((g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_Enemy[id].rot.y += ((g_Enemy[id].rot_goal.y - g_Enemy[id].rot.y) * StopEnergy);
	}

	// �s�b�`����
	g_Enemy[id].rot.x += ((g_Enemy[id].rot_goal.x - g_Enemy[id].rot.x) * StopEnergy);
}

//************************************************
// �G�l�~�[�ړ�
//************************************************
void MoveEnemy(int id)
{
	if (g_Enemy[id].param.state != stateAtk_e &&
		g_Enemy[id].param.state != stateCharge_e &&
		g_Enemy[id].param.state != stateRotate_e &&
		g_Enemy[id].param.state != stateDamage_e &&
		g_Enemy[id].param.state != stateDead_e)
	{ // �U���F���߁F��]�F�����F���S��ԂłȂ����
		if (g_Enemy[id].param.style == Dragonfly)
		{ // �X�^�C���F��x

			Player* pPlayer = GetInfoPlayer();							// �v���C���[�ւ̃|�C���^
			int target = g_Enemy[id].param.target;						// �ǐՑΏۂ̎���
			D3DXVECTOR3 vec = pPlayer[target].pos - g_Enemy[id].pos;	// �ǐՑΏۂւ̃x�N�g��

			if (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z) < pPlayer[target].param.rad + 70.0f)
			{ // ���͈͓��ɋ߂Â��Ƌ����I�����U����Ԃ�
			
				g_Enemy[id].param.state = stateAtk_e;	// �U����Ԃ�
				g_Enemy[id].param.motion_now = 1;		// �U���̑���ɒʏ탂�[�V�������Đ�

				return; // �ȍ~�̏�����S�čs��Ȃ�
			}

			// �ړ��ʂ̕t�^
			if (g_Enemy[id].pos.y > 20.0f)
			{
				g_Enemy[id].move =
				{
					sinf(atan2f(vec.x, vec.z)),
					sinf(atan2f(vec.y, vec.z)),
					cosf(atan2f(vec.x, vec.z))
				};
			}
			else
			{
				g_Enemy[id].move =
				{
					sinf(atan2f(vec.x, vec.z)),
					-sinf(atan2f(vec.y, vec.z)),
					cosf(atan2f(vec.x, vec.z))
				};
			}

			// ������t�^	
			g_Enemy[id].rot_goal.y = atan2f(-vec.x, -vec.z);											// ���[
			g_Enemy[id].rot_goal.x = atan2f(-g_Enemy[id].pos.y, sqrtf(vec.x * vec.x + vec.z * vec.z));	// �s�b�`

			// �ړ��ʔ��f
			g_Enemy[id].pos += g_Enemy[id].move * g_Enemy[id].param.SPD * 2.5f; 

			g_Enemy[id].param.state = stateMove_e;	// �ړ���Ԃ�  
			g_Enemy[id].param.motion_now = 1;		// �ړ����[�V�������Đ�
		}
		else if (g_Enemy[id].param.style == Ant)
		{ // �X�^�C���F�a

		}
	}
}

//************************************************
// �G�l�~�[�U��
//************************************************
void AtkEnemy(int id)
{
	if (g_Enemy[id].param.state != stateAtk_e &&
		g_Enemy[id].param.state != stateCharge_e &&
		g_Enemy[id].param.state != stateRotate_e)
	{ // �U���F���ߏ�ԂŖ�����΃��^�[��
		return;
	}

	if (g_Enemy[id].param.style == Dragonfly)
	{ // �X�^�C���F��x

		if (g_Enemy[id].param.state == stateAtk_e)
		{ // �U����Ԃ̂Ƃ�

			g_Enemy[id].param.state = stateCharge_e;		// ���ߏ�ԂɑJ��
			g_Enemy[id].param.dur = 40;						// ����
		}
		else if (g_Enemy[id].param.state == stateCharge_e)
		{ // ���ߏ�Ԃ̎�

			if (g_Enemy[id].param.dur > 35)
			{
				Player* pPlayer = GetInfoPlayer();
				int target = g_Enemy[id].param.target;						// �ǐՑΏۂ̎���
				D3DXVECTOR3 vec = pPlayer[target].pos - g_Enemy[id].pos;	// �ǐՑΏۂւ̃x�N�g��

				// ���ʂȈړ��ʂ̕t�^
				g_Enemy[id].move =
				{
					-sinf(atan2f(vec.x, vec.z)),	
					0.75f,							// ����
					-cosf(atan2f(vec.x, vec.z))
				};

				// �ړ��ʂ𔽉f
				g_Enemy[id].pos += g_Enemy[id].move * 10.0f;	// �f����������

				// ���ʂȌ���
				g_Enemy[id].rot_goal.y -= 0.2f;	// ���[�F�����Ђ˂�
				g_Enemy[id].rot_goal.x = 0.0f;	// �s�b�`�F�ǂ����悤
			}

			if (CntDuration(&g_Enemy[id].param.dur))
			{ // ���ԏI����
				g_Enemy[id].param.state = stateRotate_e;	// ��]��ԂɑJ��
				g_Enemy[id].param.dur = 120;				// ����
			}
		}
		else if (g_Enemy[id].param.state == stateRotate_e)
		{ // ��]��Ԃ̂Ƃ�

			Player* pPlayer = GetInfoPlayer();							// �v���C���[�ւ̃|�C���^
			int target = g_Enemy[id].param.target;						// �ǐՑΏۂ̎���
			D3DXVECTOR3 vec = pPlayer[target].pos - g_Enemy[id].pos;	// �ǐՑΏۂւ̃x�N�g��

			// �ړ��ʂ̕t�^
			if (g_Enemy[id].pos.y > 20.0f)
			{
				g_Enemy[id].move =
				{
					sinf(atan2f(vec.x, vec.z)),
					sinf(atan2f(vec.y, vec.z)),
					cosf(atan2f(vec.x, vec.z))
				};
			}
			else
			{
				g_Enemy[id].move =
				{
					sinf(atan2f(vec.x, vec.z)),
					-sinf(atan2f(vec.y, vec.z)),
					cosf(atan2f(vec.x, vec.z))
				};
			}

			// ������t�^
			g_Enemy[id].rot_goal.y = atan2f(-vec.x, -vec.z);	// ���[
			g_Enemy[id].rot_goal.x = 0.0f;						// �s�b�`

			// �ړ��ʔ��f
			g_Enemy[id].pos += g_Enemy[id].move * g_Enemy[id].param.SPD * 2.5f;

			g_Enemy[id].param.motion_now = 0;	// �ʏ탂�[�V�������Đ�

			// ��]�𑱂���
			g_Enemy[id].rot.y += 1.0f;

			// �v���C���[�Ƃ̓����蔻��
			if (pPlayer[target].param.state != stateDamage_p &&
				CollisionSph(g_Enemy[id].pos, g_Enemy[id].param.rad, pPlayer[target].pos, pPlayer[target].param.rad))
			{
				// ��e�̏���
				HitPlayer(target);

				// ���ʂɃm�b�N�o�b�N��^����
				pPlayer[target].move.x = g_Enemy[id].move.x * g_Enemy[id].param.SPD * 80.0f;
				pPlayer[target].move.z = g_Enemy[id].move.z * g_Enemy[id].param.SPD * 80.0f;
			}

			if (CntDuration(&g_Enemy[id].param.dur))
			{ // ���ԏI����
				g_Enemy[id].param.state = stateNormal_e;	// �ʏ��ԂɑJ��
			}
		}
	}
	else if (g_Enemy[id].param.style == Ant)
	{ // �X�^�C���F�a

	}
}

//************************************************
// �G�l�~�[�̒ǐՑΏۂ����߂�
//************************************************
int SetTargetEnemy(int id)
{
	int target = -1;					// �ǐՑΏۂ̎��ʔԍ����i�[
	Player* pPlayer = GetInfoPlayer();	// �v���C���[�ւ̃|�C���^
	float dist[MAX_PLAYER] = {};		// �v���C���[�Ƃ̋���
	int max_dist = 0;					// �Z�o���������̑������i�[

	for (int i = 0; i < MAX_PLAYER; i++, max_dist++)
	{ // �S�Ẵv���C���[�Ƃ̋������Z�o

		if (!pPlayer[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		D3DXVECTOR3 vec = pPlayer[i].pos - g_Enemy[id].pos;
		dist[i] = sqrtf(vec.x * vec.x + vec.z * vec.z);
	}

	float min = FLT_MAX;	// ���������̍ő�l

	for (int i = 0; i < max_dist; i++)
	{ // �Z�o���������̒��ň�ԏ��������̂��Z�o

		if (min > dist[i])
		{ // ��萔�l���i�[���Ă�����̂ƌ���
			min = dist[i];
			target = i;	// ���̎��̎��ʔԍ����i�[
		}
	}

	return target;
}

//************************************************
// �G�l�~�[��e��
//************************************************
void HitEnemy(int id)
{
	g_Enemy[id].param.state = stateDamage_e;	// ������Ԃ�
	g_Enemy[id].param.motion_now = 1;			// �Ȃ񂩂̃��[�V����
	g_Enemy[id].param.dur = 45;					// �p�����Ԃ�t�^
	g_Enemy[id].param.HP--;
}

//************************************************
// �G�l�~�[����
//************************************************
void DamageEnemy(int id)
{
	if (g_Enemy[id].param.state != stateDamage_e)
	{ // ������ԂłȂ���ΏI��
		return;
	}

	/*---�y�ȉ�������Ԏ��̂݁z---*/

	// �_��
	g_Enemy[id].col.a *= -1.0f;

	if (g_Enemy[id].param.style == Dragonfly)
	{ // ��x�̂ݓ��ʂɈړ�
		g_Enemy[id].pos += g_Enemy[id].move;
		g_Enemy[id].pos.y += 1.0f;
		g_Enemy[id].rot.x += 0.05f;
	}

	if (CntDuration(&g_Enemy[id].param.dur))
	{
		g_Enemy[id].param.state = stateNormal_e;	// �ʏ��Ԃ�
		g_Enemy[id].param.motion_now = 0;			// �ʏ탂�[�V����
		g_Enemy[id].col.a = 1.0f;					// �ʏ�F��
	}
}

//************************************************
// �G�l�~�[���S
//************************************************
void DeadEnemy(int id)
{
	// ���S��Ԃ�t�^
	if (g_Enemy[id].param.state == stateDamage_e && g_Enemy[id].param.HP <= 0)
	{ // ������Ԃő̗͂������Ƃ��̂�
		g_Enemy[id].param.state = stateDead_e;	// ���S��Ԃ�
		g_Enemy[id].param.dur = 25;				// �p�����ԕt�^
		g_Enemy[id].param.motion_now = 2;		// ���S���[�V����
		g_Enemy[id].col.a = 0.5f;				// ��������
	}

	if (g_Enemy[id].param.state != stateDead_e)
	{ // ���S��ԂłȂ���ΏI��
		return;
	}

	/*---�y�ȉ����S��Ԏ��̂݁z---*/

	// �k��
	g_Enemy[id].size -= { 0.035f, 0.035f, 0.035f };

	if (CntDuration(&g_Enemy[id].param.dur))
	{
#ifdef _DEBUG

		// ��������̂ݎז��Ȃ̂ŏ���
		DeleteVisibleSph(g_Enemy[id].id_sph);

#endif	// _DEBUG

		// �e������
		DeleteShadow(g_Enemy[id].id_shadow);

		// ����
		DeleteEnemy(id);
	}
}

//************************************************
// �G�l�~�[����
//************************************************
void ResurrectEnemy(int id)
{
	if (g_Enemy[id].param.state == stateDead_e)
	{ // ���S��Ԃł����
		g_Enemy[id].param.state = stateNormal_e;
		g_Enemy[id].param.HP = 3;	//!< ���i�K�ł͓K���ɐݒ�
	}
}

//************************************************
// �G�l�~�[�̃��[�V�����Ǘ�
//************************************************
void MotionEnemy(int id)
{
	if (!g_Enemy[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	// �Đ����i�[�p
	int* pNow = &g_Enemy[id].param.motion_now;			// ���݂̃��[�V�������
	int* pOld = &g_Enemy[id].param.motion_old;			// �ߋ��̃��[�V�������
	EnemyMotion* pMotion = &g_Enemy[id].motion[*pNow];	// �e�G�l�~�[�̃��[�V�������

	// �ύX�����m
	ChangeMotionEnemy(id, pNow, pOld);

	// �p�[�c�̓���
	MoveMotionEnemy(id, pMotion);

	// �t���[���J�E���g
	if (g_Enemy[id].param.state != stateCharge_e)
	{ // ���ߏ�ԂłȂ��Ƃ��̂�
		CntMotionEnemy(id, pMotion);
	}
}

//************************************************
// �G�l�~�[�̃��[�V�����ύX���m
//************************************************
void ChangeMotionEnemy(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // �ߋ��ƌ��݂̍Đ����[�V�����������Ȃ烊�^�[��
		return;
	}

	// �ߋ��̃��[�V�����̃L�[�ƃt���[�������Z�b�g
	g_Enemy[id].motion[*pOld].id_key = 0;
	g_Enemy[id].motion[*pOld].id_frame = 0;

	// �V�������[�V�����ֈڂ������Ƃ�ۑ�
	*pOld = *pNow;
}

//************************************************
// �G�l�~�[�̃��[�V��������p
//************************************************
void MoveMotionEnemy(int id, EnemyMotion* pMotion)
{
	// �Đ����̃L�[�̑��t���[�������猻�݂̃t���[���ԍ�����������
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---�y�����I�ɁA�g�p����Ă���p�[�c�̐����z---*/
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		{ // �p�[�c�����g�p�Ȃ�R���e�B�j���[
		if (g_Enemy[id].parts[i].pMesh == NULL)
			continue;
		}

		g_Enemy[id].parts[i].pos_moved += (pMotion->key[pMotion->id_key].dest[i].pos - g_Enemy[id].parts[i].pos_moved) / dest;
		g_Enemy[id].parts[i].rot_moved += (pMotion->key[pMotion->id_key].dest[i].rot - g_Enemy[id].parts[i].rot_moved) / dest;
	}
}

//************************************************
// �G�l�~�[�̃��[�V�����J�E���g�p
//************************************************
void CntMotionEnemy(int id, EnemyMotion* pMotion)
{
	// �t���[���J�E���g
	pMotion->id_frame++;

	if (pMotion->id_frame >= pMotion->key[pMotion->id_key].amount_frame)
	{ // �Đ����̃L�[�̑��t���[�����o�߂�

		// �t���[���ԍ������Z�b�g��
		pMotion->id_frame = 0;

		// �L�[�J�E���g
		pMotion->id_key++;

		if (pMotion->id_key >= pMotion->amount_key)
		{ // �Đ����̃��[�V�����̑��L�[���o�߂�

			if (pMotion->loop == 1)
			{ // ���[�v�t���O���L��Ȃ�

				// �L�[�ԍ����Z�b�g�����^�[��
				pMotion->id_key = 0;
				return;
			}

			/*---�y����A�����I�ɑҋ@���[�V�����߂��z---*/
			g_Enemy[id].param.motion_now = 0;
		}
	}
}

//************************************************
// �G�l�~�[����
//************************************************
void DeleteEnemy(int id)
{
	Enemy* pEnemy = &g_Enemy[id];

	// �g�p�t���O
	pEnemy->use = false;

	// �p�����[�^
	pEnemy->param =
	{
		0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0		// �����o�[���̓w�b�_�t�@�C�����m�F���ĉ�����
	};

	// ���W�n
	pEnemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pEnemy->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �F
	pEnemy->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
	{ // �e�p�[�c�������Z�b�g
		EnemyModel* pModel = &pEnemy->parts[j];

		// ���f��
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int k = 0; k < AMOUNT_MAT; k++)
		{ // �}�e���A��
			pModel->pTex[k] = NULL;
		}

		// ���f�����W
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �e�C���f�b�N�X
		pModel->IdxParent = -1;
	}

	// ���莯�ʔԍ�
	pEnemy->id_sph = -1;
}

//************************************************
// �G�l�~�[�p�̃��[���h�}�g���b�N�X���v�Z
//************************************************
void CalcMtxEnemy(void)
{
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int enemy_id = 0; enemy_id < AMOUNT_ENEMY; enemy_id++)
	{
		if (!g_Enemy[enemy_id].use)
		{ // ���̔Ԃ̎g�p�t���O�������ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy[enemy_id].mtxWorld);

		if (g_Enemy[enemy_id].param.state == stateDead_e)
		{ // ���S���̂�

			// �傫���𔽉f1
			D3DXMatrixScaling(&mtxScale,
				1.0f + g_Enemy[enemy_id].size.x,
				1.0f + g_Enemy[enemy_id].size.y,
				1.0f + g_Enemy[enemy_id].size.z);

			// �傫���𔽉f2
			D3DXMatrixMultiply(&g_Enemy[enemy_id].mtxWorld,
				&g_Enemy[enemy_id].mtxWorld,
				&mtxScale);
		}

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Enemy[enemy_id].rot.y,
			g_Enemy[enemy_id].rot.x,
			g_Enemy[enemy_id].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_Enemy[enemy_id].mtxWorld,
			&g_Enemy[enemy_id].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Enemy[enemy_id].pos.x,
			g_Enemy[enemy_id].pos.y,
			g_Enemy[enemy_id].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Enemy[enemy_id].mtxWorld,
			&g_Enemy[enemy_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_ENEMY_PARTS; Ps_id++)
		{
			if (g_Enemy[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // ����ۂȂ�R���e�B�j���[
				continue;
			}

			// ���̔ԃp�[�c�́u�e�p�[�c�v�̃C���f�b�N�X��ۑ�
			int IdxParent = g_Enemy[enemy_id].parts[Ps_id].IdxParent;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[enemy_id].parts[Ps_id].mtxWorld);

			// ���[�V���������̔��f
			D3DXVECTOR3 PartsRot =
			{
				g_Enemy[enemy_id].parts[Ps_id].rot_offset.x + g_Enemy[enemy_id].parts[Ps_id].rot_moved.x,
				g_Enemy[enemy_id].parts[Ps_id].rot_offset.y + g_Enemy[enemy_id].parts[Ps_id].rot_moved.y,
				g_Enemy[enemy_id].parts[Ps_id].rot_offset.z + g_Enemy[enemy_id].parts[Ps_id].rot_moved.z
			};

			// �����𔽉f1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// �����𔽉f2
			D3DXMatrixMultiply(&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// ���[�V�����ʒu�̔��f
			D3DXVECTOR3 PartsPos =
			{
				g_Enemy[enemy_id].parts[Ps_id].pos_offset.x + g_Enemy[enemy_id].parts[Ps_id].pos_moved.x,
				g_Enemy[enemy_id].parts[Ps_id].pos_offset.y + g_Enemy[enemy_id].parts[Ps_id].pos_moved.y,
				g_Enemy[enemy_id].parts[Ps_id].pos_offset.z + g_Enemy[enemy_id].parts[Ps_id].pos_moved.z
			};

			// �ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// �ʒu�𔽉f
			D3DXMatrixMultiply(&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// �e�̃��[���h�}�g���b�N�X���擾
			if (IdxParent == -1)
			{ //���C���p�[�c�̂݃��[���h���W�ɒ���
				mtxParent = g_Enemy[enemy_id].mtxWorld;
			}
			else
			{ //���̑��p�[�c�͂��ꂼ��̐e�p�[�c�֕t��
				mtxParent = g_Enemy[enemy_id].parts[IdxParent].mtxWorld;
			}

			// �p�[�c���Ƃ̃��[���h�}�g���b�N�X���Z�o
			D3DXMatrixMultiply(&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&g_Enemy[enemy_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}
	}
}

//************************************************
// �G�l�~�[�`��
//************************************************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int id_enemy = 0; id_enemy < AMOUNT_ENEMY; id_enemy++)
	{
		if (!g_Enemy[id_enemy].use)
		{ // ���̔Ԃ̎g�p�t���O�������ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[id_enemy].mtxWorld);

		for (int id_Ps = 0; id_Ps < AMOUNT_ENEMY_PARTS; id_Ps++)
		{
			if (g_Enemy[id_enemy].parts[id_Ps].pMesh == NULL)
			{ // �p�[�c�����g�p�Ȃ�R���e�B�j���[
				continue;
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[id_enemy].parts[id_Ps].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Enemy[id_enemy].parts[id_Ps].pBuffMat->GetBufferPointer();

			for (int id_mat = 0; id_mat < (int)g_Enemy[id_enemy].parts[id_Ps].NumMat; id_mat++)
			{
				// �J���[A�l���f
				pMat[id_mat].MatD3D.Diffuse.a = g_Enemy[id_enemy].col.a;

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[id_mat].MatD3D);

				// �e�N�X�`���̐ݒ�
				if (g_Enemy[id_enemy].parts[id_Ps].pTex[id_mat] != NULL)
				{
					pDevice->SetTexture(0, g_Enemy[id_enemy].parts[id_Ps].pTex[id_mat]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// ���f���p�[�c�̕`��
				g_Enemy[id_enemy].parts[id_Ps].pMesh->DrawSubset(id_mat);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//************************************************
// �G�l�~�[�����擾
//************************************************
Enemy* GetInfoEnemy(void)
{
	return &g_Enemy[0];
}