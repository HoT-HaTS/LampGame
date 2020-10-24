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

#define INIT_SPEED_POWER (1.4)	//加算速度
#define INIT_ANI_MAX_TIME (5.0)	

#define INIT_FRICTION (0.2)	//摩擦係数

#define BLOCK_TYPE (0.0)	//ブロックの種類識別用

#define HBLOCK_INT_X_SIZE (64.0f)	//主人公横サイズ
#define HBLOCK_INT_Y_SIZE (128.0f)//主人公縦サイズ
#define STAGE_Y_OUT (800.0f)	//下方向ステージ外判定


//ベクトルの正規化を行う関数
bool UnitVec(float* vx, float* vy);

//オブジェクト：
class CObjHero : public CObj
{
	public:
		CObjHero() {};
		~CObjHero() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

		//関数
		float GetX() { return m_px; }
		float GetY() { return m_py; }
		float GetVY() { return m_vy; }
		float GetVX() { return m_vx; }
		int GetBT() { return m_block_type; }

		float GetPosture() { return m_posture; }

		bool Get_L_flag(){ return L_flag; }

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
		float m_sx;			//世界切り替え時の位置
		float m_sy;

		float m_posture;	//姿勢

		float m_ani_time;	//アニメーションフレーム動作間隔
		float m_ani_s_time;	//ストップアニメーションフレーム動作間隔
		int m_ani_frame;	//描画フレーム
		int m_ani_s_frame;	//ストップアニメーション描画フレーム

		float m_speed_power;	//スピードパワー
		float m_ani_max_time;	//アニメーション動作間隔最大値

		int time;				//世界切り替え制御用時間

		//blockとの衝突状態確認用
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;

		bool attack_flag;	//攻撃制御用フラグ

		//光の世界フラグ
		bool L_flag;
		//光の世界制御用フラグ
		bool m_flag;

		//踏んでいるblockの種類確認用
		int m_block_type;

		float CheckWindow(float pos_x, float pos_y,
			float window_x, float window_y, float window_w, float window_h);
};

