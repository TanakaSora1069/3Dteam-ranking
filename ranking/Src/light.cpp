//************************************************
//
// ���C�g[light.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "light.h"
// ����
#include "input.h"

/*/ �}�N����` /*/
#define AMOUNT_LIGHT 3	// ���C�g�̐�

/*/ �O���[�o���ϐ� /*/
D3DLIGHT9 g_Light[AMOUNT_LIGHT] = {};	// ���C�g���
int g_LightType = 0;					// ���C�g�ԍ����ʗp

//************************************************
//���C�g����
//************************************************
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���C�g�̏���������
	ZeroMemory(&g_Light[0], sizeof(D3DLIGHT9));

	// ���C�g�ԍ�
	g_LightType = 0;

	for (int i = 0; i < AMOUNT_LIGHT; i++)
	{
		D3DXVECTOR3 vecDir;	// �ݒ�p�����x�N�g��

		// ���C�g�̎�ނ�ݒ�
		g_Light[i].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		g_Light[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (i)
		{ // ���C�g�̕�����ݒ�
		case 0:
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			break;
		case 1:
			vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(0.8f, 0.1f, 0.4f);
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);	// �x�N�g�����擾����
		g_Light[i].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(i, &g_Light[i]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(i, TRUE);
	}
}

//************************************************
// ���C�g�X�V
//************************************************
void UpdateLight(void)
{
	// �ړ�
	MoveLight();

	// �ړ����f
	SetLight();
}

//************************************************
// ���C�g�ԍ��ύX
//************************************************
void ChangeLightType(void)
{
	if (GetKeyboardTrigger(DIK_LSHIFT))
	{ // ���C�g�ԍ��ύX
		g_LightType < 2 ? g_LightType++ : g_LightType = 0;
	}
}

//************************************************
// ���C�g�ړ�
//************************************************
void MoveLight(void)
{
	// ���C�g�ԍ��ύX
	ChangeLightType();

	if (GetKeyboardPress(DIK_5))
	{ // X�����ύX
		g_Light[g_LightType].Direction.x += 0.1f;
	}
	else if (GetKeyboardPress(DIK_6))
	{
		g_Light[g_LightType].Direction.x -= 0.1f;
	}

	if (GetKeyboardPress(DIK_7))
	{ //Y�����ύX
		g_Light[g_LightType].Direction.y += 0.1f;
	}
	else if (GetKeyboardPress(DIK_8))
	{
		g_Light[g_LightType].Direction.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_9))
	{ // Z�����ύX
		g_Light[g_LightType].Direction.z += 0.1f;
	}
	else if (GetKeyboardPress(DIK_0))
	{
		g_Light[g_LightType].Direction.z -= 0.1f;
	}

	// �S���C�g�ړ����Z�b�g
	ResetLight();
}

//************************************************
// ���C�g���Z�b�g
//************************************************
void ResetLight(void)
{
	if (GetKeyboardTrigger(DIK_R))
	{ // ���C�g���Z�b�g
		switch (g_LightType)
		{
		case 0:
			g_Light[g_LightType].Direction = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			break;
		case 1:
			g_Light[g_LightType].Direction = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
			break;
		case 2:
			g_Light[g_LightType].Direction = D3DXVECTOR3(0.8f, 0.1f, 0.4f);
			break;
		}
	}
}

//************************************************
//���C�g���f
//************************************************
void SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�ύX���f
	for (int i = 0; i < AMOUNT_LIGHT; i++)
	{
		D3DXVECTOR3 vecDir = g_Light[i].Direction;	//�ݒ�p�����x�N�g��
		D3DXVec3Normalize(&vecDir, &vecDir);	//�x�N�g�����擾����
		g_Light[i].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(i, &g_Light[i]);
	}
}

//************************************************
// ���C�g�����擾
//************************************************
D3DLIGHT9* GetInfoLight(void)
{
	return &g_Light[0];
}

//************************************************
// ���C�g�ԍ������擾
//************************************************
int GetInfoLightType(void)
{
	return g_LightType;
}