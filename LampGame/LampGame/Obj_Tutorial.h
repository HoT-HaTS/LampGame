#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjTutorial : public CObj
{
public:
	CObjTutorial(float x, float y);
	~CObjTutorial() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

	//void SetNum(int i) { b_number = i; }


private:
	float m_scroll;     //左右スクロール用
	float m_px;
	float m_py;
	bool T_Sensor;
	int b_number;		//看板番号
};