//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "Obj_Goalscene.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGoalscene::Init()
{
	//P_flag = true;
	mx = 0;
	my = 0;
	alpha = 0.0f;
	s_flag = true;
}

//アクション
void CObjGoalscene::Action()
{

}

//ドロー
void CObjGoalscene::Draw()
{
	

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, alpha };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = WINDOW_SIZE_X;
	src.m_bottom = WINDOW_SIZE_Y;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + WINDOW_SIZE_X;
	dst.m_bottom = dst.m_top + WINDOW_SIZE_Y;

	//flagがtrueの時、演出開始
	if (s_flag==true)
	{
		alpha += 0.01f;
		//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
		Draw::Draw(61, &src, &dst, c, 0.0f);
		if (alpha >= 1.0f)
			s_flag = false;
	}
	else
	{
		alpha += ALPHA_MINUS;
		//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
		Draw::Draw(61, &src, &dst, c, 0.0f);

		//ステージクリアテロップ表示
		if (alpha <= 0.0f)
		{
			//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
			float  c_sc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

			RECT_F src_sc;	//描画元切り取り位置
			RECT_F dst_sc;	//描画先表示位置

			//切り取り位置の設定
			src_sc.m_top = 0.0f;
			src_sc.m_left = 0.0f;
			src_sc.m_right = CLEARTELOP_SIZE_X;
			src_sc.m_bottom = CLEARTELOP_SIZE_Y;

			//表示位置の設定
			dst_sc.m_top = CLEARTELOP_POS_Y;
			dst_sc.m_left = CLEARTELOP_POS_X;
			dst_sc.m_right = dst_sc.m_left + CLEARTELOP_SIZE_X;
			dst_sc.m_bottom = dst_sc.m_top + CLEARTELOP_SIZE_Y;
			Draw::Draw(63, &src_sc, &dst_sc, c_sc, 0.0f);
			Audio::Start(13);
		}
			
	}
	
}