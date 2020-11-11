#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define INIT_MAP_X (10)
#define INIT_MAP_Y (100)
#define INIT_
#define INIT_X (64.0f)

#define INIT_SCROLL (0.0f)
#define INIT_APPEAR_LINE (500.0f)

#define BLOCK_SIZE (64.0f)

//�I�u�W�F�N�g�F
class CObjStage1 : public CObj
{
public:
	CObjStage1(int map[10][100]);
	~CObjStage1() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
	//void  SetScroll(float s) { m_scroll = s; }
	//float GetScroll() { return m_scroll; }

private:
	float s1_scroll;
	int m_map[10][100];
	bool g_f;
	bool g_f2;
	bool l_f;

	void BlockDraw(float x, float y, RECT_F* dst, float c[], int block_id);


	enum BLOCKNUM
	{
		NO_BLOCK,
		STAGE_BLOCK,
		GOAL_BLOCK,
		ENEMY_BLOCK,
		G_BLOCK3,
		G_BLOCK2,
		G_SWITCH2,
		G_BLOCK5,
		G_SWITCH5,

		//��ɍ폜�H
		G_BLOCK,
	};
};
