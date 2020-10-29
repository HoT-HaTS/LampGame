#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

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