//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"

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
	g_f2 = false;
	s1_scroll = INIT_SCROLL;
	l_f = true;

	alpha = 1.0f;
	count = 0;
	t = 0;
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

	CObj_G_Block2* gflag2 = (CObj_G_Block2*)Objs::GetObj(OBJ_BLOCK);
	g_f2 = gflag2->Get_G2_flag();


	//主人公の位置+300をobject出現ライン(初期値)にし、+500をobjectの出現ラインにする。
	float line = hx + (-s1_scroll) + OBJECT_LINE  + t;
	if (t < 200)
	{
		t += 64;
	}

	//object出現ラインを要素番号化
	int ex = ((int)line) / BLOCK_SIZE;

	ScrollLine(ex);

}

//ScrollLine関数
//要素番号をもとにブロック等を出現させる
//引数1	int ex マップのx座標(要素番号)
void CObjStage1::ScrollLine(int ex)
{

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
			//G3ブロック出現
			CObj_G_Block3* objg3 = new CObj_G_Block3(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objg3, G_BLOCK3, 7);

			//出現場所の値を0にする
			m_map[i][ex] = NO_BLOCK;
		}
		//列の中からG_BLOCK2を探す
		if (m_map[i][ex] == G_BLOCK2)
		{
			//G2ブロック出現
			CObj_G_Block2* objg2 = new CObj_G_Block2(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objg2, OBJ_BLOCK, 8);

			//出現場所の値を0にする
			m_map[i][ex] = NO_BLOCK;
		}
		//列の中からSWITCH2のスイッチを探す
		if (m_map[i][ex] == G_SWITCH2)
		{
			//スイッチ2出現
			CObjSwitch2* objs2 = new CObjSwitch2(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objs2, OBJ_SWITCH2, 7);

			//スイッチ2出現場所の値を0にする
			m_map[i][ex] = NO_BLOCK;
		}
		//列の中からG_BLOCK5を探す
		if (m_map[i][ex] == G_BLOCK5)
		{
			//G5ブロック出現
			CObj_G_Block5* objg5 = new CObj_G_Block5(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objg5, OBJ_BLOCK, 8);

			//出現場所の値を0にする
			m_map[i][ex] = NO_BLOCK;
		}
		//列の中からコインを探す
		if (m_map[i][ex] == G_SWITCH5)
		{
			//コイン出現
			CObjKeyCoin* objs5 = new CObjKeyCoin(ex * BLOCK_SIZE, i * BLOCK_SIZE);
			Objs::InsertObj(objs5, OBJ_KEYCOIN, 7);

			//出現場所の値を0にする
			m_map[i][ex] = NO_BLOCK;
		}
	}
}

//ドロー
void CObjStage1::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool S_flag = hero->GetG_Flag();

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
				if (m_map[i][j] == G_SWITCH5)
				{
					;//ブロック
					//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				if (m_map[i][j] == 9)
				{
					;//ブロック
					//BlockDraw(320.0f + 64.0f, 64.0f, &dst, c, 3);
				}
				else if (m_map[i][j] == GOAL_BLOCK)
				{
					if (S_flag == true)
						alpha -= 0.01f;

					float gc[4] = { 1.0f,1.0f,1.0f,alpha };

					dst.m_top = i * BLOCK_SIZE - GOAL_T;
					dst.m_left = j * BLOCK_SIZE + s1_scroll - GOAL_T;
					dst.m_right = dst.m_left + GOAL_R;
					dst.m_bottom = dst.m_top + GOAL_B;
					
					//ゴールブロック描画
					BlockDraw(BLOCK_SIZE, 0.0f, &dst, gc, GOAL_BLOCK);
				}
				else if (m_map[i][j] == G_BLOCK3)
				{
					//ギミックブロック
					//BlockDraw(BLOCK_SIZE, 0.0f, &dst, c, G_BLOCK3);
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
	//主人公から光フラグを取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool l_f = hero->Get_L_flag();

	if (block_id == 6)
	{
		//ギミックブロック2を描画
		//RECT_F src;
		//src.m_top = y;
		//src.m_left = x;
		//src.m_right = src.m_left + BLOCK_SIZE;
		//src.m_bottom = src.m_top + BLOCK_SIZE;
		////描画
		//Draw::Draw(3, &src, dst, c, 0.0f);
	}
	else if (block_id == STAGE_BLOCK)
	{
		if (l_f == true)
		{
			//床ブロック(光)描画
			RECT_F src;
			src.m_top = y;
			src.m_left = x;
			src.m_right = src.m_left + BLOCK_SIZE;
			src.m_bottom = src.m_top + BLOCK_SIZE;
			//描画
			Draw::Draw(((UserData*)Save::GetData())->stage_id + 40, &src, dst, c, 0.0f);
		}

		else if (l_f == false)
		{
			//床ブロック(影)描画
			RECT_F src;
			src.m_top = y;
			src.m_left = x;
			src.m_right = src.m_left + BLOCK_SIZE;
			src.m_bottom = src.m_top + BLOCK_SIZE;
			//描画
			Draw::Draw(51, &src, dst, c, 0.0f);
		}
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
	else if (block_id == G_BLOCK3)
	{
		if (l_f == false)
		{
			//床ブロック(影)描画
			RECT_F src;
			src.m_top = y;
			src.m_left = x;
			src.m_right = src.m_left + BLOCK_SIZE;
			src.m_bottom = src.m_top + BLOCK_SIZE;
			//描画
			Draw::Draw(5, &src, dst, c, 0.0f);
		}
	}
}