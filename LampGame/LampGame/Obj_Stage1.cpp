//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Stage1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


CObjStage1::CObjStage1(int map[INIT_MAP_X][INIT_MAP_Y])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int) * (INIT_MAP_X * INIT_MAP_Y));
}

//�C�j�V�����C�Y
void CObjStage1::Init()
{
	//g_f = false;
	g_f2 = true;
	s1_scroll = INIT_SCROLL;
}

//�A�N�V����
void CObjStage1::Action()
{
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	s1_scroll = block->GetScroll();

	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	bool L_flag = hero->Get_L_flag();


	//CObj_G_Block* gflag = (CObj_G_Block*)Objs::GetObj(OBJ_BLOCK);
	//g_f = gflag->Get_G_flag();

	CObj_G_Block2* gflag2 = (CObj_G_Block2*)Objs::GetObj(OBJ_BLOCK);
	g_f2 = gflag2->Get_G2_flag();

	//�G�o�����C��
	//��l���̈ʒu+500��G�o�����C���ɂ���
	float line = hx + (-s1_scroll) + 500;

	//�G�o�����C����v�f�ԍ���
	int ex = ((int)line) / BLOCK_SIZE;

	/*�G�o�����C���̗������
	0:�Ȃɂ��Ȃ�
	1:�X�e�[�W�u���b�N
	2:�S�[���u���b�N
	3:�G�o���p�u���b�N
	4:�e�̐��E�ł��������Ȃ��u���b�N(G3)
	5:�X�C�b�`�������Əo���A���ł���u���b�N(G2)
	6:5�p�̃X�C�b�`
	7:���ƘA������u���b�N(G5)
	8:7�p�̌�
	9:�\��*/

	for (int i = 0; i < INIT_MAP_X; i++)
	{
		//��̒�����STAGEBLOCK��T��
		if (m_map[i][ex] == STAGE_BLOCK)
		{

			//�o���ꏊ�̒l��0�ɂ���
			//m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����GOALBLOCK��T��
		if (m_map[i][ex] == GOAL_BLOCK)
		{

			//�o���ꏊ�̒l��0�ɂ���
			//m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����ENEMYBLOCK��T��
		if (m_map[i][ex] == ENEMY_BLOCK)
		{
			//�G�o��
			CObjEnemy* obje = new CObjEnemy(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(obje, OBJ_ENEMY, 14);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = NO_BLOCK;

		}
		//��̒�����G_BLOCK3��T��
		if (m_map[i][ex] == G_BLOCK3)
		{

			//�o���ꏊ�̒l��0�ɂ���
			//m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����G_BLOCK2��T��
		if (m_map[i][ex] == G_BLOCK2)
		{
			if (g_f2 == false)
			{
				//G2�u���b�N�o��
				CObj_G_Block2* objg2 = new CObj_G_Block2(ex * BLOCK_SIZE, i * BLOCK_SIZE);
				Objs::InsertObj(objg2, OBJ_BLOCK, 8);
			}

			//�o���ꏊ�̒l��0�ɂ���
			//m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����G_BLOCK2�̃X�C�b�`��T��
		if (m_map[i][ex] == G_SWITCH2)
		{
			//�X�C�b�`�o��
			CObjSwitch* objs = new CObjSwitch(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objs, OBJ_SWITCH, 7);

			//�X�C�b�`�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����G_BLOCK5��T��
		if (m_map[i][ex] == G_BLOCK5)
		{

			//�o���ꏊ�̒l��0�ɂ���
			//m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����G_BLOCK5�̃X�C�b�`��T��
		if (m_map[i][ex] == G_SWITCH5)
		{

			//�o���ꏊ�̒l��0�ɂ���
			//m_map[i][ex] = NO_BLOCK;
		}
		////��̒�����G_BLOCK��T��(�e�X�g�p)
		//if (m_map[i][ex] == G_BLOCK)
		//{
		//	//G�u���b�N�o��
		//	CObj_G_Block* objg = new CObj_G_Block(ex * BLOCK_SIZE, i * BLOCK_SIZE);
		//	Objs::InsertObj(objg, OBJ_BLOCK, 8);

		//	//G�u���b�N�o���ꏊ�̒l��0�ɂ���
		//	m_map[i][ex] = NO_BLOCK;
		//}
	}
}

//�h���[
void CObjStage1::Draw()
{
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float  c1[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�u���b�N�`��
	for (int i = 0; i < INIT_MAP_X; i++)
	{
		for (int j = 0; j < INIT_MAP_Y; j++)
		{
			if (m_map[i][j] > NO_BLOCK)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top = i * BLOCK_SIZE;
				dst.m_left = j * BLOCK_SIZE + s1_scroll;
				dst.m_right = dst.m_left + BLOCK_SIZE;
				dst.m_bottom = dst.m_top + BLOCK_SIZE;
				if (m_map[i][j] == 8)
				{
					;//�u���b�N
					//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				else if (m_map[i][j] == GOAL_BLOCK)
				{
					dst.m_top = i * BLOCK_SIZE - 128.0f;
					dst.m_left = j * BLOCK_SIZE + s1_scroll - 128.0f;
					dst.m_right = dst.m_left + 320.0f;
					dst.m_bottom = dst.m_top + 256.0f;
					//�S�[���u���b�N
					BlockDraw(BLOCK_SIZE, 0.0f, &dst, c, GOAL_BLOCK);
				}
				else if (m_map[i][j] == 4)
				{
					;//�M�~�b�N�u���b�N
					//BlockDraw(0.0f, 0.0f, &dst, c, 2);
				}
				else if (m_map[i][j] == 5)
				{
					;//�G�o���p BlockDraw(320.0f, 0.0f, &dst, c);
				}
				else if (m_map[i][j] == 6)
				{
					;//�X�C�b�`�o���p BlockDraw(64.0f, 0.0f, &dst, c, 21);
				}
				else if (m_map[i][j]==STAGE_BLOCK)
				{
					//�X�e�[�W�u���b�N
					BlockDraw(BLOCK_SIZE, 0.0f, &dst, c1, STAGE_BLOCK);
				}
			}
		}
	}
}



//BlockDrawMethod�֐�
//����1 float		x		:���\�[�X�؂���ʒux
//����2 float		y		:���\�[�X�؂���ʒuy
//����3 RECT_F* dst			:�`��ʒu
//����4 float		c[]		:�J���[���
//����5 int block_id		:�u���b�NID
//�u���b�N��64�~64����`��p�B���\�[�X�؂���ʒu�̂�x,y�Őݒ�ł���B
void CObjStage1::BlockDraw(float x, float y, RECT_F* dst, float c[], int block_id)
{
	if (block_id == 6)
	{
		//�M�~�b�N�u���b�N(��)�`��
		RECT_F src;
		src.m_top = y;
		src.m_left = x;
		src.m_right = src.m_left + BLOCK_SIZE;
		src.m_bottom = src.m_top + BLOCK_SIZE;
		//�`��
		Draw::Draw(3, &src, dst, c, 0.0f);
	}
	else if (block_id == STAGE_BLOCK)
	{
		//���u���b�N�`��
		RECT_F src;
		src.m_top = y;
		src.m_left = x;
		src.m_right = src.m_left + BLOCK_SIZE;
		src.m_bottom = src.m_top + BLOCK_SIZE;
		//�`��
		Draw::Draw(21, &src, dst, c, 0.0f);
	}
	else if (block_id == GOAL_BLOCK)
	{
		//�S�[���u���b�N�`��
		RECT_F src;
		src.m_top = y;
		src.m_left = x - BLOCK_SIZE;
		src.m_right = src.m_left + 192.0f;
		src.m_bottom = src.m_top + 128.0f;
		//�`��
		Draw::Draw(24, &src, dst, c, 0.0f);
	}
}