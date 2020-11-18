#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define BOARD_SIXE_X (192.0)
#define BOARD_SIXE_Y (128.0)

#define BOARDCUT_SIZE (288.0)

#define BOARDDRAW_SIZE_T (270.0)
#define BOARDDRAW_SIZE_R (192.0)
#define BOARDDRAW_SIZE_B (180.0)


//オブジェクト：
class CObjBoard : public CObj
{
public:
	CObjBoard(float x, float y, int i);
	~CObjBoard() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	bool Get_Tuto_Sensor() { return T_Sensor; };//チュートリアル表示センサー

	int GetNum() { return b_num; };

private:
	float m_scroll;     //左右スクロール用
	float m_px;
	float m_py;
	int count;	//看板の数
	bool T_Sensor;
	bool m_flag;

	bool CheckWindow(float pos_x, float pos_y,
		float window_x, float window_y, float window_w, float window_h);

	//看板番号
	int b_num;
};
