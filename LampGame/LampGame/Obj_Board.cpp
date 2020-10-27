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

CObjBoard::CObjBoard(int map[10][100])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int) * (10 * 100));
}

//イニシャライズ
void CObjBoard::Init()
{

}

//アクション
void CObjBoard::Action()
{

}

//ドロー
void CObjBoard::Draw()
{
	int background_flag = 0;

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);



		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 64.0f;
		dst.m_bottom = 64.0f;
		Draw::Draw(20, &src, &dst, c, 0.0f);
}


