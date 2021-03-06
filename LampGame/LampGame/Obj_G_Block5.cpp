//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "Obj_G_Block5.h"

//使用するネームスペース
using namespace GameL;

CObj_G_Block5::CObj_G_Block5(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObj_G_Block5::Init()
{
	G5_flag = false;			//false→ある。true→消滅

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//アクション
void CObj_G_Block5::Action()
{
	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の位置の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//敵の位置の取得
	CObjEnemy* enemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);

	////主人公の衝突確認用のフラグの初期化
	//hero->SetUp(false);
	//hero->SetDown(false);
	//hero->SetLeft(false);
	//hero->SetRight(false);

	//enemy->SetUp(false);
	//enemy->SetDown(false);
	//enemy->SetLeft(false);
	//enemy->SetRight(false);

	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);



	////主人公とG5_BLOCKのあたり判定チェック
	////当たっている場合
	//if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	//{
	//	float hx = hero->GetX();
	//	float hy = hero->GetY();

	//	//G5_BLOCKの上じゃない条件
	//	if (hy + (2 * BLOCK_SIZE - 8) > m_py)
	//	{
	//		//G5_BLOCKの左部分に接触
	//		if (m_px + scroll->GetScroll() > hx)
	//		{
	//			hero->SetRight(true);
	//			hero->SetX(m_px - (BLOCK_SIZE + 0.5) + scroll->GetScroll());
	//			hero->SetVX(0.0f);
	//		}
	//		//G5_BLOCKの右部分に接触
	//		else if (hx > m_px + scroll->GetScroll())
	//		{
	//			hero->SetLeft(true);
	//			hero->SetX(m_px + (BLOCK_SIZE - 0.5) + scroll->GetScroll());
	//			hero->SetVX(0.0f);
	//		}
	//	}
	//	//G5_BLOCKの上部分に接触
	//	if (hy + (2 * BLOCK_SIZE - 1) <= m_py)
	//	{
	//		hero->SetDown(true);
	//		hero->SetY(m_py - (2 * BLOCK_SIZE + 0.5));
	//		hero->SetVY(0.0f);
	//	}
	//	//G5_BLOCKの下部分に接触
	//	else if (m_py + (BLOCK_SIZE + 1) <= hy)
	//	{
	//		hero->SetUp(true);
	//		hero->SetY(m_py + (BLOCK_SIZE - 0.5));
	//		hero->SetVY(0.0f);
	//	}
	//}

	////敵とG5_BLOCKのあたり判定チェック
	////当たっている場合
	//if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	//{
	//	float hx = enemy->GetX();
	//	float hy = enemy->GetY();

	//	//G5_BLOCKの上じゃない条件
	//	if (hy + (2 * BLOCK_SIZE - 8) > m_py)
	//	{
	//		//G5_BLOCKの左部分に接触
	//		if (m_px + scroll->GetScroll() > hx)
	//		{
	//			enemy->SetRight(true);
	//			enemy->SetX(m_px - (BLOCK_SIZE + 0.5) );
	//			enemy->SetVX(0.0f);
	//		}
	//		//G5_BLOCKの右部分に接触
	//		else if (hx > m_px + scroll->GetScroll())
	//		{
	//			enemy->SetLeft(true);
	//			enemy->SetX(m_px + (BLOCK_SIZE - 0.5));
	//			enemy->SetVX(0.0f);
	//		}
	//	}
	//	//G5_BLOCKの上部分に接触
	//	if (hy + (2 * BLOCK_SIZE - 1) <= m_py)
	//	{
	//		enemy->SetDown(true);
	//		enemy->SetY(m_py - (2 * BLOCK_SIZE + 0.5));
	//		enemy->SetVY(0.0f);
	//	}
	//	//G5_BLOCKの下部分に接触
	//	else if (m_py + (BLOCK_SIZE + 1) <= hy)
	//	{
	//		enemy->SetUp(true);
	//		enemy->SetY(m_py + (BLOCK_SIZE - 0.5));
	//		enemy->SetVY(0.0f);
	//	}
	//}

	coin_count = hero->GetCoin();

	if (coin_count >= 3)
	{
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			//ブロック削除効果音
			Audio::Start(8);

			this->SetStatus(false);		//コイン3舞取得状態で主人公が触れると削除
			Hits::DeleteHitBox(this);	//所有するHitBoxを削除
		}
	}

}

//ドロー
void CObj_G_Block5::Draw()
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
	Draw::Draw(31, &src, &dst, c, 0.0f);
}
