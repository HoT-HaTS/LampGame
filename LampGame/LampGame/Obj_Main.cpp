//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_Main.h"

//使用するネームスペース
using namespace GameL;



//イニシャライズ
void CObjMain::Init()
{
	 m_flag = true;
	 coin_count = 0;
	 g_flag = false;
	 alpha = 0.0f;
}

//アクション
void CObjMain::Action()
{

	//Rキー入力でリトライ
	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
	{
		if (Input::GetVKey('R') == true)
		{
			Scene::SetScene(new CSceneStage_1());
			pause_flag = false;
			switch_flag = true;
		}	
	
	}

	//ゴールの演出用、主人公の情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	g_flag = hero->GetG_Flag();
	if (g_flag == false)
	{
			float  c[4] = { 1.0f, 1.0f, 1.0f, alpha };

			alpha += 0.1f;

			RECT_F src;	//描画元切り取り位置
			RECT_F dst;	//描画先表示位置

			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 800.0f;
			src.m_bottom = 600.0f;
			dst.m_top = 0.0f;
			dst.m_left = 0.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(61, &src, &dst, c, 0.0f);
	}

	//ポーズ用
	if (Input::GetVKey('P') == true)
	{

		if (m_flag == true && pause_flag == false)
		{
			pause_flag = true;
			m_flag = false;
			CObjPause* obj_pause = new CObjPause();
			Objs::InsertObj(obj_pause, OBJ_PAUSE, 99);
		}
		else if (m_flag == true && pause_flag == true)
		{
			pause_flag = false;
			m_flag = false;
		}
	}
	else
	{
		m_flag = true;
	}	
}

//ドロー
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//主人公情報の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	coin_count = hero->GetCoin();


	RECT_F src2;	//描画元切り取り位置
	RECT_F dst2;	//描画先表示位置
	RECT_F dst3;	//描画先表示位置
	RECT_F dst4;	//描画先表示位置

	//コイン枚数の描画
	src2.m_top = 0.0f;
	src2.m_left = 0.0f;
	src2.m_right = src2.m_left + BLOCK_SIZE;
	src2.m_bottom = src2.m_top + BLOCK_SIZE;

	if (1 <= coin_count)
	{
		dst2.m_top = 0.0f;
		dst2.m_left = 0.0f;
		dst2.m_right = dst2.m_left + BLOCK_SIZE;
		dst2.m_bottom = dst2.m_top + BLOCK_SIZE;
		Draw::Draw(30, &src2, &dst2, c, 0.0f);
	}
	if (2 <= coin_count)
	{
		dst3.m_top = 0.0f;
		dst3.m_left = 0.0f + BLOCK_SIZE;
		dst3.m_right = dst3.m_left + BLOCK_SIZE;
		dst3.m_bottom = dst3.m_top + BLOCK_SIZE;
		Draw::Draw(30, &src2, &dst3, c, 0.0f);
	}
	if (3 <= coin_count)
	{
		dst4.m_top = 0.0f;
		dst4.m_left = 0.0f + 2 * BLOCK_SIZE;
		dst4.m_right = dst4.m_left + BLOCK_SIZE;
		dst4.m_bottom = dst4.m_top + BLOCK_SIZE;
		Draw::Draw(30, &src2, &dst4, c, 0.0f);
	}
}