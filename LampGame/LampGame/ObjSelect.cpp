//使用するヘッダーファイル
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjSelect.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjSelect::Init()
{
	m_key_flag = false;
	select_flag = true;

	((UserData*)Save::GetData())->stage_id = 0;
}

//アクション
void CObjSelect::Action()
{
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		if (select_flag == true)
		{
			((UserData*)Save::GetData())->stage_id++;
			select_flag = false;
			
			//カーソル音を鳴らす
			Audio::Start(0);
		}
	}
	else if (Input::GetVKey(VK_LEFT) == true)
	{
		if (select_flag == true)
		{
			((UserData*)Save::GetData())->stage_id--;
			select_flag = false;

			//カーソル音を鳴らす
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

				//カーソル音を鳴らす
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

				//カーソル音を鳴らす
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
	
	//エンターキーを押してシーン：ゲームメインに移行する
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

//ドロー（文字）
void CObjSelect::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float c1[4] = { 1.0f,1.0f,0.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 250.0f;
	src.m_bottom = src.m_top + 187.0f;

	Font::StrDraw(L"STAGE SELECT", 304, 40, 32, c);
	Font::StrDraw(L"チュートリアル", 41, 106, 16, c);
	Font::StrDraw(L"ステージ1", 236, 106, 16, c);
	Font::StrDraw(L"ステージ2", 431, 106, 16, c);
	Font::StrDraw(L"ステージ3", 626, 106, 16, c);
	Font::StrDraw(L"ステージ4", 41, 306, 16, c);
	Font::StrDraw(L"ステージ5", 236, 306, 16, c);
	Font::StrDraw(L"ステージ6", 431, 306, 16, c);
	Font::StrDraw(L"START : Push_EnterKey", 240, 500, 32, c);
	Font::StrDraw(L"Exit : Push_Esc", 640, 574, 20, c);

	if (((UserData*)Save::GetData())->clear[0] == true)
	{
		Font::StrDraw(L"★", 88, 150, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[1] == true)
	{
		Font::StrDraw(L"★", 88, 200, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[2] == true)
	{
		Font::StrDraw(L"★", 88, 250, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[3] == true)
	{
		Font::StrDraw(L"★", 88, 300, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[4] == true)
	{
		Font::StrDraw(L"★", 88, 350, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[5] == true)
	{
		Font::StrDraw(L"★", 418, 150, 32, c1);
	}
	if (((UserData*)Save::GetData())->clear[6] == true)
	{
		Font::StrDraw(L"★", 418, 200, 32, c1);
	}

	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		//Font::StrDraw(L"→", 56, 150, 32, c);
		//表示位置の設定
		dst.m_top = 100.0f;
		dst.m_left = 35.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 1)
	{
		//Font::StrDraw(L"→", 56, 200, 32, c);
		//表示位置の設定
		dst.m_top = 100.0f;
		dst.m_left = 230.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		//Font::StrDraw(L"→", 56, 250, 32, c);
		//表示位置の設定
		dst.m_top = 100.0f;
		dst.m_left = 425.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		//Font::StrDraw(L"→", 56, 300, 32, c);
		//表示位置の設定
		dst.m_top = 100.0f;
		dst.m_left = 620.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		//Font::StrDraw(L"→", 56, 350, 32, c);
		//表示位置の設定
		dst.m_top = 300.0f;
		dst.m_left = 35.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		//Font::StrDraw(L"→", 386, 150, 32, c);
		//表示位置の設定
		dst.m_top = 300.0f;
		dst.m_left = 230.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 6)
	{
		//表示位置の設定
		dst.m_top = 300.0f;
		dst.m_left = 425.0f;
		dst.m_right = dst.m_left + 150.0f;
		dst.m_bottom = dst.m_top + 150.0f;
	}
	//else if (((UserData*)Save::GetData())->stage_id == 7)
	//{
	//	//表示位置の設定
	//	dst.m_top = 300.0f;
	//	dst.m_left = 620.0f;
	//	dst.m_right = dst.m_left + 150.0f;
	//	dst.m_bottom = dst.m_top + 150.0f;
	//}
	
	//1番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}