//************************************************
//
// ���C�g�A�w�b�_�t�@�C��[light.h]
// Author�F���c����
//
//************************************************
#ifndef _LIGHT_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _LIGHT_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

/*/ �v���g�^�C�v�錾 /*/
void InitLight(void);			// ����
void UpdateLight(void);			// �X�V
void ChangeLightType(void);		// ���C�g�ԍ���ύX
void MoveLight(void);			// �ړ�
void ResetLight(void);			// ���Z�b�g
void SetLight(void);			// ���f
D3DLIGHT9* GetInfoLight(void);	// ���C�g�����擾
int GetInfoLightType(void);		// ���C�g�ԍ����擾

#endif