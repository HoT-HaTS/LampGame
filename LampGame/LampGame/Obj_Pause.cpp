//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Pause.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;



//�C�j�V�����C�Y
void CObjPause::Init()
{
	//P_flag = true;
	mx = 0;
	my = 0;
}

//�A�N�V����
void CObjPause::Action()
{
	//flag��false�̂Ƃ����g�����ł�����
	if (pause_flag == false)
	{
		this->SetStatus(false);		//�X�C�b�`�������ꂽ�����
		//Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
		return;
	}
}

//�h���[
void CObjPause::Draw()
{
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 540.0f;
	src.m_bottom = 370.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 100.0f;
	dst.m_left = 150.0f;
	dst.m_right = dst.m_left + 500.0f;
	dst.m_bottom = dst.m_top + 400.0f;

	//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(13, &src, &dst, c, 0.0f);
}