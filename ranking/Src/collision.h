//************************************************
//
// �Փ˔���A�w�b�_�t�@�C��[collision.h]
// Author�F���c����
//
//************************************************
#ifndef _COLLISION_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _COLLISION_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

/*/ �v���g�^�C�v�錾 /*/
bool CollisionSph(const D3DXVECTOR3 sph1, const float r1,
	const D3DXVECTOR3 sph2, const float r2);								// �����m�̏Փ˔���
bool CollisionAABB(const COLLISION_AABB box1, const COLLISION_AABB box2);   // AABB���m�̏Փ˔���

#endif