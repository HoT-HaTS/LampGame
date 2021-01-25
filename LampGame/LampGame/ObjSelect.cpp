//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjSelect.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjSelect::Init()
{
	m_key_flag = false;
	select_flag = true;

	((UserData*)Save::GetData())->stage_id = 0;
}

//�A�N�V����
void CObjSelect::Action()
{
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		if (select_flag == true)
		{
			((UserData*)Save::GetData())->stage_id++;
			select_flag = false;
			
			//�J�[�\������炷
			Audio::Start(0);
		}
	}
	else if (Input::GetVKey(VK_LEFT) == true)
	{
		if (select_flag == true)
		{
			((UserData*)Save::GetData())->stage_id--;
			select_flag = false;

			//�J�[�\������炷
			Audio::Start(0);
		}
	}
	else if (Input::GetVKey(VK_DOWN) == true)
	{
		if (select_flag == true)
		{
			if (((UserData*)Save::GetData())->stage_id <= 2)
			{
				((UserData*)Save::GetData())->stage_id += 4;
				select_flag = false;

				//�J�[�\������炷
				Audio::Start(0);
			}
		}
	}
	else if (Input::GetVKey(VK_UP) == true)
	{
		if (select_flag == true)
		{
			if (((UserData*)Save::GetData())->stage_id >= 4)
			{
				((UserData*)Save::GetData())->stage_id -= 4;
				select_flag = false;

				//�J�[�\������炷
				Audio::Start(0);
			}
		}
	}
	else
	{
		select_flag = true;
	}

	if (((UserData*)Save::GetData())->stage_id <= -1)
		((UserData*)Save::GetData())->stage_id = 6;
	if (((UserData*)Save::GetData())->stage_id >= 7)
		((UserData*)Save::GetData())->stage_id = 0;
	
	//�G���^�[�L�[�������ăV�[���F�Q�[�����C���Ɉڍs����
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneStage_1());
			m_key_flag = false;
			switch_flag = true;
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//�h���[
void CObjSelect::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//�T���l�C���A�J�[�\���A�N���A�}�[�N�p
	float c1[4] = { 1.0f,0.4f,0.0f,1.0f };

	//�T���l�C���A�N���A�}�[�N�\���ʒu
	float top[7] = { CLEAR_MARK_Y1, CLEAR_MARK_Y1, CLEAR_MARK_Y1, CLEAR_MARK_Y1,
					 CLEAR_MARK_Y2, CLEAR_MARK_Y2, CLEAR_MARK_Y2 };
	float left[7] = { CLEAR_MARK_X1, CLEAR_MARK_X2, CLEAR_MARK_X3, CLEAR_MARK_X4,
					  CLEAR_MARK_X1, CLEAR_MARK_X2, CLEAR_MARK_X3 };

	RECT_F src;			//�X�e�[�W�T���l�C���`�挳�؂���ʒu
	RECT_F dst;			//�X�e�[�W�T���l�C���\���ʒu
	RECT_F src1;		//�J�[�\���`�挳�؂���ʒu
	RECT_F dst1;		//�J�[�\���`���\���ʒu
	RECT_F src2;		//�N���A�}�[�N�`�挳�؂���ʒu
	RECT_F dst2;		//�N���A�}�[�N�`���\���ʒu
	RECT_F src3;		//�X�e�[�W�Z���N�g�w�i�`�挳�؂���ʒu
	RECT_F dst3;		//�X�e�[�W�Z���N�g�w�i�`���\���ʒu
	RECT_F src_select;	//�����摜�`�挳�؂���ʒu
	RECT_F dst_select;	//�����\���ʒu
	RECT_F src_start;	//�����摜�`�挳�؂���ʒu
	RECT_F dst_start;	//�����\���ʒu
	RECT_F src_exit;	//�����摜�`�挳�؂���ʒu
	RECT_F dst_exit;	//�����\���ʒu

	//STAGE SELECT �̕���
	{
		src_select.m_top = 0.0f;
		src_select.m_left = 0.0f;
		src_select.m_right = src_select.m_left + SELECT_SIZE_X;
		src_select.m_bottom = src_select.m_top + SELECT_SIZE_Y;

		dst_select.m_top = SELECT_DRAW_X;
		dst_select.m_left = SELECT_DRAW_Y;
		dst_select.m_right = dst_select.m_left + SELECT_SIZE_X;
		dst_select.m_bottom = dst_select.m_top + SELECT_SIZE_Y;

		Draw::Draw(11, &src_select, &dst_select, c, 0.0f);
	}

	//ENTER �������ăX�^�[�g �̕���
	{
		src_start.m_top = 0.0f;
		src_start.m_left = 0.0f;
		src_start.m_right = src_start.m_left + ENTER_SIZE_X;
		src_start.m_bottom = src_start.m_top + ENTER_SIZE_Y;

		dst_start.m_top = ENTER_DRAW_Y;
		dst_start.m_left = ENTER_DRAW_X;
		dst_start.m_right = dst_start.m_left + ENTER_SIZE_X;
		dst_start.m_bottom = dst_start.m_top + ENTER_SIZE_Y;

		Draw::Draw(12, &src_start, &dst_start, c, 0.0f);
	}

	//EXIT �̕���
	{
		src_exit.m_top = 0.0f;
		src_exit.m_left = 0.0f;
		src_exit.m_right = src_exit.m_left + EXIT_SIZE_X;
		src_exit.m_bottom = src_exit.m_top + EXIT_SIZE_Y;

		dst_exit.m_top = EXIT_DRAW_Y;
		dst_exit.m_left = EXIT_DRAW_X;
		dst_exit.m_right = dst_exit.m_left + EXIT_SIZE_X;
		dst_exit.m_bottom = dst_exit.m_top + EXIT_SIZE_Y;

		Draw::Draw(13, &src_exit, &dst_exit, c, 0.0f);
	}

	//�X�e�[�W�T���l�C���؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 140.0f;
	src.m_bottom = src.m_top + 140.0f;

	for (int x = 0; x < 7; x++)
	{
		//�X�e�[�W�T���l�C���\���ʒu�̐ݒ�ƕ\��
		dst.m_top = top[x];
		dst.m_left = left[x];
		dst.m_right = dst.m_left + 140.0f;
		dst.m_bottom = dst.m_top + 140.0f;
		Draw::Draw(x, &src, &dst, c, 0.0f);
	}

	//�J�[�\���؂���ʒu�̐ݒ�
	src1.m_top = 0.0f;
	src1.m_left = 0.0f;
	src1.m_right = src1.m_left + 250.0f;
	src1.m_bottom = src1.m_top + 187.0f;

	//�N���A�}�[�N�؂���ʒu�̐ݒ�
	src2.m_top = 0.0f;
	src2.m_left = 0.0f;
	src2.m_right = src2.m_left + 64.0f;
	src2.m_bottom = src2.m_top + 64.0f;

	//Font::StrDraw(L"STAGE SELECT", 304, 40, 32, c1);
	//Font::StrDraw(L"START : Push_EnterKey", 240, 500, 32, c1);
	//Font::StrDraw(L"Exit : Push_Esc", 640, 574, 20, c1);

	for (int x = 0; x < 7; x++)
	{
		if (((UserData*)Save::GetData())->clear[x] == true)
		{
			//�N���A�}�[�N�\���ʒu�̐ݒ�ƕ\��
			dst2.m_top = top[x];
			dst2.m_left = left[x];
			dst2.m_right = dst2.m_left + 140.0f;
			dst2.m_bottom = dst2.m_top + 140.0f;
			Draw::Draw(9, &src2, &dst2, c, 0.0f);
		}
	}

	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		//�\���ʒu�̐ݒ�
		dst1.m_top = 100.0f;
		dst1.m_left = 35.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 1)
	{
		//�\���ʒu�̐ݒ�
		dst1.m_top = 100.0f;
		dst1.m_left = 230.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		//�\���ʒu�̐ݒ�
		dst1.m_top = 100.0f;
		dst1.m_left = 425.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		//�\���ʒu�̐ݒ�
		dst1.m_top = 100.0f;
		dst1.m_left = 620.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		//�\���ʒu�̐ݒ�
		dst1.m_top = 300.0f;
		dst1.m_left = 35.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		//�\���ʒu�̐ݒ�
		dst1.m_top = 300.0f;
		dst1.m_left = 230.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 6)
	{
		//�\���ʒu�̐ݒ�
		dst1.m_top = 300.0f;
		dst1.m_left = 425.0f;
	}
	//else if (((UserData*)Save::GetData())->stage_id == 7)
	//{
	//	//�\���ʒu�̐ݒ�
	//	dst.m_top = 300.0f;
	//	dst.m_left = 620.0f;
	//}
	else
	{
		dst1.m_top = 0.0f;
		dst1.m_left = 0.0f;
	}

	dst1.m_right = dst1.m_left + 150.0f;
	dst1.m_bottom = dst1.m_top + 150.0f;
	
	//8�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(8, &src1, &dst1, c, 0.0f);
}