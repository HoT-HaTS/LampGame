#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[10][100]);	
	~CObjBlock() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	void  SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	//int GetMap() { return m_map[10][100]; }
	//ブロックとの当たり判定
	void BlockHit
	(
		float* x, float* y, bool scroll_on,
		bool* up, bool* down, bool* left, bool* right,
		float* vx, float* vy, int* btu,int* btg
	);



private:
	int m_map[10][100]; //マップ情報

	float m_scroll;     //左右スクロール用
	float m_px;
	float m_py;

};
