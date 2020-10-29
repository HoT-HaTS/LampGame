//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Block.h"
#include "Obj_Stage1.h"

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
	float  c[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	bool L_flag_background = hero->Get_L_flag();

	if (L_flag_background == true)
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
		Draw::Draw(20, &src, &dst, c, 0.0f);
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
}


//BlockHit�֐�(�����蔻��)
//����1	float* x			:������s��object(��l���Ȃ�)��X�ʒu
//����2 float* y			:������s��object(��l���Ȃ�)��Y�ʒu
//����3 bool	scroll_on	:������s��object�̓X�N���[���̉e����^���邩�ǂ���(true=�^���� false=�^���Ȃ�)
//����4 bool* up			:�㉺����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
//����5 bool* down			:�㉺����̉������ɂ������Ă��邩�ǂ�����Ԃ�
//����6 bool* left			:�㉺����̍������ɂ������Ă��邩�ǂ�����Ԃ�
//����7 bool* right			:�㉺����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
//����8 float* px			:���E���莞�A���Ε����ɍ��W��ύX���Ĉʒu��Ԃ�
//����9 float* py			:�㉺���莞�A���Ε����ɍ��W��ύX���Ĉʒu��Ԃ�
//����10 int* btu			:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//����11 int* btr			:�E�������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHit(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* btu, int* btg
)
{
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*btu = 0;
	*btg = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 1 || m_map[i][j] == 3)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��(�u���b�N�̍�:�E:��:���̏�)
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 128.0f > by) && (*y < by + 64.0f))
				{
					//�㉺���E����

					//��l���ƃu���b�N�̒��S��vector�쐬
					float rvx = (*x + (-scroll) + 32.0f) - (bx + 32.0f);
					float rvy = (*y + 64.0f) - (by + 32.0f);

					//����len�����߂�
					float len = sqrt(rvx * rvx + rvy * rvy);

					//�p�xr�����߂�
					float r = atan2(rvy, rvx);	//(���W�A��)
					r = r * 180.0f / 3.14f;		//�x

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//len��������̒������Z���ꍇ�ɔ���ɓ���B
					if (len < 111.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 56 && r>=0) || r > 304)
						{
							//�E
							//*right = true;	//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
							*x = bx + 63.5f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
							*vx = -(*vx) * 0.1f;	//-VX*�����W��
							*btg = m_map[i][j];
						}
						if (r > 56 && r < 124)
						{
							//��
							//*down = true;	//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
								*y = by - 128.0f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
							//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
							if (m_map[i][j] >= 2)
							{
								*btu = m_map[i][j];	//�u���b�N�̗v�f(type)���I�u�W�F�N�g�ɓn��
								*btg = m_map[i][j];
							}
							*vy = 0.0f;
						}
						if (r > 124 && r <236 )
						{
							//��
							//*left = true;	//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
							*x = bx - 64.5f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
							*vx = -(*vx) * 0.1f;	//-VX*�����W��
							*btg = m_map[i][j];
						}
						if (236 < r && r < 304)
						{
							//��
							//*up = true;	//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
							*y = by + 63.5f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
							*btg = m_map[i][j];
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


