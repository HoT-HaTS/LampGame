//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_Main.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;



//�C�j�V�����C�Y
void CObjMain::Init()
{
	 m_flag = true;
}

//�A�N�V����
void CObjMain::Action()
{

	//R�L�[���͂Ń��g���C
	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false)
	{
		if (Input::GetVKey('R') == true)
		{
			Scene::SetScene(new CSceneStage_1());
			pause_flag = false;
		}	
	
	}


	//�|�[�Y�p
	if (Input::GetVKey('P') == true)
	{

		if (m_flag == true && pause_flag == false)
		{
			pause_flag = true;
			m_flag = false;
			CObjPause* obj_pause = new CObjPause();
			Objs::InsertObj(obj_pause, OBJ_PAUSE, 99);
		}
		else if (m_flag == true && pause_flag == true)
		{
			pause_flag = false;
			m_flag = false;
		}
	}
	else
	{
		m_flag = true;
	}	
}

//�h���[
void CObjMain::Draw()
{

}