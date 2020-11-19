#pragma once
//使用するヘッダーファイル
#include "GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

#define BOARD1_X (640.0)
#define BOARD2_X (1664.0)
#define BOARD3_X (3456.0)
#define BOARD_Y (512.0)

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
