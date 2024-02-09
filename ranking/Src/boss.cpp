//************************************************
//
// �{�X����[boss.cpp]
// Author�F�����h��
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "boss.h"
#include "collision.h"
#include "player.h"
#include "visible_sph.h"
// ����
#include "game.h"
#include "input.h"
#include "sound.h"

#include <stdlib.h>
#include <time.h>

// ������
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif	// _DEBUG

/*/ �O���[�o���ϐ� /*/
BOSSModel g_BossModel[AMOUNT_BOSS_PARTS];	// �{�X�p���f�����̂ЂȌ`
BossMotion g_BossMotion[NUM_MOTION];		// �{�X���[�V�������̂ЂȌ`
BOSS g_aBoss[MAX_BOSS];						// �{�X���
int g_nCntStop = 0;							// �����Ȃ������鎞��
D3DXVECTOR3 g_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�{�X�̈ړ���


//************************************************
// �{�X����
//************************************************
void InitBoss(void)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{ // �{�X�p���f�����̂ЂȌ`�̃��Z�b�g
		BOSSModel* pModel = &g_BossModel[i];

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
		pModel->pos_offset = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �e�C���f�b�N�X
		pModel->IdxParent = -1;
	}

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_BOSS; i++)
	{ // �{�X���̃��Z�b�g
		BOSS* pBoss = &g_aBoss[i];

		// �g�p�t���O
		pBoss->use = false;

		// �p�����[�^
		pBoss->Param.style = 0;								//�ԍ�
		pBoss->Param.state = stateNormal_b;					//���
		pBoss->Param.dur = 0;								//HP���Ȃ��Ȃ��Ă���`�悳��Ȃ��Ȃ�܂ł̎���
		pBoss->Param.HP = 0;								//���C�t
		pBoss->Param.SPD = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ړ���
		pBoss->Param.Radius = 0.0f;							//�����蔻��̔��a
		pBoss->Param.motion_now = 0;						//���Đ����̃��[�V����
		pBoss->Param.motion_old = 0;						//1�O�ɍĐ�����Ă������[�V����
		//pBoss->Param.bMove = true;							//�ړ����Ă��邩�ǂ���

		// ���W
		pBoss->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �F
		pBoss->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		// ���莯�ʔԍ�
		pBoss->id_sph = -1;


		for (int j = 0; j < AMOUNT_BOSS_PARTS; j++)
		{ // �e�p�[�c�������Z�b�g
			BOSSModel* pModel = &pBoss->parts[j];

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
	}

	/*--------------------------------------------*/

	// �{�X�p�̃��f�������擾
	ImportModelBoss();

	// �{�X�p�̃��[�V���������擾
	ImportMotionBoss();

	// �{�X�p�̃p�����[�^�����擾
	ImportParamBoss();

	/*---�y���[�V���������R�s�[(�C���\��)�z---*/
	for (int i = 0; i < MAX_BOSS; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (g_BossMotion[j].amount_key == 0)
			{ // ���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			// ���[�V���������R�s�[
			g_aBoss[i].motion[j] = g_BossMotion[j];
		}

		g_aBoss[i].Param.bMove = true;	//�ړ����Ă��邩�ǂ���

	}
	//�O���[�o���ϐ��̏�����
	g_nCntStop = 0;	//�G�̃X�^������
	g_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[�J���ϐ��錾
	D3DXVECTOR3 KeepMove = D3DXVECTOR3(0.0f,0.0f,0.0f);
	float fNumberx = 0.0f;
	float fNumberz = 0.0f;
	float fKeepNumx = 0.0f;
	float fKeepNumz = 0.0f;

	//�G�̋����̎Z�o
	srand((unsigned int)time(NULL));
	fNumberx = rand() % 50 + 1;
	fNumberz = rand() % 50 + 1;

	fKeepNumx = fNumberx / 10;
	fKeepNumz = fNumberz / 10;

	KeepMove = D3DXVECTOR3(fKeepNumx / 10, 0.0f, fKeepNumz / 10);

	g_Move = D3DXVECTOR3(KeepMove.x, KeepMove.y, KeepMove.z);


	
	/******************************/

	/*---�y�����I�ɓG��z�u(�����\��)�z---*/

	//DEBUG_GenerateEnemy();

	/******************************/
}

//************************************************
// ���f������ǂݍ���
//************************************************
void ImportModelBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int AmountModel = 0;		// ���f���̐����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�{�X���f�����̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &AmountModel);
		}

#ifdef _DEBUG

		// �G���[
		assert(AmountModel < AMOUNT_BOSS_PARTS && "�{�X���f�����f����񂪍ő�ʂ��z���܂���");

#endif

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%s", &FileString[0], 128);

			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_BossModel[id_Model].pBuffMat,
				NULL,
				&g_BossModel[id_Model].NumMat,
				&g_BossModel[id_Model].pMesh);

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}

	// �e���f���̃I�t�Z�b�g�����擾
	ImportOffsetBoss(pFile, AmountModel);

	// �e���f���̃e�N�X�`�������擾
	ImportTexBoss(AmountModel);

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// ���f���I�t�Z�b�g����ǂݍ���
//************************************************
void ImportOffsetBoss(FILE* pFile, int AmountModel)
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
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &Style);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // �e�̃C���f�b�N�X���擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu�̃I�t�Z�b�g���擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �����̃I�t�Z�b�g���擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			g_BossModel[id_Model].style = Style;
			g_BossModel[id_Model].IdxParent = IdxParent;
			g_BossModel[id_Model].pos_offset = pos;
			g_BossModel[id_Model].rot_offset = rot;

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
void ImportTexBoss(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < AmountModel; i++)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_BossModel[i].pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int j = 0; j < (int)g_BossModel[i].NumMat; j++)
		{
			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_BossModel[i].pTex[j]);
			}
			else
			{
				g_BossModel[i].pTex[j] = NULL;
			}
		}
	}
}

//************************************************
// �G�̃p�����[�^���̓Ǎ���
//************************************************
void ImportParamBoss(void)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};		// ���͂��i�[
	int i = 0;						// �ėp����
	int appear = 0;					// �o���^�C�~���O���i�[
	int style = 0;					// �X�^�C�����i�[
	float hp = 0.0f;				// ���C�t���i�[
	float radius = 0.0f;			// ���a���i�[(�����蔻��p)
	//float spd = 0;				// ���x���i�[
	D3DXVECTOR3 pos, rot, spd;		// �ʒu�ƌ������i�[

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_param.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�{�X�p�����[�^���̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (i >= MAX_BOSS)
		{ // �G�̍ő吔���z����Ƌ����I��
			break;
		}

		if (strcmp(&FileString[0], "APPEAR") == 0)
		{ // �o���^�C�~���O���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 64, &appear);
		}

		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // �X�^�C�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 64, &style);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // ���C�t���擾
			fscanf_s(pFile, "%s %f", &FileString[0], 64, &hp);
		}

		if (strcmp(&FileString[0], "SPD") == 0)
		{ // ���x���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &spd.x,&spd.y,&spd.z);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �������擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "RADIUS") == 0)
		{ // �������擾
			fscanf_s(pFile, "%s %f", &FileString[0], 64, &radius);
		}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // �擾�������𔽉f
			g_aBoss[i].Param =
			{
				appear, style, 0, 0, hp,spd,radius
			};

			g_aBoss[i].pos = pos;
			g_aBoss[i].rot = rot;

			i++;	// ���̔ԍ���
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{
			break;	// �I��
		}
	}
}

////************************************************
//// �G�̏o���ݒ�
////************************************************
//void DEBUG_GenerateEnemy(void)
//{
//	/*---�y���݁A�����I�ɓG�̏��ݒ�(�C���\��)�z---*/
//	for (int i = 0; i < MAX_BOSS; i++)
//	{
//		// �p�����[�^
//		g_aBoss[i].Param.style = 0;
//		g_aBoss[i].Param.SPD = 0.1f + i * 0.1f;
//
//		g_aBoss[i].use = true;
//		g_aBoss[i].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
//
//		// �X�^�C���ԍ����ƍ�
//		VerifyStyleBOSS(i);
//
//		break;	// 1�̂̂�
//	}
//}

//************************************************
// �X�^�C���ԍ��̏ƍ�
//************************************************
void VerifyStyleBoss(int id)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		if (g_aBoss[id].Param.style == g_BossModel[i].style)
		{ // �e�{�X�̃X�^�C���ƑS�p�[�c�̃X�^�C�����ƍ�
			g_aBoss[id].parts[i] = g_BossModel[i];	//!< �ԍ��̈�v���Ă���p�[�c�̂ݗL����
		}
	}
}

//************************************************
// ���[�V��������ǂݍ���
//************************************************
void ImportMotionBoss(void)
{
	 //�t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int i = 0, j = 0, k = 0;	// �ėp����
	int Loop = 0;				// ���[�v�t���O���i�[
	int AmountKey = 0;			// ���L�[�����擾
	int AmountFrame = 0;		// ���t���[�������擾
	D3DXVECTOR3 pos, rot;		// �ʒu�ƌ������i�[

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_motion.txt", "r") != 0)
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
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &Loop);
		}

		if (strcmp(&FileString[0], "NUM_KEY") == 0)
		{ // ���L�[�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountKey);
		}

		if (strcmp(&FileString[0], "FRAME") == 0)
		{ // �t���[�������擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountFrame);
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
			g_BossMotion[i].key[j].dest[k].pos = pos;
			g_BossMotion[i].key[j].dest[k].rot = rot;

			k++;	// �p�[�c�ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // �L�[����ۑ�
			g_BossMotion[i].key[j].amount_frame = AmountFrame;

			k = 0;	// �p�[�c�ԍ������Z�b�g
			j++;	// �L�[�ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // ���[�V��������ۑ�
			g_BossMotion[i].loop = Loop;
			g_BossMotion[i].amount_key = AmountKey;

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
// �{�X�j��
//************************************************
void UninitBoss(void)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_BossModel[i].pTex[j] != NULL)
			{ // �e�N�X�`���̔j��
				g_BossModel[i].pTex[j]->Release();
				g_BossModel[i].pTex[j] = NULL;
			}
		}

		if (g_BossModel[i].pMesh != NULL)
		{ // ���b�V���̔j��
			g_BossModel[i].pMesh->Release();
			g_BossModel[i].pMesh = NULL;
		}

		if (g_BossModel[i].pBuffMat != NULL)
		{ // �}�e���A���̔j��
			g_BossModel[i].pBuffMat->Release();
			g_BossModel[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// �{�X�X�V
//************************************************
void UpdateBoss(void)
{
	for (int i = 0; i < MAX_BOSS; i++)
	{
		// �o��
		AppearBoss(i);

		// �ߋ��̈ʒu���L�^
		g_aBoss[i].pos_old = g_aBoss[i].pos;

		// ��]
		RotateBoss(i);

		//�ړ�
		MoveBoss(i);

		//��e
		DamageBoss(i);

		//���S
		DeadBoss(i);

		// ���[�V����
		MotionBoss(i);

	}

	// �Ō�ɍs��v�Z
	CalcMtxBoss();
#ifdef _DEBUG

	PrintDebugProc("�{�X�̍��W : %f %f %f\n", g_aBoss[0].pos.x, g_aBoss[0].pos.y, g_aBoss[0].pos.z);
	PrintDebugProc("�{�X�̌��� : %f %f %f\n", g_aBoss[0].rot.x, g_aBoss[0].rot.y, g_aBoss[0].rot.z);
#endif

#ifdef _DEBUG

	for (int i = 0; i < 1; i++)
	{
		BOSS* pBoss = &g_aBoss[i];
		char pStr[8];

		switch (pBoss->Param.state)
		{
		case stateNormal_b:
			snprintf(&pStr[0], 8, "�ʏ�");
			break;

		case stateMove_b:
			snprintf(&pStr[0], 8, "�ړ�");
			break;

		case stateAtk_b:
			snprintf(&pStr[0], 8, "�U��");
			break;

		case stateDamage_b:
			snprintf(&pStr[0], 8, "��e");
			break;

		case stateDead_b:
			snprintf(&pStr[0], 8, "���S");
			break;

		default:

			// �G���[
			assert(false && "�����ꂩ�̃G�l�~�[��ԂɃG���[");

			break;
		}

		PrintDebugProc("�y%dB�z\nstate : %s\n", i + 1, &pStr[0]);	// �X�e�[�^�X
		PrintDebugProc("HP : %f\n", pBoss->Param.HP);				// ���C�t
		PrintDebugProc("SPD : %f\n", pBoss->Param.SPD);				// ���x
	}
#endif
}

//************************************************
// �{�X�o��
//************************************************
void AppearBoss(int id)
{
	if (g_aBoss[id].Param.appear > 0)
	{ // �o���^�C�~���O���ݒ肳��Ă����
		g_aBoss[id].Param.appear--;

		if (g_aBoss[id].Param.appear <= 0)
		{ // �o���^�C�~���O���Ԃɓ��B��
			g_aBoss[id].use = true;

			// �X�^�C���ԍ����ƍ�
			VerifyStyleBoss(id);
#ifdef _DEBUG
			// ���̂Ƃ������蔻�������
			g_aBoss[id].id_sph = CreateVisibleSph(g_aBoss[id].Param.Radius, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_aBoss[id].pos);
#endif
		}
	}
}

//************************************************
// �{�X��]
//************************************************
void RotateBoss(int id)
{
	// �u���[�L��
	float StopEnergy = 0.1f;

	// ��]�u���[�L
	if (g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y > D3DX_PI)
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y < -D3DX_PI)
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy);
	}
}

//************************************************
// �{�X�ړ�
//************************************************
void MoveBoss(int id)
{
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{

		switch (g_aBoss[nCntBoss].Param.style)
		{
		case 0:
			MidBossBehavior(nCntBoss);	//���{�X�̋���
			break;
		case 1:
			BigBossBehavior(nCntBoss);	//��{�X�̋���
			break;
		default:
			break;
		}
	}
}

//************************************************
// ���{�X�̋���
//************************************************
void MidBossBehavior(int id)
{
	if (g_aBoss[id].use && g_aBoss[id].Param.state != stateDamage_b && g_aBoss[id].Param.state != stateDead_b)
	{
		g_aBoss[id].Param.state = stateMove_b;		// �ړ����

		//���������߂�
		g_aBoss[id].rot_goal.y = atan2f(-g_aBoss[id].Param.SPD.x - g_Move.x , -g_aBoss[id].Param.SPD.z - g_Move.z);

		if (g_aBoss[id].Param.bMove)
		{
			//�ʒu�𓮂���
			g_aBoss[id].pos += g_Move + g_aBoss[id].Param.SPD;
		}

	}

}

//************************************************
// ��{�X�̋���
//************************************************
void BigBossBehavior(int id)
{

}

//************************************************
// �{�X�̓����蔻��
//************************************************
void HitBoss(int id)
{
	g_aBoss[id].Param.state = stateDamage_b;	// ������Ԃ�
	g_aBoss[id].Param.dur = 20;				// �p�����Ԃ�t�^
	g_aBoss[id].Param.HP--;						// HP�����炷

}

//************************************************
// �{�X�̕�������
//************************************************
void DamageBoss(int id)
{
	if (g_aBoss[id].Param.state != stateDamage_b)
	{ // ������ԂłȂ���ΏI��
		return;
	}

	/*---�y�ȉ�������Ԏ��̂݁z---*/

	// �_��
	g_aBoss[id].col.a *= -1.0f;


	if (CntDuration(&g_aBoss[id].Param.dur))
	{
		g_aBoss[id].Param.state = stateNormal_b;	// �ʏ��Ԃ�
		g_aBoss[id].col.a = 1.0f;					// �ʏ�F��

			//���[�J���ϐ��錾
		D3DXVECTOR3 KeepMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float fNumberx = 0.0f;
		float fNumberz = 0.0f;
		float fKeepNumx = 0.0f;
		float fKeepNumz = 0.0f;

		//�G�̋����̎Z�o
		srand((unsigned int)time(NULL));
		fNumberx = rand() % 50 + 1;
		fNumberz = rand() % 50 + 1;

		fKeepNumx = fNumberx / 10;
		fKeepNumz = fNumberz / 10;

		KeepMove = D3DXVECTOR3(fKeepNumx / 10, 0.0f, fKeepNumz / 10);

		g_Move = D3DXVECTOR3(KeepMove.x, KeepMove.y, KeepMove.z);

	}

}

//************************************************
// �{�X�̎��S����
//************************************************
void DeadBoss(int id)
{
	if (g_aBoss[id].Param.state == stateDamage_b && g_aBoss[id].Param.HP <= 0.0f)
	{ // ������Ԃő̗͂������Ƃ��̂�
		g_aBoss[id].Param.state = stateDead_b;	// ���S��Ԃ�
		g_aBoss[id].Param.dur = 180;			// �p�����ԕt�^
		g_aBoss[id].col.a = 0.5f;				// ��������
	}


	if (g_aBoss[id].Param.state != stateDead_b)
	{ // ���S��ԂłȂ���ΏI��
		return;
	}

	/*---�y�ȉ����S��Ԏ��̂݁z---*/

	if (CntDuration(&g_aBoss[id].Param.dur))
	{
		/*---�y�����Ɍ��ꂸ�A�������̗\������邽�߂���Łz---*/
		g_aBoss[id].use = false;	// �g�p�t���O

#ifdef _DEBUG

		// ��������̂ݎז��Ȃ̂ŏ���
		DeleteVisibleSph(g_aBoss[id].id_sph);

#endif	// _DEBUG

		g_aBoss[id].id_sph = -1;	// ��ڂ��I�������l�����Z�b�g
	}
}



//************************************************
// �{�X�̕�������
//************************************************
void ResurrectBoss(int id)
{
	if (g_aBoss[id].Param.state == stateDead_b)
	{ // ���S��Ԃł����
		g_aBoss[id].Param.state = stateNormal_b;
		g_aBoss[id].Param.HP = 3;	//!< ���i�K�ł͓K���ɐݒ�
	}				

}

//************************************************
// ���[�V�����Ǘ�����
//************************************************
void MotionBoss(int id)
{
	if (!g_aBoss[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	// �Đ����i�[�p
	int* pNow = &g_aBoss[id].Param.motion_now;			// ���݂̃��[�V�������
	int* pOld = &g_aBoss[id].Param.motion_old;			// �ߋ��̃��[�V�������
	BossMotion* pMotion = &g_aBoss[id].motion[*pNow];	// �e�G�l�~�[�̃��[�V�������

	switch (g_aBoss[id].Param.state)
	{
	case stateNormal_b:
		g_aBoss[id].Param.motion_now = motion_neutral;		//�j���[�g�������[�V����
		break;
	case stateMove_b:
		g_aBoss[id].Param.motion_now = motion_move;			//�ړ����[�V����
		break;
	case stateAtk_b:
		g_aBoss[id].Param.motion_now = motion_action;		//�U�����[�V����
		break;
	case stateDamage_b:
		g_aBoss[id].Param.motion_now = motion_neutral;		//��e���[�V����
		break;
	case stateDead_b:
		g_aBoss[id].Param.motion_now = motion_collapse;		//���S���[�V����
		break;
	case steteResurrect_b:
		g_aBoss[id].Param.motion_now = motion_Resurrect;	//�������[�V����
		break;

	}

	// �ύX�����m
	ChangeMotionBoss(id, pNow, pOld);

	// �p�[�c�̓���
	MoveMotionBoss(id, pMotion);

	// �t���[���J�E���g
	CntMotionBoss(id, pMotion);

}

//************************************************
// ���[�V�����ύX����
//************************************************
void ChangeMotionBoss(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // �ߋ��ƌ��݂̍Đ����[�V�����������Ȃ烊�^�[��
		return;
	}

	// �ߋ��̃��[�V�����̃L�[�ƃt���[�������Z�b�g
	g_aBoss[id].motion[*pOld].id_key = 0;
	g_aBoss[id].motion[*pOld].id_frame = 0;

	// �V�������[�V�����ֈڂ������Ƃ�ۑ�
	*pOld = *pNow;

}

//************************************************
// ���[�V�������쏈��
//************************************************
void MoveMotionBoss(int id, BossMotion* pMotion)
{
	// �Đ����̃L�[�̑��t���[�������猻�݂̃t���[���ԍ�����������
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---�y�����I�ɁA�g�p����Ă���p�[�c�̐����z---*/
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		{ // �p�[�c�����g�p�Ȃ�R���e�B�j���[
			if (g_aBoss[id].parts[i].pMesh == NULL)
				continue;
		}

		g_aBoss[id].parts[i].pos_moved += (pMotion->key[pMotion->id_key].dest[i].pos - g_aBoss[id].parts[i].pos_moved) / dest;
		g_aBoss[id].parts[i].rot_moved += (pMotion->key[pMotion->id_key].dest[i].rot - g_aBoss[id].parts[i].rot_moved) / dest;
	}

}

//************************************************
// ���[�V�����J�E���g�p
//************************************************
void CntMotionBoss(int id, BossMotion* pMotion)
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
			g_aBoss[id].Param.motion_now = 0;
		}
	}

}

//************************************************
// �{�X�p�̃��[���h�}�g���b�N�X���v�Z
//************************************************
void CalcMtxBoss(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int enemy_id = 0; enemy_id < MAX_BOSS; enemy_id++)
	{
		if (!g_aBoss[enemy_id].use)
		{ // ���̔Ԃ̎g�p�t���O�������ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBoss[enemy_id].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aBoss[enemy_id].rot.y,
			g_aBoss[enemy_id].rot.x,
			g_aBoss[enemy_id].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_aBoss[enemy_id].mtxWorld,
			&g_aBoss[enemy_id].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aBoss[enemy_id].pos.x,
			g_aBoss[enemy_id].pos.y,
			g_aBoss[enemy_id].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aBoss[enemy_id].mtxWorld,
			&g_aBoss[enemy_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_BOSS_PARTS; Ps_id++)
		{
			if (g_aBoss[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // ����ۂȂ�R���e�B�j���[
				continue;
			}

			// ���̔ԃp�[�c�́u�e�p�[�c�v�̃C���f�b�N�X��ۑ�
			int IdxParent = g_aBoss[enemy_id].parts[Ps_id].IdxParent;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld);

			// ���[�V���������̔��f
			D3DXVECTOR3 PartsRot =
			{
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.x + g_aBoss[enemy_id].parts[Ps_id].rot_moved.x,
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.y + g_aBoss[enemy_id].parts[Ps_id].rot_moved.y,
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.z + g_aBoss[enemy_id].parts[Ps_id].rot_moved.z
			};

			// �����𔽉f1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// �����𔽉f2
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// ���[�V�����ʒu�̔��f
			D3DXVECTOR3 PartsPos =
			{
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.x + g_aBoss[enemy_id].parts[Ps_id].pos_moved.x,
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.y + g_aBoss[enemy_id].parts[Ps_id].pos_moved.y,
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.z + g_aBoss[enemy_id].parts[Ps_id].pos_moved.z
			};

			// �ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// �ʒu�𔽉f
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// �e�̃��[���h�}�g���b�N�X���擾
			if (IdxParent == -1)
			{ //���C���p�[�c�̂݃��[���h���W�ɒ���
				mtxParent = g_aBoss[enemy_id].mtxWorld;
			}
			else
			{ //���̑��p�[�c�͂��ꂼ��̐e�p�[�c�֕t��
				mtxParent = g_aBoss[enemy_id].parts[IdxParent].mtxWorld;
			}

			// �p�[�c���Ƃ̃��[���h�}�g���b�N�X���Z�o
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}
	}
}

//************************************************
// �{�X�`��
//************************************************
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int enemy_id = 0; enemy_id < MAX_BOSS; enemy_id++)
	{
		if (!g_aBoss[enemy_id].use)
		{ // ���̔Ԃ̎g�p�t���O�������ŃR���e�B�j���[
			continue;
		}
		 
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[enemy_id].mtxWorld);

		for (int Ps_id = 0; Ps_id < AMOUNT_BOSS_PARTS; Ps_id++)
		{
			if (g_aBoss[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // ����ۂȂ�R���e�B�j���[
				continue;
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[enemy_id].parts[Ps_id].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aBoss[enemy_id].parts[Ps_id].pBuffMat->GetBufferPointer();

			for (int mat_id = 0; mat_id < (int)g_aBoss[enemy_id].parts[Ps_id].NumMat; mat_id++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[mat_id].MatD3D);

				// �e�N�X�`���̐ݒ�
				if (g_aBoss[enemy_id].parts[Ps_id].pTex[mat_id] != NULL)
				{
					pDevice->SetTexture(0, g_aBoss[enemy_id].parts[Ps_id].pTex[mat_id]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// ���f���p�[�c�̕`��
				g_aBoss[enemy_id].parts[Ps_id].pMesh->DrawSubset(mat_id);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}

	}
}

//************************************************
// �{�X�����擾
//************************************************
BOSS* GetInfoBoss(void)
{
	return g_aBoss;
}	

