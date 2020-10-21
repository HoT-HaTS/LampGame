//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Block.h"

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
		if (hx < 80)
		{
			hero->SetX(80);
			m_scroll -= hero->GetVX();
		}

		//前方スクロールライン
		if (hx > 300)
		{
			hero->SetX(300);
			m_scroll -= hero->GetVX();
		}
	}

	/*//敵出現ライン
	//主人公の位置+500を敵出現ラインにする
	float line = hx + (-m_scroll) + 500;

	//敵出現ラインを要素番号化
	int ex = ((int)line) / 64;

	//敵出現ラインの列を検索
	for (int i = 0; i < 10; i++)
	{
		//列の中から5を探す
		if (m_map[i][ex] == 5)
		{
			//5があれば、敵を出現
			CObjEnemy* obje = new CObjEnemy(ex * 64.0f, i * 64.0f);
			Objs::InsertObj(obje, OBJ_ENEMY, 10);

			//敵出現場所の値を0にする
			m_map[i][ex] = 0;
		}
	}*/
}

//ドロー
void CObjBlock::Draw()
{
	int background_flag = 0;

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	bool L_flag_background = hero->Get_L_flag();

	if (L_flag_background == true)
		background_flag = 0;
	else
		background_flag = 1;

	if (background_flag == 0)
	{
		//背景表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 896.0f;
		src.m_bottom = 640.0f;
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	else
	{
		//背景表示
		src.m_top = 640.0f;
		src.m_left = 0.0f;
		src.m_right = 896.0f;
		src.m_bottom = 1280.0f;
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(20, &src, &dst, c, 0.0f);
	}


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
				//表示位置の設定
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f + m_scroll;
				dst.m_right = dst.m_left + 64.0f;
				dst.m_bottom = dst.m_top + 64.0f;
				if (m_map[i][j] == 2)
				{
					//ギミックブロック
					BlockDraw(0.0f, 0.0f, &dst, c, 2);
				}
				else if (m_map[i][j] == 3)
				{
					//看板ブロック
					;//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				//else if (m_map[i][j] == 4)
				//{
				//	;//ゴールブロック
				//}
				else if (m_map[i][j] == 5)
				{
					;//敵出現用 BlockDraw(320.0f, 0.0f, &dst, c);
				}
				else if(m_map[i][j]==6)
				{
					;//スイッチ出現用 BlockDraw(64.0f, 0.0f, &dst, c, 21);
				}
				else 
				{
					//床ブロック
					BlockDraw(64.0f, 0.0f, &dst, c, 1);
				}
			}
		}
	}

}

//BlockDrawMethod関数
//引数1 float		x		:リソース切り取り位置x
//引数2 float		y		:リソース切り取り位置y
//引数3 RECT_F* dst			:描画位置
//引数4 float		c[]		:カラー情報
//引数5 int block_id		:ブロックID
//ブロックを64×64限定描画用。リソース切り取り位置のみx,yで設定できる。
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[], int block_id)
{
	if (block_id == 2)
	{
		//ギミックブロック(木)描画
		RECT_F src;
		src.m_top = y;
		src.m_left = x;
		src.m_right = src.m_left + 32.0f;
		src.m_bottom = src.m_top + 64.0f;
		//描画
		Draw::Draw(3, &src, dst, c, 0.0f);
	}
	else if(block_id==1)
	{
		//床ブロック描画
		RECT_F src;
		src.m_top = y;
		src.m_left = x;
		src.m_right = src.m_left + 64.0f;
		src.m_bottom = src.m_top + 64.0f;
		//描画
		Draw::Draw(21, &src, dst, c, 0.0f);
	}
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
void CObjBlock::BlockHit(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* bt
)
{
	/*int map[10][100];
	int Map[10][100];*/

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	int Scroll = block->GetScroll();
	//Map[10][100] = block->GetMap();

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
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f + 32.0f;
				float by = i * 64.0f + 32.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 128.0f > by) && (*y < by + 128.0f))
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
							if (m_map[i][j] >= 2)
								*bt = m_map[i][j];	//ブロックの要素(type)をオブジェクトに渡す
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
