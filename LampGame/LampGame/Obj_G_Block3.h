#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObj_G_Block3 : public CObj
{
public:
	CObj_G_Block3(float x, float y);
	~CObj_G_Block3() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[


private:
	bool L_flag;

	float m_px;			//�ʒu
	float m_py;

};


