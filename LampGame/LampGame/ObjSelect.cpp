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
	if (Input::GetVKey(VK_DOWN) == true)
	{
		if (select_flag == true)
		{
			((UserData*)Save::GetData())->stage_id++;
			select_flag = false;
			
			//�J�[�\������炷
			Audio::Start(0);
		}
	}
	else if (Input::GetVKey(VK_UP) == true)
	{
		if (select_flag == true)
		{
			((UserData*)Save::GetData())->stage_id--;
			select_flag = false;

			//�J�[�\������炷
			Audio::Start(0);
		}
	}
	else
	{
		select_flag = true;
	}

	if (((UserData*)Save::GetData())->stage_id == -1)
		((UserData*)Save::GetData())->stage_id = 5;
	if (((UserData*)Save::GetData())->stage_id == 6)
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

	/*
	�X�e�[�W�\���ύX��
	���ł̃X�e�[�W���`���[�g���A���Ƃ��āA����ȍ~���P�A�Q...�Ƃ��Ă����B
	�X�e�[�W���e�Ɋւ��ẮA�M�~�b�N������s�b�N�A�b�v�����X�e�[�W���ŏ��ɒu���āA
	�㔼�ɍ��̃X�e�[�W2�A3�������Ă����\��B
	*/

	Font::StrDraw(L"STAGE SELECT", 304, 50, 32, c);
	Font::StrDraw(L"�`���[�g���A��", 120, 150, 32, c);
	Font::StrDraw(L"�X�e�[�W1", 120, 200, 32, c);
	Font::StrDraw(L"�X�e�[�W2", 120, 250, 32, c);
	Font::StrDraw(L"�X�e�[�W3", 120, 300, 32, c);
	Font::StrDraw(L"�X�e�[�W4", 120, 350, 32, c);
	Font::StrDraw(L"�X�e�[�W5", 450, 150, 32, c);
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

	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		Font::StrDraw(L"��", 56, 150, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 1)
	{
		Font::StrDraw(L"��", 56, 200, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		Font::StrDraw(L"��", 56, 250, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		Font::StrDraw(L"��", 56, 300, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		Font::StrDraw(L"��", 56, 350, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		Font::StrDraw(L"��", 386, 150, 32, c);
	}

	////�؂���ʒu�̐ݒ�
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = src.m_left + 250.0f;
	//src.m_bottom = src.m_top + 187.0f;

	////�\���ʒu�̐ݒ�   ���x���
	//dst.m_top = 0.0f + m_py;
	//dst.m_right = 0.0f + m_px + scroll->GetScroll();
	//dst.m_left = dst.m_right + E_XSIZE;
	//dst.m_bottom = dst.m_top + E_YSIZE;

	////0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	//Draw::Draw(22, &src, &dst, c, 0.0f);
}