#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL/SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define BOARD1_X (640.0)
#define BOARD2_X (1664.0)
#define BOARD3_X (3456.0)
#define BOARD_Y (512.0)

//�V�[���F���C��
class CSceneStage_1 :public CScene
{
public:
	CSceneStage_1();
	~CSceneStage_1();
	void InitScene(); //���������\�b�h
	void Scene();		//���s�����\�b�h
	void Draw();
private:
};
