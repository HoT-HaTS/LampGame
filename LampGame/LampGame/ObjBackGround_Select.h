#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define SELECT_BG_X_SIZE (896.0f)
#define SELECT_BG_Y_SIZE (640.0f)

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