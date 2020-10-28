#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

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

	void BlockDraw(float x, float y, RECT_F* dst, float c[], int block_id);
};
