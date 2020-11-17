//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle :: Init()
{
	m_key_flag = false;

}

//アクション
void CObjTitle::Action()
{
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneSelect());
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//ドロー
	void CObjTitle::Draw()
	{
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };
		/*Font::StrDraw(L"ランプの妖精と影の世界", TITLE1_X, TITLE1_Y, TITLE_SIZE, c);

		Font::StrDraw(L"GameStart : Push_EnterKey", TITLE2_X, TITLE2_Y, TITLE_SIZE, c);*/

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

		//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}