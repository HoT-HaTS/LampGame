//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneStage_1.h"
#include "GameHead.h"
#include "GameL/UserData.h"

//コンストラクタ
CSceneStage_1::CSceneStage_1()
{

}

//デストラクタ
CSceneStage_1::~CSceneStage_1()
{

}

//初期化メソッド
void CSceneStage_1::InitScene()
{
	//マップデータ完成したら追加
	unique_ptr<wchar_t>p;
	int size;
	p = Save::ExternalDataOpen(L"Stages.csv", &size);
	int map[10][100];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);
			map[i][j] = w;
			count += 2;
		}
	}

	Draw::LoadImageW(L"lamp_walk.png", 0, TEX_SIZE_512);
	Draw::LoadImageW(L"lamp_shadow_walk.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"stage_background", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"stage_ground.png", 21, TEX_SIZE_512);
	Draw::LoadImageW(L"stage_button.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"stage_plate.png", 23, TEX_SIZE_512);

	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 9);

	/*CObj_G_Block* objg = new CObj_G_Block(map);
	Objs::InsertObj(objb, OBJ_G_BLOCK, 8);

	CObjSwitch* objs = new CObjSwitch;
	Objs::InsertObj(objb, OBJ_SWITCH, 7);*/


	/*CObjEnemy* obje = new CObjEnemy(map);
	Objs::InsertObj(obje, OBJ_ENEMY, 12);*/
}

//実行中メソッド実行中メソッド
void CSceneStage_1::Scene()
{

}