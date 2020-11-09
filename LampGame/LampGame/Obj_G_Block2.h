#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObj_G_Block2 : public CObj
{
	public:
		CObj_G_Block2(float x, float y);
		~CObj_G_Block2() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー
	
		bool Get_G2_flag() { return G2_flag; }
	
	
	private:
		bool G2_flag;
	
		float m_px;			//位置
		float m_py;
};