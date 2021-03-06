//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "ObjBackGround.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBackGround::Init()
{
}

//アクション
void CObjBackGround::Action()
{
	

}

//ドロー
void CObjBackGround::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//背景の描画
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = BG_X;
		src.m_bottom = BG_Y;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + BG_X;
		dst.m_bottom = dst.m_top + BG_Y;

		//14番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}

}