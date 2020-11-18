//�O���t�B�b�N�ǉ��ƕ\��������Ƃ��납��


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

CObjBoard::CObjBoard(float x, float y, int i)
{
	m_px = x;			//�ʒu
	m_py = y;
	b_num = i;
}

//�C�j�V�����C�Y
void CObjBoard::Init()
{
	count = 0;
	m_flag = true;
	T_Sensor = false;

	Hits::SetHitBox(this, m_px, m_py, 192.0f, 128.0f, ELEMENT_BOARD, OBJ_BOARD, 1);

}

//�A�N�V����
void CObjBoard::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px+scroll->GetScroll()-64 , m_py-64);

	//��l����HitBox�ɓ������flag��true�ɂ���
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		T_Sensor = true;	//�Z���T�[�̃t���O��true��
		m_flag = false;
		if (m_flag == false)
		{
			count++;
			m_flag = true;
		}
	}
	else
		T_Sensor = false;
	//�Ŕ������̉�ʊO�ɏo����폜
	bool check = CheckWindow(m_px, m_py, -32.0f, -32.0f, 800.0f, 600.0f);
	if (check == false)
	{
		this->SetStatus(false);	//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);//�Ŕ����L����HitBox���폜����
		T_Sensor = false;
	}
}

//�h���[
void CObjBoard::Draw()
{
	
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


		//���Ŕ����`��

		RECT_F src2;	//�`�挳�؂���ʒu
		RECT_F dst2;	//�`���\���ʒu

		src2.m_top = 0.0f;
		src2.m_left = 0.0f + 288 * b_num;
		src2.m_right = src2.m_left + 288.0f;
		src2.m_bottom = src2.m_top + 288.0f;

		dst2.m_top = 270;
		dst2.m_left = m_px + scroll->GetScroll() - 65.0f;
		dst2.m_right = dst2.m_left + 192.0f;
		dst2.m_bottom = dst2.m_top + 180.0f;
		if (T_Sensor == true)
		{
			Draw::Draw(50, &src2, &dst2, c, 0.0f);
		}


}


//---CheckWindow�֐�
//����1	float pos_x		:�̈�O���ǂ������ׂ�x�ʒu
//����2	float pos_y		:�̈�O���ǂ������ׂ�y�ʒu
//����3	float window_x	:�̈��top�ʒu
//����4	float window_y	:�̈��left�ʒu
//����5	float window_w	:�̈��right�ʒu
//����6	float window_h	:�̈��bottom�ʒu
//�߂�l bool		:true=�̈�� false=�̈�O
//���e
//�̈�����ǂ������ׂ�ʒupos_(x,y)��window_(xywh)�̓����O���𒲂ׂ�B

bool CObjBoard::CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h)
{
	//�̈�`�F�b�N
	if (pos_x < window_x)
	{
		return false;	//�̈�O
	}
	//if (pos_x > window_w)
	//{
	//	return false;	//�̈�O
	//}
	if (pos_y < window_y)
	{
		return false;	//�̈�O
	}
	if (pos_y > window_h)
	{
		return false;	//�̈�O
	}

	return true;		//�̈��
}

