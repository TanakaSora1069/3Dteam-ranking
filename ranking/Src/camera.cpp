//************************************************
//
// �J����[camera.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "camera.h"
// ����
#include "input.h"
// ������
#include "player.h"

/*/ �}�N����` /*/
#define TRACK_VERIFY	// �����I�Ǐ]�X�C�b�`

/*/ �O���[�o���ϐ� /*/
Camera g_Camera[AMOUNT_CAMERA];	// �J�������
UIport g_UIport;				// UI�p�|�[�g

//************************************************
// �J��������
//************************************************
void InitCamera(int joined)
{
	for (int i = 0; i < AMOUNT_CAMERA; i++)
	{ // �J�������̏�����	
		g_Camera[i].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[i].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[i].rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[i].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_Camera[i].distance = 200.0f;

		switch (i)
		{ // �r���[�|�[�g�̈ʒu
		case 0:
			g_Camera[i].viewport.X = 0;
			g_Camera[i].viewport.Y = 0;
			break;
		case 1:
			g_Camera[i].viewport.X = SCREEN_HALFWIDTH;
			g_Camera[i].viewport.Y = 0;
			break;
		case 2:
			g_Camera[i].viewport.X = 0;
			g_Camera[i].viewport.Y = SCREEN_HALFHEIGHT;
			break;
		case 3:
			g_Camera[i].viewport.X = SCREEN_HALFWIDTH;
			g_Camera[i].viewport.Y = SCREEN_HALFHEIGHT;
			break;
		}

		// �r���[�|�[�g�̃T�C�Y
		g_Camera[i].viewport.Width = 0;
		g_Camera[i].viewport.Height = 0;

		// �r���[�|�[�g�̐[�x
		g_Camera[i].viewport.MinZ = 0.0f;
		g_Camera[i].viewport.MaxZ = 1.0f;
	}

	// �r���[�|�[�g�T�C�Y����
	viewportSize Size = SetSizeViewport(joined);

	// �r���[�|�[�g�̃T�C�Y���f
	for (int i = 0; i < joined; i++)
	{
		g_Camera[i].viewport.Width = Size.Width;
		g_Camera[i].viewport.Height = Size.Height;
	}

	// UI�|�[�g�̏�����
	InitUIport();
}

//************************************************
// UI�|�[�g����
//************************************************
void InitUIport(void)
{
	// �r���[�|�[�g�̈ʒu
	g_UIport.viewport.X = 0;
	g_UIport.viewport.Y = 0;

	// �r���[�|�[�g�̃T�C�Y
	g_UIport.viewport.Width = SCREEN_WIDTH;
	g_UIport.viewport.Height = SCREEN_HEIGHT;

	// �r���[�|�[�g�̐[�x
	g_UIport.viewport.MinZ = 0.0f;
	g_UIport.viewport.MaxZ = 1.0f;
}

//************************************************
// �r���[�|�[�g�T�C�Y�ݒ�
//************************************************
viewportSize SetSizeViewport(int joined)
{
	// �r���[�|�[�g�T�C�Y�p
	viewportSize Size = { 0,0 };

	switch (joined)
	{ // �l���ł��̂܂ܕ���
	case 1:
		Size.Width = SCREEN_WIDTH;
		Size.Height = SCREEN_HEIGHT;
		break;

	case 2:
		Size.Width = SCREEN_HALFWIDTH;
		Size.Height = SCREEN_HEIGHT;
		break;

	case 3:
		Size.Width = SCREEN_HALFWIDTH;
		Size.Height = SCREEN_HALFHEIGHT;
		break;

	case 4:
		Size.Width = SCREEN_HALFWIDTH;
		Size.Height = SCREEN_HALFHEIGHT;
		break;
	}

	return Size;
}

//************************************************
// �J�����X�V
//************************************************
void UpdateCamera(int joined)
{
	const Player* pPlayer = GetInfoPlayer();	//!< �����I�Ƀv���C���[���Q�Ƃ��܂��B

	// �r���[�|�[�g�T�C�Y����
	viewportSize Size = SetSizeViewport(joined);

	// �r���[�|�[�g�̃T�C�Y���f
	for (int i = 0; i < joined; i++)
	{
		g_Camera[i].viewport.Width = Size.Width;
		g_Camera[i].viewport.Height = Size.Height;
	}

#ifdef _DEBUG

	// �L�[�{�[�h�Ŏ��_�ύX
	static int camera_id = 0;

	if (GetKeyboardTrigger(DIK_1))
	{
		camera_id = 0;
	}
	else if (GetKeyboardTrigger(DIK_2))
	{
		camera_id = 1;
	}
	else if (GetKeyboardTrigger(DIK_3))
	{
		camera_id = 2;
	}
	else if (GetKeyboardTrigger(DIK_4))
	{
		camera_id = 3;
	}

	// �Y�[���C�� / �A�E�g
	if (GetKeyboardPress(DIK_AT) && g_Camera[camera_id].distance > 10.0f)
	{
		g_Camera[camera_id].distance -= 10.0f;
	}
	else if (GetKeyboardPress(DIK_COLON))
	{
		g_Camera[camera_id].distance += 10.0f;
	}
	
	// �����ԃ��Z�b�g
	if (GetKeyboardTrigger(DIK_BACKSLASH))
	{
		g_Camera[camera_id].distance = 200.0f;
	}

	// ���E
	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_Camera[camera_id].rot_goal.y += 0.025f;
	}
	else if (GetKeyboardPress(DIK_LEFT))
	{
		g_Camera[camera_id].rot_goal.y -= 0.025f;
	}

	// �㉺
	if (GetKeyboardPress(DIK_UP))
	{
		g_Camera[camera_id].rot_goal.x += 0.025f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		g_Camera[camera_id].rot_goal.x -= 0.025f;
	}

#endif	// _DEBUG

	for (int i = 0; i < joined; i++)
	{
		if (!pPlayer[i].use)
		{ // ���g�p�̏ꍇ�R���e�B�j���[
			continue;
		}

		if (GetJoyStickR(i))
		{ // �E�X�e�B�b�N�Ŏ��_�ύX (��)

			const XINPUT_GAMEPAD GamePad = GetGamePad(i);

			g_Camera[i].rot_goal.x += (float)(GamePad.sThumbRY * 0.000001);
			g_Camera[i].rot_goal.y += (float)(GamePad.sThumbRX * 0.000001);
		}

		// �ړ��ʃu���[�L
		g_Camera[i].rot_goal *= 0.8f;

		// �ړ����f
		g_Camera[i].rot += g_Camera[i].rot_goal * 0.5f;

		// ���������̉�]�͈�
		if (g_Camera[i].rot.y > D3DX_PI)
		{
			g_Camera[i].rot.y = -D3DX_PI;
		}
		if (g_Camera[i].rot.y < -D3DX_PI)
		{
			g_Camera[i].rot.y = D3DX_PI;
		}

		//�Ίp�̉�]�͈�
		if (g_Camera[i].rot.x > D3DX_PI * 0.35f)
		{
			g_Camera[i].rot.x = D3DX_PI * 0.35f;
		}
		if (g_Camera[i].rot.x < -D3DX_PI * 0.25f)
		{
			g_Camera[i].rot.x = -D3DX_PI * 0.25f;
		}

		// �Ώە��̍��W
		D3DXVECTOR3 target;
		target = pPlayer[i].pos;

		// ���_���Z�o
		CalcPosV(i, target);

		// �����_���Z�o
		CalcPosR(i, target);
	}
}

//************************************************
// ���_���Z�o
//************************************************
void CalcPosV(int id, const D3DXVECTOR3 target)
{
	// ���_�͑Ώە��̌����
	g_Camera[id].posV =
	{
		target.x - (sinf(g_Camera[id].rot.y) * cosf(g_Camera[id].rot.x) * (g_Camera[id].distance)),
		target.y - (sinf(g_Camera[id].rot.x) * (g_Camera[id].distance)),
		target.z - (cosf(g_Camera[id].rot.y) * cosf(g_Camera[id].rot.x) * (g_Camera[id].distance))
	};
}

//************************************************
// �����_���Z�o
//************************************************
void CalcPosR(int id, const D3DXVECTOR3 target)
{
	// �����_��Ώە��̑O����
	g_Camera[id].posR =
	{
		target.x + (sinf(g_Camera[id].rot.y) * cosf(g_Camera[id].rot.x) * g_Camera[id].distance),
		target.y + (sinf(g_Camera[id].rot.x) * g_Camera[id].distance),
		target.z + (cosf(g_Camera[id].rot.y) * cosf(g_Camera[id].rot.x) * g_Camera[id].distance)
	};
}

//************************************************
// �J�����ݒ�
//************************************************
void SetInfoCamera(int id, int joined)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_Camera[id].viewport);

	// ��ʃo�b�t�@�N���A
	pDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �v���W�F�N�V�����}�g���b�N�X���v�Z
	CalcMatrixProjectionCamera(id, joined);

	// �r���[�}�g���b�N�X���v�Z
	CalcMatrixViewCamera(id);
}

//************************************************
// �v���W�F�N�V�����}�g���b�N�X���v�Z
//************************************************
void CalcMatrixProjectionCamera(int id, int joined)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[id].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�𐶐�
	if (joined != 2)
	{ // �ʏ�A�X�y�N�g��
		D3DXMatrixPerspectiveFovLH(&g_Camera[id].mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			5000.0f);
	}
	else
	{ // �����̂ݔ����T�C�Y
		D3DXMatrixPerspectiveFovLH(&g_Camera[id].mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_HALFWIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			5000.0f);
	}

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_Camera[id].mtxProjection);
}

//************************************************
// �r���[�}�g���b�N�X���v�Z
//************************************************
void CalcMatrixViewCamera(int id)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[id].mtxView);

	// ���_�ʒu�̒����p
	D3DXVECTOR3 posV = g_Camera[id].posV;
	D3DXVECTOR3 posR = g_Camera[id].posR;
	posV.y += 150.0f;

	// �r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&g_Camera[id].mtxView,
		&posV,
		&posR,
		&g_Camera[id].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW,
		&g_Camera[id].mtxView);
}

//************************************************
// UI�|�[�g�̐ݒ�
//************************************************
void SetInfoUIport(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_UIport.viewport);

	/*---�y�N���A���Ȃ��c�H�z---*/

	// ��ʃo�b�t�@�N���A
	//pDevice->Clear(0, NULL,
	//	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	//	D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
}

//************************************************
// �J���������擾
//************************************************
Camera* GetInfoCamera(void)
{
	return &g_Camera[0];
}