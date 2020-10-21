//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Block.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBlock::CObjBlock(int map[10][100])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int) * (10 * 100));
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	m_scroll = 0.0f;
}

//�A�N�V����
void CObjBlock::Action()
{
	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	bool L_flag = hero->Get_L_flag();
	
	if (L_flag == true)
	{
		//����X�N���[�����C��
		if (hx < 80)
		{
			hero->SetX(80);
			m_scroll -= hero->GetVX();
		}

		//�O���X�N���[�����C��
		if (hx > 300)
		{
			hero->SetX(300);
			m_scroll -= hero->GetVX();
		}
	}

	/*//�G�o�����C��
	//��l���̈ʒu+500��G�o�����C���ɂ���
	float line = hx + (-m_scroll) + 500;

	//�G�o�����C����v�f�ԍ���
	int ex = ((int)line) / 64;

	//�G�o�����C���̗������
	for (int i = 0; i < 10; i++)
	{
		//��̒�����5��T��
		if (m_map[i][ex] == 5)
		{
			//5������΁A�G���o��
			CObjEnemy* obje = new CObjEnemy(ex * 64.0f, i * 64.0f);
			Objs::InsertObj(obje, OBJ_ENEMY, 10);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}
	}*/
}

//�h���[
void CObjBlock::Draw()
{
	int background_flag = 0;

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	bool L_flag_background = hero->Get_L_flag();

	if (L_flag_background == true)
		background_flag = 0;
	else
		background_flag = 1;

	if (background_flag == 0)
	{
		//�w�i�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 896.0f;
		src.m_bottom = 640.0f;
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	else
	{
		//�w�i�\��
		src.m_top = 640.0f;
		src.m_left = 0.0f;
		src.m_right = 896.0f;
		src.m_bottom = 1280.0f;
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(20, &src, &dst, c, 0.0f);
	}


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f + m_scroll;
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
				else if(m_map[i][j]==6)
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
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[], int block_id)
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
	else if(block_id==1)
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


//BlockHit�֐�(�����蔻��)
//����1	float* x			:������s��object��X�ʒu
//����2 float* y			:������s��object��Y�ʒu
//����3 bool	scroll_on	:������s��object�̓X�N���[���̉e����^���邩�ǂ���(true=�^���� false=�^���Ȃ�)
//����4 bool* up			:�㉺����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
//����5 bool* down			:�㉺����̉������ɂ������Ă��邩�ǂ�����Ԃ�
//����6 bool* left			:�㉺����̍������ɂ������Ă��邩�ǂ�����Ԃ�
//����7 bool* right			:�㉺����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
//����8 float* vx			:���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
//����9 float* vy			:�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
//����10 int* bt			:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//����11 int map[10][100]	:�}�b�v�f�[�^
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHit(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* bt
)
{
	/*int map[10][100];
	int Map[10][100];*/

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	int Scroll = block->GetScroll();
	//Map[10][100] = block->GetMap();

	//�}�b�v�f�[�^���R�s�[
	//memcpy(&Map, map, sizeof(int) * (10 * 100));

	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	int x1 = *x + 32.0f;
	int y1 = *y + 64.0f;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 64.0f + 32.0f;
				float by = i * 64.0f + 32.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 128.0f > by) && (*y < by + 128.0f))
				{
					//�㉺���E����

					//vector�̍쐬(���W)
					float rvx = (x1 + (-scroll)) - bx;
					float rvy = y1 - by;

					//���������߂�
					float len = sqrt(rvx * rvx + rvy * rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//len��������̒����̂��Z���ꍇ�ɔ���ɓ���B
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right = true;	//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
							*x = bx + 64.0f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
							*vx = -(*vx) * 0.1f;	//-VX*�����W��
						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;	//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
							*y = by - 64.0f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
							//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
							if (m_map[i][j] >= 2)
								*bt = m_map[i][j];	//�u���b�N�̗v�f(type)���I�u�W�F�N�g�ɓn��
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;	//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
							*x = bx - 64.0f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
							*vx = -(*vx) * 0.1f;	//-VX*�����W��
						}
						if (225 < r && r < 315)
						{
							//��
							*up = true;	//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
							*y = by + 64.0f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}
