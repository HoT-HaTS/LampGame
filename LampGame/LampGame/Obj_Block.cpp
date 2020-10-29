//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

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
	float  c[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	bool L_flag_background = hero->Get_L_flag();

	if (L_flag_background == true)
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
		Draw::Draw(20, &src, &dst, c, 0.0f);
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
//引数11 int* btr			:右部分判定時、特殊なブロックのタイプを返す
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

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 1 || m_map[i][j] == 3)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//オブジェクトとブロックの当たり判定(ブロックの左:右:上:下の順)
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 128.0f > by) && (*y < by + 64.0f))
				{
					//上下左右判定

					//主人公とブロックの中心でvector作成
					float rvx = (*x + (-scroll) + 32.0f) - (bx + 32.0f);
					float rvy = (*y + 64.0f) - (by + 32.0f);

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
					if (len < 111.0f)
					{
						//角度で上下左右を判定
						if ((r < 56 && r>=0) || r > 304)
						{
							//右
							//*right = true;	//オブジェクトの左の部分が衝突している
							*x = bx + 63.5f + (scroll);	//ブロックの位置+オブジェクトの幅
							*vx = -(*vx) * 0.1f;	//-VX*反発係数
							*btg = m_map[i][j];
						}
						if (r > 56 && r < 124)
						{
							//上
							//*down = true;	//オブジェクトの下の部分が衝突している
								*y = by - 128.0f;	//ブロックの位置+オブジェクトの幅
							//種類を渡すのスタートとゴールのみ変更する
							if (m_map[i][j] >= 2)
							{
								*btu = m_map[i][j];	//ブロックの要素(type)をオブジェクトに渡す
								*btg = m_map[i][j];
							}
							*vy = 0.0f;
						}
						if (r > 124 && r <236 )
						{
							//左
							//*left = true;	//オブジェクトの右の部分が衝突している
							*x = bx - 64.5f + (scroll);	//ブロックの位置+オブジェクトの幅
							*vx = -(*vx) * 0.1f;	//-VX*反発係数
							*btg = m_map[i][j];
						}
						if (236 < r && r < 304)
						{
							//下
							//*up = true;	//オブジェクトの上の部分が衝突している
							*y = by + 63.5f;	//ブロックの位置+オブジェクトの幅
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


