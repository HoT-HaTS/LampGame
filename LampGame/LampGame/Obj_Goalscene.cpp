//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

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
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + 800.0f;
	dst.m_bottom = dst.m_top + 600.0f;

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
		alpha -= 0.01f;
		//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
		Draw::Draw(61, &src, &dst, c, 0.0f);
			
	}
	
}