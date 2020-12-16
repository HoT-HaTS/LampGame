//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle :: Init()
{
	m_key_flag = false;

	((UserData*)Save::GetData())->clear[6] = { false };

}

//�A�N�V����
void CObjTitle::Action()
{
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneSelect());
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//�h���[
void CObjTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 422.0f;
	src.m_bottom = src.m_top + 62.0f;

	dst.m_top = 460.0f;
	dst.m_left = 189.0f;
	dst.m_right = dst.m_left + 422.0f;
	dst.m_bottom = dst.m_top + 62.0;

	Draw::Draw(15, &src, &dst, c, 0.0f);
}