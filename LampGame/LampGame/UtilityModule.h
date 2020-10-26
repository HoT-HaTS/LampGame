#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//プロトタイプ宣言
bool UnitVec(float* vx, float* vy);	//ベクトルの正規化を行う関数

bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);	//領域内外かどうか調べる関数

//ブロックとの当たり判定
void BlockHit
(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* bt
);

void BlockDraw(float x, float y, RECT_F* dst, float c[]);

int Map[10][100];
float Scroll;