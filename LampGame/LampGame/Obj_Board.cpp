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

	Hits::SetHitBox(this, m_px, m_py, BOARD_SIXE_X, BOARD_SIXE_Y, ELEMENT_BOARD, OBJ_BOARD, 1);

}

//アクション
void CObjBoard::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll() - BLOCK_SIZE, m_py - BLOCK_SIZE);

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
	bool check = CheckWindow(m_px, m_py, -(BLOCK_SIZE/2), -(BLOCK_SIZE / 2), STAGE_X_OUT, STAGE_Y_OUT);
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
		src.m_right = src.m_left + BLOCK_SIZE;
		src.m_bottom = src.m_top + BLOCK_SIZE;

		dst.m_top = m_py + 0.0f;
		dst.m_left = m_px + scroll->GetScroll() +0.0f;
		dst.m_right = dst.m_left + BLOCK_SIZE;
		dst.m_bottom = dst.m_top + BLOCK_SIZE;

		Draw::Draw(23, &src, &dst, c, 0.0f);


		//↓看板説明描画

		RECT_F src2;	//描画元切り取り位置
		RECT_F dst2;	//描画先表示位置

		src2.m_top = 0.0f;
		src2.m_left = 0.0f + BOARDCUT_SIZE * b_num;
		src2.m_right = src2.m_left + BOARDCUT_SIZE;
		src2.m_bottom = src2.m_top + BOARDCUT_SIZE;

		dst2.m_top = BOARDDRAW_SIZE_T;
		dst2.m_left = m_px + scroll->GetScroll() - (BLOCK_SIZE + 1);
		dst2.m_right = dst2.m_left + BOARDDRAW_SIZE_R;
		dst2.m_bottom = dst2.m_top + BOARDDRAW_SIZE_B;
		if (T_Sensor == true)
		{
			Draw::Draw(50, &src2, &dst2, c, 0.0f);
		}

		//ガイドの表示（別のソースコードで作る）
		//RECT_F src_guide;	//描画元切り取り位置
		//RECT_F dst_guide;	//描画先表示位置

		//src_guide.m_top = 0.0f;
		//src_guide.m_left = 0.0f;
		//src_guide.m_right = src_guide.m_left + 600.0f;
		//src_guide.m_bottom = src_guide.m_top + 32.0f;

		//dst_guide.m_top = 0.0f;
		//dst_guide.m_left = 200.0f;
		//dst_guide.m_right = dst_guide.m_left + 600.0f;
		//dst_guide.m_bottom = dst_guide.m_top + 32.0f;

		//Draw::Draw(0, &src_guide, &dst_guide, c, 0.0f);
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

