//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"

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
	g_f2 = false;
	s1_scroll = INIT_SCROLL;
	l_f = true;

	alpha = 1.0f;
	count = 0;
	t = 0;
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

	CObj_G_Block2* gflag2 = (CObj_G_Block2*)Objs::GetObj(OBJ_BLOCK);
	g_f2 = gflag2->Get_G2_flag();


	//��l���̈ʒu+300��object�o�����C��(�����l)�ɂ��A+500��object�̏o�����C���ɂ���B
	float line = hx + (-s1_scroll) + OBJECT_LINE  + t;
	if (t < 200)
	{
		t += 64;
	}

	//object�o�����C����v�f�ԍ���
	int ex = ((int)line) / BLOCK_SIZE;

	ScrollLine(ex);

}

//ScrollLine�֐�
//�v�f�ԍ������ƂɃu���b�N�����o��������
//����1	int ex �}�b�v��x���W(�v�f�ԍ�)
void CObjStage1::ScrollLine(int ex)
{

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
			//G3�u���b�N�o��
			CObj_G_Block3* objg3 = new CObj_G_Block3(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objg3, G_BLOCK3, 7);

			//�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����G_BLOCK2��T��
		if (m_map[i][ex] == G_BLOCK2)
		{
			//G2�u���b�N�o��
			CObj_G_Block2* objg2 = new CObj_G_Block2(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objg2, OBJ_BLOCK, 8);

			//�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����SWITCH2�̃X�C�b�`��T��
		if (m_map[i][ex] == G_SWITCH2)
		{
			//�X�C�b�`2�o��
			CObjSwitch2* objs2 = new CObjSwitch2(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objs2, OBJ_SWITCH2, 7);

			//�X�C�b�`2�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����G_BLOCK5��T��
		if (m_map[i][ex] == G_BLOCK5)
		{
			//G5�u���b�N�o��
			CObj_G_Block5* objg5 = new CObj_G_Block5(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objg5, OBJ_BLOCK, 8);

			//�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = NO_BLOCK;
		}
		//��̒�����R�C����T��
		if (m_map[i][ex] == G_SWITCH5)
		{
			//�R�C���o��
			CObjKeyCoin* objs5 = new CObjKeyCoin(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objs5, OBJ_KEYCOIN, 7);

			//�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = NO_BLOCK;
		}
	}
}

//�h���[
void CObjStage1::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool S_flag = hero->GetG_Flag();

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
				if (m_map[i][j] == G_SWITCH5)
				{
					;//�u���b�N
					//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				if (m_map[i][j] == 9)
				{
					;//�u���b�N
					//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				else if (m_map[i][j] == GOAL_BLOCK)
				{
					if (S_flag == true)
						alpha -= 0.01f;

					float gc[4] = { 1.0f,1.0f,1.0f,alpha };

					dst.m_top = i * BLOCK_SIZE - GOAL_T;
					dst.m_left = j * BLOCK_SIZE + s1_scroll - GOAL_T;
					dst.m_right = dst.m_left + GOAL_R;
					dst.m_bottom = dst.m_top + GOAL_B;
					
					//�S�[���u���b�N�`��
					BlockDraw(BLOCK_SIZE, 0.0f, &dst, gc, GOAL_BLOCK);
				}
				else if (m_map[i][j] == G_BLOCK3)
				{
					//�M�~�b�N�u���b�N
					//BlockDraw(BLOCK_SIZE, 0.0f, &dst, c, G_BLOCK3);
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
	//��l��������t���O���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool l_f = hero->Get_L_flag();

	if (block_id == 6)
	{
		//�M�~�b�N�u���b�N2��`��
		//RECT_F src;
		//src.m_top = y;
		//src.m_left = x;
		//src.m_right = src.m_left + BLOCK_SIZE;
		//src.m_bottom = src.m_top + BLOCK_SIZE;
		////�`��
		//Draw::Draw(3, &src, dst, c, 0.0f);
	}
	else if (block_id == STAGE_BLOCK)
	{
		if (l_f == true)
		{
			//���u���b�N(��)�`��
			RECT_F src;
			src.m_top = y;
			src.m_left = x;
			src.m_right = src.m_left + BLOCK_SIZE;
			src.m_bottom = src.m_top + BLOCK_SIZE;
			//�`��
			Draw::Draw(((UserData*)Save::GetData())->stage_id + 40, &src, dst, c, 0.0f);
		}

		else if (l_f == false)
		{
			//���u���b�N(�e)�`��
			RECT_F src;
			src.m_top = y;
			src.m_left = x;
			src.m_right = src.m_left + BLOCK_SIZE;
			src.m_bottom = src.m_top + BLOCK_SIZE;
			//�`��
			Draw::Draw(51, &src, dst, c, 0.0f);
		}
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
	else if (block_id == G_BLOCK3)
	{
		if (l_f == false)
		{
			//���u���b�N(�e)�`��
			RECT_F src;
			src.m_top = y;
			src.m_left = x;
			src.m_right = src.m_left + BLOCK_SIZE;
			src.m_bottom = src.m_top + BLOCK_SIZE;
			//�`��
			Draw::Draw(5, &src, dst, c, 0.0f);
		}
	}
}