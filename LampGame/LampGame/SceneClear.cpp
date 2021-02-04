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
#include "SceneClear.h"
#include "GameHead.h"
#include "ObjClear.h"

//コンストラクタ
CSceneClear::CSceneClear()
{

}

//デストラクタ
CSceneClear::~CSceneClear()
{

}

//ゲームメイン初期化メソッド
void CSceneClear::InitScene()
{
	//出力させる文字のグラフィックを作成
	Font::SetStrTex(L"クリア");

	Draw::LoadImageW(L"graphic/Stage_Area0.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area1.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area2.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area3.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area4.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area5.png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area6.png", 7, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/White.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Game_clear_text.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/lamp Clear.png", 10, TEX_SIZE_512);

	//音楽データ読み込み用
	Audio::LoadAudio(0, L"BGM/Beta_Clear.wav", BACK_MUSIC);

	//SE読み込み用
	//Audio::LoadAudio(0, L"SE/Cursor.wav", EFFECT);

	//クリアオブジェクト作成
	CObjClear* objc = new CObjClear();
	Objs::InsertObj(objc, OBJ_CLEAR, 10);

	//マスターボリュームを1に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((0.4 - v));

	Audio::Start(11);
}

//ゲームメイン実行中メソッド
void CSceneClear::Scene()
{

}