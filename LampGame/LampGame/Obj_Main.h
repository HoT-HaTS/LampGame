#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define DEAD_TIME (60)
#define ADD_ALPHA (0.02f)
#define SRC_BLACK_R (8.0f)
#define SRC_BLACK_B (6.0f)
#define SRC_GUIDE_R (600.0f)
#define SRC_GUIDE_B (32.0f)
#define DST_GUIDE_L (200.0f)
#define DST_GUIDE_R (600.0f)
#define DST_GUIDE_B (32.0f)

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
	float dead_alpha;
	float in_alpha;
	float d_time;
	bool g_flag;
	bool ga_flag;
	bool d_flag;
};