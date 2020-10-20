#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define SBLOCK_INT_X_SIZE (64.0f) //スイッチの横サイズ
#define SBLOCK_INT_Y_SIZE (64.0f) //スイッチの横サイズ
//主人公の縦サイズ

//オブジェクト：
class CObjSwitch : public CObj
{
public:
	CObjSwitch() {};
	~CObjSwitch() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	
	bool Get_S_flag() { return S_flag; };	//スイッチのオンorオフ
private:
	float m_px; 		//位置
	float m_py;

	bool  S_flag;		//スイッチのフラグ管理用関数
};

