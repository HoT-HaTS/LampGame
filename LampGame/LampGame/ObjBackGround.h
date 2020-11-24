#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define BG_X (800.0)
#define BG_Y (600.0)

//オブジェクト：タイトル
class CObjBackGround :public CObj
{
public:
	CObjBackGround() {};
	~CObjBackGround() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:

};