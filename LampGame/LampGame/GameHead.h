#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_MAIN,
	OBJ_ATTACK,
	OBJ_BLOCK,
	OBJ_ENEMY,
	OBJ_G_BLOCK,
	OBJ_G_BLOCK2,
	OBJ_G_BLOCK3,
	OBJ_G_BLOCK4,
	OBJ_KEYCOIN,
	OBJ_HERO,
	OBJ_SWITCH,
	OBJ_SWITCH2,
	OBJ_BOARD,
	OBJ_SELECT,
	OBJ_PAUSE,

	OBJ_STAGE1,
	OBJ_TITLE,
	OBJ_CLEAR,
	OBJ_GOALSCENE,
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_ATTACK,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLOCK,
	ELEMENT_WHITE,
	ELEMENT_SWITCH,
	ELEMENT_BOARD,
	ELEMENT_COIN,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	int stage_id;
	bool clear[6];
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
extern bool pause_flag;	//�|�[�Y��ʗp�̃t���O
extern bool switch_flag;	//�X�C�b�`�p�t���O


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "Obj_Main.h"
#include "Obj_Attack.h"
#include "Obj_Block.h"
#include "Obj_Enemy.h"
//#include "Obj_G_Block1.h"
#include "Obj_G_Block2.h"
#include "Obj_G_Block3.h"
#include "Obj_G_Block4.h"
#include "Obj_G_Block5.h"
#include "Obj_KeyCoin.h"
#include "Obj_Hero.h"
//#include "Obj_Switch.h"
#include "Obj_Switch2.h"
#include "Obj_Stage1.h"
#include "ObjSelect.h"
#include "Obj_Board.h"
#include "Obj_Pause.h"
#include "ObjTitle.h"
#include "ObjClear.h"
#include "ObjBackGround.h"
#include "Obj_Goalscene.h"
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneStage_1.h"
#include "SceneSelect.h"
#include "SceneTitle.h"
#include "SceneClear.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
//#define SET_GAME_START CSceneSelect
#define SET_GAME_START CSceneTitle
//-----------------------------------------------