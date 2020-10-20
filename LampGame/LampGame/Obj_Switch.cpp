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



//�C�j�V�����C�Y
void CObjSwitch::Init()
{
	m_px = 0.0f;			//�ʒu
	m_py = 0.0f;

	S_flag = false;			//�X�C�b�`���I�t�̂Ƃ���false�A�I���̂Ƃ���true

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_SWITCH, OBJ_SWITCH, 1);
}

//�A�N�V����
void CObjSwitch::Action()
{
	//��l���̈ʒu�̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//��l���̏Փˊm�F�p�̃t���O�̏�����
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//��l���ƃX�C�b�`�̂����蔻��`�F�b�N
	if ((m_px + 64 > hx) && (hx + 64 > m_px) && (m_py + 64 > hy) && (hy + 64 > m_py))
	{
		//�������Ă���ꍇ

		//�x�N�g���̍쐬
		float vx = hx - m_px;
		float vy = hx - m_py;

		//���������߂�
		float len = sqrt(vx * vx + vy * vy);
		
		//�p�x�����߂�
		float r = atan2(vy, vx);
		r = r * 180.0f / 3.14f;

		if (r <= 0.0f)
			r = abs(r);
		else
			r = 360.0f - abs(r);

		//len��������̒������Z���ꍇ�ɔ���ɓ���
		if (len < 88.0f)
		{

			//���߂��p�x�ŏ㉺���E�𔻒�
			//�X�C�b�`����l���̍������ɐڐG
			if ((r < 45 && r>0) || r > 315)
			{
				hero->SetLeft(true);
				hero->SetX(hx + 64);
				hero->SetVX(0.0f);
			}

			//�X�C�b�`����l���̏㕔���ɐڐG
			if (r > 225 || r < 315)
			{
				hero->SetUp(true);
				hero->SetY(hy);
				hero->SetVY(0.0f);
			}

			//�X�C�b�`����l���̉������ɐڐG
			if (r > 45 || r < 135)
			{
				hero->SetDown(true);
				hero->SetY(hy + 64);
				hero->SetVY(0.0f);
			}

			//�X�C�b�`����l���̉E�����ɐڐG
			if (r > 135 || r < 225)
			{
				hero->SetRight(true);
				hero->SetX(hx);
				hero->SetVX(0.0f);
			}
		}

	}

	//�X�C�b�`�������ꂽ��t���O�؂�ւ��A�X�C�b�`������
	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);

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
	int switch_graphic;		//�e�ƌ��ŃX�C�b�`�̕`���ς��邽�߂̐���

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
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 64.0f;
	dst.m_bottom = 64.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(10, &src, &dst, c, 0.0f);
}