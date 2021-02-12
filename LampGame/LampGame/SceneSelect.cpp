//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneSelect.h"
#include "GameHead.h"
#include "ObjSelect.h"

//コンストラクタ
CSceneSelect::CSceneSelect()
{

}

//デストラクタ
CSceneSelect::~CSceneSelect()
{

}

//ゲームメイン初期化メソッド
void CSceneSelect::InitScene()
{
	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"LampGame");

	//画像データ読み込み
	Draw::LoadImageW(L"graphic/tumb_0.png", 0, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_1.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_2.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_3.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_4.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_5.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_6.png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stageselect_cursor.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/St_Cleared_mark.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/BG_sellect.png", 10, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_desc.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_desc2.png", 12, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_desc3.png", 13, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Locked.png", 14, TEX_SIZE_512);

	//音楽データ読み込み用
	Audio::LoadAudio(11, L"BGM/Sunrise_Title.wav", BACK_MUSIC);

	//SE読み込み用
	Audio::LoadAudio(0, L"SE/Cursor.wav", EFFECT);
	Audio::LoadAudio(1, L"SE/Switch.wav", EFFECT);

	//ステージセレクトオブジェクト作成
	CObjSelect* obj = new CObjSelect();   //ステージセレクトオブジェクト作成
	Objs::InsertObj(obj, OBJ_SELECT, 10);

	//ステージセレクトオブジェクト作成
	CObjBackGround_Select* objs_bg = new CObjBackGround_Select();   //ステージセレクトオブジェクト作成
	Objs::InsertObj(objs_bg, OBJ_SELECT, 10);

	//オーディオスタート
	Audio::Start(11);
}

//ゲームメイン実行中メソッド
void CSceneSelect::Scene()
{

}