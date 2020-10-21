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

//BlockHit関数(当たり判定)
//引数1	float* x			:判定を行うobjectのX位置
//引数2 float* y			:判定を行うobjectのY位置
//引数3 bool	scroll_on	:判定を行うobjectはスクロールの影響を与えるかどうか(true=与える false=与えない)
//引数4 bool* up			:上下判定の上部分にあたっているかどうかを返す
//引数5 bool* down			:上下判定の下部分にあたっているかどうかを返す
//引数6 bool* left			:上下判定の左部分にあたっているかどうかを返す
//引数7 bool* right			:上下判定の右部分にあたっているかどうかを返す
//引数8 float* vx			:左右判定時の反発による移動方向・力の値を変えて返す
//引数9 float* vy			:上下判定時による自由落下運動の移動方向・力の値を変えて返す
//引数10 int* bt			:下部分判定時、特殊なブロックのタイプを返す
//引数11 int map[10][100]	:マップデータ
//判定を行うobjectとブロック64×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
void BlockHit(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* bt
)
{
	int map[10][100];
	int Map[10][100];

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	int Scroll = block->GetScroll();
	Map[10][100] = block->GetMap();

	//マップデータをコピー
	//memcpy(&Map, map, sizeof(int) * (10 * 100));

	//衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	int x1 = *x + 32.0f;
	int y1 = *y + 64.0f;

	//踏んでいるblockの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (Map[i][j] > 0 && Map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f + 32.0f;
				float by = i * 64.0f + 32.0f;

				//スクロールの影響
				float scroll = scroll_on ? Scroll : 0;

				//オブジェクトとブロックの当たり判定
				if (( *x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 128.0f > by) && (*y < by + 128.0f))
				{
					//上下左右判定

					//vectorの作成(座標)
					float rvx = (x1 + (-scroll)) - bx;
					float rvy = y1 - by;

					//長さを求める
					float len = sqrt(rvx * rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//lenがある一定の長さのより短い場合に判定に入る。
					if (len < 88.0f)
					{
						//角度で上下左右を判定
						if ((r < 45 && r>0) || r > 315)
						{
							//右
							*right = true;	//オブジェクトの左の部分が衝突している
							*x = bx + 64.0f + (scroll);	//ブロックの位置+オブジェクトの幅
							*vx = -(*vx) * 0.1f;	//-VX*反発係数
						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;	//オブジェクトの下の部分が衝突している
							*y = by - 64.0f;	//ブロックの位置+オブジェクトの幅
							//種類を渡すのスタートとゴールのみ変更する
							if (Map[i][j] >= 2)
								*bt = Map[i][j];	//ブロックの要素(type)をオブジェクトに渡す
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;	//オブジェクトの右の部分が衝突している
							*x = bx - 64.0f + (scroll);	//ブロックの位置+オブジェクトの幅
							*vx = -(*vx) * 0.1f;	//-VX*反発係数
						}
						if (225 < r && r < 315)
						{
							//下
							*up = true;	//オブジェクトの上の部分が衝突している
							*y = by + 64.0f;	//ブロックの位置+オブジェクトの幅
							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}
