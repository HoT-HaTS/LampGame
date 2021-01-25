#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define PAUSE_DRAW_SIZE_T (10.0f)
#define PAUSE_DRAW_SIZE_L (15.0f)
#define PAUSE_DRAW_SIZE_R (775.0f)
#define PAUSE_DRAW_SIZE_B (580.0f)

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


