#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObjBoard : public CObj
{
public:
	CObjBoard(float x, float y);
	~CObjBoard() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
	bool Get_Tuto_Sensor() { return T_Sensor; };//�`���[�g���A���\���Z���T�[
private:
	float m_scroll;     //���E�X�N���[���p
	float m_px;
	float m_py;
	int count;	//�Ŕ̐�
	bool T_Sensor;
	bool m_flag;

	bool CheckWindow(float pos_x, float pos_y,
		float window_x, float window_y, float window_w, float window_h);
};
