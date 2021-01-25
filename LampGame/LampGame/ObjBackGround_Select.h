#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define CUTOUT_X (896.0f)
#define CUTOUT_Y (640.0f)
#define DRAW_X (800.0f)
#define DRAW_Y (600.0f)

//オブジェクト：タイトル
class CObjBackGround_Select : public CObj
{
	public:
		CObjBackGround_Select() {};
		~CObjBackGround_Select() {};
		void Init();     //イニシャライズ
		void Action();   //アクション
		void Draw();     //ドロー
	private:
};