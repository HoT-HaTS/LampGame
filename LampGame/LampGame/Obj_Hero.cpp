//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"


#include "GameHead.h"
#include "Obj_Hero.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHero::Init()
{
	m_px = INIT_H_PX;		//位置
	m_py = INIT_H_PY;
	m_vx = INIT_H_VX;		//移動ベクトル
	m_vy = INIT_H_VY;
	m_sx = INIT_H_PX;		//世界切り替え時の位置
	m_sy = INIT_H_PY;

	m_posture = INIT_H_POSTURE;	//右向き0.0f 左向き1.0f

	m_ani_time = INIT_ANI_TIME;
	m_ani_frame = INIT_ANI_FLAME;	//静止フレームを初期にする
	m_ani_s_time = INIT_ANI_TIME;
	m_ani_s_frame = INIT_ANI_FLAME;	//静止フレームを初期にする


	m_speed_power = INIT_SPEED_POWER;	//通常速度
	m_ani_max_time = INIT_ANI_MAX_TIME;	//アニメーション間隔幅

	attack_flag = true;	//攻撃制御用フラグ

	L_flag = true;	//開始時は光フラグON
	m_flag = true;	//光の世界制御用

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type_under = BLOCK_TYPE_U;	//踏んでいるblockの種類確認用(下)
	m_block_type_right = BLOCK_TYPE_R;	//blockの種類確認用(右)

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, HBLOCK_INT_X_SIZE, HBLOCK_INT_Y_SIZE, ELEMENT_PLAYER, OBJ_HERO, 1);

	//テスト用
	move_flag = true;
	x = 0;
	y = 0;
	ar = 0;
}

//アクション
void CObjHero::Action()
{
	//落下によるゲームオーバー
	if (m_py > STAGE_Y_OUT)
	{
		//場外に出たらリセット
		Scene::SetScene(new CSceneStage_1());
	}


	if (move_flag == true)
	{
		if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
		{
			//主人公の攻撃
			if (Input::GetVKey('Z') == true)
			{
				if (attack_flag == true)
				{
					//攻撃オブジェクトの作成
					CObjAttack* obj_attack = new CObjAttack(m_px, m_py); //弾丸オブジェクト作成
					Objs::InsertObj(obj_attack, OBJ_ATTACK, 100);		//作った弾丸オブジェクトをマネージャーに登録

					attack_flag = false;
				}
			}
			else
			{
				attack_flag = true;
			}
		}
		//移動(光の世界)
		if (L_flag == true)
		{
			//キーの入力方向
			if (Input::GetVKey(VK_RIGHT) == true)
			{
				m_vx += 2 * m_speed_power;
				m_posture = 1.0f;
				m_ani_time += 1.0;
			}
			else if (Input::GetVKey(VK_LEFT) == true)
			{
				m_vx -= 2 * m_speed_power;
				m_posture = 0.0f;
				m_ani_time += 1.0;
			}
			else
			{
				m_ani_frame = 1;	//キー入力がない場合は静止フレームにする
				m_ani_time = 0;
			}

			//摩擦
			m_vx += -(m_vx * INIT_FRICTION);

			//自由落下運動
			m_vy += 9.8 / (64.0f);

			//位置の更新
			m_px += m_vx;
			m_py += m_vy;
		}

		//移動(影の世界)
		if (L_flag == false)
		{
			//キーの入力方向
			if (Input::GetVKey(VK_RIGHT) == true)
			{
				m_vx += m_speed_power;
				m_posture = 1.0f;
				m_ani_time += 1.0;
			}
			else if (Input::GetVKey(VK_LEFT) == true)
			{
				m_vx -= m_speed_power;
				m_posture = 0.0f;
				m_ani_time += 1.0;
			}

			if (Input::GetVKey(VK_UP) == true)
			{
				m_vy -= m_speed_power;
				m_ani_time += 1.0;
			}
			else if (Input::GetVKey(VK_DOWN) == true)
			{
				m_vy += m_speed_power;
				m_ani_time += 1.0;
			}

			if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
			{
				m_ani_frame = 1;	//キー入力がない場合は静止フレームにする
				m_ani_time = 0;
			}

			//摩擦
			m_vx += -(m_vx * INIT_FRICTION);
			m_vy += -(m_vy * INIT_FRICTION);

			//位置の更新
			m_px += m_vx;
			m_py += m_vy;


			//右方向
			if (m_px + 64.0 > 800)
			{
				m_px = 800.0f - 64.0f; //はみ出ない位置に移動させる。
			}
			//左方向
			if (m_px < 0.0f)
			{
				m_px = 0.0f;
			}
			//上方向
			if (m_py < 0.0f)
			{
				m_py = 0.0f;
			}
			////下方向
			//if (m_py + 128.0f > 600 )
			//{
			//	m_py = 600.0f - 128.0f;
			//}

			//画面外に行かない処理
			//CheckWindow(m_px, m_py, -32.0f, -32.0f, 800.0f, 600.0f);
		}
		//自身のHitBoxを持ってくる
		CHitBox* hit = Hits::GetHitBox(this);

		//HitBoxの位置の変更
		hit->SetPos(m_px, m_py);

		//ブロックとの当たり判定実行
		CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		pb->BlockHit(&m_px, &m_py, true,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type_under, &m_block_type_right);
	}


	//アニメーション
	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
	{
		m_ani_s_time += 1.0;
	}
	//アニメーション関連(静止用)
	if (m_ani_s_time > m_ani_max_time)
	{
		m_ani_s_frame += 1;
		m_ani_s_time = 0;
	}
	if (m_ani_s_frame == m_ani_max_time)
	{
		m_ani_s_frame = 0;
	}



	//アニメーション関連(移動用)
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == m_ani_max_time)
	{
		m_ani_frame = 0;
	}


	if (move_flag == true)
	{
		//世界切り替え:光→影(X押すと切り替え)
		if (L_flag == true)
		{
			if (Input::GetVKey('X') == true)
			{
				if (m_flag == true)
				{
					L_flag = false;
					m_flag = false;
					m_vy = 0;
					m_sx = m_px;
					m_sy = m_py;
				}
			}
			else
			{
				m_flag = true;
			}
		}

		//世界切り替え:影→光(X押すと切り替え)
		if (L_flag == false)
		{
			if (Input::GetVKey('X') == true)
			{
				if (m_flag == true)
				{
					m_vx = 0;
					m_vy = 0;
					move_flag = false;
					Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
				}
			}
			else
			{
				m_flag = true;
			}
		}
	}
	
	if(move_flag==false)
	{
		x = m_sx - m_px;
		y = m_sy - m_py;
		ar = GetAtan2Angle(x, -y);

		//移動方向を主人公機の方向にする
		m_vx = cos(3.14 / 180 * ar);
		m_vy = -sin(3.14 / 180 * ar);
		UnitVec(&m_vx, &m_vy);

		m_px += 5 * m_vx;
		m_py += 5 * m_vy;

		if (m_sx - 5 < m_px && m_px < m_sx + 5)
		{
			//当たり判定用のHitBoxを作成
			Hits::SetHitBox(this, m_px, m_py, HBLOCK_INT_X_SIZE, HBLOCK_INT_Y_SIZE, ELEMENT_PLAYER, OBJ_HERO, 1);
			L_flag = true;
			m_flag = false;
			move_flag = true;
		}
	}


	//ステージ終了条件(ゴール到達)
	if (m_block_type_right == 4)
	{
		Scene::SetScene(new CSceneSelect());
	}













	//敵関係
	////敵と当たっているか確認
	//if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	//{
	//	//主人公がどの敵とどの角度で当たっているかを確認
	//	HIT_DATA** hit_data;							//当たった時の細かな情報を入れるための構造体
	//	hit_data = hit->SearchObjNameHit(OBJ_ENEMY);	//hit_dataに主人公と当たっているほかすべてのHitBoxとの情報を入れる
	//	for (int i = 0; i < hit->GetCount(); i++)
	//	{
	//		//敵の左右に当たったら
	//		float r = hit_data[i]->r;
	//		if ((r < 45 && r >= 0 || r>315))
	//		{
	//			m_vx = -5.0f;	//左に移動させる
	//		}
	//		if (r > 135 && r < 225)
	//		{
	//			m_vx = +5.0f;	//右に移動させる
	//		}
	//		if (r >= 225 && r < 315)
	//		{
	//			//敵の移動方向を主人公の位置に加算(oはオブジェクトアドレス)
	//			m_px += ((CObjEnemy*)hit_data[i]->o)->GetVx();

	//			CObjBlock* b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//			//後方スクロールライン
	//			if (m_px < 80)
	//			{
	//				m_px = 80;				//主人公はラインを超えないようにする
	//				b->SetScroll(b->GetScroll() + 5.0f);	//主人公が本来動くべき分の値をm_scrollに加える
	//			}

	//			//前方スクロールライン
	//			if (m_px > 300)
	//			{
	//				m_px = 300;				//主人公はラインを超えないようにする
	//				b->SetScroll(b->GetScroll() - 5.0f);	//主人公が本来動くべき分の値をm_scrollに加える
	//			}
	//		}
	//	}
	//}

}

//ドロー
void CObjHero::Draw()
{
	//アニメーション番号
	int AniData[5] =
	{
		0, 1, 2, 3, 1,
	};

	//描画カラー情報 R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_s_frame] * HBLOCK_INT_X_SIZE;
		src.m_right = HBLOCK_INT_X_SIZE + AniData[m_ani_s_frame] * HBLOCK_INT_X_SIZE;
		src.m_bottom = HBLOCK_INT_Y_SIZE;
	}
	else
	{
		src.m_top = HBLOCK_INT_Y_SIZE;
		src.m_left = 0.0f + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
		src.m_right = HBLOCK_INT_X_SIZE + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
		src.m_bottom = src.m_top + HBLOCK_INT_Y_SIZE;
	}

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (HBLOCK_INT_X_SIZE - HBLOCK_INT_X_SIZE * m_posture) + m_px;
	dst.m_right = (HBLOCK_INT_X_SIZE * m_posture) + m_px;
	dst.m_bottom = HBLOCK_INT_Y_SIZE + m_py;

	//光フラグがONなら
	if (L_flag == true)
	{
		//0番目に登録したグラフィック(主人公・光)をsrc・dst・c の情報をもとに描画
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	//光フラグがOFFなら
	else 
	{
		//1番目に登録したグラフィック(主人公・影)をsrc・dst・c の情報をもとに描画
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
}


//---GetAtan2Angle関数
//引数1		float w		:幅
//引数2		float h		:高さ
//戻り値	float		:角度(0°〜360°)
//内容		
//高さと幅から直角三角形があると仮定しその角度を求める。
float CObjHero:: GetAtan2Angle(float w, float h)
{
	//atan2で角度を求める
	float r = atan2(h, w) * 180.0f / 3.14f;

	//-180.0°〜0°を180°〜360°に変換
	if (r < 0)
	{
		r = 360 - fabs(r);
	}

	return r;
}

//---UnitVec関数
//引数1　float*vx	:ベクトルのx成分のポインタ
//引数2　float*vy	:ベクトルのy成分のポインタ
//戻り値 bool		:true=計算成功	false=計算失敗
//内容
//引数のベクトルを正規化しその値をvx,vyに変更します。
bool CObjHero:: UnitVec(float* vx, float* vy)
{
	//ベクトルの長さを求める（三平方の定理）
	float r = 0.0f;
	r = (*vx) * (*vx) + (*vy) * (*vy);
	r = sqrt(r);

	//長さが0かどうか調べる
	if (r == 0.0f)
	{
		//0なら計算失敗
		return false;
	}
	else
	{
		//正規化を行いvxとvyの参照先の値を変更
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);
	}

	//計算成功
	return true;
}

//HeroMove関数:Xボタンを押した瞬間の光と影の位置から角度を求めて一定速度で元の位置に戻る


void CObjHero::HeroMove(float mx,float my, float sx, float sy, float vx, float vy)
{
		float x = sx - mx;
		float y = sy - my;
		float ar = GetAtan2Angle(x, -y);


		//移動方向を主人公機の方向にする
		vx = cos(3.14 / 180 * ar);
		vy = -sin(3.14 / 180 * ar);
		UnitVec(&vx, &vy);

		sx += 4 * vx;
		sy += 4 * vy;

}