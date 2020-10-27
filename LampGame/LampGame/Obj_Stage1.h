#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjStage1 : public CObj
{
public:
	CObjStage1(int map[10][100]);
	~CObjStage1() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	//void  SetScroll(float s) { m_scroll = s; }
	//float GetScroll() { return m_scroll; }

private:
	float s1_scroll;
	int m_map[10][100];
	bool g_f;

	void BlockDraw(float x, float y, RECT_F* dst, float c[], int block_id);
};
