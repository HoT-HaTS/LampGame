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

	//HitBox�쐬
	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_G_BLOCK3, 1);
}

//�A�N�V����
void CObj_G_Block3::Action()
{
	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���̏��̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l���̏Փˊm�F�p�̃t���O�̏�����
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//��or�e�̏��������Ă���
	L_flag = hero->Get_L_flag();

	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//��l����G_Block�̂����蔻��`�F�b�N
	//�������Ă���ꍇ
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//��l���̈ʒu�擾
		float hx = hero->GetX();
		float hy = hero->GetY();

		hero->SetDown2(false);

		//G_Block�̏�or������Ȃ�����
		if (hy + 120 > m_py ) //|| m_py + 50 < hy)
		{
			//G_Block�̍������ɐڐG
			if (m_px + scroll->GetScroll() > hx)
			{
				hero->SetRight(true);
				hero->SetX(m_px - 64.5 + scroll->GetScroll());
				hero->SetVX(-0.8);
				hero->SetVY(0.0);
			}
			//G_Block�̉E�����ɐڐG
			if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + 63.5 + scroll->GetScroll());
				hero->SetVX(0.0);
				hero->SetVY(0.0);
			}
		}
			//G_Block�̏㕔���ɐڐG
			if (hy + 125 < m_py)
			{
				hero->SetDown2(true);
				hero->SetY(m_py - 128.5);
				hero->SetVY(0.0);
			}
			//G_Block�̉������ɐڐG
			if (m_py + 55 < hy)
			{
				hero->SetUp(true);
				hero->SetY(m_py + 64.5);
				hero->SetVY(0.0);
			}
	}
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
	src.m_right = 64.0;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	if (L_flag == false)
	{	
		//4�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
}