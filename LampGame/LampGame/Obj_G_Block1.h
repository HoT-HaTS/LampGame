#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObj_G_Block : public CObj
{
	public:
		CObj_G_Block(float x, float y);
		~CObj_G_Block() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

	
		//�u���b�N�Ƃ̓����蔻��
		void BlockHit
		(
			float* x, float* y, bool scroll_on,
			bool* up, bool* down, bool* left, bool* right,
			float* vx, float* vy, int* bt
		);

		//��l���ƕǂ̌�������
		bool HeroBlockCrossPoint(
			float x, float y, float vx, float vy,
			float* out_px, float* out_py, float* out_len
		);
	private:
		float m_px;			//�ʒu
		float m_py;

		//���Ɛ��ƌ�������
		bool LineCrossPoint(
			float a1x, float a1y, float a2x, float a2y,
			float b1x, float b1y, float b2x, float b2y,
			float* out_px, float* out_py
		);
};

