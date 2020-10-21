#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�v���g�^�C�v�錾
bool UnitVec(float* vx, float* vy);	//�x�N�g���̐��K�����s���֐�

bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);	//�̈���O���ǂ������ׂ�֐�

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

void BlockDraw(float x, float y, RECT_F* dst, float c[]);

float Dot(float ax, float ay, float bx, float by);		//����
float Cross(float ax, float ay, float bx, float by);	//�O��

//���Ɛ��ƌ�������
bool LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float* out_px, float* out_py
);


int m_map[10][100];
float m_scroll;