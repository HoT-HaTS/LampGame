//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "GameHead.h"
#include "SceneTitle.h"
#include "ObjTitle.h"
#include "ObjBackGround.h"

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


	//音楽データ読み込み用
	Audio::LoadAudio(11, L"BGM/Sunrise_Title.wav", BACK_MUSIC);


	////初期化させる文字のグラフィック作成
	//Font::SetStrTex(L"ランプの妖精と影の世界");

	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();    //タイトルオブジェクト作成
	Objs::InsertObj(obj, OBJ_TITLE, 6); 

	//背景オブジェクト作成
	CObjBackGround* objbg = new CObjBackGround();    //背景オブジェクト作成
	Objs::InsertObj(objbg, OBJ_TITLE, 6); 


	//マスターボリュームを1に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((1.0 - v));

	Audio::Start(11);
}

//ゲームメイン実行中メゾット
void CSceneTitle:: Scene()
{

}