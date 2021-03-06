//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "Obj_Switch2.h"

//使用するネームスペース
using namespace GameL;

CObjSwitch2::CObjSwitch2(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}


//イニシャライズ
void CObjSwitch2::Init()
{
	m_scroll = 0.0f;

	//S2_flag = switch_flag;		//スイッチがオフのときはfalse、オンのときはtrue
	a_flag = false;

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE - 5.0f, SBLOCK_INT_Y_SIZE, ELEMENT_SWITCH, OBJ_SWITCH, 1);
}

//アクション
void CObjSwitch2::Action()
{

	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の位置の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);


	//主人公の衝突確認用のフラグの初期化
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);



	//主人公から光フラグを取ってくる
	bool L_flag_switch = hero->Get_L_flag();

	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 2.5f + scroll->GetScroll(), m_py);

	//主人公とスイッチのあたり判定チェック
	//当たっている場合
	if ((hit->CheckObjNameHit(OBJ_HERO) != nullptr) && (L_flag_switch == false))
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//スイッチの上じゃない条件
		if (hy + (2 * BLOCK_SIZE - 8) > m_py)
		{
			//スイッチの左部分に接触
			if (m_px + scroll->GetScroll() > hx)
			{
				hero->SetRight(true);
				hero->SetX(m_px - (BLOCK_SIZE + 0.5) + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
			//スイッチの右部分に接触
			else if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + (BLOCK_SIZE - 0.5) + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
		}
		//スイッチの上部分に接触
		if (hy + (2 * BLOCK_SIZE - 1) <= m_py)
		{
			hero->SetDown(true);
			hero->SetY(m_py - (2 * BLOCK_SIZE + 0.5));
			hero->SetVY(0.0f);
		}
		//スイッチの下部分に接触
		else if (m_py + (BLOCK_SIZE + 1) <= hy)
		{
			hero->SetUp(true);
			hero->SetY(m_py + (BLOCK_SIZE - 0.5));
			hero->SetVY(0.0f);
		}
	}

	//主人公の攻撃がHitBoxに当たるとflagをtrueにする

	//当たってないとfalse
	if (hit->CheckObjNameHit(OBJ_ATTACK) == nullptr)
		a_flag = false;				//スイッチのフラグをtrueに

	if (a_flag == false)
	{
		if (switch_flag == false)
		{
			if (hit->CheckObjNameHit(OBJ_ATTACK) != nullptr)
			{
				switch_flag = true;				//スイッチのフラグをtrueに
				a_flag = true;
				//スイッチの音
				Audio::Start(7);
			}
		}
	}
	if (a_flag == false)
	{
		if (switch_flag == true)
		{
			if (hit->CheckObjNameHit(OBJ_ATTACK) != nullptr)
			{
				switch_flag = false;				//スイッチのフラグをtrueに
				a_flag = true;

				//スイッチの音
				Audio::Start(7);
			}
		}
	}
}

//ドロー
void CObjSwitch2::Draw()
{
	int switch_graphic;		//影と光でスイッチの描画を変えるための数字、ここだけでしか使わないため、ここで宣言している

	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//Hero.cppから光フラグを取得する
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool L_flag_switch = hero->Get_L_flag();
	if (L_flag_switch == true)
		switch_graphic = 0;
	else
		switch_graphic = 1;


	//切り取り位置の設定
	src.m_top = 0.0f + (switch_graphic * BLOCK_SIZE);
	src.m_left = 0.0f + (switch_flag * BLOCK_SIZE);
	src.m_right = BLOCK_SIZE + (switch_flag * BLOCK_SIZE);
	src.m_bottom = BLOCK_SIZE + (switch_graphic * BLOCK_SIZE);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//12番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(12, &src, &dst, c, 0.0f);
}