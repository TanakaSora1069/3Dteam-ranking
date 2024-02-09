//************************************************
//
// �Փ˔���[collision.cpp]
// Author�F���c����
//
//************************************************
/*/ �C���N���[�h�t�@�C�� /*/
#include "collision.h"
// �f�o�b�O��
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif	// _DEBUG

/*/ �}�N����` /*/
#define SPH_AABB_VERIFY 0  // �Փ˔���̎�����ύX

//************************************************
// �����m�̏Փ˔���
//************************************************
bool CollisionSph(const D3DXVECTOR3 sph1, const float r1, const D3DXVECTOR3 sph2, const float r2)
{
    // ����1���狅��2�ւ̃x�N�g�����Z�o
    D3DXVECTOR3 vec = sph2 - sph1;

    // ���̊Ԃ̋������Z�o
    float dist = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    // ���̊ԋ������݂��̔��a�̍��v�ȉ��ł���ΐڐG
    return (dist <= r1 + r2);
}

//************************************************
// ����AABB�̏Փ˔���
//************************************************
#pragma warning(disable:4100)
bool CollisionSph(const D3DXVECTOR3 sph, const float r, const COLLISION_AABB box)
#pragma warning(default:4100)
{
#if SPH_AABB_VERIFY
    
    // ����̓E�\�ł�
    return (sph.x < box.max.x &&
        sph.x > box.min.x &&
        sph.y < box.max.y &&
        sph.y > box.min.y &&
        sph.z < box.max.z &&
        sph.z > box.min.z);

#else
    return false;
#endif
}

//************************************************
// AABB���m�̏Փ˔���
//************************************************
bool CollisionAABB(const COLLISION_AABB box1, const COLLISION_AABB box2)
{
    // �e���ł��݂��̍ő�E�ŏ������Ԑ������d�Ȃ�ΐڐG
    return (box1.min.x < box2.max.x &&
        box1.max.x > box2.min.x &&
        box1.min.y < box2.max.y &&
        box1.max.y > box2.min.y &&
        box1.min.z < box2.max.z &&
        box1.max.z > box2.min.z);
}