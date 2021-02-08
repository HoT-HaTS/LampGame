#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL/SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define MAP_X (100)
#define MAP_Y (10)

#define MAX_STR (128)

#define INIT_COUNT (1)
#define PLUS_COUNT (2)

#define BOARD1a_X (256.0)
#define BOARD1b_X (3830.0)
#define BOARD2a_X (2432.0)
#define BOARD2b_X (3776.0)
#define BOARD3_X (3712.0)
#define BOARD4_X (1536.0)
#define BOARD5_X (640.0)
#define BOARD6_X (896.0)
#define BOARD7_X (4736.0)
#define BOARD_Y (512.0)
#define BOARD_Yb (128.0)

#define BOARD_MOVE1 (0)
#define BOARD_MOVE2 (6)
#define BOARD_Z_KEY (1)
#define BOARD_X_KEY1 (2)
#define BOARD_X_KEY2 (7)
#define BOARD_SPACE_KEY (3)
#define BOARD_GLASS_BLOCK (4)
#define BOARD_KEY_BLOAK (5)

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
