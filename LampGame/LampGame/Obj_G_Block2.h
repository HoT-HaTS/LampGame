#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObj_G_Block2 : public CObj
{
public:
	CObj_G_Block2(float x, float y);
	~CObj_G_Block2() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

	bool Get_G2_flag() { return G2_flag; }


private:
	bool G2_flag;		//�M�~�b�N�u���b�N�p
	bool a_flag;		//HitBox���邩���ׂ�t���O

	bool l_f;

	float m_px;			//�ʒu
	float m_py;
};