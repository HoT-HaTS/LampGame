//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "Obj_Goalscene.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGoalscene::Init()
{
	//P_flag = true;
	mx = 0;
	my = 0;
	alpha = 0.0f;
	s_flag = true;
}

//�A�N�V����
void CObjGoalscene::Action()
{

}

//�h���[
void CObjGoalscene::Draw()
{
	

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, alpha };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = WINDOW_SIZE_X;
	src.m_bottom = WINDOW_SIZE_Y;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + WINDOW_SIZE_X;
	dst.m_bottom = dst.m_top + WINDOW_SIZE_Y;

	//flag��true�̎��A���o�J�n
	if (s_flag==true)
	{
		alpha += 0.01f;
		//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(61, &src, &dst, c, 0.0f);
		if (alpha >= 1.0f)
			s_flag = false;
	}
	else
	{
		alpha += ALPHA_MINUS;
		//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(61, &src, &dst, c, 0.0f);

		//�X�e�[�W�N���A�e���b�v�\��
		if (alpha <= 0.0f)
		{
			//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
			float  c_sc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

			RECT_F src_sc;	//�`�挳�؂���ʒu
			RECT_F dst_sc;	//�`���\���ʒu

			//�؂���ʒu�̐ݒ�
			src_sc.m_top = 0.0f;
			src_sc.m_left = 0.0f;
			src_sc.m_right = CLEARTELOP_SIZE_X;
			src_sc.m_bottom = CLEARTELOP_SIZE_Y;

			//�\���ʒu�̐ݒ�
			dst_sc.m_top = CLEARTELOP_POS_Y;
			dst_sc.m_left = CLEARTELOP_POS_X;
			dst_sc.m_right = dst_sc.m_left + CLEARTELOP_SIZE_X;
			dst_sc.m_bottom = dst_sc.m_top + CLEARTELOP_SIZE_Y;
			Draw::Draw(63, &src_sc, &dst_sc, c_sc, 0.0f);
			Audio::Start(13);
		}
			
	}
	
}