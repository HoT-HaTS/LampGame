#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define ASCROLL_LINE (300)
#define BSCROLL_LINE (200)

#define BLOCKCUT_SIZE_T (640.0f)
#define BLOCKCUT_SIZE_R (896.0f)
#define BLOCKCUT_SIZE_B (640.0f)

#define DRAW_SIZE_R (800.0f)
#define DRAW_SIZE_B (600.0f)

#define BLOCK_SIZE (64.0f)
#define HIT_LENGTH (111.0f)


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

	void BlockHit2
	(
		float* x, float* y, bool scroll_on,
		bool* up, bool* down, bool* left, bool* right,
		float* vx, float* vy, int* btu, int* btg
	);



private:
	int m_map[10][100]; //�}�b�v���

	float m_scroll;     //���E�X�N���[���p

	//float m_px; //�g���Ă��Ȃ��̂ŃR�����g�A�E�g
	//float m_py;

};
