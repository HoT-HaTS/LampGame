//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_Hero.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHero::Init()
{
	m_px = INIT_H_PX;		//位置
	m_py = INIT_H_PY;
	m_vx = INIT_H_VX;		//移動ベクトル
	m_vy = INIT_H_VY;
	m_posture = INIT_H_POSTURE;	//右向き0.0f 左向き1.0f

	int m_ani_time = INIT_ANI_TIME;
	int m_ani_frame = INIT_ANI_FLAME;	//静止フレームを初期にする

	m_speed_power = INIT_SPEED_POWER;	//通常速度
	m_ani_max_time = INIT_ANI_MAX_TIME;	//アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = BLOCK_TYPE;	//踏んでいるblockの種類確認用

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, HBLOCK_INT_X_SIZE, HBLOCK_INT_Y_SIZE, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//キーの入力方向
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1.0;
	}

	else if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1.0;
	}

	else
	{
		m_ani_frame = 1;	//キー入力がない場合は静止フレームにする
		m_ani_time = 0;
	}

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == m_ani_max_time)
	{
		m_ani_frame = 0;
	}

	//摩擦
	m_vx += -(m_vx * INIT_FRICTION);

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//HitBoxの位置の変更
	hit->SetPos(m_px, m_py);
}

//ドロー
void CObjHero::Draw()
{
	//アニメーション番号
	int AniData[4] =
	{
		0,1,2,3,
	};

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
	src.m_right = HBLOCK_INT_X_SIZE + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
	src.m_bottom = HBLOCK_INT_Y_SIZE;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (HBLOCK_INT_X_SIZE - HBLOCK_INT_X_SIZE * m_posture) + m_px;
	dst.m_right = (HBLOCK_INT_X_SIZE * m_posture) + m_px;
	dst.m_bottom = HBLOCK_INT_Y_SIZE + m_py;

	//光フラグがONなら
	//if～～
	//0番目に登録したグラフィック(主人公・光)をsrc・dst・c の情報をもとに描画
	Draw::Draw(0, &src, &dst, c, 0.0f);


	//影フラグがONなら
	//if～～
	//1番目に登録したグラフィック(主人公・影)をsrc・dst・c の情報をもとに描画
	//Draw::Draw(1, &src, &dst, c, 0.0f);

}