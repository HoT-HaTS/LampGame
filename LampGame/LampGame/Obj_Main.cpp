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
		}	
	
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

}