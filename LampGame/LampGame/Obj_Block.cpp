//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"

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


	coin_count = 0;
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
		if (hx < BSCROLL_LINE)
		{
			hero->SetX(BSCROLL_LINE);
			m_scroll -= hero->GetVX();
		}

		//�O���X�N���[�����C��
		if (hx > ASCROLL_LINE)
		{
			hero->SetX(ASCROLL_LINE);
			m_scroll -= hero->GetVX();
		}
	}
}

//�h���[
void CObjBlock::Draw()
{
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float  c2[4] = { 1.0f, 1.0f, 1.0f, 0.9f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	bool L_flag_background = hero->Get_L_flag();

	if (L_flag_background == true)
	{
		//�w�i�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = BLOCKCUT_SIZE_R;
		src.m_bottom = BLOCKCUT_SIZE_B;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = DRAW_SIZE_R;
		dst.m_bottom = DRAW_SIZE_B;

		Draw::Draw(((UserData*)Save::GetData())->stage_id + 14, &src, &dst, c, 0.0f);
	}
	else
	{
		//�w�i�\��
		src.m_top = BLOCKCUT_SIZE_T;
		src.m_left = 0.0f;
		src.m_right = BLOCKCUT_SIZE_R;
		src.m_bottom = 2 * BLOCKCUT_SIZE_B;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = DRAW_SIZE_R;
		dst.m_bottom = DRAW_SIZE_B;

		Draw::Draw(((UserData*)Save::GetData())->stage_id + 14, &src, &dst, c, 0.0f);
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
//����11 int* btg			:�S�[�����莞�A�S�[���u���b�N�̃^�C�v��Ԃ�
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

	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	coin_count = hero->GetCoin();

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//���u���b�N�ƃS�[���u���b�N�A�����u���b�N
			if (m_map[i][j] == 1 || m_map[i][j] == 2|| m_map[i][j] == 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * BLOCK_SIZE;
				float by = i * BLOCK_SIZE;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��(�u���b�N�̍�:�E:��:���̏�)
				if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
				{
					//�㉺���E����

					//��l���ƃu���b�N�̒��S��vector�쐬
					float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
					float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

					//����len�����߂�
					float len = sqrt(rvx * rvx + rvy * rvy);

					//�p�xr�����߂�
					float r = atan2(rvy, rvx);	//(���W�A��)
					r = r * 180 / PI;		//�x

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360 - abs(r);

					//�����蔻��p:��l���ƃu���b�N�̊p�x(�̒[)�����߂�
					float a1 = (HBLOCK_INT_Y_SIZE / 2 - 5) + BLOCK_SIZE / 2;	//���	:��l���c+�u���b�N�c����(����)
					float b1 = (HBLOCK_INT_X_SIZE / 2 - 5) + BLOCK_SIZE / 2;  //����	:��l����+�u���b�N������(����)
					float t1 = 90.0 - (atan2(b1, a1) * 180 / PI); //��l���̒��S�ƃu���b�N�̒��S�̊p�x(�P��:�x)
					int t = (int)t1;

					float hit_length = sqrt(a1 * a1 + b1 * b1) - 1;

					//len��������̒������Z���ꍇ�ɔ���ɓ���B
					if (len < hit_length)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < t && r >= 0) || r > 360-t)
						{
							if (m_map[i][j] != 2)
							{
								//�E
								*right = true;								//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
								*x = bx + (BLOCK_SIZE - 0.5) + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
							}
							*btg = m_map[i][j];
						}
						if (r > t && r < 180-t)
						{
							if (m_map[i][j] != 2)
							{
								//��
								*down = true;					//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
								*y = by - (2 * BLOCK_SIZE);		//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vy = 0.0f;
							}
							if (m_map[i][j] >= 2)
							{
								*btu = m_map[i][j];	//�u���b�N�̗v�f(type)���I�u�W�F�N�g�ɓn��
								*btg = m_map[i][j];
							}
						}
						if (r > 180-t && r < 180+t)
						{
							if (m_map[i][j] != 2)
							{
								//��
								*left = true;								//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
								*x = bx - (BLOCK_SIZE + 0.5) + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
							}
							*btg = m_map[i][j];
						}
						if (180+t < r && r < 360-t)
						{
							if (m_map[i][j] != 2)
							{
								//��
								*up = true;						//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
								*y = by + (BLOCK_SIZE - 0.5);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
							}
							*btg = m_map[i][j];
						}
					}
				}
			}
			else if (m_map[i][j] == 5)
			{
				if (switch_flag == true)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//�X�N���[���̉e��
					float scroll = scroll_on ? m_scroll : 0;

					//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��(�u���b�N�̍�:�E:��:���̏�)
					if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
					{
						//�㉺���E����

						//��l���ƃu���b�N�̒��S��vector�쐬
						float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
						float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

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
						if (len < HIT_LENGTH)
						{
							//�p�x�ŏ㉺���E�𔻒�
							if ((r < 58.5 && r >= 0) || r > 301.5)
							{
								//�E
								*right = true;								//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
								*x = bx + (BLOCK_SIZE - 0.5) + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
								*btg = m_map[i][j];
							}
							if (r > 58.5 && r < 121.5)
							{
								//��
								*down = true;					//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
								*y = by - (2 * BLOCK_SIZE);		//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
								if (m_map[i][j] >= 2)
								{
									*btu = m_map[i][j];	//�u���b�N�̗v�f(type)���I�u�W�F�N�g�ɓn��
									*btg = m_map[i][j];
								}
								*vy = 0.0f;
							}
							if (r > 121.5 && r < 238.5)
							{
								//��
								*left = true;								//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
								*x = bx - (BLOCK_SIZE + 0.5) + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
								*btg = m_map[i][j];
							}
							if (238.5 < r && r < 301.5)
							{
								//��
								*up = true;						//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
								*y = by + (BLOCK_SIZE - 0.5);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
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
			else if (m_map[i][j] == 7)
			{
				if (coin_count < 3)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//�X�N���[���̉e��
					float scroll = scroll_on ? m_scroll : 0;

					//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��(�u���b�N�̍�:�E:��:���̏�)
					if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
					{
						//�㉺���E����

						//��l���ƃu���b�N�̒��S��vector�쐬
						float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
						float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

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
						if (len < HIT_LENGTH)
						{
							//�p�x�ŏ㉺���E�𔻒�
							if ((r < 58.5 && r >= 0) || r > 301.5)
							{
								//�E
								*right = true;								//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
								*x = bx + (BLOCK_SIZE - 0.2) + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
								*btg = m_map[i][j];
							}
							if (r > 58.5 && r < 121.5)
							{
								//��
								*down = true;					//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
								*y = by - (2 * BLOCK_SIZE);		//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
								if (m_map[i][j] >= 2)
								{
									*btu = m_map[i][j];	//�u���b�N�̗v�f(type)���I�u�W�F�N�g�ɓn��
									*btg = m_map[i][j];
								}
								*vy = 0.0f;
							}
							if (r > 121.5 && r < 238.5)
							{
								//��
								*left = true;								//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
								*x = bx - (BLOCK_SIZE + 0.2) + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
								*btg = m_map[i][j];
							}
							if (238.5 < r && r < 301.5)
							{
								//��
								*up = true;						//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
								*y = by + (BLOCK_SIZE - 0.2);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
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
}


//BlockHitEnemy�֐�(�G�p�̓����蔻��)
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
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHitEnemy(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* bt
)
{
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	coin_count = hero->GetCoin();

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 1 || m_map[i][j] == 2 || m_map[i][j] == 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

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
			else if (m_map[i][j] == 5)
			{
				if (switch_flag == true)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//�X�N���[���̉e��
					float scroll = scroll_on ? m_scroll : 0;

					//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��(�u���b�N�̍�:�E:��:���̏�)
					if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
					{
						//�㉺���E����

						//��l���ƃu���b�N�̒��S��vector�쐬
						float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
						float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

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
						if (len < 88.0)
						{
							//�p�x�ŏ㉺���E�𔻒�
							if ((r < 45 && r >= 0) || r > 315)
							{
								//�E
								*right = true;								//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
								*x = bx + 64.0f + (scroll);				//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;					//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
								*y = by - (2 * BLOCK_SIZE);		//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
								if (m_map[i][j] >= 2)
								{
								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;								//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll);					//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
							}
							if (225 < r && r < 45)
							{
								//��
								*up = true;						//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
								*y = by + (BLOCK_SIZE - 0.5);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
							}
						}
					}
				}
			}
			else if (m_map[i][j] == 7)
			{
				if (coin_count < 3)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//�X�N���[���̉e��
					float scroll = scroll_on ? m_scroll : 0;

					//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��(�u���b�N�̍�:�E:��:���̏�)
					if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
					{
						//�㉺���E����

						//��l���ƃu���b�N�̒��S��vector�쐬
						float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
						float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

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
						if (len < 88.0)
						{
							//�p�x�ŏ㉺���E�𔻒�
							if ((r < 45 && r >= 0) || r > 315)
							{
								//�E
								*right = true;								//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
								*x = bx + 64.0f + (scroll);				//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;					//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
								*y = by - (2 * BLOCK_SIZE);		//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
								if (m_map[i][j] >= 2)
								{
								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;								//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll);					//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = -(*vx) * 0.1f;							//-VX*�����W��
							}
							if (225 < r && r < 45)
							{
								//��
								*up = true;						//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
								*y = by + (BLOCK_SIZE - 0.5);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
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
}