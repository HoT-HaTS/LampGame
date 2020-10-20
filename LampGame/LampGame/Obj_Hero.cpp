//�g�p����w�b�_�[�t�@�C��
#include <math.h>
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_Hero.h"

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

	int m_ani_time = INIT_ANI_TIME;
	int m_ani_frame = INIT_ANI_FLAME;	//�Î~�t���[���������ɂ���

	m_speed_power = INIT_SPEED_POWER;	//�ʏ푬�x
	m_ani_max_time = INIT_ANI_MAX_TIME;	//�A�j���[�V�����Ԋu��

	attack_flag = true;	//�U������p�t���O

	L_flag = true;	//�J�n���͌��t���OON
	m_flag = true;	//���̐��E����p

	//�e�X�g
	move_flag = true;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = BLOCK_TYPE;	//����ł���block�̎�ފm�F�p

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, HBLOCK_INT_X_SIZE, HBLOCK_INT_Y_SIZE, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	//�����ɂ��Q�[���I�[�o�[
	if (m_py > STAGE_Y_OUT)
	{
		//��O�ɏo���烊�Z�b�g
		Scene::SetScene(new CSceneStage_1());
	}


	//��l���̍U��
	//if (Input::GetVKey('Z') == true)
	//{
	//	if (attack_flag == true)
	//	{
	//		//�U���I�u�W�F�N�g�̍쐬
	//		CObjAttack* obj_attack = new CObjAttack(m_px, m_py); //�e�ۃI�u�W�F�N�g�쐬
	//		Objs::InsertObj(obj_attack, OBJ_ATTACK, 100);		//������e�ۃI�u�W�F�N�g���}�l�[�W���[�ɓo�^

	//		attack_flag = false;
	//	}
	//}
	//else
	//{
	//	attack_flag = true;
	//}

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

		//���C
		m_vx += -(m_vx * INIT_FRICTION);

		//�ʒu�̍X�V
		m_px += m_vx;
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
			m_ani_time += 1.0;
		}
		else if (Input::GetVKey(VK_DOWN) == true)
		{
			m_vy += m_speed_power;
			m_ani_time += 1.0;
		}

		if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
		{
			m_ani_frame = 1;	//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
			m_ani_time = 0;
		}

		//���C
		m_vx += -(m_vx * INIT_FRICTION);
		m_vy += -(m_vy * INIT_FRICTION);

		//�ړ��x�N�g���̐��K��
		//UnitVec(&m_vy, &m_vx);

		//�ʒu�̍X�V
		m_px += m_vx ;
		m_py += m_vy ;
	}

	//�A�j���[�V�����֘A
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == m_ani_max_time)
	{
		m_ani_frame = 0;
	}

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px, m_py);

	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type);


	//���E�؂�ւ��e�X�g�p:�����e(X�����Ɛ؂�ւ�)
	if (L_flag == true)
	{
		if (Input::GetVKey('X') == true )
		{
			if (m_flag == true)
			{
				L_flag = false;
				m_flag = false;
				m_sx = m_px;
				m_sy = m_py;
			}
		}
		else
		{
			m_flag = true;
		}
	}

	//���E�؂�ւ��e�X�g�p:�e����(X�����Ɛ؂�ւ�)
	if (L_flag == false)
	{
		if (Input::GetVKey('X') == true )
		{
			if (m_flag == true)
			{
				L_flag = true;
				m_flag = false;
				m_px = m_sx;
				m_py = m_sy;

			}
		}
		else
		{
			m_flag = true;
		}
	}

	//�G�֌W
	////�G�Ɠ������Ă��邩�m�F
	//if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	//{
	//	//��l�����ǂ̓G�Ƃǂ̊p�x�œ������Ă��邩���m�F
	//	HIT_DATA** hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
	//	hit_data = hit->SearchObjNameHit(OBJ_ENEMY);	//hit_data�Ɏ�l���Ɠ������Ă���ق����ׂĂ�HitBox�Ƃ̏�������

	//	for (int i = 0; i < hit->GetCount(); i++)
	//	{
	//		//�G�̍��E�ɓ���������
	//		float r = hit_data[i]->r;
	//		if ((r < 45 && r >= 0 || r>315))
	//		{
	//			m_vx = -5.0f;	//���Ɉړ�������
	//		}
	//		if (r > 135 && r < 225)
	//		{
	//			m_vx = +5.0f;	//�E�Ɉړ�������
	//		}
	//		if (r >= 225 && r < 315)
	//		{
	//			//�G�̈ړ���������l���̈ʒu�ɉ��Z(o�̓I�u�W�F�N�g�A�h���X)
	//			m_px += ((CObjEnemy*)hit_data[i]->o)->GetVx();

	//			CObjBlock* b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//			//����X�N���[�����C��
	//			if (m_px < 80)
	//			{
	//				m_px = 80;				//��l���̓��C���𒴂��Ȃ��悤�ɂ���
	//				b->SetScroll(b->GetScroll() + 5.0f);	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
	//			}

	//			//�O���X�N���[�����C��
	//			if (m_px > 300)
	//			{
	//				m_px = 300;				//��l���̓��C���𒴂��Ȃ��悤�ɂ���
	//				b->SetScroll(b->GetScroll() - 5.0f);	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
	//			}
	//		}
	//	}
	//}

}

//�h���[
void CObjHero::Draw()
{
	//�A�j���[�V�����ԍ�
	int AniData[4] =
	{
		0,1,2,3,
	};

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
	src.m_right = HBLOCK_INT_X_SIZE + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
	src.m_bottom = HBLOCK_INT_Y_SIZE;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (HBLOCK_INT_X_SIZE - HBLOCK_INT_X_SIZE * m_posture) + m_px;
	dst.m_right = (HBLOCK_INT_X_SIZE * m_posture) + m_px;
	dst.m_bottom = HBLOCK_INT_Y_SIZE + m_py;

	//���t���O��ON�Ȃ�
	if (L_flag == true)
	{
		//0�Ԗڂɓo�^�����O���t�B�b�N(��l���E��)��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	//���t���O��OFF�Ȃ�
	else 
	{
		//1�Ԗڂɓo�^�����O���t�B�b�N(��l���E�e)��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
}



//---UnitVec�֐�
//����1�@float*vx	:�x�N�g����x�����̃|�C���^
//����2�@float*vy	:�x�N�g����y�����̃|�C���^
//�߂�l bool		:true=�v�Z����	false=�v�Z���s
//���e
//�����̃x�N�g���𐳋K�������̒l��vx,vy�ɕύX���܂��B
bool UnitVec(float* vx, float* vy)
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