#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define BG_X (800.0)
#define BG_Y (600.0)

//�I�u�W�F�N�g�F�^�C�g��
class CObjBackGround :public CObj
{
public:
	CObjBackGround() {};
	~CObjBackGround() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[
private:

};