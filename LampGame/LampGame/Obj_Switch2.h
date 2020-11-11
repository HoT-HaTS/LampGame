#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define SBLOCK_INT_X_SIZE (64.0f) //�X�C�b�`�̉��T�C�Y
#define SBLOCK_INT_Y_SIZE (64.0f) //�X�C�b�`�̏c�T�C�Y
//��l���̏c�T�C�Y

//�I�u�W�F�N�g�F
class CObjSwitch2 : public CObj
{
public:
	CObjSwitch2(float x, float y);
	~CObjSwitch2() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

	bool Get_S2_flag() { return S2_flag; };	//�X�C�b�`�̃I��or�I�t
private:
	float m_px; 		//�ʒu
	float m_py;

	float m_scroll;		//�X�N���[���p�̕ϐ�

	bool  S2_flag;		//�X�C�b�`�̃t���O�Ǘ��p�֐�
	bool  a_flag;       //�U���̓�����񐔒����p
};