//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "Obj_G_Block1.h"

//使用するネームスペース
using namespace GameL;

CObj_G_Block::CObj_G_Block(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObj_G_Block::Init()
{

}

//アクション
void CObj_G_Block::Action()
{
		
}

//ドロー
void CObj_G_Block::Draw()
{
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 320.0f;

	//表示位置の設定
	dst.m_top = 0.0f; +m_px;
	dst.m_left = 0.0f; +m_py;
	dst.m_right = 32.0f; +m_px;
	dst.m_bottom = 320.0f; +m_py;

	//0番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}