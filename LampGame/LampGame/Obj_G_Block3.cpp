//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block3.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObj_G_Block3::CObj_G_Block3(float x, float y)
{
	m_px = x;	//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObj_G_Block3::Init()
{
	//false���e�Btrue����
	L_flag = true;

	m_scroll = 0;
}

//�A�N�V����
void CObj_G_Block3::Action()
{
	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	m_scroll = scroll->GetScroll();


	//��l���̏��̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��or�e�̏��������Ă���
	L_flag = hero->Get_L_flag();

}

//�h���[
void CObj_G_Block3::Draw()
{
	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���̏��̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	L_flag = hero->Get_L_flag();

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = BLOCK_SIZE;
	src.m_bottom = BLOCK_SIZE;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	if (L_flag == false)
	{
		//4�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
}
