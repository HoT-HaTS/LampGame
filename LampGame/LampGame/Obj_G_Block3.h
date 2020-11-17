#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObj_G_Block3 : public CObj
{
public:
	CObj_G_Block3(float x, float y);
	~CObj_G_Block3() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

		//ブロックとの当たり判定
	void BlockHit3
	(
		float* x, float* y, bool scroll_on,
		bool* up, bool* down, bool* left, bool* right,
		float* vx, float* vy
	);

private:
	bool L_flag;

	float m_px;			//位置
	float m_py;

	float m_scroll;

};


