//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"

#include "GameHead.h"
#include "Obj_Hero.h"
#include "GameL/Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;



//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = INIT_H_PX;		//�ʒu
	m_py = INIT_H_PY;
	m_vx = INIT_H_VX;		//�ړ��x�N�g��
	m_vy = INIT_H_VY;
	m_sx = INIT_H_PX;		//���E�؂�ւ����̈ʒu
	m_sy = INIT_H_PY;

	m_posture = INIT_H_POSTURE;	//�E����0.0f ������1.0f
	m_sposture = INIT_H_POSTURE;//�E����0.0f ������1.0f

	m_ani_time = INIT_ANI_TIME;
	m_dani_time = INIT_ANI_TIME;
	m_ani_frame = INIT_ANI_FRAME;	//�Î~�t���[���������ɂ���
	m_dani_frame = INIT_ANI_FRAME;	//�Î~�t���[���������ɂ���
	m_ani_s_time = INIT_ANI_TIME;
	m_ani_s_frame = INIT_ANI_FRAME;	//�Î~�t���[���������ɂ���


	m_speed_power = INIT_SPEED_POWER;	//�ʏ푬�x
	m_ani_max_time = INIT_H_ANI_MAX_TIME;	//�A�j���[�V�����Ԋu��
	m_dani_max_time = INIT_H_ANI_MAX_TIME;	//�A�j���[�V�����Ԋu��

	attack_flag = true;	//�U������p�t���O

	L_flag = true;	//�J�n���͌��t���OON
	m_flag = true;	//���̐��E����p
	m_flagj = true; //�W�����v����p

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_hit_down2=false;

	m_block_type_under = BLOCK_TYPE_U;	//����ł���block�̎�ފm�F�p(��)
	m_block_type_goal = BLOCK_TYPE_G;	//block�̎�ފm�F�p(�E)

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, HBLOCK_INT_X_SIZE, HBLOCK_INT_Y_SIZE, ELEMENT_PLAYER, OBJ_HERO, 1);

	//�����e�ړ��p�ϐ�
	move_flag = true;
	x = 0;
	y = 0;
	ar = 0;

	fall_time = 0;

	m_coin_count = 0;

	count = 0;

	dead_flag = false;
	audio = false;

	respawn_time = 0;
	hg_flag = false;
	goal_white = 0;
}

//�A�N�V����
void CObjHero::Action()
{
	if (dead_flag == false)
	{
		if (pause_flag == false)
		{
			//�����ɂ��Q�[���I�[�o�[
			if (m_py > STAGE_Y_OUT)
			{
				dead_flag = true;
				Audio::Start(12);
			}


			if (move_flag == true)
			{
				//�u���b�N�Ƃ̓����蔻����s
				CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
				pb->BlockHit(&m_px, &m_py, true,
					&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
					&m_block_type_under, &m_block_type_goal);


				//if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
				{
					//��l���̍U��
					if (Input::GetVKey('Z') == true)
					{
						if (attack_flag == true && hg_flag == false)
						{
							//�U���I�u�W�F�N�g�̍쐬
							CObjAttack* obj_attack = new CObjAttack(m_px, m_py); //�e�ۃI�u�W�F�N�g�쐬
							Objs::InsertObj(obj_attack, OBJ_ATTACK, 100);		//������e�ۃI�u�W�F�N�g���}�l�[�W���[�ɓo�^

							//�U������炷
							Audio::Start(9);

							attack_flag = false;
						}
					}
					else
					{
						attack_flag = true;
					}
				}
				//�ړ�(���̐��E)
				if (L_flag == true)
				{
					//�L�[�̓��͕���
					if (Input::GetVKey(VK_RIGHT) == true)
					{
						m_vx += m_speed_power;
						m_posture = 1.0f;
						m_ani_time += 1.0;
					}
					else if (Input::GetVKey(VK_LEFT) == true)
					{
						m_vx -= m_speed_power;
						m_posture = 0.0f;
						m_ani_time += 1.0;
					}
					else
					{
						m_ani_frame = 1;	//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
						m_ani_time = 0;
					}

					//A�L�[���͂ŃW�����v
					if (Input::GetVKey(' ') == true)
					{
						if (m_flagj == true)
						{
							if (m_hit_down == true || m_hit_down2 == true)
							{
								//jump����炷
								Audio::Start(2);

								m_vy = -10;
								m_hit_down = false;
								m_hit_down2 = false;
								m_flagj = false;
							}
						}
					}
					else
					{
						m_flagj = true;
					}
					//���C
					m_vx += -(m_vx * INIT_FRICTION);

					//���R�����^��
					m_vy += 9.8 / (20.0f);

					//�ʒu�̍X�V
					m_px += m_vx;
					m_py += m_vy;
				}

				//�ړ�(�e�̐��E)
				if (L_flag == false)
				{
					//�L�[�̓��͕���
					if (Input::GetVKey(VK_RIGHT) == true)
					{
						m_vx += m_speed_power;
						m_posture = 1.0f;
						m_ani_time += 1.0;
					}
					else if (Input::GetVKey(VK_LEFT) == true)
					{
						m_vx -= m_speed_power;
						m_posture = 0.0f;
						m_ani_time += 1.0;
					}

					if (Input::GetVKey(VK_UP) == true)
					{
						m_vy -= m_speed_power;
					}
					else if (Input::GetVKey(VK_DOWN) == true)
					{
						m_vy += m_speed_power;
					}

					if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
					{
						m_ani_frame = 1;	//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
						m_ani_time = 0;
					}

					//���C
					m_vx += -(m_vx * INIT_FRICTION);
					m_vy += -(m_vy * INIT_FRICTION);

					//�ʒu�̍X�V
					m_px += m_vx;
					m_py += m_vy;


					//�E����
					if (m_px + BLOCK_SIZE > STAGE_X_OUT)
					{
						m_px = STAGE_X_OUT - BLOCK_SIZE; //�͂ݏo�Ȃ��ʒu�Ɉړ�������B
					}
					//������
					if (m_px < 0.0f)
					{
						m_px = 0.0f;
					}
					//�����
					if (m_py < 0.0f)
					{
						m_py = 0.0f;
					}
					////������
					//if (m_py + 128.0f > 600 )
					//{
					//	m_py = 600.0f - 128.0f;
					//}
				}
				//���g��HitBox�������Ă���
				CHitBox* hit = Hits::GetHitBox(this);

				//HitBox�̈ʒu�̕ύX
				hit->SetPos(m_px, m_py);

				//�G�I�u�W�F�N�g�ƐڐG������dead_flag��true�ɂ���
				if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
				{
					if (L_flag == true)
					{
						dead_flag = true;
						if (audio == false)
						{
							Audio::Start(10);
							audio = true;
						}
					}
				}
			}


			//�A�j���[�V����
			if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
			{
				m_ani_s_time += 1.0;
			}
			//�A�j���[�V�����֘A(�Î~�p)
			if (m_ani_s_time > m_ani_max_time)
			{
				m_ani_s_frame += 1;
				m_ani_s_time = 0;
			}
			if (m_ani_s_frame == m_ani_max_time)
			{
				m_ani_s_frame = 0;
			}



			//�A�j���[�V�����֘A(�ړ��p)
			if (m_ani_time > m_ani_max_time)
			{
				m_ani_frame += 1;
				m_ani_time = 0;
			}
			if (m_ani_frame == m_ani_max_time)
			{
				m_ani_frame = 0;
			}


			if (move_flag == true)
			{
				//���E�؂�ւ�:�����e(X�����Ɛ؂�ւ�)
				if (L_flag == true && hg_flag == false)
				{
					if (Input::GetVKey('X') == true)
					{
						if (m_flag == true)
						{
							L_flag = false;
							m_flag = false;
							m_vy = 0;
							m_block_type_goal = 0;
							m_sx = m_px;
							m_sy = m_py;
							m_sposture = m_posture;

							//�ړ�����炷(�����e)
							Audio::Start(1);
						}
					}
					else
					{
						m_flag = true;
					}
				}

				//���E�؂�ւ�:�e����(X�����Ɛ؂�ւ�)
				if (L_flag == false)
				{
					if (Input::GetVKey('X') == true)
					{
						if (m_flag == true)
						{
							m_vx = 0;
							m_vy = 0;
							move_flag = false;
							m_block_type_goal = 0;
							Hits::DeleteHitBox(this);	//��l�������L����HitBox���폜

							//�ړ�����炷(�e����)
							Audio::Start(0);
						}
					}
					else
					{
						m_flag = true;
					}
				}
			}

			//�e�������Ɏ�l���̈ʒu�����ɖ߂�
			if (move_flag == false)
			{
				x = m_sx - m_px;
				y = m_sy - m_py;
				ar = GetAtan2Angle(x, -y);

				//�ړ���������l���@�̕����ɂ���
				m_vx = cos(3.14 / 180 * ar);
				m_vy = -sin(3.14 / 180 * ar);
				UnitVec(&m_vx, &m_vy);

				m_px += 12 * m_vx;
				m_py += 12 * m_vy;

				if (m_sx - 10 < m_px && m_px < m_sx + 10 && m_sy - 10 < m_py && m_py < m_sy + 10)
				{
					//�����蔻��p��HitBox���쐬
					Hits::SetHitBox(this, m_px, m_py, HBLOCK_INT_X_SIZE, HBLOCK_INT_Y_SIZE, ELEMENT_PLAYER, OBJ_HERO, 1);
					L_flag = true;
					m_flag = false;
					move_flag = true;
					m_posture = m_sposture;
				}
			}

			//�S�[����
			if (L_flag == true)
			{
				if (hg_flag == true)
					goal_white += 1;
				//�X�e�[�W�I������(�S�[�����B)
				if (m_block_type_goal == H_GOAL_BLOCK)
				{
					hg_flag = true;
					((UserData*)Save::GetData())->clear[((UserData*)Save::GetData())->stage_id] = true;
				}
				
				if (goal_white > 300)
				{
					for (int i = 1; i <= 6; i++)
					{
						if (((UserData*)Save::GetData())->clear[i] == true)
						{
							count++;
						}
					}

					hg_flag = false;
					goal_white = 0;
					if (count == 6)
					{
						Scene::SetScene(new CSceneClear());
					}
					else
					{
						Scene::SetScene(new CSceneSelect());
					}
				}
				
			}
		}
	}
	//���S�����
	if (dead_flag == true)
	{
		//m_dani_time ++;
		respawn_time++;
	}

	if (respawn_time == 8)
	{
		m_dani_frame++;
		respawn_time = 0;
	}

	if (m_dani_frame == 20)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);

		Scene::SetScene(new CSceneStage_1());
		switch_flag = true;
	}
}


//�h���[
void CObjHero::Draw()
{
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float  c1[4] = { 0, 0, 0, 1.0 };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�e�̈ʒu�̂�e�X�g�p
	RECT_F src1;	//�`�挳�؂���ʒu
	RECT_F dst1;	//�`���\���ʒu

	if (dead_flag == false)
	{
		//�A�j���[�V�����ԍ�
		int AniData[5] =
		{
			0, 1, 2, 3, 1,
		};
		//�؂���ʒu�̐ݒ�
		if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false || pause_flag == true)
		{
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData[m_ani_s_frame] * HBLOCK_INT_X_SIZE;
			src.m_right = HBLOCK_INT_X_SIZE + AniData[m_ani_s_frame] * HBLOCK_INT_X_SIZE;
			src.m_bottom = HBLOCK_INT_Y_SIZE;
		}
		else if (pause_flag == false)
		{
			src.m_top = HBLOCK_INT_Y_SIZE;
			src.m_left = 0.0f + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
			src.m_right = HBLOCK_INT_X_SIZE + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
			src.m_bottom = src.m_top + HBLOCK_INT_Y_SIZE;
		}

		//�e���̎�l���̌��̈ʒu��\������摜
		src1.m_top = 0.0f;
		src1.m_left = HBLOCK_INT_X_SIZE;
		src1.m_right = HBLOCK_INT_X_SIZE + HBLOCK_INT_X_SIZE;
		src1.m_bottom = HBLOCK_INT_Y_SIZE;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = (HBLOCK_INT_X_SIZE - HBLOCK_INT_X_SIZE * m_posture) + m_px;
		dst.m_right = (HBLOCK_INT_X_SIZE * m_posture) + m_px;
		dst.m_bottom = HBLOCK_INT_Y_SIZE + m_py;

		//�e���̎�l���̌��̈ʒu��\������ʒu
		dst1.m_top = 0.0f + m_sy;
		dst1.m_left = (HBLOCK_INT_X_SIZE - HBLOCK_INT_X_SIZE*m_sposture ) + m_sx;
		dst1.m_right = (HBLOCK_INT_X_SIZE*m_sposture ) + m_sx;
		dst1.m_bottom = HBLOCK_INT_Y_SIZE + m_sy;

		//���t���O��ON�Ȃ�
		if (L_flag == true)
		{
			//2�Ԗڂɓo�^�����O���t�B�b�N(��l���E��)��src�Edst�Ec �̏������Ƃɕ`��
			Draw::Draw(2, &src, &dst, c, 0.0f);
		}
		//���t���O��OFF�Ȃ�
		else
		{
			//1�Ԗڂɓo�^�����O���t�B�b�N(��l���E�e)��src�Edst�Ec �̏������Ƃɕ`��
			Draw::Draw(1, &src, &dst, c, 0.0f);
			////�e���̎�l���̌��̈ʒu��\������
			Draw::Draw(1, &src1, &dst1, c1, 0.0f);
		}
	}
	if (dead_flag == true)
	{
		//�A�j���[�V�����ԍ�
		int AniData[16] =
		{
			0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
		};
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = AniData[m_dani_frame] * 2 * BLOCK_SIZE;
		src.m_right = src.m_left + 2 * BLOCK_SIZE;
		src.m_bottom = 2 * BLOCK_SIZE;

		//�\���ʒu�̐ݒ�
		dst.m_top =  m_py;
		dst.m_left = m_px - 64;
		dst.m_right = dst.m_left + 2*BLOCK_SIZE;
		dst.m_bottom = dst.m_top + 2*BLOCK_SIZE;

		//6�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
}


//---GetAtan2Angle�֐�
//����1		float w		:��
//����2		float h		:����
//�߂�l	float		:�p�x(0���`360��)
//���e		
//�����ƕ����璼�p�O�p�`������Ɖ��肵���̊p�x�����߂�B
float CObjHero:: GetAtan2Angle(float w, float h)
{
	//atan2�Ŋp�x�����߂�
	float r = atan2(h, w) * 180.0f / 3.14f;

	//-180.0���`0����180���`360���ɕϊ�
	if (r < 0)
	{
		r = 360 - fabs(r);
	}

	return r;
}

//---UnitVec�֐�
//����1�@float*vx	:�x�N�g����x�����̃|�C���^
//����2�@float*vy	:�x�N�g����y�����̃|�C���^
//�߂�l bool		:true=�v�Z����	false=�v�Z���s
//���e
//�����̃x�N�g���𐳋K�������̒l��vx,vy�ɕύX����
bool CObjHero:: UnitVec(float* vx, float* vy)
{
	//�x�N�g���̒��������߂�i�O�����̒藝�j
	float r = 0.0f;
	r = (*vx) * (*vx) + (*vy) * (*vy);
	r = sqrt(r);

	//������0���ǂ������ׂ�
	if (r == 0.0f)
	{
		//0�Ȃ�v�Z���s
		return false;
	}
	else
	{
		//���K�����s��vx��vy�̎Q�Ɛ�̒l��ύX
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);
	}

	//�v�Z����
	return true;
}

//HeroMove�֐�:X�{�^�����������u�Ԃ̌��Ɖe�̈ʒu����p�x�����߂Ĉ�葬�x�Ō��̈ʒu�ɖ߂�
void CObjHero::HeroMove(float mx,float my, float sx, float sy, float vx, float vy)
{
		float x = sx - mx;
		float y = sy - my;
		float ar = GetAtan2Angle(x, -y);

		//�ړ���������l���@�̕����ɂ���
		vx = cos(3.14 / 180 * ar);
		vy = -sin(3.14 / 180 * ar);
		UnitVec(&vx, &vy);

		sx += 20 * vx;
		sy += 20 * vy;
}