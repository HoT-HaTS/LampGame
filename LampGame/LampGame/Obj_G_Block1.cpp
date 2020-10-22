//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

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

}

//�A�N�V����
void CObj_G_Block::Action()
{
		
}

//�h���[
void CObj_G_Block::Draw()
{
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 320.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f; +m_px;
	dst.m_left = 0.0f; +m_py;
	dst.m_right = 32.0f; +m_px;
	dst.m_bottom = 320.0f; +m_py;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
}