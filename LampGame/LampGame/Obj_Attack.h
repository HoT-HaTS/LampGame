#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

#define INIT_ANI_TIME (0.0)		//�A�j���[�V�����^�C��	
#define INIT_ANI_FLAME (0.0)	//�A�j���[�V�����t���[��

#define INIT_A_POSTURE (1.0)	//�U������

#define ABLOCK_INT_X_SIZE (64.0f)	//�U�����T�C�Y
#define ABLOCK_INT_Y_SIZE (64.0f)	//�U���c�T�C�Y

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObjAttack : public CObj
{
public:
	CObjAttack(float x, float y);
	~CObjAttack() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	int m_ani_frame;		//�A�j���[�V�����^�C��
	int m_ani_time;		//�A�j���[�V�����t���[��

	int m_posture;		//�U���̌���(1�ŉE�A0�ō�)

	float m_px;			//�ʒu
	float m_py;
};

