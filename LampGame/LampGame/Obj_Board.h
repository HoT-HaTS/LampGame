#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObjBoard : public CObj
{
public:
	CObjBoard(int map[10][100]);	
	~CObjBoard() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
	void  SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

private:
	int m_map[10][100]; //�}�b�v���

	float m_scroll;     //���E�X�N���[���p
	float m_px;
	float m_py;

};
