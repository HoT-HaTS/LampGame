//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "Obj_Tutorial.h"
#include "GameHead.h"
#include "Obj_Stage1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjTutorial::CObjTutorial(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjTutorial::Init()
{
	T_Sensor = false;
}

//�A�N�V����
void CObjTutorial::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	CObjBoard* TSensor = (CObjBoard*)Objs::GetObj(OBJ_BOARD);
	T_Sensor = TSensor->Get_Tuto_Sensor();

	if (T_Sensor == false)
	{
		this->SetStatus(false);		//�X�C�b�`�������ꂽ�����
		Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
	}
	
}

//�h���[
void CObjTutorial::Draw()
{
	int background_flag = 0;
	
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + 288.0f;
		src.m_bottom = src.m_top + 288.0f;

		dst.m_top = m_py-144.0f;
		dst.m_left = m_px + scroll->GetScroll()-144.0f;
		dst.m_right = dst.m_left + 208.0f;
		dst.m_bottom = dst.m_top + 208.0f;

		Draw::Draw(50, &src, &dst, c, 0.0f);
}


