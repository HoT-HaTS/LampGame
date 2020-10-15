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
#include "SceneMain.h"
#include "GameHead.h"
#include "GameL/UserData.h"

//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::CSceneMain()
{

}

//初期化メソッド
void CSceneMain::InitScene()
{
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

	Draw::LoadImageW(L"lamp walk.png", 0, TEX_SIZE_512);
	Draw::LoadImageW(L"lamp shadow walk.png", 1, TEX_SIZE_512);

	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 9);

	CObj_G_Block* objg = new CObj_G_Block(map);
	Objs::InsertObj(objb, OBJ_G_BLOCK, 8);

	CObjSwitch* objs = new CObjSwitch;
	Objs::InsertObj(objb, OBJ_SWITCH, 7);


	/*CObjEnemy* obje = new CObjEnemy(map);
	Objs::InsertObj(obje, OBJ_ENEMY, 12);*/
}

//実行中メソッド実行中メソッド
void CSceneMain::Scene()
{

}