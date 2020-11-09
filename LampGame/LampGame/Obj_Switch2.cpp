//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Switch2.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjSwitch2::CObjSwitch2(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}


//�C�j�V�����C�Y
void CObjSwitch2::Init()
{
	m_scroll = 0.0f;

	S2_flag = false;			//�X�C�b�`���I�t�̂Ƃ���false�A�I���̂Ƃ���true

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_SWITCH, OBJ_SWITCH, 1);
}

//�A�N�V����
void CObjSwitch2::Action()
{
	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���̈ʒu�̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);


	//��l���̏Փˊm�F�p�̃t���O�̏�����
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);



	//��l��������t���O������Ă���
	bool L_flag_switch = hero->Get_L_flag();

	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//��l���ƃX�C�b�`�̂����蔻��`�F�b�N
	//�������Ă���ꍇ
	if ((hit->CheckObjNameHit(OBJ_HERO) != nullptr) && (L_flag_switch == false))
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//�X�C�b�`�̏ザ��Ȃ�����
		if (hy + 120 > m_py)
		{
			//�X�C�b�`�̍������ɐڐG
			if (m_px + scroll->GetScroll() > hx)
			{
				hero->SetRight(true);
				hero->SetX(m_px - 64.5 + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
			//�X�C�b�`�̉E�����ɐڐG
			else if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + 63.5 + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
		}
		//�X�C�b�`�̏㕔���ɐڐG
		if (hy + 127 <= m_py)
		{
			hero->SetDown(true);
			hero->SetY(m_py - 128.5);
			hero->SetVY(0.0f);
		}
		//�X�C�b�`�̉������ɐڐG
		else if (m_py + 65 <= hy)
		{
			hero->SetUp(true);
			hero->SetY(m_py + 63.5);
			hero->SetVY(0.0f);
		}
	}

	//��l���̍U����HitBox�ɓ������flag��true�ɂ���
	if (hit->CheckObjNameHit(OBJ_ATTACK) != nullptr)
	{
		if (S2_flag == true)
		{
			S2_flag = false;				//�X�C�b�`�̃t���O��false��
		}
		else
		{
			S2_flag = true;				//�X�C�b�`�̃t���O��true��
		}
	}

	////flag��true�̂Ƃ����g�����ł�����
	//if (S2_flag == true)
	//{
	//	//this->SetStatus(false);		//�X�C�b�`�������ꂽ�����
	//	//Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
	//	return;
	//}

}

//�h���[
void CObjSwitch2::Draw()
{
	int switch_graphic;		//�e�ƌ��ŃX�C�b�`�̕`���ς��邽�߂̐����A���������ł����g��Ȃ����߁A�����Ő錾���Ă���

	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//Hero.cpp������t���O���擾����
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool L_flag_switch = hero->Get_L_flag();
	if (L_flag_switch == true)
		switch_graphic = 0;
	else
		switch_graphic = 1;


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f + (switch_graphic * 64.0f);
	src.m_left = 0.0f + (S2_flag * 64.0f);
	src.m_right = 64.0f + (S2_flag * 64.0f);
	src.m_bottom = 64.0f + (switch_graphic * 64.0f);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	//12�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(12, &src, &dst, c, 0.0f);
}