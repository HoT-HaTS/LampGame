#pragma once
//使用するヘッダー

#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObj_G_Block4 : public CObj
{
public:
	CObj_G_Block4(float x, float y);
	~CObj_G_Block4() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

	bool Get_G4_flag() { return G4_flag; }


private:
	bool G4_flag;		//ギミックブロック用
	bool a_flag;		//HitBox作れるか調べるフラグ

	float m_px;			//位置
	float m_py;

	int m_time;			//時間
};
