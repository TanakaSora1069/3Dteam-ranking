//************************************************
//
// �ҏW�J����[editcamera.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "editcamera.h"
// ����
#include "input.h"
// ������
#include "object.h"

/*/ �}�N����` /*/
#define AA_MODE	1	// ���e���[�h�ύX

/*/ �O���[�o���ϐ� /*/
EditCamera g_EditCamera;	// �ҏW�J�������

//************************************************
// �J��������
//************************************************
void InitEditCamera(void)
{
	// �ҏW�J�������̏�����	
	g_EditCamera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditCamera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditCamera.rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_EditCamera.distance = 300.0f;

	// �r���[�|�[�g�̈ʒu
	g_EditCamera.viewport.X = 0;
	g_EditCamera.viewport.Y = 0;

	// �r���[�|�[�g�̃T�C�Y
	g_EditCamera.viewport.Width = SCREEN_WIDTH;
	g_EditCamera.viewport.Height = SCREEN_HEIGHT;

	// �r���[�|�[�g�̐[�x
	g_EditCamera.viewport.MinZ = 0.0f;
	g_EditCamera.viewport.MaxZ = 1.0f;
}

//************************************************
// �J�����X�V
//************************************************
void UpdateEditCamera(void)
{
	const Object* pGizmoObject = GetInfoGizmoObject();

	// �Y�[���C�� / �A�E�g
	if (GetKeyboardPress(DIK_AT) && g_EditCamera.distance > 10.0f)
	{
		g_EditCamera.distance -= 10.0f;
	}
	else if (GetKeyboardPress(DIK_COLON))
	{
		g_EditCamera.distance += 10.0f;
	}

	// �����ԃ��Z�b�g
	if (GetKeyboardTrigger(DIK_BACKSLASH))
	{
		g_EditCamera.distance = 200.0f;
	}

	if (GetKeyboardPress(DIK_LALT))
	{ // L - Alt����
		bool move = false;
		float X = 0.0f;
		float Z = 0.0f;

		if (GetKeyboardPress(DIK_LEFT))
		{
			X = -1.0f;
		}
		else if (GetKeyboardPress(DIK_RIGHT))
		{
			X = 1.0f;
		}

		if (GetKeyboardPress(DIK_UP))
		{
			Z = 1.0f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{
			Z = -1.0f;
		}

		if (X != 0.0f || Z != 0.0f)
		{ // ��������͂��Ă���Έړ����Ă��锻��
			move = true;
		}

		if (move)
		{
			g_EditCamera.rot.y = atan2f(X, Z);
		}
	}
	else
	{
		// ���E
		if (GetKeyboardPress(DIK_RIGHT))
		{
			g_EditCamera.rot_goal.y += 0.025f;
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{
			g_EditCamera.rot_goal.y -= 0.025f;
		}

		// �㉺
		if (GetKeyboardPress(DIK_UP))
		{
			g_EditCamera.rot_goal.x += 0.025f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{
			g_EditCamera.rot_goal.x -= 0.025f;
		}
	}

	// �ړ��ʃu���[�L
	g_EditCamera.rot_goal *= 0.8f;

	// �ړ����f
	g_EditCamera.rot += g_EditCamera.rot_goal * 0.5f;

	// ���������̉�]�͈�
	if (g_EditCamera.rot.y > D3DX_PI)
	{
		g_EditCamera.rot.y = -D3DX_PI;
	}
	else if (g_EditCamera.rot.y < -D3DX_PI)
	{
		g_EditCamera.rot.y = D3DX_PI;
	}

	//�Ίp�̉�]�͈�
	if (g_EditCamera.rot.x > D3DX_PI * 0.45f)
	{
		g_EditCamera.rot.x = D3DX_PI * 0.45f;
	}
	else if (g_EditCamera.rot.x < -D3DX_PI * 0.45f)
	{
		g_EditCamera.rot.x = -D3DX_PI * 0.45f;
	}

	// �Ώە��̍��W
	D3DXVECTOR3 target;
	target = pGizmoObject->pos;

	// ���_���Z�o
	CalcEditPosV(target);

	// �����_���Z�o
	CalcEditPosR(target);
}

//************************************************
// ���_���Z�o
//************************************************
void CalcEditPosV(const D3DXVECTOR3 target)
{
	// ���_�͑Ώە��̌����
	g_EditCamera.posV =
	{
		target.x - (sinf(g_EditCamera.rot.y) * cosf(g_EditCamera.rot.x) * (g_EditCamera.distance)),
		target.y - (sinf(g_EditCamera.rot.x) * (g_EditCamera.distance)),
		target.z - (cosf(g_EditCamera.rot.y) * cosf(g_EditCamera.rot.x) * (g_EditCamera.distance))
	};
}

//************************************************
// �����_���Z�o
//************************************************
void CalcEditPosR(const D3DXVECTOR3 target)
{
	// �����_��Ώە��̑O����
	g_EditCamera.posR =
	{
		target.x + (sinf(g_EditCamera.rot.y) * cosf(g_EditCamera.rot.x) * g_EditCamera.distance),
		target.y + (sinf(g_EditCamera.rot.x) * g_EditCamera.distance),
		target.z + (cosf(g_EditCamera.rot.y) * cosf(g_EditCamera.rot.x) * g_EditCamera.distance)
	};
}

//************************************************
// �J�����ݒ�
//************************************************
void SetInfoEditCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_EditCamera.viewport);

	// ��ʃo�b�t�@�N���A
	pDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_EditCamera.mtxProjection);

#if AA_MODE

	// �v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&g_EditCamera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

#else

	// ���s���e���[�h
	D3DXMatrixOrthoLH(&g_EditCamera.mtxProjection,
		(float)SCREEN_WIDTH,
		(float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

#endif	// AA_MODE

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_EditCamera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_EditCamera.mtxView);

	// ���_�ʒu�̒����p
	D3DXVECTOR3 posV = g_EditCamera.posV;
	D3DXVECTOR3 posR = g_EditCamera.posR;

	// �r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&g_EditCamera.mtxView,
		&posV,
		&posR,
		&g_EditCamera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW,
		&g_EditCamera.mtxView);
}

//************************************************
// �J���������擾
//************************************************
EditCamera* GetInfoEditCamera(void)
{
	return &g_EditCamera;
}