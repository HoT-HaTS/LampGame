#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjPause : public CObj
{
public:
	CObjPause() {};
	~CObjPause() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	float mx;
	float my;
	bool P_flag;
};


