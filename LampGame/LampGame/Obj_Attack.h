#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjAttack : public CObj
{
public:
	CObjAttack(float x, float y);
	~CObjAttack() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	float m_x;
	float m_y;
};

