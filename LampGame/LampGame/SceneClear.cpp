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

	//Draw::LoadImageW(L"graphic/Stageselect_cursor.png", 1, TEX_SIZE_512);

	//音楽データ読み込み用
	//Audio::LoadAudio(11, L"BGM/Sunrise_Title.wav", BACK_MUSIC);

	//SE読み込み用
	//Audio::LoadAudio(0, L"SE/Cursor.wav", EFFECT);

	//クリアオブジェクト作成
	CObjClear* objc = new CObjClear();   //ステージセレクトオブジェクト作成
	Objs::InsertObj(objc, OBJ_CLEAR, 10);

	//マスターボリュームを1に戻す
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((0.4 - v));

	//Audio::Start(11);
}

//ゲームメイン実行中メソッド
void CSceneClear::Scene()
{

}