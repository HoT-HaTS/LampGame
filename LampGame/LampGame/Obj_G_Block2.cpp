//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block2.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObj_G_Block2::CObj_G_Block2(float x, float y)
{
	m_px = x;	//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObj_G_Block2::Init()
{
	G2_flag = false;			//false������Btrue�����ŁB
	a_flag = false;				//true��HitBox�쐬�\�Bfalse���쐬�s�B

	l_f = true;

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//�A�N�V����
void CObj_G_Block2::Action()
{
	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���̈ʒu�̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	G2_flag = switch_flag;

	if (G2_flag == false)
	{
		Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
		a_flag = true;
	}
	else if (G2_flag == true)
	{
		if (a_flag == true)
		{
			Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
			a_flag = false;
		}
		//��l���̏Փˊm�F�p�̃t���O�̏�����
		hero->SetUp(false);
		hero->SetDown(false);
		hero->SetLeft(false);
		hero->SetRight(false);

		//HitBox�̓��e���X�V
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + scroll->GetScroll(), m_py);
	}
}

//�h���[
void CObj_G_Block2::Draw()
{
	//��l��������t���O���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool l_f = hero->Get_L_flag();

	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = BLOCK_SIZE;
	src.m_bottom = BLOCK_SIZE;

	if (switch_flag == true)
	{
		if (l_f == true)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px + scroll->GetScroll();
			dst.m_right = dst.m_left + BLOCK_SIZE;
			dst.m_bottom = dst.m_top + BLOCK_SIZE;

			//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
			Draw::Draw(3, &src, &dst, c, 0.0f);
		}
		else if (l_f == false)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px + scroll->GetScroll();
			dst.m_right = dst.m_left + BLOCK_SIZE;
			dst.m_bottom = dst.m_top + BLOCK_SIZE;

			//4�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
			Draw::Draw(4, &src, &dst, c, 0.0f);
		}
	}
}