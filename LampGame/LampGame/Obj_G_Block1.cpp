//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block1.h"

//使用するネームスペース
using namespace GameL;

CObj_G_Block::CObj_G_Block(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObj_G_Block::Init()
{
	G_flag = false;			//false→ある。true→消滅

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//アクション
void CObj_G_Block::Action()
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


	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//主人公とG_Blockのあたり判定チェック
	//当たっている場合
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//スイッチの上じゃない条件
		if (hy + 120 > m_py)
		{
			//スイッチの左部分に接触
			if (m_px + scroll->GetScroll() > hx)
			{
				hero->SetRight(true);
				hero->SetX(m_px - 64 + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
			//スイッチの右部分に接触
			else if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + 64 + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
		}
		//スイッチの上部分に接触
		if (hy + 127 <= m_py)
		{
			hero->SetDown(true);
			hero->SetY(m_py - 128);
			hero->SetVY(0.0f);
		}
		//スイッチの下部分に接触
		else if (m_py + 65 <= hy)
		{
			hero->SetUp(true);
			hero->SetY(m_py + 64);
			hero->SetVY(0.0f);
		}
	}


	//スイッチが押されたらフラグ切り替え、ギミックブロックを消滅
	CObjSwitch* sflag = (CObjSwitch*)Objs::GetObj(OBJ_SWITCH);
	 G_flag = sflag->Get_S_flag();

	if (G_flag == true)
	{
		this->SetStatus(false);		//スイッチが押されたら消滅
		Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
	}

}

//ドロー
void CObj_G_Block::Draw()
{
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

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}