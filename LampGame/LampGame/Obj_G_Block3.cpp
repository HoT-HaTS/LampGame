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

	m_px = 0;
	m_py = 0;
	m_scroll = 0;

	//HitBox作成
	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_G_BLOCK3, 1);
}

//アクション
void CObj_G_Block3::Action()
{
	//スクロールの値を取得
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	m_scroll = scroll->GetScroll();


	//主人公の情報の取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公の衝突確認用のフラグの初期化
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//光or影の情報を持ってくる
	L_flag = hero->Get_L_flag();

	////HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	////主人公とG_Blockのあたり判定チェック
	////当たっている場合
	//if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	//{
	//	//主人公の位置取得
	//	float hx = hero->GetX();
	//	float hy = hero->GetY();

	//	hero->SetDown2(false);

	//	//G_Blockの上or下じゃない条件
	//	if (hy + 120 > m_py ) //|| m_py + 50 < hy)
	//	{
	//		//G_Blockの左部分に接触
	//		if (m_px + scroll->GetScroll() > hx)
	//		{
	//			hero->SetRight(true);
	//			hero->SetX(m_px - 64.5 + scroll->GetScroll());
	//			hero->SetVX(-0.8);
	//			hero->SetVY(0.0);
	//		}
	//		//G_Blockの右部分に接触
	//		if (hx > m_px + scroll->GetScroll())
	//		{
	//			hero->SetLeft(true);
	//			hero->SetX(m_px + 63.5 + scroll->GetScroll());
	//			hero->SetVX(0.0);
	//			hero->SetVY(0.0);
	//		}
	//	}
	//		//G_Blockの上部分に接触
	//		if (hy + 125 < m_py)
	//		{
	//			hero->SetDown2(true);
	//			hero->SetY(m_py - 128.5);
	//			hero->SetVY(0.0);
	//		}
	//		//G_Blockの下部分に接触
	//		if (m_py + 55 < hy)
	//		{
	//			hero->SetUp(true);
	//			hero->SetY(m_py + 64.5);
	//			hero->SetVY(0.0);
	//		}
	//}


	//float h_px = hero->GetX();
	//float h_py = hero->GetY();
	//bool h_hit_up = hero->GetUp();
	//bool h_hit_down = hero->GetDown();
	//bool h_hit_right = hero->GetRight();
	//bool h_hit_left = hero->GetLeft();
	//float h_vx = hero->GetVX();
	//float h_vy = hero->GetVY();

	////G3ブロックとの当たり判定実行(テスト)
	//CObj_G_Block3* pb3 = (CObj_G_Block3*)Objs::GetObj(OBJ_G_BLOCK3);
	//pb3->BlockHit3(&h_px, &h_py, true,
	//	&h_hit_up, &h_hit_down, &h_hit_left, &h_hit_right, &h_vx, &h_vy
	//);
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
		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
}


////BlockHit関数(当たり判定)
////引数1	float* x			:判定を行うobject(主人公など)のX位置
////引数2 float* y			:判定を行うobject(主人公など)のY位置
////引数3 bool	scroll_on	:判定を行うobjectはスクロールの影響を与えるかどうか(true=与える false=与えない)
////引数4 bool* up			:上下判定の上部分にあたっているかどうかを返す
////引数5 bool* down			:上下判定の下部分にあたっているかどうかを返す
////引数6 bool* left			:上下判定の左部分にあたっているかどうかを返す
////引数7 bool* right			:上下判定の右部分にあたっているかどうかを返す
////引数8 float* px			:左右判定時、反対方向に座標を変更して位置を返す
////引数9 float* py			:上下判定時、反対方向に座標を変更して位置を返す
////引数10 int* btu			:下部分判定時、特殊なブロックのタイプを返す
////引数11 int* btr			:右部分判定時、特殊なブロックのタイプを返す
////判定を行うobjectとブロック64×64限定で、当たり判定と上下左右判定を行う
////その結果は引数4～10に返す
//void CObj_G_Block3::BlockHit3(
//	float* x, float* y, bool scroll_on,
//	bool* up, bool* down, bool* left, bool* right,
//	float* vx, float* vy)
//{
//	//衝突状態確認用フラグの初期化
//	*up = false;
//	*down = false;
//	*left = false;
//	*right = false;
//
//	//要素番号を座標に変更
//	float bx = 0 + m_px;
//	float by = 0 + m_py;
//
//	//スクロールの影響
//	float scroll = scroll_on ? m_scroll : 0;
//
//				//オブジェクトとブロックの当たり判定(ブロックの左:右:上:下の順)
//				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 128.0f > by) && (*y < by + 64.0f))
//				{
//					//上下左右判定
//
//					//主人公とブロックの中心でvector作成
//					float rvx = (*x + (-scroll) + 32.0f) - (bx + 32.0f);
//					float rvy = (*y + 64.0f) - (by + 32.0f);
//
//					//長さlenを求める
//					float len = sqrt(rvx * rvx + rvy * rvy);
//
//					//角度rを求める
//					float r = atan2(rvy, rvx);	//(ラジアン)
//					r = r * 180.0f / 3.14f;		//度
//
//					if (r <= 0.0f)
//						r = abs(r);
//					else
//						r = 360.0f - abs(r);
//
//					//lenがある一定の長さより短い場合に判定に入る。
//					if (len < 111.0f)
//					{
//						//角度で上下左右を判定
//						if ((r < 56 && r >= 0) || r > 304)
//						{
//							//右
//							*right = true;				//オブジェクトの左の部分が衝突している
//							*x = bx + 63.5f + (scroll);	//ブロックの位置+オブジェクトの幅
//							*vx = -(*vx) * 0.1f;			//-VX*反発係数
//						}
//						if (r > 56 && r < 124)
//						{
//							//上
//							*down = true;			//オブジェクトの下の部分が衝突している
//							*y = by - 128.0f;		//ブロックの位置+オブジェクトの幅
//							*vy = 0.0f;
//						}
//						if (r > 124 && r < 236)
//						{
//							//左
//							*left = true;				//オブジェクトの右の部分が衝突している
//							*x = bx - 64.5f + (scroll);	//ブロックの位置+オブジェクトの幅
//							*vx = -(*vx) * 0.1f;			//-VX*反発係数
//						}
//						if (236 < r && r < 304)
//						{
//							//下
//							*up = true;			//オブジェクトの上の部分が衝突している
//							*y = by + 63.5f;	//ブロックの位置+オブジェクトの幅
//							if (*vy < 0)
//							{
//								*vy = 0.0f;
//							}
//						}
//					}
//				}
//			}
