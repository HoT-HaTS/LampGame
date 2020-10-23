//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObj_G_Block::CObj_G_Block(float x, float y)
{
	m_px = x;	//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObj_G_Block::Init()
{
	G_flag = false;			//false������Btrue������

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//�A�N�V����
void CObj_G_Block::Action()
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


	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//��l����G_Block�̂����蔻��`�F�b�N
	//�������Ă���ꍇ
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
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
				hero->SetX(m_px - 64 + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
			//�X�C�b�`�̉E�����ɐڐG
			else if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + 64 + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
		}
		//�X�C�b�`�̏㕔���ɐڐG
		if (hy + 127 <= m_py)
		{
			hero->SetDown(true);
			hero->SetY(m_py - 128);
			hero->SetVY(0.0f);
		}
		//�X�C�b�`�̉������ɐڐG
		else if (m_py + 65 <= hy)
		{
			hero->SetUp(true);
			hero->SetY(m_py + 64);
			hero->SetVY(0.0f);
		}
	}


	//�X�C�b�`�������ꂽ��t���O�؂�ւ��A�M�~�b�N�u���b�N������
	CObjSwitch* sflag = (CObjSwitch*)Objs::GetObj(OBJ_SWITCH);
	 G_flag = sflag->Get_S_flag();

	if (G_flag == true)
	{
		this->SetStatus(false);		//�X�C�b�`�������ꂽ�����
		Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
	}

}

//�h���[
void CObj_G_Block::Draw()
{
	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

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

	//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
}