#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define SELECT_BG_X_SIZE (896.0f)
#define SELECT_BG_Y_SIZE (640.0f)

//�I�u�W�F�N�g�F�^�C�g��
class CObjBackGround_Select : public CObj
{
	public:
		CObjBackGround_Select() {};
		~CObjBackGround_Select() {};
		void Init();     //�C�j�V�����C�Y
		void Action();   //�A�N�V����
		void Draw();     //�h���[
	private:
};