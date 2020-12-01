#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_MAIN,
	OBJ_ATTACK,
	OBJ_BLOCK,
	OBJ_ENEMY,
	OBJ_G_BLOCK,
	OBJ_G_BLOCK2,
	OBJ_G_BLOCK3,
	OBJ_G_BLOCK4,
	OBJ_KEYCOIN,
	OBJ_HERO,
	OBJ_SWITCH,
	OBJ_SWITCH2,
	OBJ_BOARD,
	OBJ_SELECT,
	OBJ_PAUSE,

	OBJ_STAGE1,
	OBJ_TITLE,
	OBJ_CLEAR,
	OBJ_GOALSCENE,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_ATTACK,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLOCK,
	ELEMENT_WHITE,
	ELEMENT_SWITCH,
	ELEMENT_BOARD,
	ELEMENT_COIN,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	int stage_id;
	bool clear[6];
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--
extern bool pause_flag;	//ポーズ画面用のフラグ
extern bool switch_flag;	//スイッチ用フラグ


//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "Obj_Main.h"
#include "Obj_Attack.h"
#include "Obj_Block.h"
#include "Obj_Enemy.h"
//#include "Obj_G_Block1.h"
#include "Obj_G_Block2.h"
#include "Obj_G_Block3.h"
#include "Obj_G_Block4.h"
#include "Obj_G_Block5.h"
#include "Obj_KeyCoin.h"
#include "Obj_Hero.h"
//#include "Obj_Switch.h"
#include "Obj_Switch2.h"
#include "Obj_Stage1.h"
#include "ObjSelect.h"
#include "Obj_Board.h"
#include "Obj_Pause.h"
#include "ObjTitle.h"
#include "ObjClear.h"
#include "ObjBackGround.h"
#include "Obj_Goalscene.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneStage_1.h"
#include "SceneSelect.h"
#include "SceneTitle.h"
#include "SceneClear.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
//#define SET_GAME_START CSceneSelect
#define SET_GAME_START CSceneTitle
//-----------------------------------------------