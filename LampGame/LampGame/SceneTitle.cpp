//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "GameHead.h"
#include "SceneTitle.h"
#include "ObjTitle.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームメイン初期化メゾット
void CSceneTitle::InitScene()
{
	Draw::LoadImageW(L"graphic/Title.png", 14, TEX_SIZE_512);

	////初期化させる文字のグラフィック作成
	//Font::SetStrTex(L"ランプの妖精と影の世界");

	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();    //タイトルオブジェクト作成
	Objs::InsertObj(obj, OBJ_TITLE, 10); //主人公オブジェクト登録
}

//ゲームメイン実行中メゾット
void CSceneTitle:: Scene()
{

}