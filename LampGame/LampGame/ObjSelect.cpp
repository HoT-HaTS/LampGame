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

	RECT_F src;	//ステージサムネイル描画元切り取り位置
	RECT_F dst0;	//チュートリアルサムネイル描画先表示位置
	RECT_F dst1;	//ステージ1サムネイル描画先表示位置
	RECT_F dst2;	//ステージ2サムネイル描画先表示位置
	RECT_F dst3;	//ステージ3サムネイル描画先表示位置
	RECT_F dst4;	//ステージ4サムネイル描画先表示位置
	RECT_F dst5;	//ステージ5サムネイル描画先表示位置
	RECT_F dst6;	//ステージ6サムネイル描画先表示位置
	//RECT_F dst7;	//ステージ7サムネイル描画先表示位置
	RECT_F src10;	//カーソル描画元切り取り位置
	RECT_F dst10;	//カーソル描画先表示位置

	//ステージサムネイル切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 140.0f;
	src.m_bottom = src.m_top + 140.0f;

	//チュートリアルステージ表示位置の設定と表示
	dst0.m_top = 105.0f;
	dst0.m_left = 40.0f;
	dst0.m_right = dst0.m_left + 140.0f;
	dst0.m_bottom = dst0.m_top + 140.0f;
	Draw::Draw(0, &src, &dst0, c, 0.0f);
	//ステージ1表示位置の設定と表示
	dst1.m_top = 105.0f;
	dst1.m_left = 235.0f;
	dst1.m_right = dst1.m_left + 140.0f;
	dst1.m_bottom = dst1.m_top + 140.0f;
	Draw::Draw(1, &src, &dst1, c, 0.0f);
	//ステージ2表示位置の設定と表示
	dst2.m_top = 105.0f;
	dst2.m_left = 430.0f;
	dst2.m_right = dst2.m_left + 140.0f;
	dst2.m_bottom = dst2.m_top + 140.0f;
	Draw::Draw(2, &src, &dst2, c, 0.0f);
	//ステージ3表示位置の設定と表示
	dst3.m_top = 105.0f;
	dst3.m_left = 625.0f;
	dst3.m_right = dst3.m_left + 140.0f;
	dst3.m_bottom = dst3.m_top + 140.0f;
	Draw::Draw(3, &src, &dst3, c, 0.0f);
	//ステージ4表示位置の設定と表示
	dst4.m_top = 305.0f;
	dst4.m_left = 40.0f;
	dst4.m_right = dst4.m_left + 140.0f;
	dst4.m_bottom = dst4.m_top + 140.0f;
	Draw::Draw(4, &src, &dst4, c, 0.0f);
	//ステージ5表示位置の設定と表示
	dst5.m_top = 305.0f;
	dst5.m_left = 235.0f;
	dst5.m_right = dst5.m_left + 140.0f;
	dst5.m_bottom = dst5.m_top + 140.0f;
	Draw::Draw(5, &src, &dst5, c, 0.0f);
	//ステージ6表示位置の設定と表示
	dst6.m_top = 305.0f;
	dst6.m_left = 430.0f;
	dst6.m_right = dst6.m_left + 140.0f;
	dst6.m_bottom = dst6.m_top + 140.0f;
	Draw::Draw(6, &src, &dst6, c, 0.0f);
	//ステージ7表示位置のと表示
	/*dst7.m_top = 305.0f;
	dst7.m_left = 625.0f;
	dst7.m_right = dst7.m_left + 140.0f;
	dst7.m_bottom = dst7.m_top + 140.0f;
	Draw::Draw(7, &src, &dst7, c, 0.0f);*/

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
		//Font::StrDraw(L"→", 56, 150, 32, c);
		//表示位置の設定
		dst10.m_top = 100.0f;
		dst10.m_left = 35.0f;
		dst10.m_right = dst10.m_left + 150.0f;
		dst10.m_bottom = dst10.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 1)
	{
		//Font::StrDraw(L"→", 56, 200, 32, c);
		//表示位置の設定
		dst10.m_top = 100.0f;
		dst10.m_left = 230.0f;
		dst10.m_right = dst10.m_left + 150.0f;
		dst10.m_bottom = dst10.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		//Font::StrDraw(L"→", 56, 250, 32, c);
		//表示位置の設定
		dst10.m_top = 100.0f;
		dst10.m_left = 425.0f;
		dst10.m_right = dst10.m_left + 150.0f;
		dst10.m_bottom = dst10.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		//Font::StrDraw(L"→", 56, 300, 32, c);
		//表示位置の設定
		dst10.m_top = 100.0f;
		dst10.m_left = 620.0f;
		dst10.m_right = dst10.m_left + 150.0f;
		dst10.m_bottom = dst10.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		//Font::StrDraw(L"→", 56, 350, 32, c);
		//表示位置の設定
		dst10.m_top = 300.0f;
		dst10.m_left = 35.0f;
		dst10.m_right = dst10.m_left + 150.0f;
		dst10.m_bottom = dst10.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		//Font::StrDraw(L"→", 386, 150, 32, c);
		//表示位置の設定
		dst10.m_top = 300.0f;
		dst10.m_left = 230.0f;
		dst10.m_right = dst10.m_left + 150.0f;
		dst10.m_bottom = dst10.m_top + 150.0f;
	}
	else if (((UserData*)Save::GetData())->stage_id == 6)
	{
		//表示位置の設定
		dst10.m_top = 300.0f;
		dst10.m_left = 425.0f;
		dst10.m_right = dst10.m_left + 150.0f;
		dst10.m_bottom = dst10.m_top + 150.0f;
	}
	//else if (((UserData*)Save::GetData())->stage_id == 7)
	//{
	//	//表示位置の設定
	//	dst.m_top = 300.0f;
	//	dst.m_left = 620.0f;
	//	dst.m_right = dst.m_left + 150.0f;
	//	dst.m_bottom = dst.m_top + 150.0f;
	//}
	
	//8番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(8, &src10, &dst10, c, 0.0f);
}