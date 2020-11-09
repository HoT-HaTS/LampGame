//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "Obj_KeyCoin.h"
#include "Obj_Stage1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjKeycoin::CObjKeycoin(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjKeycoin::Init()
{
	Hits::SetHitBox(this, m_px, m_py, 64.0f, 64.0f, ELEMENT_COIN, OBJ_COIN, 1);
	m_ani_time = 0;
	m_ani_frame = 0;

	coin_count = 0;
}

//�A�N�V����
void CObjKeycoin::Action()
{
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	m_ani_time++;

	if (m_ani_time % 10 == 0)
	{
		m_ani_frame++;
	}
	if (m_ani_time == 40)
	{
		m_ani_time, m_ani_frame = 0;
	}


	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	//��l���̈ʒu�̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	coin_count = hero->GetCoin();

	//��l���ƐڐG��������ł���B
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		coin_count++;
		hero->SetCoin(coin_count);
	}

}

//�h���[
void CObjKeycoin::Draw()
{
	int background_flag = 0;

	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu



	src.m_top = 0.0f;
	src.m_left = 0.0f + (64.0 * m_ani_frame);
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	dst.m_top = m_py + 0.0f;
	dst.m_left = m_px + scroll->GetScroll() + 0.0f;
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	Draw::Draw(30, &src, &dst, c, 0.0f);
}