#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[10][100]);	//マップサイズは仮値
	~CObjBlock() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
};
