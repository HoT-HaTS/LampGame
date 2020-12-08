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

	float top[7] = { 105, 105, 105, 105, 305, 305, 305};
	float left[7] = { 40, 235, 430, 625, 40, 235, 430};

	RECT_F src;		//ステージサムネイル描画元切り取り位置
	RECT_F dst;		//ステージサムネイル表示位置
	RECT_F src10;	//カーソル描画元切り取り位置
	RECT_F dst10;	//カーソル描画先表示位置

	//ステージサムネイル切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 140.0f;
	src.m_bottom = src.m_top + 140.0f;

	for (int x = 0; x < 7; x++)
	{
		//ステージサムネイル表示位置の設定と表示
		dst.m_top = top[x];
		dst.m_left = left[x];
		dst.m_right = dst.m_left + 140.0f;
		dst.m_bottom = dst.m_top + 140.0f;
		Draw::Draw(x, &src, &dst, c, 0.0f);
	}

	//カーソル切り取り位置の設定
	src10.m_top = 0.0f;
	src10.m_left = 0.0f;
	src10.m_right = src10.m_left + 250.0f;
	src10.m_bottom = src10.m_top + 187.0f;

	Font::StrDraw(L"STAGE SELECT", 304, 40, 32, c);
	Font::StrDraw(L"START : Push_EnterKey", 240, 500, 32, c);
	Font::StrDraw(L"Exit : Push_Esc", 640, 574, 20, c);

	if (((UserData*)Save::GetData())->clear[0] == true)
	{
		Font::StrDraw(L"★", 41, 106, 16, c1);
	}
	else
	{
		Font::StrDraw(L"☆", 41, 106, 16, c);
	}
	if (((UserData*)Save::GetData())->clear[1] == true)
	{
		Font::StrDraw(L"★", 236, 106, 16, c1);
	}
	else
	{
		Font::StrDraw(L"☆", 236, 106, 16, c);
	}
	if (((UserData*)Save::GetData())->clear[2] == true)
	{
		Font::StrDraw(L"★", 431, 106, 16, c1);
	}
	else
	{
		Font::StrDraw(L"☆", 431, 106, 16, c);
	}
	if (((UserData*)Save::GetData())->clear[3] == true)
	{
		Font::StrDraw(L"★", 626, 106, 16, c1);
	}
	else
	{
		Font::StrDraw(L"☆", 626, 106, 16, c);
	}
	if (((UserData*)Save::GetData())->clear[4] == true)
	{
		Font::StrDraw(L"★", 41, 306, 16, c1);
	}
	else
	{
		Font::StrDraw(L"☆", 41, 306, 16, c);
	}
	if (((UserData*)Save::GetData())->clear[5] == true)
	{
		Font::StrDraw(L"★", 236, 306, 16, c1);
	}
	else
	{
		Font::StrDraw(L"☆", 236, 306, 16, c);
	}
	if (((UserData*)Save::GetData())->clear[6] == true)
	{
		Font::StrDraw(L"★", 431, 306, 16, c1);
	}
	else
	{
		Font::StrDraw(L"☆", 431, 306, 16, c);
	}

	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		//表示位置の設定
		dst10.m_top = 100.0f;
		dst10.m_left = 35.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 1)
	{
		//表示位置の設定
		dst10.m_top = 100.0f;
		dst10.m_left = 230.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		//表示位置の設定
		dst10.m_top = 100.0f;
		dst10.m_left = 425.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		//表示位置の設定
		dst10.m_top = 100.0f;
		dst10.m_left = 620.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		//表示位置の設定
		dst10.m_top = 300.0f;
		dst10.m_left = 35.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		//表示位置の設定
		dst10.m_top = 300.0f;
		dst10.m_left = 230.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 6)
	{
		//表示位置の設定
		dst10.m_top = 300.0f;
		dst10.m_left = 425.0f;
	}
	//else if (((UserData*)Save::GetData())->stage_id == 7)
	//{
	//	//表示位置の設定
	//	dst.m_top = 300.0f;
	//	dst.m_left = 620.0f;
	//}

	dst10.m_right = dst10.m_left + 150.0f;
	dst10.m_bottom = dst10.m_top + 150.0f;
	
	//8番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(8, &src10, &dst10, c, 0.0f);
}