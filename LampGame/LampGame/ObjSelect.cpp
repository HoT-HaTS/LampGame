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

//�h���[�i�����j
void CObjSelect::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float c1[4] = { 1.0f,1.0f,0.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 250.0f;
	src.m_bottom = src.m_top + 187.0f;

	Font::StrDraw(L"STAGE SELECT", 304, 40, 32, c);
	Font::StrDraw(L"�`���[�g���A��", 41, 106, 16, c);
	Font::StrDraw(L"�X�e�[�W1", 236, 106, 16, c);
	Font::StrDraw(L"�X�e�[�W2", 431, 106, 16, c);
	Font::StrDraw(L"�X�e�[�W3", 626, 106, 16, c);
	Font::StrDraw(L"�X�e�[�W4", 41, 306, 16, c);
	Font::StrDraw(L"�X�e�[�W5", 236, 306, 16, c);
	Font::StrDraw(L"�X�e�[�W6", 431, 306, 16, c);
	Font::StrDraw(L"START : Push_EnterKey", 240, 500, 32, c);
	Font::StrDraw(L"Exit : Push_Esc", 640, 574, 20, c);

	if (((UserData*)Save::GetData())->clear[0] == true)
	{
		Font::StrDraw(L"��", 88, 150, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[1] == true)
	{
		Font::StrDraw(L"��", 88, 200, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[2] == true)
	{
		Font::StrDraw(L"��", 88, 250, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[3] == true)
	{
		Font::StrDraw(L"��", 88, 300, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[4] == true)
	{
		Font::StrDraw(L"��", 88, 350, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[5] == true)
	{
		Font::StrDraw(L"��", 418, 150, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[6] == true)
	{
		Font::StrDraw(L"��", 418, 200, 32, c1);
	}

	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		//Font::StrDraw(L"��", 56, 150, 32, c);
		//�\���ʒu�̐ݒ�
		dst.m_top = 100.0f;
		dst.m_left = 35.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 1)
	{
		//Font::StrDraw(L"��", 56, 200, 32, c);
		//�\���ʒu�̐ݒ�
		dst.m_top = 100.0f;
		dst.m_left = 230.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		//Font::StrDraw(L"��", 56, 250, 32, c);
		//�\���ʒu�̐ݒ�
		dst.m_top = 100.0f;
		dst.m_left = 425.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		//Font::StrDraw(L"��", 56, 300, 32, c);
		//�\���ʒu�̐ݒ�
		dst.m_top = 100.0f;
		dst.m_left = 620.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		//Font::StrDraw(L"��", 56, 350, 32, c);
		//�\���ʒu�̐ݒ�
		dst.m_top = 300.0f;
		dst.m_left = 35.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		//Font::StrDraw(L"��", 386, 150, 32, c);
		//�\���ʒu�̐ݒ�
		dst.m_top = 300.0f;
		dst.m_left = 230.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 6)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = 300.0f;
		dst.m_left = 425.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	//else if (((UserData*)Save::GetData())->stage_id == 7)
	//{
	//	//�\���ʒu�̐ݒ�
	//	dst.m_top = 300.0f;
	//	dst.m_left = 620.0f;
	//	dst.m_right = dst.m_left + 150.0f;
	//	dst.m_bottom = dst.m_top + 150.0f;
	//}
	
	//1�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}