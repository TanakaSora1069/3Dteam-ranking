////************************************************
////
//// �����̂̔���������A�w�b�_�t�@�C��[visible_box.h]
//// Author�F���c����
////
////************************************************
//#ifndef _VISIBLE_BOX_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
//#define _VISIBLE_BOX_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)
//
///*/ �C���N���[�h�t�@�C�� /*/
//#include "main.h"
//
//// ����\���p
//struct Box
//{
//	D3DXVECTOR3 pos;		// ����\���̈ʒu
//	D3DXVECTOR3* pPos;		// �Ώە��̈ʒu�̃A�h���X�i�[
//	D3DXCOLOR col;			// �\���J���[
//	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
//};
//
////�v���g�^�C�v�錾
//void InitVisible_Box(void);			// ����
//void UninitVisible_Box(void);		// �j��
//void UpdateVisible_Box(void);		// �X�V
//void CreateVisible_Box(const COLLISION_AABB box, D3DXCOLOR col, D3DXVECTOR3* pPos);	// ����
//void DeleteVisible_Box(int Box_id);	// ����
//void DrawVisible_Box(void);			// �`��
//
//#endif