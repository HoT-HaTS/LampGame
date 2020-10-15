#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObj_G_Block : public CObj
{
public:
	CObj_G_Block() {};
	~CObj_G_Block() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
};

