#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObjKeyCoin : public CObj
{
public:
	CObjKeyCoin(float x, float y);
	~CObjKeyCoin() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	float m_scroll;     //���E�X�N���[���p
	float m_px;
	float m_py;
	int m_ani_time;
	int m_ani_frame;

	//�e�X�g�F�R�C�������m�F�p
	int coin_count;
};
