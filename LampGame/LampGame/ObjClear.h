#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjClear : public CObj
{
public:
	CObjClear() {};
	~CObjClear() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

private:
	int scene_num;	//�`��p�̔w�i�p�ԍ�
	float alpha_b;	//�����x

	bool white_out;
	bool white;
	bool w_end;

	int h_ani_frame;
	int h_ani_time;

	float alpha_w;

	bool m_key_flag;  //�L�[�t���O
};