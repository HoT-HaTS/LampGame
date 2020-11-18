#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define ASCROLL_LINE (300)
#define BSCROLL_LINE (200)

#define BLOCKCUT_SIZE_T (640.0f)
#define BLOCKCUT_SIZE_R (896.0f)
#define BLOCKCUT_SIZE_B (640.0f)

#define DRAW_SIZE_R (800.0f)
#define DRAW_SIZE_B (600.0f)

#define BLOCK_SIZE (64.0f)
#define HIT_LENGTH (111.0f)


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

	void BlockHit2
	(
		float* x, float* y, bool scroll_on,
		bool* up, bool* down, bool* left, bool* right,
		float* vx, float* vy, int* btu, int* btg
	);



private:
	int m_map[10][100]; //マップ情報

	float m_scroll;     //左右スクロール用

	//float m_px; //使われていないのでコメントアウト
	//float m_py;

};
