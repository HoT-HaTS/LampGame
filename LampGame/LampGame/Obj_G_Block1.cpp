//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObj_G_Block::CObj_G_Block(float x, float y)
{
	m_px = x;	//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObj_G_Block::Init()
{
	G_flag = false;			//false������Btrue������

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//�A�N�V����
void CObj_G_Block::Action()
{
	//�X�C�b�`�������ꂽ��t���O�؂�ւ��A�M�~�b�N�u���b�N������
	CObjSwitch* sflag = (CObjSwitch*)Objs::GetObj(OBJ_SWITCH);
	 G_flag = sflag->Get_S_flag();


	if (Input::GetVKey('A') == true)
	{
		G_flag == true;
	}

	//if (G_flag == true)
	//{
	//	this->SetStatus(false);		//�X�C�b�`�������ꂽ�����
	//	Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
	//}

}

//�h���[
void CObj_G_Block::Draw()
{

}