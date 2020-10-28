//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjSelect.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjSelect::Init()
{
	m_key_flag = false;
	select_flag = true;

	count = 0;
}

//�A�N�V����
void CObjSelect::Action()
{
	
	if (Input::GetVKey(VK_DOWN) == true)
	{
		if (select_flag == true)
		{
			count++;
			select_flag = false;
		}
	}
	else if (Input::GetVKey(VK_UP) == true)
	{
		if (select_flag == true)
		{
			count--;
			select_flag = false;
		}
	}
	else
	{
		select_flag = true;
	}
	
	//�G���^�[�L�[�������ăV�[���F�Q�[�����C���Ɉڍs����
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (count == 0)
		{
			if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneStage_1());
				m_key_flag = false;
			}
		}
		if (count == 1)
		{
			/*if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneStage_2());
				m_key_flag = false;
			}*/
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
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	Font::StrDraw(L"STAGE SELECT", 300, 50, 32, c);
	Font::StrDraw(L"�X�e�[�W1", 120, 150, 32, c);
	Font::StrDraw(L"�X�e�[�W2", 120, 200, 32, c);
	Font::StrDraw(L"START : PushEnterKey", 230, 500, 32, c);

	if (count == 0)
	{
		Font::StrDraw(L"��", 80, 150, 32, c);
	}
	else if (count == 1)
	{
		Font::StrDraw(L"��", 80, 200, 32, c);
	}
}