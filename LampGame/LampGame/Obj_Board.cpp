//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Board.h"
#include "Obj_Stage1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBoard::CObjBoard(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjBoard::Init()
{

	Hits::SetHitBox(this, m_px, m_py, 64.0f, 64.0f, ELEMENT_BOARD, OBJ_BOARD, 1);

}

//�A�N�V����
void CObjBoard::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//��l����HitBox�ɓ������flag��true�ɂ���
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		T_Sensor = true;				//�Z���T�[�̃t���O��true��
	}
	else
	{
		T_Sensor = false;
	}

	if (T_Sensor == true)
	{
		CObjTutorial* obj_tutorial = new CObjTutorial(m_px+64.0f, m_py - 194.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_tutorial, OBJ_TUTORIAL, 100);
	}

}

//�h���[
void CObjBoard::Draw()
{
	int background_flag = 0;
	
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu



		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + 64.0f;
		src.m_bottom = src.m_top + 64.0f;

		dst.m_top = m_py + 0.0f;
		dst.m_left = m_px + scroll->GetScroll() +0.0f;
		dst.m_right = dst.m_left + 64.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		Draw::Draw(23, &src, &dst, c, 0.0f);
}


