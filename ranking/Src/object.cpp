//************************************************
//
// �I�u�W�F�N�g[object.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "object.h"
// ������
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"
#include "input.h"
#include <assert.h>
#endif	// _DEBUG

/*/ �O���[�o���ϐ� /*/
ObjectModel g_ObjectModel[AMOUNT_MODEL_OBJECT];	// �I�u�W�F�N�g���f�����̂ЂȌ`
Object g_Object[AMOUNT_OBJECT];					// �I�u�W�F�N�g���
Object g_PreObject;								// ���z�̃I�u�W�F�N�g���
Object g_GizmoObject;							// �M�Y�����f���p
int g_MaxModel = 0;								// ���f������ސ��i�[
int g_MaxObject = 0;							// �������f�������i�[
bool g_TrackAA = true;							// �ړ����[�h����
bool g_Overwrite = false;						// �ҏW���[�h����
int g_obj_id = 0;								// �I�����Ă�������I�u�W�F�N�g����

//************************************************
// �I�u�W�F�N�g����
//************************************************
void InitObject(void)
{
	g_MaxModel = 0;			// ���f������ސ����Z�b�g
	g_MaxObject = 0;		// �������f�������Z�b�g
	g_TrackAA = true;		// �ړ����[�h�F���s
	g_Overwrite = false;	// �ҏW���[�h�F�ʏ�
	g_obj_id = 0;

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{ // �I�u�W�F�N�g�p���f�����̂ЂȌ`�̃��Z�b�g
		g_ObjectModel[i].pMesh = NULL;
		g_ObjectModel[i].pBuffMat = NULL;
		g_ObjectModel[i].NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �e�N�X�`���̏��̃��Z�b�g
			g_ObjectModel[i].pTex[j] = NULL;
		}
	}

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{ // �I�u�W�F�N�g�̏��̃��Z�b�g
		g_Object[i].type = 0;
		g_Object[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[i].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[i].aabb = {};
		g_Object[i].model.pMesh = NULL;
		g_Object[i].model.pBuffMat = NULL;
		g_Object[i].model.NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �e�N�X�`�����̃��Z�b�g
			g_ObjectModel[i].pTex[j] = NULL;
		}
		g_Object[i].nIdxShadow = 0;	//!< ���ݖ��g�p
	}

#ifdef _DEBUG

	// ���z�̃I�u�W�F�N�g�̏��̃��Z�b�g
	InitPreObject();

	// �M�Y���������Z�b�g
	InitGizmoObject();

#endif // _DEBUG

	// �I�u�W�F�N�g�p�̃��f�������擾
	ImportModelObject();	//!< �֐����Ăԏ��Ԃ����d�v

#ifdef _DEBUG

	g_PreObject.model = g_ObjectModel[0];	//!< ���z�̃I�u�W�F�N�g���Ƀ��f������1�Z�b�g(�`��G���[���)

#endif // _DEBUG
}

//************************************************
// ���z�̃I�u�W�F�N�g����
//************************************************
void InitPreObject(void)
{
	// ���z�̃I�u�W�F�N�g�̏��̃��Z�b�g
	g_PreObject.type = 0;
	g_PreObject.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PreObject.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PreObject.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PreObject.aabb = {};
	g_PreObject.model.pMesh = NULL;
	g_PreObject.model.pBuffMat = NULL;
	g_PreObject.model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // �e�N�X�`���������Z�b�g
		g_PreObject.model.pTex[i] = NULL;
	}
	g_PreObject.nIdxShadow = 0;	//!< ���ݖ��g�p
}

//************************************************
// �M�Y������
//************************************************
void InitGizmoObject(void)
{
	// �M�Y�����̃��Z�b�g
	g_GizmoObject.type = 0;
	g_GizmoObject.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_GizmoObject.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_GizmoObject.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_GizmoObject.aabb = {};
	g_GizmoObject.model.pMesh = NULL;
	g_GizmoObject.model.pBuffMat = NULL;
	g_GizmoObject.model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // �e�N�X�`���������Z�b�g
		g_GizmoObject.model.pTex[i] = NULL;
	}
	g_GizmoObject.nIdxShadow = 0;	//!< ���ݖ��g�p
}

//************************************************
// �I�u�W�F�N�g���f������ǂݍ���
//************************************************
void ImportModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int id_Model = 0;			// ���f���̎��ʗp

	/*--------------------------------------------*/

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_import.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�I�u�W�F�N�g���f�����̓W�J�Ɏ��s");

#endif	// _DEBUG
	}

	/*--------------------------------------------*/

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &g_MaxModel);
		}

#ifdef _DEBUG

		// �G���[
		assert(g_MaxModel < AMOUNT_MODEL_OBJECT && "�I�u�W�F�N�g���f����񂪍ő�ʂ��z���܂���");

#endif	// _DEBUG

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
				&g_ObjectModel[id_Model].pBuffMat,
				NULL,
				&g_ObjectModel[id_Model].NumMat,
				&g_ObjectModel[id_Model].pMesh);

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == g_MaxModel)
			{ // �����f����ސ����ǂݎ��I���ƏI��
				break;
			}
		}
	}

	/*--------------------------------------------*/

	// �e���f���̃e�N�X�`�������擾
	ImportTexObject();

	// �e���f���̔z�u�����擾
	ImportLayoutObject(pFile);

	// �t�@�C�������
	fclose(pFile);

#ifdef _DEBUG

	// �M�Y�����f����ǂݍ���
	ImportGizmoModelObject();

#endif
}

//************************************************
// �M�Y�����f������ǂݍ���
//************************************************
void ImportGizmoModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXLoadMeshFromX("data\\MODEL\\OBJECT\\Gizmo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_GizmoObject.model.pBuffMat,
		NULL,
		&g_GizmoObject.model.NumMat,
		&g_GizmoObject.model.pMesh);
}

//************************************************
// ���f���e�N�X�`������ǂݍ���
//************************************************
void ImportTexObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < g_MaxModel; i++)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_ObjectModel[i].pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int j = 0; j < (int)g_ObjectModel[i].NumMat; j++)
		{
			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_ObjectModel[i].pTex[j]);
			}
			else
			{
				g_ObjectModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// ���f���z�u����ǂݍ���
//************************************************
void ImportLayoutObject(FILE* pFile)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	char FileString[128] = {};	// ���͂��i�[
	int Type = -1;				// ���f���̎�ފi�[
	D3DXVECTOR3 pos = {};		// �ʒu���i�[
	D3DXVECTOR3 rot = {};		// �����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "TYPE") == 0)
		{ // ���̃��f���̎�ނ��擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &Type);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu���擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �������擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);

			// �x�����ʓx�ɕϊ�
			rot = (rot * D3DX_PI) / 180.0f;
		}

		if (strcmp(&FileString[0], "END_MODELSET") == 0)
		{
#ifdef _DEBUG

			// �G���[
			assert(Type != -1 && "�I�u�W�F�N�g���f���̎�ޏ��̓Ǎ��݂Ɏ��s");

#endif	// _DEBUG

			// �ǂݍ��񂾔z�u�����Y�����Ԃ̃I�u�W�F�N�g�փR�s�[����
			g_Object[id_Model].type = Type;
			g_Object[id_Model].pos = pos;
			g_Object[id_Model].rot = rot;

			VerifyTypeObject(id_Model);	// ��ނ̏ƍ�

			id_Model++; // �R�s�[�����玟��
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // �I��
			break;
		}
	}
}

//************************************************
// ��ނ̏ƍ�
//************************************************
void VerifyTypeObject(int id_Model)
{
	for (int i = 0; i < g_MaxModel; i++)
	{
		if (g_Object[id_Model].type == i)
		{ // �e�I�u�W�F�N�g�̎�ނ��ƍ�
			g_Object[id_Model].model = g_ObjectModel[i];	//!< �ԍ��̈�v���Ă��郂�f�������R�s�[
		}
	}
}

//************************************************
// ��ނ̏ƍ�(���z)
//************************************************
void VerifyTypePreObject(void)
{
	for (int i = 0; i < g_MaxModel; i++)
	{
		if (g_PreObject.type == i)
		{ // �e���z�I�u�W�F�N�g�̎�ނ��ƍ�
			g_PreObject.model = g_ObjectModel[i];	//!< �ԍ��̈�v���Ă��郂�f�������R�s�[
		}
	}
}

//************************************************
// �I�u�W�F�N�g�j��
//************************************************
void UninitObject(void)
{
	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_ObjectModel[i].pTex[j] != NULL)
			{ // �e�N�X�`���̔j��
				g_ObjectModel[i].pTex[j]->Release();
				g_ObjectModel[i].pTex[j] = NULL;
			}
		}

		if (g_ObjectModel[i].pMesh != NULL)
		{ // ���b�V���̔j��
			g_ObjectModel[i].pMesh->Release();
			g_ObjectModel[i].pMesh = NULL;
		}

		if (g_ObjectModel[i].pBuffMat != NULL)
		{ // �}�e���A���̔j��
			g_ObjectModel[i].pBuffMat->Release();
			g_ObjectModel[i].pBuffMat = NULL;
		}
	}

	// �M�Y���j��
	UninitGizmoObject();
}

//************************************************
// �M�Y���j��
//************************************************
void UninitGizmoObject(void)
{
	if (g_GizmoObject.model.pMesh != NULL)
	{ // ���b�V���̔j��
		g_GizmoObject.model.pMesh->Release();
		g_GizmoObject.model.pMesh = NULL;
	}

	if (g_GizmoObject.model.pBuffMat != NULL)
	{ // �}�e���A���̔j��
		g_GizmoObject.model.pBuffMat->Release();
		g_GizmoObject.model.pBuffMat = NULL;
	}
}

//************************************************
// �I�u�W�F�N�g�X�V
//************************************************
void UpdateObject(bool LayoutEdit)
{
#ifdef _DEBUG

	if (LayoutEdit)
	{ // �ҏW���[�h�łȂ���Ώ������s��Ȃ�

		EditCamera* pEditCamera = GetInfoEditCamera();	// �ҏW�J�������擾
		Object* pObject = nullptr;						// ���z�E�����I�u�W�F�N�g���ʗp
		int Loop = 1;									// �ėp���[�v��

		/*--------------------------------------------*/

		// ���f���̔z�u����ۑ�����
		if (GetKeyboardTrigger(DIK_F3))
		{
			ExportLayoutObject();
		}

		// �ړ����[�h��ύX����
		if (GetKeyboardTrigger(DIK_F4))
		{
			g_TrackAA = !g_TrackAA;
		}

		// �ҏW���[�h��ύX����
		if (GetKeyboardTrigger(DIK_F5))
		{
			g_Overwrite = !g_Overwrite;
		}

		// ���݂̔z�u���f�������擾
		g_MaxObject = GetInfoMaxObject();

		if (GetKeyboardPress(DIK_SPACE))
		{ // �����ňړ����]�̑��x�㏸
			Loop = 4;
		}

		// �I�u�W�F�N�g�̏����f�o�b�O�\��
		PrintInfoObject();

		/*--------------------------------------------*/

		// ���[�h�ɉ����Ď擾����I�u�W�F�N�g�����ʂ���
		if (g_Overwrite)
		{
			pObject = &g_Object[g_obj_id];
		}
		else
		{
			pObject = &g_PreObject;
		}

		/*--------------------------------------------*/

		// �ԍ��̕ύX (�ŏ��A�ő�ɂȂ������ɋt���։��p�ɏC���\��)
		if (g_Overwrite)
		{ // �㏑�����[�h���̂�
			if (GetKeyboardTrigger(DIK_PERIOD) || GetKeyboardPress(DIK_X))
			{
				for (int i = g_obj_id + 1; i < AMOUNT_OBJECT; i++)
				{
					if (g_Object[i].model.pMesh != NULL)
					{ // ���f���������Ԃɓ�����Ƃ��̔Ԃ֕ύX
						g_obj_id = i;

						break;
					}
				}
			}
			else if (GetKeyboardTrigger(DIK_COMMA) || GetKeyboardPress(DIK_Z))
			{
				for (int i = g_obj_id - 1; i >= 0; i--)
				{
					if (g_Object[i].model.pMesh != NULL)
					{ // ���f���������Ԃɓ�����Ƃ��̔Ԃ֕ύX
						g_obj_id = i;

						break;
					}
				}
			}
		}

		// ��ނ̕ύX
		if (GetKeyboardTrigger(DIK_RSHIFT))
		{
			pObject->type < g_MaxModel - 1 ? pObject->type++ : pObject->type = 0;

			g_Overwrite ? VerifyTypeObject(g_obj_id) : VerifyTypePreObject();
		}
		else if (GetKeyboardTrigger(DIK_LSHIFT))
		{
			pObject->type > 0 ? pObject->type-- : pObject->type = g_MaxModel - 1;

			g_Overwrite ? VerifyTypeObject(g_obj_id) : VerifyTypePreObject();
		}

		// �G���[
		assert(pObject->type >= 0 && pObject->type < g_MaxModel && "�I�u�W�F�N�g���f���̎�ނ̕ύX���s");

		/*--------------------------------------------*/

		// �ړ��n
		for (int i = 0; i < Loop; i++)
		{
			// �I�u�W�F�N�g�̉�]
			RotateObject(pObject);

			// �I�u�W�F�N�g�̈ړ�
			MoveObject(pObject);
		}

		// ���z�̃I�u�W�F�N�g���A�ʏ�I�u�W�F�N�g�Ƃ��Ĕz�u
		if (!g_Overwrite && GetKeyboardTrigger(DIK_RETURN))
		{
			for (int i = 0; i < AMOUNT_OBJECT; i++)
			{
				// ���ɕۑ���񂪂���΃R���e�B�j���[
				if (g_Object[i].model.pMesh != NULL)
				{
					continue;
				}

				g_Object[i] = g_PreObject;	// �V���ɏ���ۑ�

				break;
			}
		}

		// �����̃I�u�W�F�N�g���폜
		if (g_Overwrite && GetKeyboardTrigger(DIK_BACK))
		{
			DeleteObject();	// �����폜
		}

		/*--------------------------------------------*/

		// �����ʒu�ɃM�Y����t��
		g_GizmoObject.pos = pObject->pos;

		// ���������ɃM�Y����t��
		if (!g_TrackAA)
		{ // �������[�h���̂�
			g_GizmoObject.rot.y = pEditCamera->rot.y;
		}
		else
		{
			if (g_GizmoObject.rot.y != 0.0f)
			{
				g_GizmoObject.rot.y = 0.0f;
			}
		}

		/*--------------------------------------------*/

		// �Ō�ɍs��Z
		CalcMtxPreObject(0);	//!< ���z�I�u�W�F�N�g
		CalcMtxPreObject(1);	//!< �M�Y��
	}	// if(LayoutEdit)

#endif	// _DEBUG

	// ���[�h�Ɋւ�炸�����I�u�W�F�N�g�͍Ō�ɍs��v�Z
	CalcMtxObject();
}

//************************************************
// ���݂̔z�u���f�������擾
//************************************************
int GetInfoMaxObject(void)
{
	int Cnt = 0;

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (g_Object[i].model.pMesh != NULL)
		{
			Cnt++;	// ���ɕۑ���񂪂���΃J�E���g����
		}
	}

	return Cnt;
}

//************************************************
// �I�u�W�F�N�g�̏����f�o�b�O�\��
//************************************************
void PrintInfoObject(void)
{
#ifdef _DEBUG

	char Test[32] = {};	// �ėp������

	if (!g_Overwrite)
	{
		PrintDebugProc("�y���݂̉��z�I�u�W�F�N�g���z\n���f���̔z�u���F%d\n��ށF%d\n�ʒu�F%f %f %f\n�����F%f %f %f\n"
			, g_MaxObject, g_PreObject.type, g_PreObject.pos.x, g_PreObject.pos.y, g_PreObject.pos.z, g_PreObject.rot.x, g_PreObject.rot.y, g_PreObject.rot.z);
	}
	else
	{
		PrintDebugProc("�y���݂̊����I�u�W�F�N�g���z\n���݂̑I���F%d / %d�Ԗ�\n��ށF%d\n�ʒu�F%f %f %f\n�����F%f %f %f\n"
			, g_obj_id, g_MaxObject, g_Object[g_obj_id].type, g_Object[g_obj_id].pos.x, g_Object[g_obj_id].pos.y, g_Object[g_obj_id].pos.z, g_Object[g_obj_id].rot.x, g_Object[g_obj_id].rot.y, g_Object[g_obj_id].rot.z);
	}

	g_TrackAA ? sprintf(Test, "���s") : sprintf(Test, "����");

	PrintDebugProc("�ړ����[�h�F%s\n", &Test[0]);

	g_Overwrite ? sprintf(Test, "�㏑��") : sprintf(Test, "�ʏ�");

	PrintDebugProc("�ҏW���[�h�F%s\n", &Test[0]);

#endif	// _DEBUG
}

//************************************************
// �I�u�W�F�N�g�̉�]
//************************************************
void RotateObject(Object* pObject)
{
#ifdef _DEBUG

	// X���ɉ�]
	if (GetKeyboardPress(DIK_R))
	{
		pObject->rot.x += 0.01f;
	}
	else if (GetKeyboardPress(DIK_F))
	{
		pObject->rot.x -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_V))
	{
		pObject->rot.x = 0.0f;
	}

	// Y���ɉ�]
	if (GetKeyboardPress(DIK_T))
	{
		pObject->rot.y += 0.01f;
	}
	else if (GetKeyboardPress(DIK_G))
	{
		pObject->rot.y -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_B))
	{
		pObject->rot.y = 0.0f;
	}

	// Z���ɉ�]
	if (GetKeyboardPress(DIK_Y))
	{
		pObject->rot.z += 0.01f;
	}
	else if (GetKeyboardPress(DIK_H))
	{
		pObject->rot.z -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_N))
	{
		pObject->rot.z = 0.0f;
	}

	// X���Ɉ��l
	if (GetKeyboardTrigger(DIK_U))
	{
		pObject->rot.x += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_J))
	{
		pObject->rot.x -= D3DX_PI * 0.025f;
	}

	// Y���Ɉ��l
	if (GetKeyboardTrigger(DIK_I))
	{
		pObject->rot.y += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_K))
	{
		pObject->rot.y -= D3DX_PI * 0.025f;
	}

	// Z���Ɉ��l
	if (GetKeyboardTrigger(DIK_O))
	{
		pObject->rot.z += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_L))
	{
		pObject->rot.z -= D3DX_PI * 0.025f;
	}

#endif	// _DEBUG
}

//************************************************
// �I�u�W�F�N�g�̈ړ�
//************************************************
void MoveObject(Object* pObject)
{
#ifdef _DEBUG

	bool move = false;
	float X = 0.0f;
	float Z = 0.0f;
	const EditCamera* pCamera = GetInfoEditCamera();

	// ���E
	if (GetKeyboardPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (GetKeyboardPress(DIK_D))
	{
		X = 1.0f;
	}

	// �O��
	if (GetKeyboardPress(DIK_W))
	{
		Z = 1.0f;
	}
	else if (GetKeyboardPress(DIK_S))
	{
		Z = -1.0f;
	}

	// �㉺
	if (GetKeyboardPress(DIK_LBRACKET))
	{
		pObject->pos.y += 1.0f;
	}
	else if (GetKeyboardPress(DIK_RBRACKET))
	{
		pObject->pos.y -= 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_YEN))
	{
		pObject->pos.y = 0.0f;
	}

	// int�ւ̃L���X�g�𗘗p���ď���������؂�̂Ă邽�ߌx��������
#pragma warning(disable:4244)

	// �[������
	if (GetKeyboardTrigger(DIK_MINUS))
	{
		pObject->pos.x = (int)pObject->pos.x;
	}
	else if (GetKeyboardTrigger(DIK_CIRCUMFLEX))
	{
		pObject->pos.z = (int)pObject->pos.z;
	}

#pragma warning(default:4244)

	/*--- (�����\��) ---*/
	if (GetKeyboardTrigger(DIK_0))
	{
		pObject->pos =
		{
			0.0f,
			300.0f,
			0.0f
		};
	}

	// ���E���l
	if (GetKeyboardTrigger(DIK_NUMPAD4))
	{
		X = -1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD6))
	{
		X = 1.0f;
	}

	// �O����l
	if (GetKeyboardTrigger(DIK_NUMPAD8))
	{
		Z = 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD5))
	{
		Z = -1.0f;
	}

	// �㉺���l
	if (GetKeyboardTrigger(DIK_NUMPAD2))
	{
		pObject->pos.y += 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD0))
	{
		pObject->pos.y -= 1.0f;
	}

	if (X != 0.0f || Z != 0.0f)
	{ // ��������͂��Ă���Έړ����Ă��锻��
		move = true;
	}

	if (move)
	{
		// �ړ��ʂƖڕW���p��ݒ�
		if (g_TrackAA)
		{
			pObject->pos.x += sinf(atan2f(X, Z));
			pObject->pos.z += cosf(atan2f(X, Z));
		}
		else
		{
			pObject->pos.x += sinf(atan2f(X, Z) + pCamera->rot.y);
			pObject->pos.z += cosf(atan2f(X, Z) + pCamera->rot.y);
		}
	}

#endif	// _DEBUG
}

//************************************************
// �����̃I�u�W�F�N�g�������i�������I�u�W�F�N�g�ԍ��𖄂߂�悤�Ƀ\�[�g����\��B�����ꂪ�o����Δԍ��̕ύX���ȑO�̂��̂Ŏg���܂킹��B�j
//************************************************
void DeleteObject(void)
{
	// �I�u�W�F�N�g�̏��̃��Z�b�g
	g_Object[g_obj_id].type = 0;
	g_Object[g_obj_id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object[g_obj_id].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object[g_obj_id].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object[g_obj_id].aabb = {};
	g_Object[g_obj_id].model.pMesh = NULL;
	g_Object[g_obj_id].model.pBuffMat = NULL;
	g_Object[g_obj_id].model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // �e�N�X�`�����̃��Z�b�g
		g_ObjectModel[g_obj_id].pTex[i] = NULL;
	}
	g_Object[g_obj_id].nIdxShadow = 0;	//!< ���ݖ��g�p
}

//************************************************
// �����I�u�W�F�N�g�p�}�g���b�N�X�̌v�Z
//************************************************
void CalcMtxObject(void)
{
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (g_Object[i].model.pMesh == NULL)
		{ // �Ȃ�炩�̗��R�ŋ���ۂȂ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Object[i].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Object[i].rot.y,
			g_Object[i].rot.x,
			g_Object[i].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_Object[i].mtxWorld,
			&g_Object[i].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Object[i].pos.x,
			g_Object[i].pos.y,
			g_Object[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Object[i].mtxWorld,
			&g_Object[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// ���z�I�u�W�F�N�g�p�}�g���b�N�X�̌v�Z
//************************************************
void CalcMtxPreObject(int mode)
{
#ifdef _DEBUG

	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;		// �v�Z�p�}�g���b�N�X
	Object* pObject = nullptr;

	switch (mode)
	{
	case 0:
		// ���z�I�u�W�F�N�g
		pObject = &g_PreObject;
		break;

	case 1:
		// �M�Y��
		pObject = &g_GizmoObject;

		break;

	default:

		// �G���[
		assert(false && "���z�I�u�W�F�N�g�̃}�g���b�N�X�v�Z�ُ�");

		break;
	}

	/*--------------------------------------------*/

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pObject->mtxWorld);

	if (mode == 1)
	{ // �M�Y�����[�h�̏ꍇ�Y�[�����ɍ��킹�Ċg�k
		EditCamera* pEditCamera = GetInfoEditCamera();	// �ҏW�J�������擾

		// �������擾
		float DistanceSize = (pEditCamera->distance * 0.005f);

		//�X�P�[����ύX1
		D3DXMatrixScaling(&mtxScale,
			pObject->size.x + DistanceSize,
			pObject->size.y + DistanceSize,
			pObject->size.z + DistanceSize);

		//�X�P�[����ύX2
		D3DXMatrixMultiply(&pObject->mtxWorld,
			&pObject->mtxWorld,
			&mtxScale);
	}

	// �����𔽉f1
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		pObject->rot.y,
		pObject->rot.x,
		pObject->rot.z);

	// �����𔽉f2
	D3DXMatrixMultiply(&pObject->mtxWorld,
		&pObject->mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f1
	D3DXMatrixTranslation(&mtxTrans,
		pObject->pos.x,
		pObject->pos.y,
		pObject->pos.z);

	// �ʒu�𔽉f2
	D3DXMatrixMultiply(&pObject->mtxWorld,
		&pObject->mtxWorld,
		&mtxTrans);

#endif // _DEBUG
}

//************************************************
// �I�u�W�F�N�g�`��
//************************************************
void DrawObject(bool LayoutEdit)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int obj_id = 0; obj_id < AMOUNT_OBJECT; obj_id++)
	{
		if (g_Object[obj_id].model.pMesh == NULL)
		{ // �Ȃ�炩�̗��R�ŋ���ۂȂ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[obj_id].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Object[obj_id].model.pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int mat_id = 0; mat_id < (int)g_Object[obj_id].model.NumMat; mat_id++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[mat_id].MatD3D);

			//�e�N�X�`���̐ݒ�
			if (g_Object[obj_id].model.pTex[mat_id] != NULL)
			{
				pDevice->SetTexture(0, g_Object[obj_id].model.pTex[mat_id]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			// �I�u�W�F�N�g�p�[�c�̕`��
			g_Object[obj_id].model.pMesh->DrawSubset(mat_id);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

#ifdef _DEBUG

	if (LayoutEdit)
	{
		// ���z�I�u�W�F�N�g��`��
		if (!g_Overwrite)
		{
			DrawPreObject(0);
		}

		// �M�Y����`��
		DrawPreObject(1);
	}

#endif	// _DEBUG
}

//************************************************
// ���z�̃I�u�W�F�N�g�`��
//************************************************
void DrawPreObject(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	Object* pObject = nullptr;

	switch (mode)
	{
	case 0:
		// ���z�I�u�W�F�N�g
		pObject = &g_PreObject;
		break;

	case 1:
		// �M�Y��
		pObject = &g_GizmoObject;

		//Z�ʒu�̔�r���@�̕ύX
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// ��ɐ[�x�e�X�g�ɍ��i
		break;

	default:

#ifdef _DEBUG

		// �G���[
		assert(false && "���z�I�u�W�F�N�g�̕`�惂�[�h�ُ�");

#endif	// _DEBUG

		break;
	}

	/*--------------------------------------------*/

	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &pObject->mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pObject->model.pBuffMat->GetBufferPointer();

	// ���̃p�[�c�̎��}�e���A������
	for (int i = 0; i < (int)pObject->model.NumMat; i++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//�e�N�X�`���̐ݒ�
		if (pObject->model.pTex[i] != NULL)
		{
			pDevice->SetTexture(0, pObject->model.pTex[i]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// �I�u�W�F�N�g�p�[�c�̕`��
		pObject->model.pMesh->DrawSubset(i);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	if (mode == 1)
	{ // �M�Y���`�惂�[�h�̏ꍇ
		//Z�ʒu�̔�r���@�̏C��
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}

//************************************************
// �I�u�W�F�N�g�����擾
//************************************************
Object* GetInfoObject(void)
{
	return &g_Object[0];
}

//************************************************
// �M�Y�������擾
//************************************************
Object* GetInfoGizmoObject(void)
{
	return &g_GizmoObject;
}

//************************************************
// ���f���z�u����ۑ�����
//************************************************
void ExportLayoutObject(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 rot = {};	// �v�Z�p

	// �ۑ�����t�@�C����p��
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_export.txt", "w") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�I�u�W�F�N�g���f���z�u�ۑ��p�̃t�@�C���̗p�ӂɎ��s");

#else

		return;

#endif	// _DEBUG
	}

	// �r���[���[�Ŏg���܂킵�₷���t�H�[�}�b�g�ŏ����o���Ă����c
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# ���f���z�u���\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");

	// ���f���̎�ށA�ʒu�A�������A�u���������������o��
	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (g_Object[i].model.pMesh == NULL)
		{ // ���f����񂪖�����΂��̔Ԃ̓R���e�B�j���[
			continue;
		}

		// �ʓx��x���ɕϊ�
		rot = (g_Object[i].rot * 180.0f) / D3DX_PI;

		fprintf(pFile, "MODELSET\n");
		fprintf(pFile, "	TYPE = %d\n", g_Object[i].type);
		fprintf(pFile, "	POS = %.1f %.1f %.1f\n", g_Object[i].pos.x, g_Object[i].pos.y, g_Object[i].pos.z);
		fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", rot.x, rot.y, rot.z);
		fprintf(pFile, "END_MODELSET\n\n");
	}

	// �I��
	fprintf(pFile, "END_SCRIPT\n");

	// �t�@�C�������
	fclose(pFile);
}
