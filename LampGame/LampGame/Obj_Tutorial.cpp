//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "Obj_Tutorial.h"
#include "GameHead.h"
#include "Obj_Stage1.h"

//使用するネームスペース
using namespace GameL;

CObjTutorial::CObjTutorial(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}

//イニシャライズ
void CObjTutorial::Init()
{
	T_Sensor = false;
}

//アクション
void CObjTutorial::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	CObjBoard* TSensor = (CObjBoard*)Objs::GetObj(OBJ_BOARD);
	T_Sensor = TSensor->Get_Tuto_Sensor();

	if (T_Sensor == false)
	{
		this->SetStatus(false);		//スイッチが押されたら消滅
		Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
	}
	
}

//ドロー
void CObjTutorial::Draw()
{
	int background_flag = 0;
	
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + 288.0f;
		src.m_bottom = src.m_top + 288.0f;

		dst.m_top = m_py-144.0f;
		dst.m_left = m_px + scroll->GetScroll()-144.0f;
		dst.m_right = dst.m_left + 208.0f;
		dst.m_bottom = dst.m_top + 208.0f;

		Draw::Draw(50, &src, &dst, c, 0.0f);
}


