#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//クリアマーク表示座標
#define CLEAR_MARK_X1 (40)
#define CLEAR_MARK_X2 (235)
#define CLEAR_MARK_X3 (430)
#define CLEAR_MARK_X4 (625)
#define CLEAR_MARK_Y1 (105)
#define CLEAR_MARK_Y2 (305)

//セレクト文章表示
#define SELECT_SIZE_X (401.0f)
#define SELECT_SIZE_Y (91.0f)
#define SELECT_DRAW_X (10.0f)
#define SELECT_DRAW_Y (199.5f)

//エンターで選択　文章表示
#define ENTER_SIZE_X (372.0f)
#define ENTER_SIZE_Y (71.0f)
#define ENTER_DRAW_X (214.5f)
#define ENTER_DRAW_Y (490.0f)

//EXIT　文章表示
#define EXIT_SIZE_X (163.0f)
#define EXIT_SIZE_Y (31.0f)
#define EXIT_DRAW_X (589.0f)
#define EXIT_DRAW_Y (681.5f)

//ステージサムネ表示
#define STAGE_THUMB_SIZE_X (140.0f)
#define STAGE_THUMB_SIZE_Y (140.0f)

//ステージ選択カーソル 切り取りサイズ
#define CURSOR_CUTOUT_SIZE_X (250.0f)
#define CURSOR_CUTOUT_SIZE_Y (187.0f)
//ステージ選択カーソル　位置
#define CURSOR_X1 (35.0f)
#define CURSOR_X2 (230.0f)
#define CURSOR_X3 (425.0f)
#define CURSOR_X4 (620.0f)
#define CURSOR_Y1 (100.0f)
#define CURSOR_Y2 (300.0f)
//ステージ選択カーソル 表示サイズ
#define CURSOR_DRAW_SIZE_X (150.0f)
#define CURSOR_DRAW_SIZE_Y (150.0f)


//クリアマークサイズ
#define CLAER_MARK_SIZE_X (64.0f)
#define CLAER_MARK_SIZE_Y (64.0f)





//オブジェクト：タイトル
class CObjSelect : public CObj
{
public:
	CObjSelect() {};
	~CObjSelect() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	int GetStageID() { return stage_id; }
private:
	bool m_key_flag;  //キーフラグ
	bool select_flag; //ステージセレクト用フラグ

	int stage_id;
};