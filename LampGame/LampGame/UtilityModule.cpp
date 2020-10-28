//使用するヘッダーファイル
#include <math.h>
#include "GameL/DrawTexture.h"
#include "UtilityModule.h"

#include "GameHead.h"
#include "Obj_Block.h"

//使用するネームスペース
using namespace GameL;

//---UnitVec関数
//引数1　float*vx	:ベクトルのx成分のポインタ
//引数2　float*vy	:ベクトルのy成分のポインタ
//戻り値 bool		:true=計算成功	false=計算失敗
//内容
//引数のベクトルを正規化しその値をvx,vyに変更します。
bool UnitVec(float* vx, float* vy)
{
	//ベクトルの長さを求める（三平方の定理）
	float r = 0.0f;
	r = (*vx) * (*vx) + (*vy) * (*vy);
	r = sqrt(r);

	//長さが0かどうか調べる
	if (r == 0.0f)
	{
		//0なら計算失敗
		return false;
	}
	else
	{
		//正規化を行いvxとvyの参照先の値を変更
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);
	}

	//計算成功
	return true;
}


//---CheckWindow関数
//引数1	float pos_x		:領域外かどうか調べるx位置
//引数2	float pos_y		:領域外かどうか調べるy位置
//引数3	float window_x	:領域のtop位置
//引数4	float window_y	:領域のleft位置
//引数5	float window_w	:領域のright位置
//引数6	float window_h	:領域のbottom位置
//戻り値 bool		:true=領域内 false=領域外
//内容
//領域内かどうか調べる位置pos_(x,y)がwindow_(xywh)の内か外かを調べる。
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h)
{
	//領域チェック
	if (pos_x < window_x)
	{
		return false;	//領域外
	}
	if (pos_x > window_w)
	{
		return false;	//領域外
	}
	if (pos_y < window_y)
	{
		return false;	//領域外
	}
	if (pos_y > window_h)
	{
		return false;	//領域外
	}

	return true;		//領域内
}

//BlockDrawMethod関数
//引数1 float		x		:リソース切り取り位置x
//引数2 float		y		:リソース切り取り位置y
//引数3 RECT_F* dst			:描画位置
//引数4 float		c[]		:カラー情報
//ブロックを64×64限定描画用。リソース切り取り位置のみx,yで設定できる。
void BlockDraw(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//描画
	Draw::Draw(0, &src, dst, c, 0.0f);
}

////BlockHit関数(当たり判定)
////引数1	float* x			:判定を行うobjectのX位置
////引数2 float* y			:判定を行うobjectのY位置
////引数3 bool	scroll_on	:判定を行うobjectはスクロールの影響を与えるかどうか(true=与える false=与えない)
////引数4 bool* up			:上下判定の上部分にあたっているかどうかを返す
////引数5 bool* down			:上下判定の下部分にあたっているかどうかを返す
////引数6 bool* left			:上下判定の左部分にあたっているかどうかを返す
////引数7 bool* right			:上下判定の右部分にあたっているかどうかを返す
////引数8 float* vx			:左右判定時の反発による移動方向・力の値を変えて返す
////引数9 float* vy			:上下判定時による自由落下運動の移動方向・力の値を変えて返す
////引数10 int* bt			:下部分判定時、特殊なブロックのタイプを返す
////引数11 int map[10][100]	:マップデータ
////判定を行うobjectとブロック64×64限定で、当たり判定と上下左右判定を行う
////その結果は引数4～10に返す
//void BlockHit(
//	float* x, float* y, bool scroll_on,
//	bool* up, bool* down, bool* left, bool* right,
//	float* vx, float* vy, int* bt
//)

