//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameHead.h"
#include "Obj_Attack.h"

//使用するネームスペース
using namespace GameL;

CObjAttack::CObjAttack(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjAttack::Init()
{
	//Hits::SetHitBox(this, m_x, m_y, 32, 32, ELEMENT_PLAYER, OBJ_ATTACK);
}

//アクション
void CObjAttack::Action()
{
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);


	//Todo:アニメーション終了後にオブジェクトを破棄する
}

//ドロー
void CObjAttack::Draw()
{
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

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
	Draw::Draw(0, &src, &dst, c, 0.0f);
}