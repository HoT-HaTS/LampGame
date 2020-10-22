#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

#define INIT_ANI_TIME (0.0)		//アニメーションタイム	
#define INIT_ANI_FLAME (0.0)	//アニメーションフレーム

#define INIT_A_POSTURE (1.0)	//攻撃向き

#define ABLOCK_INT_X_SIZE (64.0f)	//攻撃横サイズ
#define ABLOCK_INT_Y_SIZE (64.0f)	//攻撃縦サイズ

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjAttack : public CObj
{
public:
	CObjAttack(float x, float y);
	~CObjAttack() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	int m_ani_frame;		//アニメーションタイム
	int m_ani_time;		//アニメーションフレーム

	int m_posture;		//攻撃の向き(1で右、0で左)

	float m_px;			//位置
	float m_py;
};

