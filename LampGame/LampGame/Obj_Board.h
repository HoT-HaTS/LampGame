#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjBoard : public CObj
{
public:
	CObjBoard(float x, float y);
	~CObjBoard() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	bool Get_Tuto_Sensor() { return T_Sensor; };//チュートリアル表示センサー
private:
	float m_scroll;     //左右スクロール用
	float m_px;
	float m_py;
	bool T_Sensor;
};
