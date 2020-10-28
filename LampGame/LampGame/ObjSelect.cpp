//使用するヘッダーファイル
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjSelect.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjSelect::Init()
{
	m_key_flag = false;
	select_flag = true;

	count = 1;
}

//アクション
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

	if (count <= 0)
		count = 1;
	if (count >= 6)
		count = 5;
	
	//エンターキーを押してシーン：ゲームメインに移行する
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (count == 1)
		{
			if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneStage_1());
				m_key_flag = false;
			}
		}
		if (count == 2)
		{
			if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneStage_1());
				m_key_flag = false;
			}
		}
		if (count == 3)
		{
			/*if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneStage_3());
				m_key_flag = false;
			}*/
		}
		if (count == 4)
		{
			/*if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneStage_4());
				m_key_flag = false;
			}*/
		}
		if (count == 5)
		{
			/*if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneStage_5());
				m_key_flag = false;
			}*/
		}

	}
	else
	{
		m_key_flag = true;
	}
}

//ドロー
void CObjSelect::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	Font::StrDraw(L"STAGE SELECT", 300, 50, 32, c);
	Font::StrDraw(L"ステージ1", 120, 150, 32, c);
	Font::StrDraw(L"ステージ2", 120, 200, 32, c);
	Font::StrDraw(L"ステージ3", 120, 250, 32, c);
	Font::StrDraw(L"ステージ4", 120, 300, 32, c);
	Font::StrDraw(L"ステージ5", 120, 350, 32, c);
	Font::StrDraw(L"START : Push_EnterKey", 230, 500, 32, c);
	Font::StrDraw(L"Exit : Push_Esc", 640, 574, 20, c);

	if (count == 1)
	{
		Font::StrDraw(L"→", 80, 150, 32, c);
	}
	else if (count == 2)
	{
		Font::StrDraw(L"→", 80, 200, 32, c);
	}
	else if (count == 3)
	{
		Font::StrDraw(L"→", 80, 250, 32, c);
	}
	else if (count == 4)
	{
		Font::StrDraw(L"→", 80, 300, 32, c);
	}
	else if (count == 5)
	{
		Font::StrDraw(L"→", 80, 350, 32, c);
	}
}