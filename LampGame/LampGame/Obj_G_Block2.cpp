//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block2.h"

//使用するネームスペース
using namespace GameL;

CObj_G_Block2::CObj_G_Block2(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObj_G_Block2::Init()
{
	G2_flag = false;			//false→ある。true→消滅。
	a_flag = false;				//true→HitBox作成可能。false→作成不可。

	l_f = true;

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//アクション
void CObj_G_Block2::Action()
{
	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の位置の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	G2_flag = switch_flag;

	if (G2_flag == false)
	{
		Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
		a_flag = true;
	}
	else if (G2_flag == true)
	{
		if (a_flag == true)
		{
			Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
			a_flag = false;
		}
		//主人公の衝突確認用のフラグの初期化
		hero->SetUp(false);
		hero->SetDown(false);
		hero->SetLeft(false);
		hero->SetRight(false);

		//HitBoxの内容を更新
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + scroll->GetScroll(), m_py);
	}
}

//ドロー
void CObj_G_Block2::Draw()
{
	//主人公から光フラグを取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool l_f = hero->Get_L_flag();

	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0;
	src.m_bottom = 64.0f;

	if (switch_flag == true)
	{
		if (l_f == true)
		{
			//表示位置の設定
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px + scroll->GetScroll();
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;

			//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
			Draw::Draw(3, &src, &dst, c, 0.0f);
		}
		else if (l_f == false)
		{
			//表示位置の設定
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px + scroll->GetScroll();
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;

			//4番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
			Draw::Draw(4, &src, &dst, c, 0.0f);
		}
	}
}