//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_Switch.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

 CObjSwitch::CObjSwitch(float x, float y)
{
	 m_px = x;			//�ʒu
	 m_py = y;
}


//�C�j�V�����C�Y
void CObjSwitch::Init()
{
	m_scroll = 0.0f;

	S_flag = false;			//�X�C�b�`���I�t�̂Ƃ���false�A�I���̂Ƃ���true

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_SWITCH, OBJ_SWITCH, 1);
}

//�A�N�V����
void CObjSwitch::Action()
{
	if (Input::GetVKey('A') == true)
	{
		S_flag == true;
	}

	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���̈ʒu�̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//��l���̏Փˊm�F�p�̃t���O�̏�����
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//��l��������t���O������Ă���
	bool L_flag_switch = hero->Get_L_flag();

	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px+scroll->GetScroll(), m_py);

	//��l���ƃX�C�b�`�̂����蔻��`�F�b�N
	//�������Ă���ꍇ

	/*
	//�X�N���[���̉e��
	float scroll = scroll_on ? m_scroll : 0;

	//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��(�u���b�N�̍�:�E:��:���̏�)
	if ((hx + (-scroll) + 64.0f > m_px) && (hx + (-scroll) < m_px + 64.0f) && (hy + 128.0f > m_py) && (hy < m_py + 64.0f))
	{
		//�㉺���E����

		//��l���ƃu���b�N�̒��S��vector�쐬
		float rvx = (hx + (-scroll) + 32.0f) - (m_px + 32.0f);
		float rvy = (hy + 64.0f) - (m_py + 32.0f);

		//����len�����߂�
		float len = sqrt(rvx * rvx + rvy * rvy);

		//�p�xr�����߂�
		float r = atan2(rvy, rvx);	//(���W�A��)
		r = r * 180.0f / 3.14f;		//�x

		if (r <= 0.0f)
			r = abs(r);
		else
			r = 360.0f - abs(r);

		//len��������̒������Z���ꍇ�ɔ���ɓ���B
		if (len < 111.0f)
		{
			//�p�x�ŏ㉺���E�𔻒�
			if ((r < 56 && r >= 0) || r > 304)
			{
				//�E
				hero->SetRight(true);	//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
				hx = m_px + 64.0f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
				*vx = -(*vx) * 0.1f;	//-VX*�����W��
			}
			if (r > 56 && r < 124)
			{
				//��
				hero->SetDown(true);	//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
				hy = m_py - 128.0f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
				*vy = 0.0f;
			}
			if (r > 124 && r < 236)
			{
				//��
				hero->SetLeft(true);	//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
				hx = m_px - 64.0f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
				*vx = -(*vx) * 0.1f;	//-VX*�����W��
			}
			if (236 < r && r < 304)
			{
				//��
				hero->SetUp(true);	//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
				hy = m_py + 64.0f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
				if (hy < 0)
				{
					*vy = 0.0f;
				}
			}
		}
	}*/
	
	/*
	if ((hit->CheckObjNameHit(OBJ_HERO) != nullptr)&&(L_flag_switch==false))
	{
		//�X�C�b�`�̍������ɐڐG

		if ((m_px+10 > hx + 64) && (m_px  > hx ))
		{
			hero->SetRight(true);

			hero->SetX(m_px - 64 + scroll->GetScroll());
			hero->SetVX(0.0f);
		}

		//�X�C�b�`�̉E�����ɐڐG
		if ((m_px + 54 < hx) && (m_px+64 < hx+64))
		{
			hero->SetLeft(true);
			hero->SetX(m_px + 64 + scroll->GetScroll());
			hero->SetVX(0.0f);
		}

		//�X�C�b�`�̏㕔���ɐڐG
		if ((m_py +10 > hy + 128) && (m_py  > hy))
		{
			hero->SetDown(true);
			hero->SetY(m_py - 128 + scroll->GetScroll());
			hero->SetVY(0.0f);
		}

		//�X�C�b�`�̉������ɐڐG
		if ((m_py + 54 < hy) && (m_py < hy+128))
		{
			hero->SetUp(true);
			hero->SetY(m_py+64 + scroll->GetScroll());
			hero->SetVY(0.0f);
		}
	}
	*/
	
	//�X�C�b�`�������ꂽ��t���O�؂�ւ��A�X�C�b�`������
	//HitBox�̓��e���X�V
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_px, m_py);

	if (hit->CheckObjNameHit(OBJ_ATTACK) != nullptr)
	{
		S_flag = true;				//�X�C�b�`�̃t���O��true��
		this->SetStatus(false);		//�X�C�b�`�������ꂽ�����
		Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
	}

}

//�h���[
void CObjSwitch::Draw()
{
	int switch_graphic;		//�e�ƌ��ŃX�C�b�`�̕`���ς��邽�߂̐����A���������ł����g��Ȃ����߁A�����Ő錾���Ă���
	
    //�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

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
	src.m_top = 0.0f;
	src.m_left = 0.0f + (switch_graphic * 64.0f);
	src.m_right = 64.0f +(switch_graphic * 64.0f);
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(10, &src, &dst, c, 0.0f);
}

