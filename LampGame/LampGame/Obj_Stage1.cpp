//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Stage1.h"

//使用するネームスペース
using namespace GameL;


CObjStage1::CObjStage1(int map[INIT_MAP_X][INIT_MAP_Y])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int) * (INIT_MAP_X * INIT_MAP_Y));
}

//イニシャライズ
void CObjStage1::Init()
{
	//g_f = false;
	g_f2 = true;
	s1_scroll = INIT_SCROLL;
}

//アクション
void CObjStage1::Action()
{
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	s1_scroll = block->GetScroll();

	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	bool L_flag = hero->Get_L_flag();


	//CObj_G_Block* gflag = (CObj_G_Block*)Objs::GetObj(OBJ_BLOCK);
	//g_f = gflag->Get_G_flag();

	CObj_G_Block2* gflag2 = (CObj_G_Block2*)Objs::GetObj(OBJ_BLOCK);
	g_f2 = gflag2->Get_G2_flag();

	//敵出現ライン
	//主人公の位置+500を敵出現ラインにする
	float line = hx + (-s1_scroll) + 500;

	//敵出現ラインを要素番号化
	int ex = ((int)line) / BLOCK_SIZE;

	/*敵出現ラインの列を検索
	0:なにもなし
	1:ステージブロック
	2:ゴールブロック
	3:敵出現用ブロック
	4:影の世界でしか見えないブロック(G3)
	5:スイッチを押すと出現、消滅するブロック(G2)
	6:5用のスイッチ
	7:鍵と連動するブロック(G5)
	8:7用の鍵
	9:予備*/

	for (int i = 0; i < INIT_MAP_X; i++)
	{
		//列の中からSTAGEBLOCKを探す
		if (m_map[i][ex] == STAGE_BLOCK)
		{

			//出現場所の値を0にする
			//m_map[i][ex] = NO_BLOCK;
		}
		//列の中からGOALBLOCKを探す
		if (m_map[i][ex] == GOAL_BLOCK)
		{

			//出現場所の値を0にする
			//m_map[i][ex] = NO_BLOCK;
		}
		//列の中からENEMYBLOCKを探す
		if (m_map[i][ex] == ENEMY_BLOCK)
		{
			//敵出現
			CObjEnemy* obje = new CObjEnemy(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(obje, OBJ_ENEMY, 14);

			//敵出現場所の値を0にする
			m_map[i][ex] = NO_BLOCK;

		}
		//列の中からG_BLOCK3を探す
		if (m_map[i][ex] == G_BLOCK3)
		{

			//出現場所の値を0にする
			//m_map[i][ex] = NO_BLOCK;
		}
		//列の中からG_BLOCK2を探す
		if (m_map[i][ex] == G_BLOCK2)
		{
			if (g_f2 == false)
			{
				//G2ブロック出現
				CObj_G_Block2* objg2 = new CObj_G_Block2(ex * BLOCK_SIZE, i * BLOCK_SIZE);
				Objs::InsertObj(objg2, OBJ_BLOCK, 8);
			}

			//出現場所の値を0にする
			//m_map[i][ex] = NO_BLOCK;
		}
		//列の中からG_BLOCK2のスイッチを探す
		if (m_map[i][ex] == G_SWITCH2)
		{
			//スイッチ出現
			CObjSwitch* objs = new CObjSwitch(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objs, OBJ_SWITCH, 7);

			//スイッチ出現場所の値を0にする
			m_map[i][ex] = NO_BLOCK;
		}
		//列の中からG_BLOCK5を探す
		if (m_map[i][ex] == G_BLOCK5)
		{

			//出現場所の値を0にする
			//m_map[i][ex] = NO_BLOCK;
		}
		//列の中からG_BLOCK5のスイッチを探す
		if (m_map[i][ex] == G_SWITCH5)
		{

			//出現場所の値を0にする
			//m_map[i][ex] = NO_BLOCK;
		}
		////列の中からG_BLOCKを探す(テスト用)
		//if (m_map[i][ex] == G_BLOCK)
		//{
		//	//Gブロック出現
		//	CObj_G_Block* objg = new CObj_G_Block(ex * BLOCK_SIZE, i * BLOCK_SIZE);
		//	Objs::InsertObj(objg, OBJ_BLOCK, 8);

		//	//Gブロック出現場所の値を0にする
		//	m_map[i][ex] = NO_BLOCK;
		//}
	}
}

//ドロー
void CObjStage1::Draw()
{
	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float  c1[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//ブロック描画
	for (int i = 0; i < INIT_MAP_X; i++)
	{
		for (int j = 0; j < INIT_MAP_Y; j++)
		{
			if (m_map[i][j] > NO_BLOCK)
			{
				//表示位置の設定
				dst.m_top = i * BLOCK_SIZE;
				dst.m_left = j * BLOCK_SIZE + s1_scroll;
				dst.m_right = dst.m_left + BLOCK_SIZE;
				dst.m_bottom = dst.m_top + BLOCK_SIZE;
				if (m_map[i][j] == 8)
				{
					;//ブロック
					//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				else if (m_map[i][j] == GOAL_BLOCK)
				{
					dst.m_top = i * BLOCK_SIZE - 128.0f;
					dst.m_left = j * BLOCK_SIZE + s1_scroll - 128.0f;
					dst.m_right = dst.m_left + 320.0f;
					dst.m_bottom = dst.m_top + 256.0f;
					//ゴールブロック
					BlockDraw(BLOCK_SIZE, 0.0f, &dst, c, GOAL_BLOCK);
				}
				else if (m_map[i][j] == 4)
				{
					;//ギミックブロック
					//BlockDraw(0.0f, 0.0f, &dst, c, 2);
				}
				else if (m_map[i][j] == 5)
				{
					;//敵出現用 BlockDraw(320.0f, 0.0f, &dst, c);
				}
				else if (m_map[i][j] == 6)
				{
					;//スイッチ出現用 BlockDraw(64.0f, 0.0f, &dst, c, 21);
				}
				else if (m_map[i][j]==STAGE_BLOCK)
				{
					//ステージブロック
					BlockDraw(BLOCK_SIZE, 0.0f, &dst, c1, STAGE_BLOCK);
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
	if (block_id == 6)
	{
		//ギミックブロック(木)描画
		RECT_F src;
		src.m_top = y;
		src.m_left = x;
		src.m_right = src.m_left + BLOCK_SIZE;
		src.m_bottom = src.m_top + BLOCK_SIZE;
		//描画
		Draw::Draw(3, &src, dst, c, 0.0f);
	}
	else if (block_id == STAGE_BLOCK)
	{
		//床ブロック描画
		RECT_F src;
		src.m_top = y;
		src.m_left = x;
		src.m_right = src.m_left + BLOCK_SIZE;
		src.m_bottom = src.m_top + BLOCK_SIZE;
		//描画
		Draw::Draw(21, &src, dst, c, 0.0f);
	}
	else if (block_id == GOAL_BLOCK)
	{
		//ゴールブロック描画
		RECT_F src;
		src.m_top = y;
		src.m_left = x - BLOCK_SIZE;
		src.m_right = src.m_left + 192.0f;
		src.m_bottom = src.m_top + 128.0f;
		//描画
		Draw::Draw(24, &src, dst, c, 0.0f);
	}
}