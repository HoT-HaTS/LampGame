#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObj_G_Block : public CObj
{
	public:
		CObj_G_Block(float x, float y);
		~CObj_G_Block() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	
		//ブロックとの当たり判定
		void BlockHit
		(
			float* x, float* y, bool scroll_on,
			bool* up, bool* down, bool* left, bool* right,
			float* vx, float* vy, int* bt
		);

		//主人公と壁の交差判定
		bool HeroBlockCrossPoint(
			float x, float y, float vx, float vy,
			float* out_px, float* out_py, float* out_len
		);
	private:
		float m_px;			//位置
		float m_py;

		//線と線と交差判定
		bool LineCrossPoint(
			float a1x, float a1y, float a2x, float a2y,
			float b1x, float b1y, float b2x, float b2y,
			float* out_px, float* out_py
		);
};

