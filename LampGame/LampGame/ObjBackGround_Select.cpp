//使用するヘッダーファイル
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjBackGround_Select.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBackGround_Select::Init()
{

}

//アクション
void CObjBackGround_Select::Action()
{
	
}

//ドロー
void CObjBackGround_Select::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,0.5f };	//セレクト画面のBG
	
	RECT_F src;		//ステージセレクト背景描画元切り取り位置
	RECT_F dst;		//ステージセレクト背景描画先表示位置

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 896.0f;
	src.m_bottom = src.m_top + 640.0f;

	dst.m_top = 0;
	dst.m_left = 0;
	dst.m_right = dst.m_left + 800;
	dst.m_bottom = dst.m_top + 600.0f;
	Draw::Draw(10, &src, &dst, c, 0.0f);
}