#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define SBLOCK_INT_X_SIZE (64.0f) //スイッチの横サイズ
#define SBLOCK_INT_Y_SIZE (64.0f) //スイッチの縦サイズ
//主人公の縦サイズ

//オブジェクト：
class CObjSwitch2 : public CObj
{
public:
	CObjSwitch2(float x, float y);
	~CObjSwitch2() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

	bool Get_S2_flag() { return S2_flag; };	//スイッチのオンorオフ
private:
	float m_px; 		//位置
	float m_py;

	float m_scroll;		//スクロール用の変数

	bool  S2_flag;		//スイッチのフラグ管理用関数
	bool  a_flag;       //攻撃の当たる回数調整用
};