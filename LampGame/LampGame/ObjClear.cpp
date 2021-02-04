//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjClear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjClear::Init()
{
	scene_num = BG_NUM;
	alpha_b = INIT_ALPHA_BLACK;
	alpha_w = INIT_ALPHA_WHITE;
	white = false;
	w_end = false;
	white_out = false;
	h_ani_time = INIT_ANI_TIME;
	h_ani_frame = INIT_ANI_FRAME;
}

//�A�N�V����
void CObjClear::Action()
{
	if (white == false && scene_num > BG_LAST)
	{
		alpha_b -= PLUS__ALPHA_BLACK;
		if (alpha_b <= 0.0f)
		{
			white = true;
			white_out = true;
		}
	}
	if (scene_num <= BG_LAST)
	{
		h_ani_time ++;
		if (h_ani_time >= MAX_H_ANI_TIME)
		{
			h_ani_frame ++;
			h_ani_time = INIT_ANI_TIME;
			if (h_ani_frame >= MAX_H_ANI_FRAME)
			{
				h_ani_frame = INIT_ANI_FRAME;
			}
		}

		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneTitle());
				m_key_flag = false;
			}
		}
		else
		{
			m_key_flag = true;
		}
	}
}

//�h���[
void CObjClear::Draw()
{
	RECT_F src1;	//�`�挳�؂���ʒu
	RECT_F src2;

	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src1.m_top = SRC_BLACK_TOP;
	src1.m_left = SRC_BLACK_LEFT;
	src1.m_right = src1.m_left + BG_X_SIZE;
	src1.m_bottom = src1.m_top + BG_Y_SIZE;
	//�؂���ʒu�̐ݒ�
	src2.m_top = SRC_WHITE_TOP;
	src2.m_left = SRC_WHITE_LEFT;
	src2.m_right = src2.m_left + BG_X_SIZE;
	src2.m_bottom = src2.m_top + BG_Y_SIZE;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + BG_X_SIZE;
	dst.m_bottom = dst.m_top + BG_Y_SIZE;

	//�`��(�e)
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c1[4] = { 1.0f, 1.0f, 1.0f, alpha_b };
	//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(scene_num, &src1, &dst, c1, 0.0f);


	//�`��(��)
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c2[4] = { 1.0f, 1.0f, 1.0f, 1.0f-alpha_b };
	//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(scene_num, &src2, &dst, c2, 0.0f);

	if (white == true)
	{
		//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
		float  c_w[4] = { 1.0f, 1.0f, 1.0f, alpha_w };

		RECT_F src_w;	//�`�挳�؂���ʒu
		RECT_F dst_w;	//�`���\���ʒu

		//�؂���ʒu�̐ݒ�
		src_w.m_top = 0.0f;
		src_w.m_left = 0.0f;
		src_w.m_right = src_w.m_left + BG_Y_SIZE;
		src_w.m_bottom = src_w.m_top + BG_X_SIZE;

		//�\���ʒu�̐ݒ�
		dst_w.m_top = 0.0f;
		dst_w.m_left = 0.0f;
		dst_w.m_right = dst_w.m_left + BG_X_SIZE;
		dst_w.m_bottom = dst_w.m_top + BG_Y_SIZE;


		//flag��true�̎��A���o�J�n
		if (white_out == true)
		{
			alpha_w +=	PLUS__ALPHA_WHITE;
		}
		else
		{
			alpha_w -= PLUS__ALPHA_WHITE;
			if (w_end == false)
			{
				scene_num --;
				alpha_b = INIT_ALPHA_BLACK;
				w_end = true;
			}
		}

		if (alpha_w >= MAX_ALPHA)
			white_out = false;


		if (alpha_w <= INIT_ALPHA_WHITE)
		{
			w_end = false;
			alpha_w = INIT_ALPHA_WHITE;
			white = false;
		}

		Draw::Draw(8, &src_w, &dst_w, c_w, 0.0f);
	}

	if (scene_num <= BG_LAST)
	{
		//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
		float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		RECT_F src_clear;	//�`�挳�؂���ʒu
		RECT_F dst_clear;	//�`���\���ʒu

		//�w�i-----------------------
		//�؂���ʒu�̐ݒ�
		src_clear.m_top = CLEAR_BG_SRC_TOP;
		src_clear.m_left = CLEAR_BG_SRC_LEFT;
		src_clear.m_right = src_clear.m_left + CLEAR_BG_X_SIZE;
		src_clear.m_bottom = src_clear.m_top + CLEAR_BG_Y_SIZE;
		//�\���ʒu�̐ݒ�
		dst_clear.m_top = 0.0f;
		dst_clear.m_left = 0.0f;
		dst_clear.m_right = dst_clear.m_left + BG_X_SIZE;
		dst_clear.m_bottom = dst_clear.m_top + BG_Y_SIZE;
		Draw::Draw(scene_num, &src_clear, &dst_clear, c, 0.0f);
		
		//�e�L�X�g-------------------
		//�؂���ʒu�̐ݒ�
		src_clear.m_top = 0.0f;
		src_clear.m_left = 0.0f;
		src_clear.m_right = src_clear.m_left + CLEAR_TEXT_X_SIZE;
		src_clear.m_bottom = src_clear.m_top + CLEAR_TEXT_Y_SIZE;
		//�\���ʒu�̐ݒ�
		dst_clear.m_top = CLEAR_TEXT_DST_TOP;
		dst_clear.m_left = CLEAR_TEXT_DST_LEFT;
		dst_clear.m_right = dst_clear.m_left + CLEAR_TEXT_X_SIZE;
		dst_clear.m_bottom = dst_clear.m_top + CLEAR_TEXT_Y_SIZE;
		Draw::Draw(9, &src_clear, &dst_clear, c, 0.0f);


		//��l��---------------------
		//�؂���ʒu�̐ݒ�
		src_clear.m_top = 0.0f;
		src_clear.m_left = 0.0f + (h_ani_frame * CLEAR_HERO_X_SIZE);
		src_clear.m_right = src_clear.m_left + CLEAR_HERO_X_SIZE;
		src_clear.m_bottom = src_clear.m_top + CLEAR_HERO_Y_SIZE;
		//�\���ʒu�̐ݒ�
		dst_clear.m_top = CLEAR_HERO_DST_TOP;
		dst_clear.m_left = CLEAR_HERO_DST_LEFT;
		dst_clear.m_right = dst_clear.m_left + CLEAR_HERO_X_SIZE;
		dst_clear.m_bottom = dst_clear.m_top + CLEAR_HERO_Y_SIZE;
		Draw::Draw(10, &src_clear, &dst_clear, c, 0.0f);
	}
}