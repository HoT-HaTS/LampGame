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

CObjBoard::CObjBoard(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}

//イニシャライズ
void CObjBoard::Init()
{

	Hits::SetHitBox(this, m_px, m_py, 64.0f, 64.0f, ELEMENT_BOARD, OBJ_BOARD, 1);

}

//アクション
void CObjBoard::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//主人公がHitBoxに当たるとflagをtrueにする
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		T_Sensor = true;				//センサーのフラグをtrueに
	}
	else
	{
		T_Sensor = false;
	}

	if (T_Sensor == true)
	{
		CObjTutorial* obj_tutorial = new CObjTutorial(m_px+64.0f, m_py - 194.0f); //弾丸オブジェクト作成
		Objs::InsertObj(obj_tutorial, OBJ_TUTORIAL, 100);
	}

}

//ドロー
void CObjBoard::Draw()
{
	int background_flag = 0;
	
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
}


