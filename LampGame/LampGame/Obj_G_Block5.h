#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObj_G_Block5 : public CObj
{
public:
	CObj_G_Block5(float x, float y);
	~CObj_G_Block5() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー


	bool Get_G5_flag() { return G5_flag; }


private:
	bool G5_flag;
	int coin_count;
	float m_px;			//位置
	float m_py;

};
