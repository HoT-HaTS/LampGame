#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define INIT_H_VX (0.0f)		//��l�����x
#define INIT_H_VY (0.0f)
#define INIT_H_PX (64.0f)		//��l���ʒu
#define INIT_H_PY (350.0f)

#define INIT_H_POSTURE (1.0)	//��l������

#define INIT_ANI_TIME (0.0)		//�A�j���[�V�����^�C��	
#define INIT_ANI_FLAME (0.0)	//�A�j���[�V�����t���[��

#define INIT_SPEED_POWER (1.2)	//���Z���x
#define INIT_ANI_MAX_TIME (5.0)	

#define INIT_FRICTION (0.2)	//���C�W��

#define BLOCK_TYPE_U (0.0)	//�u���b�N�̎�ގ��ʗp(��)
#define BLOCK_TYPE_G (0.0)	//�u���b�N�̎�ގ��ʗp(�E)

#define HBLOCK_INT_X_SIZE (64.0f)	//��l�����T�C�Y
#define HBLOCK_INT_Y_SIZE (128.0f)//��l���c�T�C�Y
#define STAGE_Y_OUT (800.0f)	//�������X�e�[�W�O����

#define H_GOAL_BLOCK (2)

//�x�N�g���̐��K�����s���֐�
bool UnitVec(float* vx, float* vy);

//�I�u�W�F�N�g�F
class CObjHero : public CObj
{
	public:
		CObjHero() {};
		~CObjHero() {};
		void SetX();
		void SetY();
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

		//�֐�
		float GetX() { return m_px; }
		float GetY() { return m_py; }
		float GetVY() { return m_vy; }
		float GetVX() { return m_vx; }
		int GetBT_U() { return m_block_type_under; }
		int GetBT_G() { return m_block_type_goal; }

		float GetPosture() { return m_posture; }

		bool Get_L_flag(){ return L_flag; }

		void SetX(float x) { m_px = x; }
		void SetY(float y) { m_py = y; }
		void SetVY(float vy) { m_vy = vy; }
		void SetVX(float vx) { m_vx = vx; }
		void SetBT_U(int t1) { m_block_type_under = t1; }
		void SetBT_G(int t2) { m_block_type_goal = t2; }

		void SetUp(bool b) { m_hit_up = b; }
		void SetDown(bool b) { m_hit_down = b; }
		void SetLeft(bool b) { m_hit_left = b; }
		void SetRight(bool b) { m_hit_right = b; }

		void SetDown2(bool b) { m_hit_down2 = b; }

		//�R�C���֌W
		int GetCoin() { return m_coin_count; }      //�R�C�������m�F�p
		void SetCoin(int p) { m_coin_count = p; }
		
	private:
		float m_px;			//�ʒu
		float m_py;
		float m_vx;			//�ړ��x�N�g��
		float m_vy;
		float m_sx;			//���E�؂�ւ����̈ʒu
		float m_sy;

		float m_posture;	//�p��

		float m_ani_time;	//�A�j���[�V�����t���[������Ԋu
		float m_ani_s_time;	//�X�g�b�v�A�j���[�V�����t���[������Ԋu
		int m_ani_frame;	//�`��t���[��
		int m_ani_s_frame;	//�X�g�b�v�A�j���[�V�����`��t���[��

		float m_speed_power;	//�X�s�[�h�p���[
		float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

		int time;				//���E�؂�ւ�����p����

		int m_coin_count;		//�R�C�������m�F�p

		//block�Ƃ̏Փˏ�Ԋm�F�p
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;

		bool m_hit_down2;

		bool attack_flag;	//�U������p�t���O

		//���̐��E�t���O
		bool L_flag;
		//���̐��E����p�t���O
		bool m_flag;

		//����ł���block�̎�ފm�F�p
		int m_block_type_under;
		int m_block_type_goal;

		void HeroMove(float mx, float my, float sx, float sy, float vx, float vy);
		float GetAtan2Angle(float w, float h);
		bool UnitVec(float* vx, float* vy);

		//�e�����ړ��p
		bool move_flag;		//��l���̑�����󂯕t����t���O
		float x;			//x�x�N�g��
		float y;			//y�x�N�g��
		float ar;			//�ړ����ƈړ���̊p�x
};