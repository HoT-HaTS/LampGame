//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"

#include "GameHead.h"
#include "Obj_Block.h"
#include "Obj_Stage1.h"

//使用するネームスペース
using namespace GameL;

CObjBlock::CObjBlock(int map[10][100])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int) * (10 * 100));
}

//イニシャライズ
void CObjBlock::Init()
{
	m_scroll = 0.0f;


	coin_count = 0;
}

//アクション
void CObjBlock::Action()
{
	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	bool L_flag = hero->Get_L_flag();

	if (L_flag == true)
	{
		//後方スクロールライン
		if (hx < BSCROLL_LINE)
		{
			hero->SetX(BSCROLL_LINE);
			m_scroll -= hero->GetVX();
		}

		//前方スクロールライン
		if (hx > ASCROLL_LINE)
		{
			hero->SetX(ASCROLL_LINE);
			m_scroll -= hero->GetVX();
		}
	}
}

//ドロー
void CObjBlock::Draw()
{
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float  c2[4] = { 1.0f, 1.0f, 1.0f, 0.9f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	bool L_flag_background = hero->Get_L_flag();

	if (L_flag_background == true)
	{
		//背景表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = BLOCKCUT_SIZE_R;
		src.m_bottom = BLOCKCUT_SIZE_B;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = DRAW_SIZE_R;
		dst.m_bottom = DRAW_SIZE_B;

		Draw::Draw(((UserData*)Save::GetData())->stage_id + 14, &src, &dst, c, 0.0f);
	}
	else
	{
		//背景表示
		src.m_top = BLOCKCUT_SIZE_T;
		src.m_left = 0.0f;
		src.m_right = BLOCKCUT_SIZE_R;
		src.m_bottom = 2 * BLOCKCUT_SIZE_B;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = DRAW_SIZE_R;
		dst.m_bottom = DRAW_SIZE_B;

		Draw::Draw(((UserData*)Save::GetData())->stage_id + 14, &src, &dst, c, 0.0f);
	}
}


//BlockHit関数(当たり判定)
//引数1	float* x			:判定を行うobject(主人公など)のX位置
//引数2 float* y			:判定を行うobject(主人公など)のY位置
//引数3 bool	scroll_on	:判定を行うobjectはスクロールの影響を与えるかどうか(true=与える false=与えない)
//引数4 bool* up			:上下判定の上部分にあたっているかどうかを返す
//引数5 bool* down			:上下判定の下部分にあたっているかどうかを返す
//引数6 bool* left			:上下判定の左部分にあたっているかどうかを返す
//引数7 bool* right			:上下判定の右部分にあたっているかどうかを返す
//引数8 float* px			:左右判定時、反対方向に座標を変更して位置を返す
//引数9 float* py			:上下判定時、反対方向に座標を変更して位置を返す
//引数10 int* btu			:下部分判定時、特殊なブロックのタイプを返す
//引数11 int* btg			:ゴール判定時、ゴールブロックのタイプを返す
//判定を行うobjectとブロック64×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
void CObjBlock::BlockHit(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* btu, int* btg
)
{
	//衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*btu = 0;
	*btg = 0;

	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	coin_count = hero->GetCoin();

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//床ブロックとゴールブロック、透明ブロック
			if (m_map[i][j] == 1 || m_map[i][j] == 2|| m_map[i][j] == 4)
			{
				//要素番号を座標に変更
				float bx = j * BLOCK_SIZE;
				float by = i * BLOCK_SIZE;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//オブジェクトとブロックの当たり判定(ブロックの左:右:上:下の順)
				if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
				{
					//上下左右判定

					//主人公とブロックの中心でvector作成
					float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
					float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

					//長さlenを求める
					float len = sqrt(rvx * rvx + rvy * rvy);

					//角度rを求める
					float r = atan2(rvy, rvx);	//(ラジアン)
					r = r * 180 / PI;		//度

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360 - abs(r);

					//当たり判定用:主人公とブロックの角度(の端)を求める
					float a1 = (HBLOCK_INT_Y_SIZE / 2 - 5) + BLOCK_SIZE / 2;	//底辺	:主人公縦+ブロック縦長さ(半分)
					float b1 = (HBLOCK_INT_X_SIZE / 2 - 5) + BLOCK_SIZE / 2;  //高さ	:主人公横+ブロック横長さ(半分)
					float t1 = 90.0 - (atan2(b1, a1) * 180 / PI); //主人公の中心とブロックの中心の角度(単位:度)
					int t = (int)t1;

					float hit_length = sqrt(a1 * a1 + b1 * b1) - 1;

					//lenがある一定の長さより短い場合に判定に入る。
					if (len < hit_length)
					{
						//角度で上下左右を判定
						if ((r < t && r >= 0) || r > 360-t)
						{
							if (m_map[i][j] != 2)
							{
								//右
								*right = true;								//オブジェクトの左の部分が衝突している
								*x = bx + (BLOCK_SIZE - 0.5) + (scroll);	//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
							}
							*btg = m_map[i][j];
						}
						if (r > t && r < 180-t)
						{
							if (m_map[i][j] != 2)
							{
								//上
								*down = true;					//オブジェクトの下の部分が衝突している
								*y = by - (2 * BLOCK_SIZE);		//ブロックの位置+オブジェクトの幅
								*vy = 0.0f;
							}
							if (m_map[i][j] >= 2)
							{
								*btu = m_map[i][j];	//ブロックの要素(type)をオブジェクトに渡す
								*btg = m_map[i][j];
							}
						}
						if (r > 180-t && r < 180+t)
						{
							if (m_map[i][j] != 2)
							{
								//左
								*left = true;								//オブジェクトの右の部分が衝突している
								*x = bx - (BLOCK_SIZE + 0.5) + (scroll);	//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
							}
							*btg = m_map[i][j];
						}
						if (180+t < r && r < 360-t)
						{
							if (m_map[i][j] != 2)
							{
								//下
								*up = true;						//オブジェクトの上の部分が衝突している
								*y = by + (BLOCK_SIZE - 0.5);	//ブロックの位置+オブジェクトの幅
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
							}
							*btg = m_map[i][j];
						}
					}
				}
			}
			else if (m_map[i][j] == 5)
			{
				if (switch_flag == true)
				{
					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//スクロールの影響
					float scroll = scroll_on ? m_scroll : 0;

					//オブジェクトとブロックの当たり判定(ブロックの左:右:上:下の順)
					if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
					{
						//上下左右判定

						//主人公とブロックの中心でvector作成
						float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
						float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

						//長さlenを求める
						float len = sqrt(rvx * rvx + rvy * rvy);

						//角度rを求める
						float r = atan2(rvy, rvx);	//(ラジアン)
						r = r * 180.0f / 3.14f;		//度

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さより短い場合に判定に入る。
						if (len < HIT_LENGTH)
						{
							//角度で上下左右を判定
							if ((r < 58.5 && r >= 0) || r > 301.5)
							{
								//右
								*right = true;								//オブジェクトの左の部分が衝突している
								*x = bx + (BLOCK_SIZE - 0.5) + (scroll);	//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
								*btg = m_map[i][j];
							}
							if (r > 58.5 && r < 121.5)
							{
								//上
								*down = true;					//オブジェクトの下の部分が衝突している
								*y = by - (2 * BLOCK_SIZE);		//ブロックの位置+オブジェクトの幅
								//種類を渡すのスタートとゴールのみ変更する
								if (m_map[i][j] >= 2)
								{
									*btu = m_map[i][j];	//ブロックの要素(type)をオブジェクトに渡す
									*btg = m_map[i][j];
								}
								*vy = 0.0f;
							}
							if (r > 121.5 && r < 238.5)
							{
								//左
								*left = true;								//オブジェクトの右の部分が衝突している
								*x = bx - (BLOCK_SIZE + 0.5) + (scroll);	//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
								*btg = m_map[i][j];
							}
							if (238.5 < r && r < 301.5)
							{
								//下
								*up = true;						//オブジェクトの上の部分が衝突している
								*y = by + (BLOCK_SIZE - 0.5);	//ブロックの位置+オブジェクトの幅
								*btg = m_map[i][j];
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
							}
						}
					}
				}
			}
			else if (m_map[i][j] == 7)
			{
				if (coin_count < 3)
				{
					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//スクロールの影響
					float scroll = scroll_on ? m_scroll : 0;

					//オブジェクトとブロックの当たり判定(ブロックの左:右:上:下の順)
					if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
					{
						//上下左右判定

						//主人公とブロックの中心でvector作成
						float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
						float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

						//長さlenを求める
						float len = sqrt(rvx * rvx + rvy * rvy);

						//角度rを求める
						float r = atan2(rvy, rvx);	//(ラジアン)
						r = r * 180.0f / 3.14f;		//度

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さより短い場合に判定に入る。
						if (len < HIT_LENGTH)
						{
							//角度で上下左右を判定
							if ((r < 58.5 && r >= 0) || r > 301.5)
							{
								//右
								*right = true;								//オブジェクトの左の部分が衝突している
								*x = bx + (BLOCK_SIZE - 0.2) + (scroll);	//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
								*btg = m_map[i][j];
							}
							if (r > 58.5 && r < 121.5)
							{
								//上
								*down = true;					//オブジェクトの下の部分が衝突している
								*y = by - (2 * BLOCK_SIZE);		//ブロックの位置+オブジェクトの幅
								//種類を渡すのスタートとゴールのみ変更する
								if (m_map[i][j] >= 2)
								{
									*btu = m_map[i][j];	//ブロックの要素(type)をオブジェクトに渡す
									*btg = m_map[i][j];
								}
								*vy = 0.0f;
							}
							if (r > 121.5 && r < 238.5)
							{
								//左
								*left = true;								//オブジェクトの右の部分が衝突している
								*x = bx - (BLOCK_SIZE + 0.2) + (scroll);	//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
								*btg = m_map[i][j];
							}
							if (238.5 < r && r < 301.5)
							{
								//下
								*up = true;						//オブジェクトの上の部分が衝突している
								*y = by + (BLOCK_SIZE - 0.2);	//ブロックの位置+オブジェクトの幅
								*btg = m_map[i][j];
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
}


//BlockHitEnemy関数(敵用の当たり判定)
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
void CObjBlock::BlockHitEnemy(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* bt
)
{
	//衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*bt = 0;

	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	coin_count = hero->GetCoin();

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 1 || m_map[i][j] == 2 || m_map[i][j] == 4)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

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
			else if (m_map[i][j] == 5)
			{
				if (switch_flag == true)
				{
					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//スクロールの影響
					float scroll = scroll_on ? m_scroll : 0;

					//オブジェクトとブロックの当たり判定(ブロックの左:右:上:下の順)
					if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
					{
						//上下左右判定

						//主人公とブロックの中心でvector作成
						float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
						float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

						//長さlenを求める
						float len = sqrt(rvx * rvx + rvy * rvy);

						//角度rを求める
						float r = atan2(rvy, rvx);	//(ラジアン)
						r = r * 180.0f / 3.14f;		//度

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さより短い場合に判定に入る。
						if (len < 88.0)
						{
							//角度で上下左右を判定
							if ((r < 45 && r >= 0) || r > 315)
							{
								//右
								*right = true;								//オブジェクトの左の部分が衝突している
								*x = bx + 64.0f + (scroll);				//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
							}
							if (r > 45 && r < 135)
							{
								//上
								*down = true;					//オブジェクトの下の部分が衝突している
								*y = by - (2 * BLOCK_SIZE);		//ブロックの位置+オブジェクトの幅
								//種類を渡すのスタートとゴールのみ変更する
								if (m_map[i][j] >= 2)
								{
								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;								//オブジェクトの右の部分が衝突している
								*x = bx - 64.0f + (scroll);					//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
							}
							if (225 < r && r < 45)
							{
								//下
								*up = true;						//オブジェクトの上の部分が衝突している
								*y = by + (BLOCK_SIZE - 0.5);	//ブロックの位置+オブジェクトの幅
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
							}
						}
					}
				}
			}
			else if (m_map[i][j] == 7)
			{
				if (coin_count < 3)
				{
					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//スクロールの影響
					float scroll = scroll_on ? m_scroll : 0;

					//オブジェクトとブロックの当たり判定(ブロックの左:右:上:下の順)
					if ((*x + (-scroll) + BLOCK_SIZE > bx) && (*x + (-scroll) < bx + BLOCK_SIZE) && (*y + (2 * BLOCK_SIZE) > by) && (*y < by + BLOCK_SIZE))
					{
						//上下左右判定

						//主人公とブロックの中心でvector作成
						float rvx = (*x + (-scroll) + (BLOCK_SIZE / 2)) - (bx + (BLOCK_SIZE / 2));
						float rvy = (*y + BLOCK_SIZE) - (by + (BLOCK_SIZE / 2));

						//長さlenを求める
						float len = sqrt(rvx * rvx + rvy * rvy);

						//角度rを求める
						float r = atan2(rvy, rvx);	//(ラジアン)
						r = r * 180.0f / 3.14f;		//度

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さより短い場合に判定に入る。
						if (len < 88.0)
						{
							//角度で上下左右を判定
							if ((r < 45 && r >= 0) || r > 315)
							{
								//右
								*right = true;								//オブジェクトの左の部分が衝突している
								*x = bx + 64.0f + (scroll);				//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
							}
							if (r > 45 && r < 135)
							{
								//上
								*down = true;					//オブジェクトの下の部分が衝突している
								*y = by - (2 * BLOCK_SIZE);		//ブロックの位置+オブジェクトの幅
								//種類を渡すのスタートとゴールのみ変更する
								if (m_map[i][j] >= 2)
								{
								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;								//オブジェクトの右の部分が衝突している
								*x = bx - 64.0f + (scroll);					//ブロックの位置+オブジェクトの幅
								*vx = -(*vx) * 0.1f;							//-VX*反発係数
							}
							if (225 < r && r < 45)
							{
								//下
								*up = true;						//オブジェクトの上の部分が衝突している
								*y = by + (BLOCK_SIZE - 0.5);	//ブロックの位置+オブジェクトの幅
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
}