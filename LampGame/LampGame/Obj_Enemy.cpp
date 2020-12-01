//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "Obj_Enemy.h"

//使用するネームスペース
using namespace GameL;

CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;		//位置
	m_py = y - 10;
}

//イニシャライズ
void CObjEnemy::Init()
{

	m_vx = INIT_E_VX;		//移動ベクトル
	m_vy = INIT_E_VY;
	//m_posture = INIT_E_POSTURE;	//右向き0.0f 左向き1.0f

	m_ani_time = INIT_ANI_TIME;
	m_ani_frame = INIT_ANI_FRAME;	//静止フレームを初期にする

	m_speed_power = INIT_E_SPEED_POWER;	//通常速度
	m_ani_max_time = INIT_E_ANI_MAX_TIME; //アニメーション間隔幅

	m_move = true;			//true=右　false=左

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	E_flag = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//アクション
void CObjEnemy::Action()
{

	//通常速度
	//m_speed_power = 0.3;    //移動速度
	//m_ani_max_time = 8;		//アニメーション間隔幅

	//Hero.cppから光フラグを取得する
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool L_flag_enemy = hero->Get_L_flag();

	if (L_flag_enemy == true)
	{

		//ブロック衝突で向き変更
		if (m_hit_left == true)
		{
			m_move = true;
		}
		if (m_hit_right == true)
		{
			m_move = false;
		}

		//移動方向
		if (m_move == false)
		{
			m_vx += m_speed_power;
			m_posture = 1.0f;		//右向き
		}
		else if (m_move == true)
		{
			m_vx -= m_speed_power;
			m_posture = 0.0f;		//左向き
		}


		if (L_flag_enemy == true)
		{
			m_ani_time += 1;
		}

		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		if (m_ani_frame >= 8)
		{
			m_ani_frame = 0;
		}


		//摩擦
		m_vx += -(m_vx * 0.098);

		//自由落下運動
		m_vy += 9.8 / (16.0f);

		//ブロックタイプ検知用の変数がないためのダミー
		int d1;

		//ブロックとの当たり判定実行
		CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		pb->BlockHitEnemy(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&d1);

		//位置の更新
		m_px += m_vx;
		m_py += m_vy;
	}

		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//HitBoxの位置の変更
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py);


	//主人公の位置の取得
	//CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公と敵のあたり判定チェック
	//当たっている場合
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//敵の上じゃない条件
		if (hy + 120 > m_py)
		{
			//敵の左部分に接触
			if (m_px + scroll->GetScroll() > hx)
			{
				hero->SetRight(true);
				hero->SetX(m_px - 64.5 + scroll->GetScroll());
				hero->SetVX(-0.8);
			}
			//敵の右部分に接触
			else if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + 63.5 + scroll->GetScroll());
				hero->SetVX(0.0);
			}
		}
		//敵の上部分に接触
		if (hy + 125 <= m_py)
		{
			hero->SetDown(true);
			hero->SetY(m_py - 128.5);
			hero->SetVY(0.0);
		}
		//敵の下部分に接触
		else if (m_py + 61 <= hy)
		{
			hero->SetUp(true);
			hero->SetY(m_py + 64.5);
			hero->SetVY(0.0);
		}
	}


	if (L_flag_enemy == true)
	{
		//光の世界かつ主人公の攻撃がHitBoxに当たるとflagをtrueにする
		if (hit->CheckObjNameHit(OBJ_ATTACK) != nullptr)
		{
			E_flag = true;				//スイッチのフラグをtrueに
		}
		//flagがtrueのとき自身を消滅させる
		if (E_flag == true)
		{
			//敵消滅SE
			Audio::Start(5);

			this->SetStatus(false);		//スイッチが押されたら消滅
			Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
			return;
		}
	}
	
}

//ドロー
void CObjEnemy::Draw()
{
	//アニメーション番号
	int AniData[8] =
	{
		0, 1, 2, 3, 4, 5, 6, 7,
	};

	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_right = AniData[m_ani_frame]*BLOCK_SIZE - BLOCK_SIZE * m_posture;
	src.m_left = src.m_right - (1 - m_posture)*BLOCK_SIZE + m_posture * BLOCK_SIZE;
	src.m_bottom = E_YSIZE;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_right = 0.0f + m_px + scroll->GetScroll();
	dst.m_left = dst.m_right + E_XSIZE;
	dst.m_bottom = dst.m_top + E_YSIZE;

	//0番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(22, &src, &dst, c, 0.0f);
}