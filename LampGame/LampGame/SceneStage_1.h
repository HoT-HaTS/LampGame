#pragma once
//使用するヘッダーファイル
#include "GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

#define MAP_X (100)
#define MAP_Y (10)

#define MAX_STR (128)

#define INIT_COUNT (1)
#define PLUS_COUNT (2)

#define BOARD1_X (256.0)
#define BOARD2a_X (2432.0)
#define BOARD2b_X (3776.0)
#define BOARD3_X (3712.0)
#define BOARD4_X (1536.0)
#define BOARD5_X (640.0)
#define BOARD6_X (896.0)
#define BOARD7_X (4736.0)
#define BOARD_Y (512.0)
#define BOARD_Yb (128.0)

#define BOARD_MOVE (0)
#define BOARD_Z_KEY (1)
#define BOARD_X_KEY (2)
#define BOARD_SPACE_KEY (3)
#define BOARD_P_KEY (4)
#define BOARD_GLASS_BLOCK (5)
#define BOARD_KEY_BLOAK (6)

//シーン：メイン
class CSceneStage_1 :public CScene
{
public:
	CSceneStage_1();
	~CSceneStage_1();
	void InitScene(); //初期化メソッド
	void Scene();		//実行中メソッド
	void Draw();
private:
};
