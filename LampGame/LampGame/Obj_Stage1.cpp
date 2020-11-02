//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Stage1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


CObjStage1::CObjStage1(int map[10][100])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int) * (10 * 100));
}

//�C�j�V�����C�Y
void CObjStage1::Init()
{
	g_f = false;
	s1_scroll = 0.0f;
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


	CObj_G_Block* gflag = (CObj_G_Block*)Objs::GetObj(OBJ_BLOCK);
	g_f = gflag->Get_G_flag();



	//if (L_flag == true)
	//{
	//	//����X�N���[�����C��
	//	if (hx < 80)
	//	{
	//		hero->SetX(80);
	//		m_scroll -= hero->GetVX();
	//	}

	//	//�O���X�N���[�����C��
	//	if (hx > 300)
	//	{
	//		hero->SetX(300);
	//		m_scroll -= hero->GetVX();
	//	}
	//}

	//�G�o�����C��
	//��l���̈ʒu+500��G�o�����C���ɂ���
	float line = hx + (-s1_scroll) + 500;

	//�G�o�����C����v�f�ԍ���
	int ex = ((int)line) / 64;

	//�G�o�����C���̗������
	for (int i = 0; i < 10; i++)
	{
		//��̒�����6��T��
		if (m_map[i][ex] == 6)
		{
			//6�������G�u���b�N�o��
			CObj_G_Block* objg = new CObj_G_Block(ex * 64.0f, i * 64.0f);
			Objs::InsertObj(objg, OBJ_BLOCK, 8);

			//G�u���b�N�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;

		}
		if (m_map[i][ex] == 2)
		{
			//2������ΊŔo��
			CObjBoard* objt = new CObjBoard(ex * 64.0f, i * 64.0f);
			Objs::InsertObj(objt, OBJ_BOARD, 9);

			//�Ŕo���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}
		//��̒�����4��T��
		if (m_map[i][ex] == 4)
		{
			//4������ΓG�o��
			CObjEnemy* obje = new CObjEnemy(ex * 64.0f, i * 64.0f);
			Objs::InsertObj(obje, OBJ_ENEMY, 14);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;

		}
		//��̒�����7��T��
		if (m_map[i][ex] == 7)
		{
			//7������΃X�C�b�`�o��
			CObjSwitch* objs = new CObjSwitch(ex * 64.0f, i * 64.0f);
			Objs::InsertObj(objs, OBJ_SWITCH, 7);

			//�X�C�b�`�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}
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
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f + s1_scroll;
				dst.m_right = dst.m_left + 64.0f;
				dst.m_bottom = dst.m_top + 64.0f;
				if (m_map[i][j] == 2)
				{
					;//�Ŕu���b�N
					//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				else if (m_map[i][j] == 3)
				{
					dst.m_top = i * 64.0f - 128.0f;
					dst.m_left = j * 64.0f + s1_scroll - 128.0f;
					dst.m_right = dst.m_left + 320.0f;
					dst.m_bottom = dst.m_top + 256.0f;
					//�S�[���u���b�N
					BlockDraw(64.0f, 0.0f, &dst, c, 3);
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
				else
				{
					//���u���b�N
					BlockDraw(64.0f, 0.0f, &dst, c1, 1);
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
		src.m_right = src.m_left + 64.0f;
		src.m_bottom = src.m_top + 64.0f;
		//�`��
		Draw::Draw(3, &src, dst, c, 0.0f);
	}
	else if (block_id == 1)
	{
		//���u���b�N�`��
		RECT_F src;
		src.m_top = y;
		src.m_left = x;
		src.m_right = src.m_left + 64.0f;
		src.m_bottom = src.m_top + 64.0f;
		//�`��
		Draw::Draw(21, &src, dst, c, 0.0f);
	}
	else if (block_id == 3)
	{
		//�S�[���u���b�N�`��
		RECT_F src;
		src.m_top = y;
		src.m_left = x - 64.0f;
		src.m_right = src.m_left + 192.0f;
		src.m_bottom = src.m_top + 128.0f;
		//�`��
		Draw::Draw(24, &src, dst, c, 0.0f);
	}
}