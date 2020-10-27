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
	Font::SetStrTex(L"シューティングゲーム");

	//タイトルオブジェクト作成
	CObjSelect* obj = new CObjSelect();   //タイトルオブジェクト作成
	Objs::InsertObj(obj, OBJ_SELECT, 10); //主人公オブジェクト登録
}

//ゲームメイン実行中メソッド
void CSceneSelect::Scene()
{

}