//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle :: Init()
{
	m_key_flag = false;

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
		Font::StrDraw(L"�����v�̗d���Ɖe�̐��E", 224, 250, 32, c);

		Font::StrDraw(L"GameStart : Push_EnterKey", 200, 400, 32, c);
	}