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

	//マップチップによるBlock設置
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
				//表示位置の設定
				dst.m_top    = i * 64.0f;
				dst.m_left   = j * 64.0f + m_scroll;
				dst.m_right  = dst.m_left + 64.0f;
				dst.m_bottom = dst.m_top  + 64.0f;

				if (m_map[i][j] == 2)
				{
					; //ギミックブロック配置用の番号のため何もしない
				}
				else if (m_map[i][j] == 3)
				{
					//看板
					BlockDraw1(320.0f + 64.0f, 0.0f, &dst, c);
				}
				else if (m_map[i][j] == 3)
				{
					//ゴールブロック
					BlockDraw(320.0f + 64.0f, 0.0f, &dst, c);
				}
				else if (m_map[i][j] == 5)
				{
					; //敵配置用の番号のため何もしない
				}
				else if (m_map[i][j] == 6)
				{
					//スイッチ
					BlockDraw2(320.0f + 64.0f, 64.0f, &dst, c);
				}
				else
				{
					BlockDraw(320.0f, 0.0f, &dst, c);
				}
			}
		}
	}
}

//BlockDrawMethod関数
//引数1 float    x   :リソース切り取り位置X
//引数2 float    y   :リソース切り取り位置Y
//引数3 RECT_F * dst :描画位置
//引数4 float    c[] :カラー情報
//ブロックを64×64限定描画用。リソース切り取り位置のみx・yで設定できる
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x + 128.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//描画
	Draw::Draw(21, &src, dst, c, 0.0f);
}
//BlockDrawMethod1：看板
void CObjBlock::BlockDraw1(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//描画
	Draw::Draw(23, &src, dst, c, 0.0f);
}
//BlockDrawMethod2：スイッチを一旦表示（後で消すかも）
void CObjBlock::BlockDraw2(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//描画
	Draw::Draw(10, &src, dst, c, 0.0f);
}