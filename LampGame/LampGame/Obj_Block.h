#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[10][100]);	
	~CObjBlock() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
	void  SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	//int GetMap() { return m_map[10][100]; }
	//�u���b�N�Ƃ̓����蔻��
	void BlockHit
	(
		float* x, float* y, bool scroll_on,
		bool* up, bool* down, bool* left, bool* right,
		float* vx, float* vy, int* btu,int* btg
	);



private:
	int m_map[10][100]; //�}�b�v���

	float m_scroll;     //���E�X�N���[���p
	float m_px;
	float m_py;

};
