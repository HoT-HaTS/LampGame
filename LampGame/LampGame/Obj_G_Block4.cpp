//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block4.h"

//使用するネームスペース
using namespace GameL;

CObj_G_Block4::CObj_G_Block4(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObj_G_Block4::Init()
{
	G4_flag = false;			//false→ある。true→消滅。
	a_flag = false;				//true→HitBox作成可能。false→作成不可。

	m_time = 270;					//時間管理

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//アクション
void CObj_G_Block4::Action()
{
	m_time++;

	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の位置の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	if (0 < m_time && m_time < 270)
	{
		Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
		G4_flag = false;
		a_flag = true;
	}
	else if (m_time >= 270)
	{
		G4_flag = true;

		if (G4_flag == true && a_flag == true)
		{
			Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
			a_flag = false;
		}
		//主人公の衝突確認用のフラグの初期化
		hero->SetUp(false);
		hero->SetDown(false);
		hero->SetLeft(false);
		hero->SetRight(false);

		hero->SetDown2(false);

		//HitBoxの内容を更新
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + scroll->GetScroll(), m_py);

		//主人公とG_Blockのあたり判定チェック
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			//当たっている場合
			float hx = hero->GetX();
			float hy = hero->GetY();

			//G_Blockの上or下じゃない条件
			if (hy + 120 > m_py) //|| m_py + 50 < hy)
			{
				//G_Blockの左部分に接触
				if (m_px + scroll->GetScroll() > hx)
				{
					hero->SetRight(true);
					hero->SetX(m_px - 64.5 + scroll->GetScroll());
					hero->SetVX(-0.8);
				}
				//G_Blockの右部分に接触
				if (hx > m_px + scroll->GetScroll())
				{
					hero->SetLeft(true);
					hero->SetX(m_px + 63.5 + scroll->GetScroll());
					hero->SetVX(0.0);
				}
			}
			//G_Blockの上部分に接触
			if (hy + 125 < m_py)
			{
				hero->SetDown2(true);
				hero->SetY(m_py - 128.5);
				hero->SetVY(0.0);
			}
			//G_Blockの下部分に接触
			if (m_py + 55 < hy)
			{
				hero->SetUp(true);
				hero->SetY(m_py + 64.5);
				hero->SetVY(0.0);
			}
		}

		if (m_time == 540)
		{
			m_time = 0;
		}
	}
}

//ドロー
void CObj_G_Block4::Draw()
{
	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の位置の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	if (G4_flag == true)
	{
		if (m_time < 480)
		{
			//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
			Draw::Draw(3, &src, &dst, c, 0.0f);
		}
		else if (m_time >= 480)
		{
			if (m_time % 12 == 9 || m_time % 12 == 10 || m_time % 12 == 11 || m_time % 12 == 0)
			{
				//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
				Draw::Draw(25, &src, &dst, c, 0.0f);
			}
		}
		//else if (m_time >= 420)
		//{
		//	if (m_time % 60 < 30 && 0 < m_time % 60)
		//	{
		//		//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
		//		Draw::Draw(3, &src, &dst, c, 0.0f);
		//	}
		//}
	}
}