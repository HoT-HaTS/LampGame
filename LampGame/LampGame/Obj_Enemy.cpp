//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "Obj_Enemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y - 10;
}

//�C�j�V�����C�Y
void CObjEnemy::Init()
{

	m_vx = INIT_E_VX;		//�ړ��x�N�g��
	m_vy = INIT_E_VY;
	//m_posture = INIT_E_POSTURE;	//�E����0.0f ������1.0f

	m_ani_time = INIT_ANI_TIME;
	m_ani_frame = INIT_ANI_FRAME;	//�Î~�t���[���������ɂ���

	m_speed_power = INIT_E_SPEED_POWER;	//�ʏ푬�x
	m_ani_max_time = INIT_E_ANI_MAX_TIME; //�A�j���[�V�����Ԋu��

	m_move = true;			//true=�E�@false=��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	E_flag = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//�A�N�V����
void CObjEnemy::Action()
{

	//�ʏ푬�x
	//m_speed_power = 0.3;    //�ړ����x
	//m_ani_max_time = 8;		//�A�j���[�V�����Ԋu��

	//Hero.cpp������t���O���擾����
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool L_flag_enemy = hero->Get_L_flag();

	if (L_flag_enemy == true)
	{

		//�u���b�N�Փ˂Ō����ύX
		if (m_hit_left == true)
		{
			m_move = true;
		}
		if (m_hit_right == true)
		{
			m_move = false;
		}

		//�ړ�����
		if (m_move == false)
		{
			m_vx += m_speed_power;
			m_posture = 1.0f;		//�E����
		}
		else if (m_move == true)
		{
			m_vx -= m_speed_power;
			m_posture = 0.0f;		//������
		}


		if (L_flag_enemy == true)
		{
			m_ani_time += 1;
		}

		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		if (m_ani_frame >= 8)
		{
			m_ani_frame = 0;
		}


		//���C
		m_vx += -(m_vx * 0.098);

		//���R�����^��
		m_vy += 9.8 / (16.0f);

		//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
		int d1;

		//�u���b�N�Ƃ̓����蔻����s
		CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		pb->BlockHitEnemy(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&d1);

		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;
	}

		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py);


	//��l���̈ʒu�̎擾
	//CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���ƓG�̂����蔻��`�F�b�N
	//�������Ă���ꍇ
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//�G�̏ザ��Ȃ�����
		if (hy + 120 > m_py)
		{
			//�G�̍������ɐڐG
			if (m_px + scroll->GetScroll() > hx)
			{
				hero->SetRight(true);
				hero->SetX(m_px - 64.5 + scroll->GetScroll());
				hero->SetVX(-0.8);
			}
			//�G�̉E�����ɐڐG
			else if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + 63.5 + scroll->GetScroll());
				hero->SetVX(0.0);
			}
		}
		//�G�̏㕔���ɐڐG
		if (hy + 125 <= m_py)
		{
			hero->SetDown(true);
			hero->SetY(m_py - 128.5);
			hero->SetVY(0.0);
		}
		//�G�̉������ɐڐG
		else if (m_py + 61 <= hy)
		{
			hero->SetUp(true);
			hero->SetY(m_py + 64.5);
			hero->SetVY(0.0);
		}
	}


	if (L_flag_enemy == true)
	{
		//���̐��E����l���̍U����HitBox�ɓ������flag��true�ɂ���
		if (hit->CheckObjNameHit(OBJ_ATTACK) != nullptr)
		{
			E_flag = true;				//�X�C�b�`�̃t���O��true��
		}
		//flag��true�̂Ƃ����g�����ł�����
		if (E_flag == true)
		{
			//�G����SE
			Audio::Start(5);

			this->SetStatus(false);		//�X�C�b�`�������ꂽ�����
			Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
			return;
		}
	}
	
}

//�h���[
void CObjEnemy::Draw()
{
	//�A�j���[�V�����ԍ�
	int AniData[8] =
	{
		0, 1, 2, 3, 4, 5, 6, 7,
	};

	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_right = AniData[m_ani_frame]*BLOCK_SIZE - BLOCK_SIZE * m_posture;
	src.m_left = src.m_right - (1 - m_posture)*BLOCK_SIZE + m_posture * BLOCK_SIZE;
	src.m_bottom = E_YSIZE;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_right = 0.0f + m_px + scroll->GetScroll();
	dst.m_left = dst.m_right + E_XSIZE;
	dst.m_bottom = dst.m_top + E_YSIZE;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(22, &src, &dst, c, 0.0f);
}