#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define INIT_H_VX (0.0f)		//主人公速度
#define INIT_H_VY (0.0f)
#define INIT_H_PX (64.0f)		//主人公位置
#define INIT_H_PY (350.0f)

#define INIT_H_POSTURE (1.0)	//主人公向き

#define INIT_ANI_TIME (0.0)		//アニメーションタイム	
#define INIT_ANI_FLAME (0.0)	//アニメーションフレーム

#define INIT_SPEED_POWER (0.4)	//加算速度
#define INIT_ANI_MAX_TIME (4.0)	//アニメーション4種変更用

#define INIT_FRICTION (0.098)	//摩擦係数

#define BLOCK_TYPE (0.0)	//ブロックの種類識別用

#define HBLOCK_INT_X_SIZE (64.0f)	//主人公横サイズ
#define HBLOCK_INT_Y_SIZE (128.0f)//主人公縦サイズ

//オブジェクト：
class CObjHero : public CObj
{
	public:
		CObjHero() {};
		~CObjHero() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

		float GetX() { return m_px; }
		float GetY() { return m_py; }
		float GetVY() { return m_vy; }
		float GetVX() { return m_vx; }
		int GetBT() { return m_block_type; }

		void SetX(float x) { m_px = x; }
		void SetY(float y) { m_py = y; }
		void SetVY(float vy) { m_vy = vy; }
		void SetVX(float vx) { m_vx = vx; }
		void SetBT(int t) { m_block_type = t; }

		void SetUp(bool b) { m_hit_up = b; }
		void SetDown(bool b) { m_hit_down = b; }
		void SetLeft(bool b) { m_hit_left = b; }
		void SetRight(bool b) { m_hit_right = b; }
	
	private:
		float m_px;			//位置
		float m_py;
		float m_vx;			//移動ベクトル
		float m_vy;
		float m_posture;	//姿勢

		float m_ani_time;		//アニメーションフレーム動作間隔
		int m_ani_frame;	//描画フレーム

		float m_speed_power;	//スピードパワー
		float m_ani_max_time;	//アニメーション動作間隔最大値

		//blockとの衝突状態確認用
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;

		//踏んでいるblockの種類確認用
		int m_block_type;

		//テスト用
		float px, py;	//交点
};

