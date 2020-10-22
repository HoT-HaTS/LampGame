//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Stage1.h"

//使用するネームスペース
using namespace GameL;


CObjStage1::CObjStage1(int map[10][100])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int) * (10 * 100));
}

//イニシャライズ
void CObjStage1::Init()
{
	m_scroll = 0.0f;
}

//アクション
void CObjStage1::Action()
{
	/*CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	m_scroll = block->GetScroll();*/

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
}

//ドロー
void CObjStage1::Draw()
{
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//ブロック描画
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
				else if (m_map[i][j] == 6)
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
void CObjStage1::BlockDraw(float x, float y, RECT_F* dst, float c[], int block_id)
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
	else if (block_id == 1)
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