//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"

#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle :: Init()
{
	m_key_flag = false;

	((UserData*)Save::GetData())->clear[6] = { false };

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
	float c[4] = { 0.0f,0.0f,0.0f,1.0f };

	//Font::StrDraw(L"ランプの妖精と影の世界", TITLE1_X, TITLE1_Y, TITLE_SIZE, c);

	Font::StrDraw(L"GameStart : Push_EnterKey", TITLE2_X, TITLE2_Y, TITLE_SIZE, c);
}