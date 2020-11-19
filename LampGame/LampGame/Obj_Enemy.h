#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//関数化
//敵のサイズ
#define E_XSIZE (64.0f);
#define E_YSIZE (64.0f);

//移動ベクトルの初期化
#define INIT_E_VX (0.0f);
#define INIT_E_VY (0.0f);

//アニメーション関係の初期化
#define INIT_E_ANI_MAX_TIME (9.0);

#define INIT_E_SPEED_POWER (0.3f)

//向きの初期化
#define INIT_E_POSTURE (1.0f);


//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjEnemy : public CObj
{
public:
	CObjEnemy(float x, float y);
	~CObjEnemy() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

	float GetVx() { return m_vx; }
private:
	float m_px;			//位置
	float m_py;
	float m_vx;			//移動ベクトル
	float m_vy;
	float m_posture;	//姿勢

	int m_ani_time;		//アニメーションフレーム動作間隔
	int m_ani_frame;	//描画フレーム

	float m_speed_power;	//スピードパワー
	float m_ani_max_time;	//アニメーション動作間隔最大値

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool E_flag;

	//移動の向きの制御用
	bool m_move;
};

