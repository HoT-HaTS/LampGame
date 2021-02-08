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

	Hits::SetHitBox(this, m_px, m_py, BOARD_SIXE_X, BOARD_SIXE_Y, ELEMENT_BOARD, OBJ_BOARD, 1);

}

//�A�N�V����
void CObjBoard::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll() - BLOCK_SIZE, m_py - BLOCK_SIZE);

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
	bool check = CheckWindow(m_px, m_py, -(BLOCK_SIZE/2), -(BLOCK_SIZE / 2), STAGE_X_OUT, STAGE_Y_OUT);
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
		src.m_right = src.m_left + BLOCK_SIZE;
		src.m_bottom = src.m_top + BLOCK_SIZE;

		dst.m_top = m_py + 0.0f;
		dst.m_left = m_px + scroll->GetScroll() +0.0f;
		dst.m_right = dst.m_left + BLOCK_SIZE;
		dst.m_bottom = dst.m_top + BLOCK_SIZE;

		Draw::Draw(23, &src, &dst, c, 0.0f);


		//���Ŕ����`��

		RECT_F src2;	//�`�挳�؂���ʒu
		RECT_F dst2;	//�`���\���ʒu

		src2.m_top = 0.0f;
		src2.m_left = 0.0f + BOARDCUT_SIZE * b_num;
		src2.m_right = src2.m_left + BOARDCUT_SIZE;
		src2.m_bottom = src2.m_top + BOARDCUT_SIZE;

		dst2.m_top = BOARDDRAW_SIZE_T;
		dst2.m_left = m_px + scroll->GetScroll() - (BLOCK_SIZE + 1);
		dst2.m_right = dst2.m_left + BOARDDRAW_SIZE_R;
		dst2.m_bottom = dst2.m_top + BOARDDRAW_SIZE_B;
		if (T_Sensor == true)
		{
			Draw::Draw(50, &src2, &dst2, c, 0.0f);
		}

		//�K�C�h�̕\���i�ʂ̃\�[�X�R�[�h�ō��j
		//RECT_F src_guide;	//�`�挳�؂���ʒu
		//RECT_F dst_guide;	//�`���\���ʒu

		//src_guide.m_top = 0.0f;
		//src_guide.m_left = 0.0f;
		//src_guide.m_right = src_guide.m_left + 600.0f;
		//src_guide.m_bottom = src_guide.m_top + 32.0f;

		//dst_guide.m_top = 0.0f;
		//dst_guide.m_left = 200.0f;
		//dst_guide.m_right = dst_guide.m_left + 600.0f;
		//dst_guide.m_bottom = dst_guide.m_top + 32.0f;

		//Draw::Draw(0, &src_guide, &dst_guide, c, 0.0f);
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

