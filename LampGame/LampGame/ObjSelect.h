#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjSelect : public CObj
{
public:
	CObjSelect() {};
	~CObjSelect() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	int GetStageID() { return stage_id; }
private:
	bool m_key_flag;  //�L�[�t���O
	bool select_flag; //�X�e�[�W�Z���N�g�p�t���O

	int stage_id;
};