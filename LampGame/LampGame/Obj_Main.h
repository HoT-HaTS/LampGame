#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObjMain : public CObj
{
public:
	CObjMain() {};
	~CObjMain() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	bool m_flag;
	int coin_count;

	//�S�[�����o�p�̕ϐ�
	float alpha;
	bool g_flag;
	bool ga_flag;
};

