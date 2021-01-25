//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_Main.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMain::Init()
{
	 m_flag = true;
	 coin_count = 0;
	 g_flag = false;
	 dead_alpha = 0.0f;
	 in_alpha = 1.0;
	 d_time = 0.0f;
	 ga_flag = false;
	 d_flag = false;
}

//�A�N�V����
void CObjMain::Action()
{
	//�S�[���̉��o�p�A��l���̏��擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	d_flag = hero->Get_D_flag();

	if (d_flag == false)
	{
		//R�L�[���͂Ń��g���C
		if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
		{
			if (Input::GetVKey('R') == true)
			{
				Scene::SetScene(new CSceneStage_1());
				pause_flag = false;
				switch_flag = true;
			}
		}

		g_flag = hero->GetG_Flag();
		//flag��true�̎��A���o�J�n,�i���̓S�[���ɐG�ꂽ�u�Ԃɉ�������o���Ă���̂Ō��d�ɂȂ�B�j
		if (g_flag == true && ga_flag == false)
		{

			CObjGoalscene* obj_goalscene = new CObjGoalscene();
			Objs::InsertObj(obj_goalscene, OBJ_GOALSCENE, 99);
			ga_flag = true;
		}
		else if (g_flag == false)
		{
			ga_flag = false;
		}

		//�|�[�Y�p
		if (Input::GetVKey('P') == true)
		{

			if (m_flag == true && pause_flag == false && g_flag == false)
			{
				pause_flag = true;
				m_flag = false;
				CObjPause* obj_pause = new CObjPause();
				Objs::InsertObj(obj_pause, OBJ_PAUSE, 90);
			}
			else if (m_flag == true && pause_flag == true)
			{
				pause_flag = false;
				m_flag = false;
			}
		}
		else
		{
			m_flag = true;
		}
	}
	else
	{
		d_time++;

		if(d_time >= DEAD_TIME)
			dead_alpha += ADD_ALPHA;
	}
}

//�h���[
void CObjMain::Draw()
{
	in_alpha -= ADD_ALPHA;

	if (in_alpha <= 0.0f)
	{
		in_alpha = 0.0f;
	}

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float c_dead[4] = { 1.0f,1.0f,1.0f,dead_alpha };
	float c_in[4] = { 1.0f,1.0f,1.0f,in_alpha };

	//��l�����̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	coin_count = hero->GetCoin();

	RECT_F src;			//�u���b�N�A�E�g�`�挳�؂���ʒu
	RECT_F dst;			//�u���b�N�A�E�g�`���\���ʒu
	RECT_F src2;		//�R�C���`�挳�؂���ʒu
	RECT_F dst2;		//�R�C���`���\���ʒu
	RECT_F dst3;		//�R�C���`���\���ʒu
	RECT_F dst4;		//�R�C���`���\���ʒu
	RECT_F src_guide;	//�K�C�h�`�挳�؂���ʒu
	RECT_F dst_guide;	//�K�C�h�`���\���ʒu

	//�u���b�N�A�E�g�`�挳�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + SRC_BLACK_R;
	src.m_bottom = src.m_top + SRC_BLACK_B;

	//�u���b�N�A�E�g�`���\���ʒu
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + DRAW_SIZE_R;
	dst.m_bottom = dst.m_top + DRAW_SIZE_B;

	//�R�C�������̕`��
	src2.m_top = 0.0f;
	src2.m_left = 0.0f;
	src2.m_right = src2.m_left + BLOCK_SIZE;
	src2.m_bottom = src2.m_top + BLOCK_SIZE;

	//�K�C�h�`�挳�؂���ʒu
	src_guide.m_top = 0.0f;
	src_guide.m_left = 0.0f;
	src_guide.m_right = src_guide.m_left + SRC_GUIDE_R;
	src_guide.m_bottom = src_guide.m_top + SRC_GUIDE_B;

	//�K�C�h�`���\���ʒu
	dst_guide.m_top = 0.0f;
	dst_guide.m_left = DST_GUIDE_L;
	dst_guide.m_right = dst_guide.m_left + DST_GUIDE_R;
	dst_guide.m_bottom = dst_guide.m_top + DST_GUIDE_B;

	//�K�C�h�\��
	Draw::Draw(0, &src_guide, &dst_guide, c, 0.0f);

	//�u���b�N�C���\��
	Draw::Draw(62, &src, &dst, c_in, 0.0f);

	if (d_flag == false)
	{
		if (1 <= coin_count)
		{
			dst2.m_top = 0.0f;
			dst2.m_left = 0.0f;
			dst2.m_right = dst2.m_left + BLOCK_SIZE;
			dst2.m_bottom = dst2.m_top + BLOCK_SIZE;
			Draw::Draw(30, &src2, &dst2, c, 0.0f);
		}
		if (2 <= coin_count)
		{
			dst3.m_top = 0.0f;
			dst3.m_left = 0.0f + BLOCK_SIZE;
			dst3.m_right = dst3.m_left + BLOCK_SIZE;
			dst3.m_bottom = dst3.m_top + BLOCK_SIZE;
			Draw::Draw(30, &src2, &dst3, c, 0.0f);
		}
		if (3 <= coin_count)
		{
			dst4.m_top = 0.0f;
			dst4.m_left = 0.0f + 2 * BLOCK_SIZE;
			dst4.m_right = dst4.m_left + BLOCK_SIZE;
			dst4.m_bottom = dst4.m_top + BLOCK_SIZE;
			Draw::Draw(30, &src2, &dst4, c, 0.0f);
		}
	}
	else
	{
		Draw::Draw(62, &src, &dst, c_dead, 0.0f);
	}
}