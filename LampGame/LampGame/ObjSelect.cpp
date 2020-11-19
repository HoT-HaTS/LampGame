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
		((UserData*)Save::GetData())->stage_id = 6;
	if (((UserData*)Save::GetData())->stage_id == 7)
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
	Font::StrDraw(L"�X�e�[�W6", 450, 200, 32, c);
	Font::StrDraw(L"START : Push_EnterKey", 240, 500, 32, c);
	Font::StrDraw(L"Exit : Push_Esc", 640, 574, 20, c);

	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		Font::StrDraw(L"��", 80, 150, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 1)
	{
		Font::StrDraw(L"��", 80, 200, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		Font::StrDraw(L"��", 80, 250, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		Font::StrDraw(L"��", 80, 300, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		Font::StrDraw(L"��", 80, 350, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		Font::StrDraw(L"��", 410, 150, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 6)
	{
		Font::StrDraw(L"��", 410, 200, 32, c);
	}
}