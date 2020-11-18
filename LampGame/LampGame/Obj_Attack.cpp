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
	m_px = x + ABLOCK_INT_X_SIZE;
	m_py = y;
}

//イニシャライズ
void CObjAttack::Init()
{
	m_ani_time = INIT_ANI_TIME;		//アニメーションタイムの初期化
	m_ani_frame = INIT_ANI_FRAME;	//アニメーションフレームの初期化

	m_vx = 0;
	m_vy = 0;

	m_posture = 0.0f;

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);		//Obj_Heroから主人公の向きを取ってくる
	m_posture = hero->GetPosture();


	//向きでHitBoxの位置を変える
	if (m_posture)
		Hits::SetHitBox(this, m_px- ABLOCK_INT_Y_SIZE, m_py, ABLOCK_INT_X_SIZE-4, ABLOCK_INT_Y_SIZE, ELEMENT_ATTACK, OBJ_ATTACK, 1);
	else
		Hits::SetHitBox(this, m_px- ABLOCK_INT_Y_SIZE, m_py, ABLOCK_INT_X_SIZE-4, ABLOCK_INT_Y_SIZE, ELEMENT_ATTACK, OBJ_ATTACK, 1);

}

//アクション
void CObjAttack::Action()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	m_posture = hero->GetPosture();

	m_px = hero->GetX() + (m_posture * ABLOCK_INT_X_SIZE);
	m_py = hero->GetY();

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	//HitBoxの位置の変更
	hit->SetPos(m_px, m_py);

	//アニメーションの調整
	m_ani_time += 1;
	if (m_ani_time % 3 == 0)
	{
		m_ani_frame += 1;
	}

	//向きでHitBoxの位置を変える
	if (m_posture)
	{
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px, m_py);
	}
	else
	{
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px - ABLOCK_INT_X_SIZE, m_py);
	}

	//アニメーション終了後にオブジェクトを破棄する
	if (m_ani_frame >= 8)
	{
		this->SetStatus(false);		//スイッチが押されたら消滅
		Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
	}
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
		src.m_top = ABLOCK_INT_X_SIZE;
		src.m_left = 0.0f + AniData[m_ani_frame] * ABLOCK_INT_X_SIZE;
		src.m_right = ABLOCK_INT_X_SIZE + AniData[m_ani_frame] * ABLOCK_INT_X_SIZE;
		src.m_bottom = src.m_top + ABLOCK_INT_X_SIZE;
	}

	//表示位置の設定　向きで表示位置を変える
	if (m_posture)
	{
		dst.m_top = 0.0f + m_py;
		dst.m_left = (ABLOCK_INT_X_SIZE - ABLOCK_INT_X_SIZE * m_posture) + m_px;
		dst.m_right = (ABLOCK_INT_X_SIZE * m_posture) + m_px;
		dst.m_bottom = ABLOCK_INT_X_SIZE + m_py;
	}
	else
	{
		dst.m_top = 0.0f + m_py;
		dst.m_left = (ABLOCK_INT_X_SIZE - ABLOCK_INT_X_SIZE * m_posture) + m_px - ABLOCK_INT_X_SIZE;
		dst.m_right = (ABLOCK_INT_X_SIZE * m_posture) + m_px - ABLOCK_INT_X_SIZE;
		dst.m_bottom = ABLOCK_INT_X_SIZE + m_py;
	}

	//0番目に登録したグラフィックをsrc・dst・c の情報をもとに描画
	Draw::Draw(11, &src, &dst, c, 0.0f);
}