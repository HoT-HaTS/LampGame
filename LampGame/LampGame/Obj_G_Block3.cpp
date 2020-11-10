//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block3.h"

//使用するネームスペース
using namespace GameL;

CObj_G_Block3::CObj_G_Block3(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObj_G_Block3::Init()
{
	//false→影。true→光
	L_flag = true;

	//HitBox作成
	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_G_BLOCK3, 1);
}

//アクション
void CObj_G_Block3::Action()
{
	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の情報の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公の衝突確認用のフラグの初期化
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//光or影の情報を持ってくる
	L_flag = hero->Get_L_flag();

	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//主人公とG_Blockのあたり判定チェック
	//当たっている場合
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//主人公の位置取得
		float hx = hero->GetX();
		float hy = hero->GetY();

		hero->SetDown2(false);

		//G_Blockの上or下じゃない条件
		if (hy + 120 > m_py ) //|| m_py + 50 < hy)
		{
			//G_Blockの左部分に接触
			if (m_px + scroll->GetScroll() > hx)
			{
				hero->SetRight(true);
				hero->SetX(m_px - 64.5 + scroll->GetScroll());
				hero->SetVX(-0.8);
				hero->SetVY(0.0);
			}
			//G_Blockの右部分に接触
			if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + 63.5 + scroll->GetScroll());
				hero->SetVX(0.0);
				hero->SetVY(0.0);
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
}

//ドロー
void CObj_G_Block3::Draw()
{
	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の情報の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	L_flag = hero->Get_L_flag();

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

	if (L_flag == false)
	{	
		//4番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
}