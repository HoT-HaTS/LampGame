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
	m_px = x+64;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjAttack::Init()
{
	m_ani_time = INIT_ANI_TIME;		//�A�j���[�V�����^�C���̏�����
	m_ani_frame = INIT_ANI_FLAME;	//�A�j���[�V�����t���[���̏�����


	Hits::SetHitBox(this, m_px, m_py, ABLOCK_INT_X_SIZE, ABLOCK_INT_Y_SIZE+64, ELEMENT_ATTACK, OBJ_ATTACK,1);
}

//�A�N�V����
void CObjAttack::Action()
{
	
	m_ani_time += 1;
	if(m_ani_time)

	CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_px, m_py);

	//Todo:�A�j���[�V�����I����ɃI�u�W�F�N�g��j������
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
		src.m_top = HBLOCK_INT_Y_SIZE;
		src.m_left = 0.0f + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
		src.m_right = HBLOCK_INT_X_SIZE + AniData[m_ani_frame] * HBLOCK_INT_X_SIZE;
		src.m_bottom = src.m_top + HBLOCK_INT_Y_SIZE;
	}

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 64.0f;
	dst.m_bottom = 64.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(11, &src, &dst, c, 0.0f);
}