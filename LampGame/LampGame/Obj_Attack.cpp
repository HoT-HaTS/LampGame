//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_Attack.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjAttack::CObjAttack(float x, float y)
{
	m_px = x+64;
	m_py = y;
}

//イニシャライズ
void CObjAttack::Init()
{
	m_ani_time = INIT_ANI_TIME;		//アニメーションタイムの初期化
	m_ani_frame = INIT_ANI_FLAME;	//アニメーションフレームの初期化


	Hits::SetHitBox(this, m_px, m_py, ABLOCK_INT_X_SIZE, ABLOCK_INT_Y_SIZE+64, ELEMENT_ATTACK, OBJ_ATTACK,1);
}

//アクション
void CObjAttack::Action()
{
	
	m_ani_time += 1;
	if(m_ani_time)

	CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_px, m_py);

	//Todo:アニメーション終了後にオブジェクトを破棄する
}

//ドロー
void CObjAttack::Draw()
{
	//アニメーション番号
	int AniData[7] =
	{
		0,1,2,3,4,5,6
	};

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	{
		src.m_top = HBLOCK_INT_Y_SIZE;
		src.m_left = 0.0f + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
		src.m_right = HBLOCK_INT_X_SIZE + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
		src.m_bottom = src.m_top + HBLOCK_INT_Y_SIZE;
	}

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 64.0f;
	dst.m_bottom = 64.0f;

	//0番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(11, &src, &dst, c, 0.0f);
}