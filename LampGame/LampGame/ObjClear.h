#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjClear : public CObj
{
public:
	CObjClear() {};
	~CObjClear() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

private:
	int scene_num;	//描画用の背景用番号
	float alpha_b;	//透明度

	bool white_out;
	bool white;
	bool w_end;

	int h_ani_frame;
	int h_ani_time;

	float alpha_w;

	bool m_key_flag;  //キーフラグ
};