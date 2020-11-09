#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define TITLE_SIZE (32.0f)
#define TITLE1_X (224.0f) 
#define TITLE1_Y (250.f)
#define TITLE2_X (200.0f)
#define TITLE2_Y (400.0f)

//オブジェクト：タイトル
class CObjTitle :public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	bool m_key_flag;
};