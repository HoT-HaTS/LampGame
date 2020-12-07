//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneStage_1.h"
#include "GameHead.h"


//ステージ読み込むたびに初期化されるグローバル変数
extern bool pause_flag = false;
extern bool switch_flag = true;

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


	//グラフィック読み込み
	Draw::LoadImageW(L"graphic/lamp_shadow_walk.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/lamp_v2.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG_shadow.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Glass_Block.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Dead.png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/switch.png", 10, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/lamp_attack.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/switch2.png", 12, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/block.png", 21, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Enemy.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Board.png", 23, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Shattersub.png", 24, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/G_Block.png", 25, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Enemy_dead.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tutorial.png", 50, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/block_shadow.png", 51, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/block.png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG1.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG2.png", 42, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG3.png", 43, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG4.png", 44, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG5.png", 45, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG6.png", 46, TEX_SIZE_512);

	Draw::LoadImageW(L"graphic/pausemenu.png", 13, TEX_SIZE_512);

	Draw::LoadImageW(L"graphic/KeyCoin.png", 30, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Keyblock.png", 31, TEX_SIZE_512);

	Draw::LoadImageW(L"graphic/BG_Area1.png", 60, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/White.png", 61, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area0.png", 14, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area1.png", 15, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area2.png", 16, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area3.png", 17, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area4.png", 18, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area5.png", 19, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area6.png", 20, TEX_SIZE_512);

	Draw::LoadImageW(L"graphic/block.png.png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG1.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG2.png", 42, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG3.png", 43, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG4.png", 44, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG5.png", 45, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG6.png", 46, TEX_SIZE_512);

	//音楽データ読み込み用
	Audio::LoadAudio(10, L"BGM/Tutorial.wav", BACK_MUSIC);
	Audio::LoadAudio(11, L"BGM/Stage1.wav", BACK_MUSIC);
	Audio::LoadAudio(12, L"BGM/Stage2.wav", BACK_MUSIC);
	Audio::LoadAudio(13, L"BGM/Stage3.wav", BACK_MUSIC);
	Audio::LoadAudio(14, L"BGM/Stage4.wav", BACK_MUSIC);
	Audio::LoadAudio(15, L"BGM/Stage5.wav", BACK_MUSIC);
	Audio::LoadAudio(16, L"BGM/Stage6.wav", BACK_MUSIC);

	//SE読み込み用
	Audio::LoadAudio(0, L"SE/Shadow_from.wav", EFFECT);
	Audio::LoadAudio(1, L"SE/Shadow_to.wav", EFFECT);
	Audio::LoadAudio(2, L"SE/Jump.wav", EFFECT);
	Audio::LoadAudio(3, L"SE/Flame.wav", EFFECT);
	Audio::LoadAudio(4, L"SE/Coin.wav", EFFECT);
	Audio::LoadAudio(5, L"SE/En_defeat.wav", EFFECT);
	Audio::LoadAudio(6, L"SE/Miss.wav", EFFECT);
	Audio::LoadAudio(7, L"SE/Switch.wav", EFFECT);
	Audio::LoadAudio(8, L"SE/Unlock.wav", EFFECT);
	Audio::LoadAudio(9, L"SE/fire.wav", EFFECT);

	//オブジェクト出現
	CObjStage1* obj_stage1 = new CObjStage1(map);
	Objs::InsertObj(obj_stage1, OBJ_STAGE1, 30);

	CObjHero* obj_h = new CObjHero();
	Objs::InsertObj(obj_h, OBJ_HERO, 10);

	CObjMain* obj_main = new CObjMain();
	Objs::InsertObj(obj_main, OBJ_MAIN, 35);

	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 6);


	//看板出現用
	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		CObjBoard* objt1 = new CObjBoard(BOARD1_X, BOARD_Y, 0);
		Objs::InsertObj(objt1, OBJ_BOARD, 9);

		CObjBoard* objt2 = new CObjBoard(BOARD2_X, BOARD_Y, 1);
		Objs::InsertObj(objt2, OBJ_BOARD, 9);

		CObjBoard* objt3 = new CObjBoard(BOARD3_X, BOARD_Y, 2);
		Objs::InsertObj(objt3, OBJ_BOARD, 9);
	}


	//マスターボリュームを1に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((0.9 - v));

	Audio::Start(((UserData*)Save::GetData())->stage_id + 10);

}

//実行中メソッド実行中メソッド
void CSceneStage_1::Scene()
{

}




