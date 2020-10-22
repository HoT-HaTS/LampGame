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


	//方針 HitBoxに当たった場合、上下左右判定を行う

	//主人公から光フラグを取ってくる
	bool L_flag_switch = hero->Get_L_flag();
	
	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);

	//主人公とスイッチのあたり判定チェック
	//当たっている場合
	if ((hit->CheckObjNameHit(OBJ_HERO) != nullptr)&&(L_flag_switch==false))
	{
		//スイッチの左部分に接触

		if ((m_px+10 > hx + 64) && (m_px  > hx ))
		{
			hero->SetRight(true);

			hero->SetX(m_px - 64);
			hero->SetVX(0.0f);
		}

		//スイッチの右部分に接触
		if ((m_px + 54 < hx) && (m_px+64 < hx+64))
		{
			hero->SetLeft(true);
			hero->SetX(m_px + 64);
			hero->SetVX(0.0f);
		}

		//スイッチの上部分に接触
		if ((m_py +10 > hy + 128) && (m_py  > hy))
		{
			hero->SetDown(true);
			hero->SetY(m_py - 128);
			hero->SetVY(0.0f);
		}

		//スイッチの下部分に接触
		if ((m_py + 54 < hy) && (m_py < hy+128))
		{
			hero->SetUp(true);
			hero->SetY(m_py+64);
			hero->SetVY(0.0f);
		}
	}
	
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
	dst.m_left = 0.0f + m_px;
	dst.m_right = 64.0f + m_px;
	dst.m_bottom = 64.0f + m_py;

	//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(10, &src, &dst, c, 0.0f);
}

