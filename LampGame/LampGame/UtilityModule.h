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

void BlockDraw(float x, float y, RECT_F* dst, float c[]);

int Map[10][100];
float Scroll;