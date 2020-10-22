//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "Obj_G_Block1.h"

//使用するネームスペース
using namespace GameL;

CObj_G_Block::CObj_G_Block(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObj_G_Block::Init()
{

}

//アクション
void CObj_G_Block::Action()
{
		
}

//ドロー
void CObj_G_Block::Draw()
{
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 320.0f;

	//表示位置の設定
	dst.m_top = 0.0f; +m_px;
	dst.m_left = 0.0f; +m_py;
	dst.m_right = 32.0f; +m_px;
	dst.m_bottom = 320.0f; +m_py;

	//0番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
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
//判定を行うobjectとブロック64×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
//void CObj_G_Block::BlockHit(
//	float* x, float* y, bool scroll_on,
//	bool* up, bool* down, bool* left, bool* right,
//	float* vx, float* vy, int* bt
//)
//{
//	//衝突状態確認用フラグの初期化
//	*up = false;
//	*down = false;
//	*left = false;
//	*right = false;
//
//	//踏んでいるblockの種類の初期化
//	*bt = 0;
//
//	//m_mapの全要素にアクセス
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 100; j++)
//		{
//			if (m_map[i][j] > 0 && m_map[i][j] != 4)
//			{
//				//要素番号を座標に変更
//				float bx = j * 64.0f;
//				float by = i * 64.0f;
//
//				//スクロールの影響
//				float scroll = scroll_on ? m_scroll : 0;
//
//				//オブジェクトとブロックの当たり判定
//				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
//				{
//					//上下左右判定
//
//					//vectorの作成
//					float rvx = (*x + (-scroll)) - bx;
//					float rvy = *y - by;
//
//					//長さを求める
//					float len = sqrt(rvx * rvx + rvy * rvy);
//
//					//角度を求める
//					float r = atan2(rvy, rvx);
//					r = r * 180.0f / 3.14f;
//
//					if (r <= 0.0f)
//						r = abs(r);
//					else
//						r = 360.0f - abs(r);
//
//					//lenがある一定の長さのより短い場合に判定に入る。
//					if (len < 88.0f)
//					{
//						//角度で上下左右を判定
//						if ((r < 45 && r>0) || r > 315)
//						{
//							//右
//							*right = true;	//オブジェクトの左の部分が衝突している
//							*x = bx + 64.0f + (scroll);	//ブロックの位置+オブジェクトの幅
//							*vx = -(*vx) * 0.1f;	//-VX*反発係数
//						}
//						if (r > 45 && r < 135)
//						{
//							//上
//							*down = true;	//オブジェクトの下の部分が衝突している
//							*y = by - 64.0f;	//ブロックの位置+オブジェクトの幅
//							//種類を渡すのスタートとゴールのみ変更する
//							if (m_map[i][j] >= 2)
//								*bt = m_map[i][j];	//ブロックの要素(type)をオブジェクトに渡す
//							*vy = 0.0f;
//						}
//						if (r > 135 && r < 225)
//						{
//							//左
//							*left = true;	//オブジェクトの右の部分が衝突している
//							*x = bx - 64.0f + (scroll);	//ブロックの位置+オブジェクトの幅
//							*vx = -(*vx) * 0.1f;	//-VX*反発係数
//						}
//						if (225 < r && r < 315)
//						{
//							//下
//							*up = true;	//オブジェクトの上の部分が衝突している
//							*y = by + 64.0f;	//ブロックの位置+オブジェクトの幅
//							if (*vy < 0)
//							{
//								*vy = 0.0f;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}