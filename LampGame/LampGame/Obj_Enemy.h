#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

using namespace GameL;

//�֐���
//�G�̃T�C�Y
#define E_XSIZE (64.0);
#define E_YSIZE (64.0);

//�ړ��x�N�g���̏�����
#define INIT_E_VX (0.0f);
#define INIT_E_VY (0.0f);

//�A�j���[�V�����֌W�̏�����
#define INIT_E_ANI_MAX_TIME (9.0);

#define INIT_E_SPEED_POWER (0.3f)

//�����̏�����
#define INIT_E_POSTURE (1.0f);

//�I�u�W�F�N�g�F
class CObjEnemy : public CObj
{
public:
	CObjEnemy(float x, float y);
	~CObjEnemy() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

	//�֐�
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }

	bool GetUp() { return m_hit_up; }
	bool GetDown() { return m_hit_down; }
	bool GetRight() { return m_hit_right; }
	bool GetLeft() { return m_hit_left; }

	float GetPosture() { return m_posture; }

	void SetX(float x) { m_px = x; }
	void SetY(float y) { m_py = y; }
	void SetVY(float vy) { m_vy = vy; }
	void SetVX(float vx) { m_vx = vx; }


	void SetUp(bool b) { m_hit_up = b; }
	void SetDown(bool b) { m_hit_down = b; }
	void SetLeft(bool b) { m_hit_left = b; }
	void SetRight(bool b) { m_hit_right = b; }


private:
	float m_px;			//�ʒu
	float m_py;
	float m_vx;			//�ړ��x�N�g��
	float m_vy;
	float m_posture;	//�p��

	int m_ani_time;		//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;	//�`��t���[��

	float m_speed_power;	//�X�s�[�h�p���[
	float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool E_flag;

	//�ړ��̌����̐���p
	bool m_move;
};

