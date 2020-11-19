//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "Obj_G_Block5.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObj_G_Block5::CObj_G_Block5(float x, float y)
{
	m_px = x;	//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObj_G_Block5::Init()
{
	G5_flag = false;			//false������Btrue������

	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
}

//�A�N�V����
void CObj_G_Block5::Action()
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



	//��l����G5_BLOCK�̂����蔻��`�F�b�N
	//�������Ă���ꍇ
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//G5_BLOCK�̏ザ��Ȃ�����
		if (hy + (2 * BLOCK_SIZE - 8) > m_py)
		{
			//G5_BLOCK�̍������ɐڐG
			if (m_px + scroll->GetScroll() > hx)
			{
				hero->SetRight(true);
				hero->SetX(m_px - (BLOCK_SIZE + 0.5) + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
			//G5_BLOCK�̉E�����ɐڐG
			else if (hx > m_px + scroll->GetScroll())
			{
				hero->SetLeft(true);
				hero->SetX(m_px + (BLOCK_SIZE - 0.5) + scroll->GetScroll());
				hero->SetVX(0.0f);
			}
		}
		//G5_BLOCK�̏㕔���ɐڐG
		if (hy + (2 * BLOCK_SIZE - 1) <= m_py)
		{
			hero->SetDown(true);
			hero->SetY(m_py - (2 * BLOCK_SIZE + 0.5));
			hero->SetVY(0.0f);
		}
		//G5_BLOCK�̉������ɐڐG
		else if (m_py + (BLOCK_SIZE + 1) <= hy)
		{
			hero->SetUp(true);
			hero->SetY(m_py + (BLOCK_SIZE - 0.5));
			hero->SetVY(0.0f);
		}
	}

	coin_count = hero->GetCoin();

	if (coin_count >= 3)
	{
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			//�u���b�N�폜���ʉ�
			Audio::Start(8);

			this->SetStatus(false);		//�R�C��3���擾��ԂŎ�l�����G���ƍ폜
			Hits::DeleteHitBox(this);	//���L����HitBox���폜
		}
	}

}

//�h���[
void CObj_G_Block5::Draw()
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
	Draw::Draw(31, &src, &dst, c, 0.0f);
}
