#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define PAUSE_DRAW_SIZE_T (10.0f)
#define PAUSE_DRAW_SIZE_L (15.0f)
#define PAUSE_DRAW_SIZE_R (775.0f)
#define PAUSE_DRAW_SIZE_B (580.0f)

//�I�u�W�F�N�g�F
class CObjPause : public CObj
{
public:
	CObjPause() {};
	~CObjPause() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	float mx;
	float my;
	bool P_flag;
};


