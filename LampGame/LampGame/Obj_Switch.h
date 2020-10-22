#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define SBLOCK_INT_X_SIZE (64.0f) //�X�C�b�`�̉��T�C�Y
#define SBLOCK_INT_Y_SIZE (64.0f) //�X�C�b�`�̉��T�C�Y
//��l���̏c�T�C�Y

//�I�u�W�F�N�g�F
class CObjSwitch : public CObj
{
public:
	CObjSwitch(float x, float y);
	~CObjSwitch() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
	
	bool Get_S_flag() { return S_flag; };	//�X�C�b�`�̃I��or�I�t
private:
	float m_px; 		//�ʒu
	float m_py;

	float m_scroll;		//�X�N���[���p�̕ϐ�

	bool  S_flag;		//�X�C�b�`�̃t���O�Ǘ��p�֐�
};

