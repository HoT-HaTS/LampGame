//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"

#include "GameHead.h"
#include "ObjClear.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjClear::Init()
{
	scene_num = 7;
	alpha_b = 1.0f;
	alpha_w = 0.0f;
	white = false;
	w_end = false;
	white_out = false;
}

//アクション
void CObjClear::Action()
{
	//しろの時の待機時間を作る

	if (white == false && scene_num >= 2)
	{
		alpha_b -= 0.005f;
		if (alpha_b <= 0.0f)
		{
			white = true;
			white_out = true;
		}
		if (scene_num < 2)
		{

		}
	}

	/*if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneTitle());
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}*/
}

//ドロー
void CObjClear::Draw()
{
	

	RECT_F src1;	//描画元切り取り位置
	RECT_F src2;

	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src1.m_top = 600.0f;
	src1.m_left = 0.0f;
	src1.m_right = 800.0f;
	src1.m_bottom = 1200.0f;
	//切り取り位置の設定
	src2.m_top = 0.0f;
	src2.m_left = 0.0f;
	src2.m_right = 800.0f;
	src2.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + 800.0f;
	dst.m_bottom = dst.m_top + 600.0f;

	//描画(影)
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c1[4] = { 1.0f, 1.0f, 1.0f, alpha_b };
	//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(scene_num, &src1, &dst, c1, 0.0f);


	//描画(光)
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c2[4] = { 1.0f, 1.0f, 1.0f, 1.0f-alpha_b };
	//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(scene_num, &src2, &dst, c2, 0.0f);

	if (white == true)
	{
		//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
		float  c_w[4] = { 1.0f, 1.0f, 1.0f, alpha_w };

		RECT_F src_w;	//描画元切り取り位置
		RECT_F dst_w;	//描画先表示位置

		//切り取り位置の設定
		src_w.m_top = 0.0f;
		src_w.m_left = 0.0f;
		src_w.m_right = 800.0f;
		src_w.m_bottom = 600.0f;

		//表示位置の設定
		dst_w.m_top = 0.0f;
		dst_w.m_left = 0.0f;
		dst_w.m_right = dst_w.m_left + 800.0f;
		dst_w.m_bottom = dst_w.m_top + 600.0f;


		//flagがtrueの時、演出開始
		if (white_out == true)
		{
			alpha_w += 0.02f;
		}
		else
		{
			alpha_w -= 0.02f;
			if (w_end == false)
			{
				scene_num -= 1;
				alpha_b = 1.0f;
				w_end = true;
			}
		}

		if (alpha_w >= 1.0f)
			white_out = false;


		if (alpha_w <= 0.0f)
		{
			w_end = false;
			alpha_w = 0.0f;
			white = false;
		}

		Draw::Draw(8, &src_w, &dst_w, c_w, 0.0f);
	}

	if (scene_num < 2)
	{
		//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
		float  c[4] = { 1.0f, 1.0f, 1.0f, alpha_w };

		RECT_F src;	//描画元切り取り位置
		RECT_F dst;	//描画先表示位置

		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 800.0f;
		src.m_bottom = 600.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 800.0f;
		dst.m_bottom = dst.m_top + 600.0f;
		Draw::Draw(scene_num, &src, &dst, c, 0.0f);
	}

}