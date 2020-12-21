#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define BG_NUM (7)
#define BG_LAST (1)

#define INIT_ALPHA_BLACK (1.0f)
#define INIT_ALPHA_WHITE (0.0f)
#define MAX_ALPHA (1.0f)

#define INIT_H_ANI_TIME (0)
#define INIT_H_ANI_FRAME (0)

#define MAX_H_ANI_TIME (10)
#define MAX_H_ANI_FRAME (4)

#define PLUS__ALPHA_BLACK (0.005f)
#define PLUS__ALPHA_WHITE (0.02f)

#define SRC_BLACK_TOP (600.0f)
#define SRC_BLACK_LEFT (0.0f)
#define SRC_WHITE_TOP (0.0f)
#define SRC_WHITE_LEFT (0.0f)

#define BG_X_SIZE (800.0f)
#define BG_Y_SIZE (600.0f)

#define CLEAR_BG_SRC_TOP (200.0f)
#define CLEAR_BG_SRC_LEFT (150.0f)
#define CLEAR_BG_X_SIZE (450.0f)
#define CLEAR_BG_Y_SIZE (250.0f)

#define CLEAR_TEXT_DST_TOP (50.0f)
#define CLEAR_TEXT_DST_LEFT (50.0f)
#define CLEAR_TEXT_X_SIZE (700.0f)
#define CLEAR_TEXT_Y_SIZE (200.0f)

#define CLEAR_HERO_DST_TOP (300.0f)
#define CLEAR_HERO_DST_LEFT (336.0f)
#define CLEAR_HERO_X_SIZE (64.0f)
#define CLEAR_HERO_Y_SIZE (128.0f)


//�I�u�W�F�N�g�F�^�C�g��
class CObjClear : public CObj
{
public:
	CObjClear() {};
	~CObjClear() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

private:
	int scene_num;	//�`��p�̔w�i�p�ԍ�
	float alpha_b;	//�����x

	bool white_out;
	bool white;
	bool w_end;

	int h_ani_frame;
	int h_ani_time;

	float alpha_w;

	bool m_key_flag;  //�L�[�t���O
};