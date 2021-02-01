#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define WINDOW_SIZE_X (800.0f)
#define WINDOW_SIZE_Y (600.0f)

#define ALPHA_MINUS (-0.01f)

#define CLEARTELOP_SIZE_X (700.0f)
#define CLEARTELOP_SIZE_Y (200.0f)

#define CLEARTELOP_POS_X (50.0f)
#define CLEARTELOP_POS_Y (100.0f)

//�I�u�W�F�N�g�F
class CObjGoalscene : public CObj
{
public:
	CObjGoalscene() {};
	~CObjGoalscene() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

	bool GetS_Flag() { return s_flag; }
private:
	float mx;
	float my;
	float alpha;
	bool s_flag;
};

