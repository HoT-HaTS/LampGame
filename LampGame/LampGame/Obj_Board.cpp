//グラフィック追加と表示させるところから


//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Board.h"
#include "Obj_Stage1.h"

//使用するネームスペース
using namespace GameL;

CObjBoard::CObjBoard(float x, float y, int i)
{
	m_px = x;			//位置
	m_py = y;
	b_num = i;
}

//イニシャライズ
void CObjBoard::Init()
{
	count = 0;
	m_flag = true;
	T_Sensor = false;

	Hits::SetHitBox(this, m_px, m_py, 192.0f, 128.0f, ELEMENT_BOARD, OBJ_BOARD, 1);

}

//アクション
void CObjBoard::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px+scroll->GetScroll()-64 , m_py-64);

	//主人公がHitBoxに当たるとflagをtrueにする
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		T_Sensor = true;	//センサーのフラグをtrueに
		m_flag = false;
		if (m_flag == false)
		{
			count++;
			m_flag = true;
		}
	}
	else
		T_Sensor = false;
	//看板が左側の画面外に出たら削除
	bool check = CheckWindow(m_px, m_py, -32.0f, -32.0f, 800.0f, 600.0f);
	if (check == false)
	{
		this->SetStatus(false);	//自身に削除命令を出す
		Hits::DeleteHitBox(this);//看板が所有するHitBoxを削除する
		T_Sensor = false;
	}
}

//ドロー
void CObjBoard::Draw()
{
	
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + 64.0f;
		src.m_bottom = src.m_top + 64.0f;

		dst.m_top = m_py + 0.0f;
		dst.m_left = m_px + scroll->GetScroll() +0.0f;
		dst.m_right = dst.m_left + 64.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		Draw::Draw(23, &src, &dst, c, 0.0f);


		//↓看板説明描画

		RECT_F src2;	//描画元切り取り位置
		RECT_F dst2;	//描画先表示位置

		src2.m_top = 0.0f;
		src2.m_left = 0.0f + 288 * b_num;
		src2.m_right = src2.m_left + 288.0f;
		src2.m_bottom = src2.m_top + 288.0f;

		dst2.m_top = 270;
		dst2.m_left = m_px + scroll->GetScroll() - 65.0f;
		dst2.m_right = dst2.m_left + 192.0f;
		dst2.m_bottom = dst2.m_top + 180.0f;
		if (T_Sensor == true)
		{
			Draw::Draw(50, &src2, &dst2, c, 0.0f);
		}


}


//---CheckWindow関数
//引数1	float pos_x		:領域外かどうか調べるx位置
//引数2	float pos_y		:領域外かどうか調べるy位置
//引数3	float window_x	:領域のtop位置
//引数4	float window_y	:領域のleft位置
//引数5	float window_w	:領域のright位置
//引数6	float window_h	:領域のbottom位置
//戻り値 bool		:true=領域内 false=領域外
//内容
//領域内かどうか調べる位置pos_(x,y)がwindow_(xywh)の内か外かを調べる。

bool CObjBoard::CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h)
{
	//領域チェック
	if (pos_x < window_x)
	{
		return false;	//領域外
	}
	//if (pos_x > window_w)
	//{
	//	return false;	//領域外
	//}
	if (pos_y < window_y)
	{
		return false;	//領域外
	}
	if (pos_y > window_h)
	{
		return false;	//領域外
	}

	return true;		//領域内
}

