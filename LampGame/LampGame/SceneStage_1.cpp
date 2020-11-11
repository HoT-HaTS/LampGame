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


extern bool pause_flag = false;

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
	

	CObjSelect* stage = (CObjSelect*)Objs::GetObj(OBJ_SELECT);

	//マップデータ完成したら追加
	unique_ptr<wchar_t>p;
	int size;
	int map[10][100];
	wchar_t str[128];

	swprintf_s(str, L"stagedata/Stage%d.csv", ((UserData*)Save::GetData())->stage_id);
	p = Save::ExternalDataOpen(str, &size);
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

	Draw::LoadImageW(L"graphic/lamp_shadow_walk.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/lamp_v2.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG_shadow.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/switch.png", 10, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/lamp_attack.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/switch2.png", 12, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_background.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/block.png", 21, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Enemy.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Board.png", 23, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Shattersub.png", 24, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/G_Block.png", 25, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tutorial.png", 50, TEX_SIZE_512);
	
	Draw::LoadImageW(L"graphic/pausemenu.png", 13, TEX_SIZE_512);

	Draw::LoadImageW(L"graphic/KeyCoin.png", 30, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Keyblock.png", 31, TEX_SIZE_512);


	CObjStage1* obj_stage1 = new CObjStage1(map);
	Objs::InsertObj(obj_stage1, OBJ_STAGE1, 30);

	CObjHero* obj_h = new CObjHero();
	Objs::InsertObj(obj_h, OBJ_HERO, 10);

	CObjMain* obj_main = new CObjMain();
	Objs::InsertObj(obj_main, OBJ_MAIN, 11);

	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 6);


	//看板出現用
	if (((UserData*)Save::GetData())->stage_id == 1)
	{
		CObjBoard* objt1 = new CObjBoard(640, 512, 0);
		Objs::InsertObj(objt1, OBJ_BOARD, 9);

		CObjBoard* objt2 = new CObjBoard(1664, 512, 1);
		Objs::InsertObj(objt2, OBJ_BOARD, 9);

		CObjBoard* objt3 = new CObjBoard(3456, 512, 2);
		Objs::InsertObj(objt3, OBJ_BOARD, 9);
	}
	//ギミックブロック3テスト用
	/*CObj_G_Block3* objb3 = new CObj_G_Block3(300, 200);
	Objs::InsertObj(objb3, OBJ_G_BLOCK3, 8);*/

	//G2ブロックテスト用
	//CObj_G_Block2* objg2 = new CObj_G_Block2(800, 500);
	//Objs::InsertObj(objg2, OBJ_G_BLOCK, 8);

	//CObj_G_Block2* objg21 = new CObj_G_Block2(864, 436);
	//Objs::InsertObj(objg21, OBJ_G_BLOCK, 8);

	//スイッチ出現
	//CObjSwitch2* objs2 = new CObjSwitch2(600, 500);
	//Objs::InsertObj(objs2, OBJ_SWITCH2, 7);

	//G4ブロック出現
	//CObj_G_Block4* objg4 = new CObj_G_Block4(800, 500);
	//Objs::InsertObj(objg4, OBJ_BLOCK, 8);

	//G5ブロックテスト用
	//CObj_G_Block5* objg5 = new CObj_G_Block5(800, 500);
	//Objs::InsertObj(objg5, OBJ_G_BLOCK, 8);

	//CObjKeycoin* objcoin1 = new CObjKeycoin(300, 500);
	//Objs::InsertObj(objcoin1, OBJ_COIN, 7);

	//CObjKeycoin* objcoin2 = new CObjKeycoin(500, 500);
	//Objs::InsertObj(objcoin2, OBJ_COIN, 7);

	//CObjKeycoin* objcoin3 = new CObjKeycoin(700, 500);
	//Objs::InsertObj(objcoin3, OBJ_COIN, 7);
}

//実行中メソッド実行中メソッド
void CSceneStage_1::Scene()
{

}




