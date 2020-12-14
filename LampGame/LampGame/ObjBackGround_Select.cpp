//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjBackGround_Select.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjBackGround_Select::Init()
{

}

//�A�N�V����
void CObjBackGround_Select::Action()
{
	
}

//�h���[
void CObjBackGround_Select::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,0.5f };	//�Z���N�g��ʂ�BG
	
	RECT_F src;		//�X�e�[�W�Z���N�g�w�i�`�挳�؂���ʒu
	RECT_F dst;		//�X�e�[�W�Z���N�g�w�i�`���\���ʒu

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 896.0f;
	src.m_bottom = src.m_top + 640.0f;

	dst.m_top = 0;
	dst.m_left = 0;
	dst.m_right = dst.m_left + 800;
	dst.m_bottom = dst.m_top + 600.0f;
	Draw::Draw(10, &src, &dst, c, 0.0f);
}