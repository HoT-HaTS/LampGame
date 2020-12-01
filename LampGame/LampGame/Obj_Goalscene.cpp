//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

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
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + 800.0f;
	dst.m_bottom = dst.m_top + 600.0f;

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
		alpha -= 0.01f;
		//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(61, &src, &dst, c, 0.0f);
			
	}
	
}