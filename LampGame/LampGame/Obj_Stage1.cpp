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
	s1_scroll = 0.0f;
}

//�A�N�V����
void CObjStage1::Action()
{
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	s1_scroll = block->GetScroll();

	////��l���̈ʒu���擾
	//CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//float hx = hero->GetX();
	//float hy = hero->GetY();
	//bool L_flag = hero->Get_L_flag();

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


	////�G�o�����C��
	////��l���̈ʒu+500��G�o�����C���ɂ���
	//float line = hx + (-m_scroll) + 500;

	////�G�o�����C����v�f�ԍ���
	//int ex = ((int)line) / 64;

	////�G�o�����C���̗������
	//for (int i = 0; i < 10; i++)
	//{
	//	//��̒�����1��T��
	//	if (m_map[i][ex] == 1)
	//	{
	//		//1������΃u���b�N�o��
	//		CObjBlock* objb = new CObjBlock();
	//		Objs::InsertObj(objb, OBJ_BLOCK, 9);

	//		m_map[i][ex] = 99;
	//	}
	//}


}

//�h���[
void CObjStage1::Draw()
{
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

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
					//�M�~�b�N�u���b�N
					BlockDraw(0.0f, 0.0f, &dst, c, 2);
				}
				else if (m_map[i][j] == 3)
				{
					//�Ŕu���b�N
					;//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				//else if (m_map[i][j] == 4)
				//{
				//	;//�S�[���u���b�N
				//}
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
					BlockDraw(64.0f, 0.0f, &dst, c, 1);
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
	if (block_id == 2)
	{
		//�M�~�b�N�u���b�N(��)�`��
		RECT_F src;
		src.m_top = y;
		src.m_left = x;
		src.m_right = src.m_left + 32.0f;
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
}