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
	((UserData*)Save::GetData())->clear[0] = true;
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
		if (((UserData*)Save::GetData())->clear[((UserData*)Save::GetData())->stage_id - 1] == true || ((UserData*)Save::GetData())->stage_id == 0)
		{
			if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneStage_1());
				m_key_flag = false;
				switch_flag = true;
			}
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
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//サムネイル、カーソル、クリアマーク用
	float c1[4] = { 1.0f,0.4f,0.0f,1.0f };


	//サムネイル、クリアマーク表示位置
	float top[7] = { CLEAR_MARK_Y1, CLEAR_MARK_Y2, CLEAR_MARK_Y1, CLEAR_MARK_Y2,
					 CLEAR_MARK_Y1, CLEAR_MARK_Y2, CLEAR_MARK_Y1 };
	float left[7] = { CLEAR_MARK_X1, (CLEAR_MARK_X2 + CLEAR_MARK_X1) / 2, CLEAR_MARK_X2, (CLEAR_MARK_X3 + CLEAR_MARK_X2) / 2,
					  CLEAR_MARK_X3, (CLEAR_MARK_X4 + CLEAR_MARK_X3) / 2, CLEAR_MARK_X4 };

	RECT_F src;			//ステージサムネイル描画元切り取り位置
	RECT_F dst;			//ステージサムネイル表示位置
	RECT_F src1;		//カーソル描画元切り取り位置
	RECT_F dst1;		//カーソル描画先表示位置
	RECT_F src2;		//クリアマーク描画元切り取り位置
	RECT_F dst2;		//クリアマーク描画先表示位置
	RECT_F src_select;	//文字画像描画元切り取り位置
	RECT_F dst_select;	//文字表示位置
	RECT_F src_start;	//文字画像描画元切り取り位置
	RECT_F dst_start;	//文字表示位置
	RECT_F src_exit;	//文字画像描画元切り取り位置
	RECT_F dst_exit;	//文字表示位置

	//STAGE SELECT の文字
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

	//ENTER を押してスタート の文字
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

	//EXIT の文字
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

	//ステージサムネイル切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE_THUMB_SIZE_X;
	src.m_bottom = src.m_top + STAGE_THUMB_SIZE_Y;

	for (int x = 0; x < 7; x++)
	{
		//ステージサムネイル表示位置の設定と表示
		dst.m_top = top[x];
		dst.m_left = left[x];
		dst.m_right = dst.m_left + STAGE_THUMB_SIZE_X;
		dst.m_bottom = dst.m_top + STAGE_THUMB_SIZE_Y;
		Draw::Draw(x, &src, &dst, c, 0.0f);
	}

	//カーソル切り取り位置の設定
	src1.m_top = 0.0f;
	src1.m_left = 0.0f;
	src1.m_right = src1.m_left + CURSOR_CUTOUT_SIZE_X;
	src1.m_bottom = src1.m_top + CURSOR_CUTOUT_SIZE_Y;

	//クリアマーク切り取り位置の設定
	src2.m_top = 0.0f;
	src2.m_left = 0.0f;
	src2.m_right = src2.m_left + CLAER_MARK_SIZE_X;
	src2.m_bottom = src2.m_top + CLAER_MARK_SIZE_Y;

	//Font::StrDraw(L"STAGE SELECT", 304, 40, 32, c1);
	//Font::StrDraw(L"START : Push_EnterKey", 240, 500, 32, c1);
	//Font::StrDraw(L"Exit : Push_Esc", 640, 574, 20, c1);

	for (int x = 1; x < 7; x++)
	{
		if (((UserData*)Save::GetData())->clear[x] == true)
		{
			//クリアマーク表示位置の設定と表示(ステージサムネに合わせる)
			dst2.m_top = top[x];
			dst2.m_left = left[x];
			dst2.m_right = dst2.m_left + STAGE_THUMB_SIZE_X;
			dst2.m_bottom = dst2.m_top + STAGE_THUMB_SIZE_Y;
			Draw::Draw(9, &src2, &dst2, c, 0.0f);
		}
	}

	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		//表示位置の設定
		dst1.m_top = top[0] - CURSOR_ADJ;
		dst1.m_left = left[0] - CURSOR_ADJ;
	}
	else if (((UserData*)Save::GetData())->stage_id == 1)
	{
		//表示位置の設定
		dst1.m_top = top[1] - CURSOR_ADJ;
		dst1.m_left = left[1] - CURSOR_ADJ;
	}
	else if (((UserData*)Save::GetData())->stage_id == 2)
	{
		//表示位置の設定
		dst1.m_top = top[2] - CURSOR_ADJ;
		dst1.m_left = left[2] - CURSOR_ADJ;
	}
	else if (((UserData*)Save::GetData())->stage_id == 3)
	{
		//表示位置の設定
		dst1.m_top = top[3] - CURSOR_ADJ;
		dst1.m_left = left[3] - CURSOR_ADJ;
	}
	else if (((UserData*)Save::GetData())->stage_id == 4)
	{
		//表示位置の設定
		dst1.m_top = top[4] - CURSOR_ADJ;
		dst1.m_left = left[4] - CURSOR_ADJ;
	}
	else if (((UserData*)Save::GetData())->stage_id == 5)
	{
		//表示位置の設定
		dst1.m_top = top[5] - CURSOR_ADJ;
		dst1.m_left = left[5] - CURSOR_ADJ;
	}
	else if (((UserData*)Save::GetData())->stage_id == 6)
	{
		//表示位置の設定
		dst1.m_top = top[6] - CURSOR_ADJ;
		dst1.m_left = left[6] - CURSOR_ADJ;
	}
	else
	{
		dst1.m_top = 0.0f;
		dst1.m_left = 0.0f;
	}

	dst1.m_right = dst1.m_left + CURSOR_DRAW_SIZE_X;
	dst1.m_bottom = dst1.m_top + CURSOR_DRAW_SIZE_Y;
	
	//8番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(8, &src1, &dst1, c, 0.0f);
}