//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Switch.h"

//使用するネームスペース
using namespace GameL;

 CObjSwitch::CObjSwitch(float x, float y)
{
	 m_px = x;			//位置
	 m_py = y;
}


//イニシャライズ
void CObjSwitch::Init()
{
	m_scroll = 0.0f;

	S_flag = false;			//スイッチがオフのときはfalse、オンのときはtrue

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_SWITCH, OBJ_SWITCH, 1);
}

//アクション
void CObjSwitch::Action()
{
	if (Input::GetVKey('A') == true)
	{
		S_flag == true;
	}

	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の位置の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//主人公の衝突確認用のフラグの初期化
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//主人公から光フラグを取ってくる
	bool L_flag_switch = hero->Get_L_flag();

	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px+scroll->GetScroll(), m_py);

	//主人公とスイッチのあたり判定チェック
	//当たっている場合

	/*
	//スクロールの影響
	float scroll = scroll_on ? m_scroll : 0;

	//オブジェクトとブロックの当たり判定(ブロックの左:右:上:下の順)
	if ((hx + (-scroll) + 64.0f > m_px) && (hx + (-scroll) < m_px + 64.0f) && (hy + 128.0f > m_py) && (hy < m_py + 64.0f))
	{
		//上下左右判定

		//主人公とブロックの中心でvector作成
		float rvx = (hx + (-scroll) + 32.0f) - (m_px + 32.0f);
		float rvy = (hy + 64.0f) - (m_py + 32.0f);

		//長さlenを求める
		float len = sqrt(rvx * rvx + rvy * rvy);

		//角度rを求める
		float r = atan2(rvy, rvx);	//(ラジアン)
		r = r * 180.0f / 3.14f;		//度

		if (r <= 0.0f)
			r = abs(r);
		else
			r = 360.0f - abs(r);

		//lenがある一定の長さより短い場合に判定に入る。
		if (len < 111.0f)
		{
			//角度で上下左右を判定
			if ((r < 56 && r >= 0) || r > 304)
			{
				//右
				hero->SetRight(true);	//オブジェクトの左の部分が衝突している
				hx = m_px + 64.0f + (scroll);	//ブロックの位置+オブジェクトの幅
				*vx = -(*vx) * 0.1f;	//-VX*反発係数
			}
			if (r > 56 && r < 124)
			{
				//上
				hero->SetDown(true);	//オブジェクトの下の部分が衝突している
				hy = m_py - 128.0f;	//ブロックの位置+オブジェクトの幅
				*vy = 0.0f;
			}
			if (r > 124 && r < 236)
			{
				//左
				hero->SetLeft(true);	//オブジェクトの右の部分が衝突している
				hx = m_px - 64.0f + (scroll);	//ブロックの位置+オブジェクトの幅
				*vx = -(*vx) * 0.1f;	//-VX*反発係数
			}
			if (236 < r && r < 304)
			{
				//下
				hero->SetUp(true);	//オブジェクトの上の部分が衝突している
				hy = m_py + 64.0f;	//ブロックの位置+オブジェクトの幅
				if (hy < 0)
				{
					*vy = 0.0f;
				}
			}
		}
	}*/
	
	/*
	if ((hit->CheckObjNameHit(OBJ_HERO) != nullptr)&&(L_flag_switch==false))
	{
		//スイッチの左部分に接触

		if ((m_px+10 > hx + 64) && (m_px  > hx ))
		{
			hero->SetRight(true);

			hero->SetX(m_px - 64 + scroll->GetScroll());
			hero->SetVX(0.0f);
		}

		//スイッチの右部分に接触
		if ((m_px + 54 < hx) && (m_px+64 < hx+64))
		{
			hero->SetLeft(true);
			hero->SetX(m_px + 64 + scroll->GetScroll());
			hero->SetVX(0.0f);
		}

		//スイッチの上部分に接触
		if ((m_py +10 > hy + 128) && (m_py  > hy))
		{
			hero->SetDown(true);
			hero->SetY(m_py - 128 + scroll->GetScroll());
			hero->SetVY(0.0f);
		}

		//スイッチの下部分に接触
		if ((m_py + 54 < hy) && (m_py < hy+128))
		{
			hero->SetUp(true);
			hero->SetY(m_py+64 + scroll->GetScroll());
			hero->SetVY(0.0f);
		}
	}
	*/
	
	//スイッチが押されたらフラグ切り替え、スイッチを消滅
	//HitBoxの内容を更新
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_px, m_py);

	if (hit->CheckObjNameHit(OBJ_ATTACK) != nullptr)
	{
		S_flag = true;				//スイッチのフラグをtrueに
		this->SetStatus(false);		//スイッチが押されたら消滅
		Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
	}

}

//ドロー
void CObjSwitch::Draw()
{
	int switch_graphic;		//影と光でスイッチの描画を変えるための数字、ここだけでしか使わないため、ここで宣言している
	
    //スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

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
	src.m_top = 0.0f;
	src.m_left = 0.0f + (switch_graphic * 64.0f);
	src.m_right = 64.0f +(switch_graphic * 64.0f);
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(10, &src, &dst, c, 0.0f);
}

