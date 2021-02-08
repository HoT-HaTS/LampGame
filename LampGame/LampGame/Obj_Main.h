#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define DEAD_TIME (60)
#define ADD_ALPHA (0.02f)
#define SRC_BLACK_R (8.0f)
#define SRC_BLACK_B (6.0f)
#define SRC_GUIDE_R (600.0f)
#define SRC_GUIDE_B (32.0f)
#define DST_GUIDE_L (200.0f)
#define DST_GUIDE_R (600.0f)
#define DST_GUIDE_B (32.0f)

//�I�u�W�F�N�g�F
class CObjMain : public CObj
{
public:
	CObjMain() {};
	~CObjMain() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	bool m_flag;
	int coin_count;

	//�S�[�����o�p�̕ϐ�
	float dead_alpha;
	float in_alpha;
	float d_time;
	bool g_flag;
	bool ga_flag;
	bool d_flag;
};