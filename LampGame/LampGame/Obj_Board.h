#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjBoard : public CObj
{
public:
	CObjBoard(int map[10][100]);	
	~CObjBoard() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	void  SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

private:
	int m_map[10][100]; //マップ情報

	float m_scroll;     //左右スクロール用
	float m_px;
	float m_py;

};
