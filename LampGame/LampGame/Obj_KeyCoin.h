#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define KEYCOIN_SIZE (59.0f)
#define ADD_SIZE (5.0f)
#define KEYCOIN_FLAME (10)
#define KEYCOIN_MAX_TIME (40)

//オブジェクト：
class CObjKeyCoin : public CObj
{
public:
	CObjKeyCoin(float x, float y);
	~CObjKeyCoin() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	float m_scroll;     //左右スクロール用
	float m_px;
	float m_py;
	int m_ani_time;
	int m_ani_frame;

	//テスト：コイン枚数確認用
	int coin_count;
};
