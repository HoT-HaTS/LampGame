#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjGoalscene : public CObj
{
public:
	CObjGoalscene() {};
	~CObjGoalscene() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

	bool GetS_Flag() { return s_flag; }
private:
	float mx;
	float my;
	float alpha;
	bool s_flag;
};

