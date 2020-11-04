//使用するヘッダーファイル
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/UserData.h"

#include "GameHead.h"
#include "ObjSelect.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjSelect::Init()
{
	m_key_flag = false;
	select_flag = true;

	((UserData*)Save::GetData())->stage_id = 1;
}

//アクション
void CObjSelect::Action()
{
	if (Input::GetVKey(VK_DOWN) == true)
	{
		if (select_flag == true)
		{
			((UserData*)Save::GetData())->stage_id++;
			select_flag = false;
		}
	}
	else if (Input::GetVKey(VK_UP) == true)
	{
		if (select_flag == true)
		{
			((UserData*)Save::GetData())->stage_id--;
			select_flag = false;
		}
	}
	else
	{
		select_flag = true;
	}

	if (((UserData*)Save::GetData())->stage_id <= 0)
		((UserData*)Save::GetData())->stage_id = 1;
	if (((UserData*)Save::GetData())->stage_id >= 6)
		((UserData*)Save::GetData())->stage_id = 5;
	
	//エンターキーを押してシーン：ゲームメインに移行する
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneStage_1());
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//ドロー（文字）
void CObjSelect::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	Font::StrDraw(L"STAGE SELECT", 304, 50, 32, c);
	Font::StrDraw(L"ステージ1", 120, 150, 32, c);
	Font::StrDraw(L"ステージ2", 120, 200, 32, c);
	Font::StrDraw(L"ステージ3", 120, 250, 32, c);
	Font::StrDraw(L"ステージ4", 120, 300, 32, c);
	Font::StrDraw(L"ステージ5", 120, 350, 32, c);
	Font::StrDraw(L"START : Push_EnterKey", 240, 500, 32, c);
	Font::StrDraw(L"Exit : Push_Esc", 640, 574, 20, c);

	if (((UserData*)Save::GetData())->stage_id == 1)
	{
		Font::StrDraw(L"→", 80, 150, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		Font::StrDraw(L"→", 80, 200, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		Font::StrDraw(L"→", 80, 250, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		Font::StrDraw(L"→", 80, 300, 32, c);
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		Font::StrDraw(L"→", 80, 350, 32, c);
	}
}