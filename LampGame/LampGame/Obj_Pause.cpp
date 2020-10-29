//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Pause.h"

//使用するネームスペース
using namespace GameL;



//イニシャライズ
void CObjPause::Init()
{
	//P_flag = true;
	mx = 0;
	my = 0;
}

//アクション
void CObjPause::Action()
{
	//flagがfalseのとき自身を消滅させる
	if (pause_flag == false)
	{
		this->SetStatus(false);		//スイッチが押されたら消滅
		//Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
		return;
	}
}

//ドロー
void CObjPause::Draw()
{
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 540.0f;
	src.m_bottom = 370.0f;

	//表示位置の設定
	dst.m_top = 100.0f;
	dst.m_left = 150.0f;
	dst.m_right = dst.m_left + 500.0f;
	dst.m_bottom = dst.m_top + 400.0f;

	//10番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(13, &src, &dst, c, 0.0f);
}