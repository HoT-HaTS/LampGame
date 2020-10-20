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



//イニシャライズ
void CObjSwitch::Init()
{
	m_px = 0.0f;			//位置
	m_py = 0.0f;

	S_flag = false;			//スイッチがオフのときはfalse、オンのときはtrue

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_SWITCH, OBJ_SWITCH, 1);
}

//アクション
void CObjSwitch::Action()
{
	//主人公の位置の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//主人公の衝突確認用のフラグの初期化
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//主人公とスイッチのあたり判定チェック
	if ((m_px + 64 > hx) && (hx + 64 > m_px) && (m_py + 64 > hy) && (hy + 64 > m_py))
	{
		//当たっている場合

		//ベクトルの作成
		float vx = hx - m_px;
		float vy = hx - m_py;

		//長さを求める
		float len = sqrt(vx * vx + vy * vy);
		
		//角度を求める
		float r = atan2(vy, vx);
		r = r * 180.0f / 3.14f;

		if (r <= 0.0f)
			r = abs(r);
		else
			r = 360.0f - abs(r);

		//lenがある一定の長さより短い場合に判定に入る
		if (len < 88.0f)
		{

			//求めた角度で上下左右を判定
			//スイッチが主人公の左部分に接触
			if ((r < 45 && r>0) || r > 315)
			{
				hero->SetLeft(true);
				hero->SetX(hx + 64);
				hero->SetVX(0.0f);
			}

			//スイッチが主人公の上部分に接触
			if (r > 225 || r < 315)
			{
				hero->SetUp(true);
				hero->SetY(hy);
				hero->SetVY(0.0f);
			}

			//スイッチが主人公の下部分に接触
			if (r > 45 || r < 135)
			{
				hero->SetDown(true);
				hero->SetY(hy + 64);
				hero->SetVY(0.0f);
			}

			//スイッチが主人公の右部分に接触
			if (r > 135 || r < 225)
			{
				hero->SetRight(true);
				hero->SetX(hx);
				hero->SetVX(0.0f);
			}
		}

	}

	//スイッチが押されたらフラグ切り替え、スイッチを消滅
	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);

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
	int switch_graphic;		//影と光でスイッチの描画を変えるための数字

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
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 64.0f;
	dst.m_bottom = 64.0f;

	//0番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(10, &src, &dst, c, 0.0f);
}