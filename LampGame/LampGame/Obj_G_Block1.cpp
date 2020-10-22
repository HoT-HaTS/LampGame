//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block1.h"

//使用するネームスペース
using namespace GameL;

CObj_G_Block::CObj_G_Block(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObj_G_Block::Init()
{
	G_flag = false;			//false→ある。true→消滅

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//アクション
void CObj_G_Block::Action()
{
	//スイッチが押されたらフラグ切り替え、ギミックブロックを消滅
	CObjSwitch* sflag = (CObjSwitch*)Objs::GetObj(OBJ_SWITCH);
	 G_flag = sflag->Get_S_flag();


	if (Input::GetVKey('A') == true)
	{
		G_flag == true;
	}

	//if (G_flag == true)
	//{
	//	this->SetStatus(false);		//スイッチが押されたら消滅
	//	Hits::DeleteHitBox(this);	//スイッチが所有するHitBoxを削除
	//}

}

//ドロー
void CObj_G_Block::Draw()
{

}