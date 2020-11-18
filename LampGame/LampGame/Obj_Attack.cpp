//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_Attack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjAttack::CObjAttack(float x, float y)
{
	m_px = x + ABLOCK_INT_X_SIZE;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjAttack::Init()
{
	m_ani_time = INIT_ANI_TIME;		//�A�j���[�V�����^�C���̏�����
	m_ani_frame = INIT_ANI_FRAME;	//�A�j���[�V�����t���[���̏�����

	m_vx = 0;
	m_vy = 0;

	m_posture = 0.0f;

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);		//Obj_Hero�����l���̌���������Ă���
	m_posture = hero->GetPosture();


	//������HitBox�̈ʒu��ς���
	if (m_posture)
		Hits::SetHitBox(this, m_px- ABLOCK_INT_Y_SIZE, m_py, ABLOCK_INT_X_SIZE-4, ABLOCK_INT_Y_SIZE, ELEMENT_ATTACK, OBJ_ATTACK, 1);
	else
		Hits::SetHitBox(this, m_px- ABLOCK_INT_Y_SIZE, m_py, ABLOCK_INT_X_SIZE-4, ABLOCK_INT_Y_SIZE, ELEMENT_ATTACK, OBJ_ATTACK, 1);

}

//�A�N�V����
void CObjAttack::Action()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	m_posture = hero->GetPosture();

	m_px = hero->GetX() + (m_posture * ABLOCK_INT_X_SIZE);
	m_py = hero->GetY();

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px, m_py);

	//�A�j���[�V�����̒���
	m_ani_time += 1;
	if (m_ani_time % 3 == 0)
	{
		m_ani_frame += 1;
	}

	//������HitBox�̈ʒu��ς���
	if (m_posture)
	{
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px, m_py);
	}
	else
	{
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px - ABLOCK_INT_X_SIZE, m_py);
	}

	//�A�j���[�V�����I����ɃI�u�W�F�N�g��j������
	if (m_ani_frame >= 8)
	{
		this->SetStatus(false);		//�X�C�b�`�������ꂽ�����
		Hits::DeleteHitBox(this);	//�X�C�b�`�����L����HitBox���폜
	}
}

//�h���[
void CObjAttack::Draw()
{
	//�A�j���[�V�����ԍ�
	int AniData[7] =
	{
		0,1,2,3,4,5,6
	};

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	{
		src.m_top = ABLOCK_INT_X_SIZE;
		src.m_left = 0.0f + AniData[m_ani_frame] * ABLOCK_INT_X_SIZE;
		src.m_right = ABLOCK_INT_X_SIZE + AniData[m_ani_frame] * ABLOCK_INT_X_SIZE;
		src.m_bottom = src.m_top + ABLOCK_INT_X_SIZE;
	}

	//�\���ʒu�̐ݒ�@�����ŕ\���ʒu��ς���
	if (m_posture)
	{
		dst.m_top = 0.0f + m_py;
		dst.m_left = (ABLOCK_INT_X_SIZE - ABLOCK_INT_X_SIZE * m_posture) + m_px;
		dst.m_right = (ABLOCK_INT_X_SIZE * m_posture) + m_px;
		dst.m_bottom = ABLOCK_INT_X_SIZE + m_py;
	}
	else
	{
		dst.m_top = 0.0f + m_py;
		dst.m_left = (ABLOCK_INT_X_SIZE - ABLOCK_INT_X_SIZE * m_posture) + m_px - ABLOCK_INT_X_SIZE;
		dst.m_right = (ABLOCK_INT_X_SIZE * m_posture) + m_px - ABLOCK_INT_X_SIZE;
		dst.m_bottom = ABLOCK_INT_X_SIZE + m_py;
	}

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(11, &src, &dst, c, 0.0f);
}