//************************************************
//
// �L�[���͏���[input.cpp]
// Author�F���c����, kasai keisuke
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "input.h"

/*/ �}�N����` /*/
#define NUM_KEY_MAX	256	// �L�[�̍ő吔

/*/ �O���[�o���ϐ� /*/
LPDIRECTINPUT8 g_Input = NULL;				// DirectInput�I�u�W�F�N�g�̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];				// �L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[���
XINPUT_STATE g_JoyKeyState[MAX_PLAYER];		//�R���g���[���[�̃v���X���(�l����)
XINPUT_STATE g_JoyKeyStateTrigger[MAX_PLAYER];//�R���g���[���[�̃g���K�[���(�l����)
bool bJoyKeyTrigger;						// �g���K�[���ǂ���
XINPUT_VIBRATION g_JoypadMotor;				// �R���g���[���̃��[�^�[���			
int g_nTime;								// �U����������
WORD g_Strength;							// �U���̋��� (0 �` 65535)

//************************************************
// �L�[���͏���
//************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_Input, NULL)))
	{ // DirectInput�I�u�W�F�N�g�̐���
		return E_FAIL;
	}

	if (FAILED(g_Input->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{ // ���̓f�o�C�X(�L�[�{�[�h)�̐���
		return E_FAIL;
	}

	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{ // �f�[�^�t�H�[�}�b�g�̐ݒ�
		return E_FAIL;
	}

	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{ // �������[�h��ݒ�
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//************************************************
// �L�[���͏I��
//************************************************
void UnInitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{ // ���̓f�o�C�X(�L�[�{�[�h)�̔j��
		g_pDevKeyboard->Unacquire();	// �L�[�{�[�h�̓��͏��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	if (g_Input != NULL)
	{ // DirectInput�I�u�W�F�N�g�̔j��
		g_Input->Release();
		g_Input = NULL;
	}
}

//************************************************
// �L�[���͍X�V
//************************************************
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��
	int nCntKey;

	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{ // ���̓f�o�C�X����f�[�^���擾
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			// �L�[�{�[�h�̃v���X����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// �L�[�{�[�h�̃A�N�Z�X�����l��
		g_pDevKeyboard->Acquire();
	}
}

//************************************************
// �L�[�{�[�h�̃v���X�����擾
//************************************************
bool GetKeyboardPress(int nKey)
{
	return((g_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
// �L�[�{�[�h�̃g���K�[�����擾
//************************************************
bool GetKeyboardTrigger(int nKey)
{
	return((g_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
// �R���g���[�����͏���
//************************************************
HRESULT InitJoypad(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//�������̃N���A
		memset(&g_JoyKeyState[nCntPlayer], 0, sizeof(XINPUT_STATE));

		//�������̃N���A
		memset(&g_JoyKeyStateTrigger[nCntPlayer], 0, sizeof(XINPUT_STATE));

		//�R���g���[���[�̏�����
		if (XInputGetState(nCntPlayer, &g_JoyKeyState[nCntPlayer]) == ERROR_SUCCESS)
		{
			g_JoyKeyStateTrigger[nCntPlayer] = g_JoyKeyState[nCntPlayer];
		}
	}

	// XInput�̃X�e�[�g�ݒ�(?)�Ƃ������̂�L���ɂ���
	XInputEnable(true);

	return S_OK;
}

//************************************************
// �R���g���[���I��
//************************************************
void UninitJoypad(void)
{
	// XInput�̃X�e�[�g�ݒ�(?)�Ƃ������̂𖳌��ɂ���
	XInputEnable(false);
}

//==================================================
//�Q�[���p�b�h�X�V
//==================================================
void UpdateJoypad()
{
	XINPUT_STATE joykeystate[MAX_PLAYER] = {};

	for (int PadNum = 0; PadNum < XUSER_MAX_COUNT; PadNum++)
	{
		//�W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(PadNum, &joykeystate[PadNum]) == ERROR_SUCCESS)
		{
			AdjustJoyStick();	// �X�e�B�b�N�̌X���̂�����

			//�R���g���[���[�̃g���K�[����ۑ�
			g_JoyKeyStateTrigger[PadNum].Gamepad.wButtons = (g_JoyKeyState[PadNum].Gamepad.wButtons ^ joykeystate[PadNum].Gamepad.wButtons) & joykeystate[PadNum].Gamepad.wButtons;
			g_JoyKeyStateTrigger[PadNum].Gamepad.bLeftTrigger = (g_JoyKeyState[PadNum].Gamepad.bLeftTrigger ^ joykeystate[PadNum].Gamepad.bLeftTrigger) & joykeystate[PadNum].Gamepad.bLeftTrigger;
			g_JoyKeyStateTrigger[PadNum].Gamepad.bRightTrigger = (g_JoyKeyState[PadNum].Gamepad.bRightTrigger ^ joykeystate[PadNum].Gamepad.bRightTrigger) & joykeystate[PadNum].Gamepad.bRightTrigger;

			g_JoyKeyState[PadNum] = joykeystate[PadNum];
		}
	}
}
//************************************************
// �R���g���[���̃v���X�����擾
//************************************************
bool GetJoypadPress(JOYKEY key, int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.wButtons & (0x01 << key)) ? true : false;

}

//************************************************
// �R���g���[���̃g���K�[�����擾
//************************************************
bool GetJoypadTrigger(JOYKEY key, int nContIndex)
{
	return (g_JoyKeyStateTrigger[nContIndex].Gamepad.wButtons & (0x01 << key)) ? true : false;

}

//************************************************
// �Q�[���p�b�h�̏����擾
//************************************************
XINPUT_GAMEPAD GetGamePad(int nContIndex)
{
		return g_JoyKeyState[nContIndex].Gamepad;
}

//************************************************
// �R���g���[���̍��g���K�[�{�^���̃v���X����
//************************************************
bool GetPressTriggerButtonL(int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
// �R���g���[���̉E�g���K�[�{�^���̃v���X����
//************************************************
bool GetPressTriggerButtonR(int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
// �R���g���[���̍��g���K�[�{�^���̃g���K�[����
//************************************************
bool GetTriggerTriggerButtonL(int nContIndex)
{
	return (g_JoyKeyStateTrigger[nContIndex].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
// �R���g���[���̉E�g���K�[�{�^���̃g���K�[����
//************************************************
bool GetTriggerTriggerButtonR(int nContIndex)
{
	return (g_JoyKeyStateTrigger[nContIndex].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD + 30.0f);
}

//************************************************
// �R���g���[���̍��X�e�B�b�N����
//************************************************
bool GetJoyStickL(int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

}

//************************************************
// �R���g���[���̉E�X�e�B�b�N����
//************************************************
bool GetJoyStickR(int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
}

//************************************************
// �R���g���[���̃X�e�B�b�N���͂̂�����
//************************************************
void AdjustJoyStick(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_JoyKeyState[nCntPlayer].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{ // ��
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLX = 0;
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLY = 0;
		}

		if (g_JoyKeyState[nCntPlayer].Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{ // �E
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRX = 0;
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRY = 0;
		}

	}

}

//************************************************
// �R���g���[���̍��X�e�B�b�N���\���L�[�ɕϊ�
//************************************************
WORD ConvertJoyStick(SHORT sThumbLX, SHORT sThumbLY, SHORT sDeadZone)
{
	// �{�^�����͂̏��ɒu�������p
	WORD wButtons = 0;

	if (sThumbLY >= sDeadZone)
	{ // �X�e�B�b�N�㑤�ɓ|�����Ƃ�
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbLY <= -sDeadZone)
	{ // �X�e�B�b�N�㑤�ɓ|�����Ƃ�
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbLX <= -sDeadZone)
	{ // ��
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbLX >= sDeadZone)
	{ // �E
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	// �{�^�����͐M�������^�[��
	return wButtons;
}

//************************************************
// �R���g���[���̐U����ݒ�
//************************************************
void SetVibration(int time, WORD strength)
{
	g_nTime = time;
	g_Strength = strength;
}

