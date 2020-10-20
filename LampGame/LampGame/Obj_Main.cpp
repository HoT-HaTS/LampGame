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
	
}

//アクション
void CObjMain::Action()
{
	//リトライ
	if (Input::GetVKey('R') == true)
	{
			Scene::SetScene(new CSceneStage_1());
	}
	
}

//ドロー
void CObjMain::Draw()
{

}