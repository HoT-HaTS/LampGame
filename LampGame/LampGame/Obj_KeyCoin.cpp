//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_KeyCoin.h"
#include "Obj_Stage1.h"

//使用するネームスペース
using namespace GameL;

CObjKeycoin::CObjKeycoin(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}

//イニシャライズ
void CObjKeycoin::Init()
{
	Hits::SetHitBox(this, m_px, m_py, 64.0f, 64.0f, ELEMENT_COIN, OBJ_COIN, 1);
	m_ani_time = 0;
	m_ani_frame = 0;

	coin_count = 0;
}

//アクション
void CObjKeycoin::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	m_ani_time++;

	if (m_ani_time % 10 == 0)
	{
		m_ani_frame++;
	}
	if (m_ani_time == 40)
	{
		m_ani_time, m_ani_frame = 0;
	}


	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//主人公の位置の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	coin_count = hero->GetCoin();

	//主人公と接触したら消滅する。
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		coin_count++;
		hero->SetCoin(coin_count);
	}

}

//ドロー
void CObjKeycoin::Draw()
{
	int background_flag = 0;

	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置



	src.m_top = 0.0f;
	src.m_left = 0.0f + (64.0 * m_ani_frame);
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	dst.m_top = m_py + 0.0f;
	dst.m_left = m_px + scroll->GetScroll() + 0.0f;
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	Draw::Draw(30, &src, &dst, c, 0.0f);
}