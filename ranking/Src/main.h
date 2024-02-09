//************************************************
//
// ���C���A�w�b�_�t�@�C��[main.h]
// Author�F���c����, kasai keisuke
//
//************************************************
#ifndef _MAIN_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _MAIN_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <Mmsystem.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	// ���̂�̃r���h���x���p�}�N��
#include <dinput.h>
#include "Xinput.h"
#include "xaudio2.h"

// ���C�u�����̃����N
#pragma	comment(lib,"d3d9.lib")		// �`�揈���p
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma	comment(lib,"dxguid.lib")	// DirectX�̃R�[�|�l���g�g�p�̂���
#pragma comment(lib,"Winmm.lib")	// �V�X�e�����Ԏ擾�p
#pragma comment(lib,"dinput8.lib")	// ���͏����p
#pragma comment(lib,"xinput.lib")	// �R���g���[�����͗p

/*/ �}�N����` /*/
#define SCREEN_WIDTH 1920		// �E�C���h�E�̉���
#define SCREEN_HALFWIDTH 960	// �E�C���h�E�̉�����
#define SCREEN_HEIGHT 1080		// �E�C���h�E�̏c��
#define SCREEN_HALFHEIGHT 540	// �E�C���h�E�̏c����

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 2D�p���_�t�H�[�}�b�g
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 3D�p���_�t�H�[�}�b�g

#define EPSILON	0.1f			// �ėp臒l
#define AMOUNT_VTX 4			// �|���S��1��������̃o�[�e�b�N�X��
#define AMOUNT_COMBINEPOLYGON 2	// �|���S��1��������̃v���~�e�B�u��
#define AMOUNT_MAT	16			// ���f��1������̍ő�}�e���A����

#define MAX_PLAYER	4	// ����̃Q�[���ɂ�����ő�v���C�l��

// 2D�|���S���p�\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ω��p�W��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W�p
}VERTEX_2D;

// 3D�|���S���p�\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W�p
}VERTEX_3D;

// AABB�Փ˔���p
typedef struct
{
	D3DXVECTOR3 min;	// �ŏ�
	D3DXVECTOR3 max;	// �ő�
}COLLISION_AABB;

// ���[�h���ʂ̗񋓌^
typedef enum
{
	MODE_TITLE = 0, // �^�C�g�����[�h
	MODE_MENU,		// ���j���[���[�h
	MODE_TUTORIAL,	// �`���[�g���A�����[�h
	MODE_RANKING,	// �����L���O���[�h
	MODE_GAME,		// �Q�[�����[�h
	MODE_RESULT,	// ���U���g���[�h
	MODE_END,		// �G���h���[�h
	MODE_MAX,		// ���[�h�̑���
}MODE;

/*/ �v���g�^�C�v�錾 /*/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�C���h�E�v���V�[�W��
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw);	// ����
void UnInit(void);		// �I��
void Update(void);		// �X�V
void Draw(void);		// �`��
LPDIRECT3DDEVICE9 GetDevice(void);	// �f�o�C�X�̎擾
int GetFPS(void);		// FPS���擾

#endif