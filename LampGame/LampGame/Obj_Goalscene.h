#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

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

