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
	int map[10][100];
	p = Save::ExternalDataOpen(L"Stages.csv", &size);
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

	Draw::LoadImageW(L"lamp_shadow_walk.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"lamp_v2.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"GBlock_Wood.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"stage_background.png", 4, TEX_SIZE_512);

	Draw::LoadImageW(L"lamp_attack.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"stage_background.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"block.png", 21, TEX_SIZE_512);

	Draw::LoadImageW(L"Enemy.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"Board.png", 23, TEX_SIZE_512);
	Draw::LoadImageW(L"switch.png", 10, TEX_SIZE_512);

	
	CObjStage1* obj_stage1 = new CObjStage1(map);
	Objs::InsertObj(obj_stage1, OBJ_STAGE1, 13);

	CObjHero* obj_h = new CObjHero();
	Objs::InsertObj(obj_h, OBJ_HERO, 10);
	

	CObjMain* obj_main = new CObjMain();
	Objs::InsertObj(obj_main, OBJ_MAIN, 11);

	/*CObjSwitch* objs = new CObjSwitch(100, 200);
	Objs::InsertObj(objs, OBJ_SWITCH, 7);*/

	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 6);

	/*CObj_G_Block* objg = new CObj_G_Block(0, 0);
	Objs::InsertObj(objg, OBJ_BLOCK, 8);*/


	/*CObjEnemy* obje = new CObjEnemy(map);
	Objs::InsertObj(obje, OBJ_ENEMY, 12);*/
}

//実行中メソッド実行中メソッド
void CSceneStage_1::Scene()
{

}




