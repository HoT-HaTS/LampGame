#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define TITLE_SIZE (32.0f)
#define TITLE1_X (224.0f) 
#define TITLE1_Y (250.f)
#define TITLE2_X (200.0f)
#define TITLE2_Y (400.0f)

//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle :public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[
private:
	bool m_key_flag;
};