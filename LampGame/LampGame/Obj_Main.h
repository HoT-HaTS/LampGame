#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjMain : public CObj
{
public:
	CObjMain() {};
	~CObjMain() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	bool m_flag;
	int coin_count;

	//ゴール演出用の変数
	float alpha;
	bool g_flag;
	bool ga_flag;
};

