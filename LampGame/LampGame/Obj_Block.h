#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[10][100]);	//�}�b�v�T�C�Y�͉��l
	~CObjBlock() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
};
