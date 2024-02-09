//************************************************
//
// �I�u�W�F�N�g�A�w�b�_�t�@�C��[object.h]
// Author�F���c����
//
//************************************************
#ifndef _OBJECT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _OBJECT_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

/*/ �}�N����` /*/
#define AMOUNT_OBJECT 256			// ���̍ő吔
#define AMOUNT_MODEL_OBJECT	64		// ���̕ێ��ł���ő僂�f���퐔

// ���p���f�����
typedef struct
{
	LPD3DXMESH pMesh;						// ���b�V�����̃|�C���^
	LPD3DXBUFFER pBuffMat;					// �}�e���A���̃|�C���^
	DWORD NumMat;							// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// �e�N�X�`���̃|�C���^
}ObjectModel;

// �����
typedef struct
{
	int type;				// ���f���̎�ފi�[
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 size;		// �T�C�Y
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	COLLISION_AABB aabb;	// AABB�Փ˔���p
	ObjectModel model;		// ���f�����i�[
	int nIdxShadow;			// �ꉞ�e�̔ԍ��i�[�p
}Object;

/*/ �v���g�^�C�v�錾 /*/
void InitObject(void);					// �I�u�W�F�N�g�̏���
void InitPreObject(void);				// ���z�̃I�u�W�F�N�g�̏���
void InitGizmoObject(void);				// �M�Y���̏���
void ImportModelObject(void);			// �I�u�W�F�N�g���f���擾
void ImportGizmoModelObject(void);		// �M�Y�����f���擾
void ImportLayoutObject(FILE* pFile);	// ���f���z�u���擾
void VerifyTypeObject(int id_Model);	// �I�u�W�F�N�g��ނ̏ƍ�
void VerifyTypePreObject(void);			// ���z�I�u�W�F�N�g��ނ̏ƍ�
void ImportTexObject(void);				// ���f���e�N�X�`����Ǎ���
void UninitObject(void);				// �I�u�W�F�N�g�j��
void UninitGizmoObject(void);			// �M�Y���j��
void UpdateObject(bool LayoutEdit);		// �X�V
int GetInfoMaxObject(void);				// ���݂̔z�u���f�������擾
void PrintInfoObject(void);				// �f�o�b�O�\��
void RotateObject(Object* pObject);		// �I�u�W�F�N�g�̉�]
void MoveObject(Object* pObject);		// �I�u�W�F�N�g�̈ړ�
void CalcMtxObject(void);				// �����I�u�W�F�N�g�p�}�g���b�N�X�̌v�Z
void CalcMtxPreObject(int mode);		// ���z�I�u�W�F�N�g�p�}�g���b�N�X�̌v�Z
void DeleteObject(void);				// �����I�u�W�F�N�g������
void DrawObject(bool LayoutEdit);		// �I�u�W�F�N�g�̕`��
void DrawPreObject(int mode);			// ���z�̃I�u�W�F�N�g�̕`��(�M�Y���܂�)
Object* GetInfoObject(void);			// �I�u�W�F�N�g�̏����擾
Object* GetInfoGizmoObject(void);		// �M�Y�������擾
void ExportLayoutObject(void);			// ���f���z�u���ۑ�

#endif