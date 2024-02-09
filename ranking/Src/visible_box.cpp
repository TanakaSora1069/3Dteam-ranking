////************************************************
////
////��`�̓����蔻�������[visible_rect.cpp]
////author�F���c����
////
////************************************************
//#include "visible_rect.h"
//
//#include "player.h"
//
////�}�N����`
//#define amount_rect	(128)	//���N�g�̍ő吔
//
////�O���[�o���ϐ�
//lpdirect3dvertexbuffer9 g_pvtxbuffrect = null;	//���_�o�b�t�@�ւ̃|�C���^
//lpdirect3dindexbuffer9 g_pidxbuffrect = null;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
//rect g_arect[amount_rect] = {};	//���N�g���
///* 1���N�g������ */
//static const int g_namountvtx = 8;	//���_�̐�
//static const int g_namountprimitive = 12;	//�ӂ̐�
//static const int g_namountidx = g_namountprimitive * 2;	//�C���f�b�N�X�̐�
//
////************************************************
////���N�g����
////************************************************
//void initvisible_rect(void)
//{
//	lpdirect3ddevice9 pdevice = getdevice();	//�f�o�C�X�̎擾
//
//	for (int i = 0; i < amount_rect; i++)
//	{
//		g_arect[i].buse = false;
//		g_arect[i].pos = d3dxvector3(0.0f, 0.0f, 0.0f);
//		g_arect[i].ppos = null;
//		g_arect[i].col = d3dxcolor(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//
//	//���_�o�b�t�@�̐���
//	pdevice->createvertexbuffer(sizeof(vertex_3d) * g_namountvtx * amount_rect,
//		d3dusage_writeonly,
//		fvf_vertex_3d,
//		d3dpool_managed,
//		&g_pvtxbuffrect,
//		null);
//
//	//���_���̃|�C���^
//	vertex_3d* pvtx;
//
//	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
//	g_pvtxbuffrect->lock(0, 0, (void**)&pvtx, 0);
//
//	for (int i = 0; i < g_namountvtx * amount_rect; i++)
//	{
//		//���_���W�̐ݒ�
//		pvtx[i].pos = d3dxvector3(0.0f, 0.0f, 0.0f);
//
//		//�@���x�N�g���̐ݒ�
//		pvtx[i].nor = d3dxvector3(0.0f, 0.0f, 0.0f);
//
//		//���_�J���[�̏����ݒ�
//		pvtx[i].col = d3dxcolor(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//�e�N�X�`�����W�̏����ݒ�
//		pvtx[i].tex = d3dxvector2(0.0f, 0.0f);
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pvtxbuffrect->unlock();
//
//	//�C���f�b�N�X�o�b�t�@�̐���
//	pdevice->createindexbuffer(sizeof(word) * g_namountidx * amount_rect,
//		d3dusage_writeonly,
//		d3dfmt_index16,
//		d3dpool_managed,
//		&g_pidxbuffrect,
//		null);
//
//	//�C���f�b�N�X�o�b�t�@�̃|�C���^
//	word* pidx;
//
//	//�C���f�b�N�X�o�b�t�@�����b�N
//	g_pidxbuffrect->lock(0, 0, (void**)&pidx, 0);
//
//	for (int i = 0; i < amount_rect; i++)
//	{
//		/* x���ɕ��s�Ȑ������� */
//		for (int j = 0; j < 8; j++, pidx++)
//		{
//			pidx[0] = (word)j;
//		}
//
//		/* y���ɕ��s�Ȑ������� */
//		for (int j = 0, k = 0; j < 4; j++, pidx += 2)
//		{
//			if (j == 2) k += 2;	/* 0,1,4,5�����C�̎n�_�ɂ��邽��3,4�̃C���f�b�N�X���΂� */
//
//			pidx[0] = (word)(j + k);
//			pidx[1] = (word)(j + 2 + k);
//		}
//
//		/* z���ɕ��s�Ȑ������� */
//		for (int j = 0; j < 4; j++, pidx += 2)
//		{
//			pidx[0] = (word)(j);
//			pidx[1] = (word)(j + 4);
//		}
//	}
//
//	//�C���f�b�N�X�o�b�t�@���A�����b�N
//	g_pidxbuffrect->unlock();
//}
//
////************************************************
////���N�g�W�J
////************************************************
//void setsizevisible_rect(const collision_aabb obj, d3dxcolor col, d3dxvector3* ppos)
//{
//	//���_���̃|�C���^
//	vertex_3d* pvtx;
//
//	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
//	g_pvtxbuffrect->lock(0, 0, (void**)&pvtx, 0);
//
//	for (int i = 0; i < amount_rect; i++, pvtx += g_namountvtx)
//	{
//		if (g_arect[i].buse) continue;
//
//		g_arect[i].buse = true;
//
//		/* �Ώۂ̃��[���h���W�𑊎E�����_��W�J���� */
//		pvtx[0].pos = { obj.min.x - ppos->x, obj.max.y - ppos->y, obj.min.z - ppos->z };
//		pvtx[1].pos = { obj.max.x - ppos->x, obj.max.y - ppos->y, obj.min.z - ppos->z };
//		pvtx[2].pos = { obj.min.x - ppos->x, obj.min.y - ppos->y, obj.min.z - ppos->z };
//		pvtx[3].pos = { obj.max.x - ppos->x, obj.min.y - ppos->y, obj.min.z - ppos->z };
//		pvtx[4].pos = { obj.min.x - ppos->x, obj.max.y - ppos->y, obj.max.z - ppos->z };
//		pvtx[5].pos = { obj.max.x - ppos->x, obj.max.y - ppos->y, obj.max.z - ppos->z };
//		pvtx[6].pos = { obj.min.x - ppos->x, obj.min.y - ppos->y, obj.max.z - ppos->z };
//		pvtx[7].pos = { obj.max.x - ppos->x, obj.min.y - ppos->y, obj.max.z - ppos->z };
//
//		for (int j = 0; j < g_namountvtx; j++)
//		{
//			pvtx[j].col = col;
//		}
//
//		/* �Ώۂ̃��[���h���W�ɓ������� */
//		g_arect[i].ppos = ppos;
//
//		break;
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pvtxbuffrect->unlock();
//}
//
////************************************************
////���N�g�j��
////************************************************
//void uninitvisible_rect(void)
//{
//	//���_�o�b�t�@�̔j��
//	if (g_pvtxbuffrect != null)
//	{
//		g_pvtxbuffrect->release();
//		g_pvtxbuffrect = null;
//	}
//
//	//�C���f�b�N�X�o�b�t�@�̔j��
//	if (g_pidxbuffrect != null)
//	{
//		g_pidxbuffrect->release();
//		g_pidxbuffrect = null;
//	}
//}
//
////************************************************
////���N�g�X�V
////************************************************
//void updatevisible_rect(void)
//{
//	//�Ώە��̒��S��
//	for (int i = 0; i < amount_rect; i++)
//	{
//		if (!g_arect[i].buse) continue;
//
//		g_arect[i].pos = *g_arect[i].ppos;
//	}
//
//	///* ���𑾂����邽��3�������ɏ��������炷 */
//	//g_arect[1].pos.x += 0.15f;
//	//g_arect[2].pos.x += -0.15f;
//
//	//g_arect[3].pos.y += 0.15f;
//	//g_arect[4].pos.y += -0.15f;
//
//	//g_arect[5].pos.z += 0.15f;
//	//g_arect[6].pos.z += -0.15f;
//}
//
////************************************************
////���N�g�`��
////************************************************
//void drawvisible_rect(void)
//{
//	lpdirect3ddevice9 pdevice = getdevice();	//�f�o�C�X�̎擾
//
//	//���C�g���I�t
//	pdevice->setrenderstate(d3drs_lighting, false);
//
//	d3dxmatrix mtxrot, mtxtrans;	//�v�Z�p�}�g���b�N�X
//
//	for (int i = 0; i < amount_rect; i++)
//	{
//		if (!g_arect[i].buse) continue;
//
//		//���[���h�}�g���b�N�X�̏�����
//		d3dxmatrixidentity(&g_arect[i].mtxworld);
//
//		//�ʒu�𔽉f1
//		d3dxmatrixtranslation(&mtxtrans,
//			g_arect[i].pos.x,
//			g_arect[i].pos.y,
//			g_arect[i].pos.z);
//
//		//�ʒu�𔽉f2
//		d3dxmatrixmultiply(&g_arect[i].mtxworld,
//			&g_arect[i].mtxworld,
//			&mtxtrans);
//
//		//���[���h�}�g���b�N�X�̐ݒ�
//		pdevice->settransform(d3dts_world, &g_arect[i].mtxworld);
//
//		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pdevice->setstreamsource(0, g_pvtxbuffrect, 0, sizeof(vertex_3d));
//
//		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pdevice->setindices(g_pidxbuffrect);
//
//		//���_�t�H�[�}�b�g�̐ݒ�
//		pdevice->setfvf(fvf_vertex_3d);
//
//		//�e�N�X�`���̐ݒ�
//		//pdevice->settexture(0, null);
//
//		//���N�g�̕`��
//		pdevice->drawindexedprimitive(d3dpt_linelist, i * g_namountvtx, 0, g_namountvtx,
//			0, g_namountprimitive);
//	}
//
//	//���C�g���I��
//	pdevice->setrenderstate(d3drs_lighting, true);
//}