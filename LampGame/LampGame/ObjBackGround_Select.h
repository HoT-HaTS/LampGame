#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define CUTOUT_X (896.0f)
#define CUTOUT_Y (640.0f)
#define DRAW_X (800.0f)
#define DRAW_Y (600.0f)

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