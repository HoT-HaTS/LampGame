//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneStage_1.h"
#include "GameHead.h"


//�X�e�[�W�ǂݍ��ނ��тɏ����������O���[�o���ϐ�
extern bool pause_flag = false;
extern bool switch_flag = true;

//�R���X�g���N�^
CSceneStage_1::CSceneStage_1()
{

}

//�f�X�g���N�^
CSceneStage_1::~CSceneStage_1()
{

}

//���������\�b�h
void CSceneStage_1::InitScene()
{
	

	CObjSelect* stage = (CObjSelect*)Objs::GetObj(OBJ_SELECT);

	//�}�b�v�f�[�^����������ǉ�
	unique_ptr<wchar_t>p;
	int size;
	int map[10][100];
	wchar_t str[128];

	swprintf_s(str, L"stagedata/Stage%d.csv", ((UserData*)Save::GetData())->stage_id);
	p = Save::ExternalDataOpen(str, &size);
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);
			map[i][j] = w;
			count += 2;
		}
	}


	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"graphic/lamp_shadow_walk.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/lamp_v2.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_blockG_shadow.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Glass_Block.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/switch.png", 10, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/lamp_attack.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/switch2.png", 12, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/stage_background_beta.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/block.png", 21, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Enemy.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Board.png", 23, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Shattersub.png", 24, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/G_Block.png", 25, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Enemy_dead.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tutorial.png", 50, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/block_shadow.png", 51, TEX_SIZE_512);

	Draw::LoadImageW(L"graphic/pausemenu.png", 13, TEX_SIZE_512);

	Draw::LoadImageW(L"graphic/KeyCoin.png", 30, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Keyblock.png", 31, TEX_SIZE_512);

	Draw::LoadImageW(L"graphic/BG_Area1.png", 60, TEX_SIZE_512);


	//���y�f�[�^�ǂݍ��ݗp
	Audio::LoadAudio(10, L"BGM/main_stage.wav", BACK_MUSIC);


	//SE�ǂݍ��ݗp
	Audio::LoadAudio(0, L"SE/Shadow_from.wav", EFFECT);
	Audio::LoadAudio(1, L"SE/Shadow_to.wav", EFFECT);
	Audio::LoadAudio(2, L"SE/Jump.wav", EFFECT);
	Audio::LoadAudio(3, L"SE/Flame.wav", EFFECT);
	Audio::LoadAudio(4, L"SE/Coin.wav", EFFECT);
	Audio::LoadAudio(5, L"SE/En_defeat.wav", EFFECT);
	Audio::LoadAudio(6, L"SE/Miss.wav", EFFECT);
	Audio::LoadAudio(7, L"SE/Switch.wav", EFFECT);
	Audio::LoadAudio(8, L"SE/Unlock.wav", EFFECT);

	//�I�u�W�F�N�g�o��
	CObjStage1* obj_stage1 = new CObjStage1(map);
	Objs::InsertObj(obj_stage1, OBJ_STAGE1, 30);

	CObjHero* obj_h = new CObjHero();
	Objs::InsertObj(obj_h, OBJ_HERO, 10);

	CObjMain* obj_main = new CObjMain();
	Objs::InsertObj(obj_main, OBJ_MAIN, 11);

	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 6);

	/*CObjKeyCoin* objcoin = new CObjKeyCoin(-1000, -1000);
	Objs::InsertObj(objcoin, OBJ_KEYCOIN, 7);*/

	//�Ŕo���p
	if (((UserData*)Save::GetData())->stage_id == 0)
	{
		CObjBoard* objt1 = new CObjBoard(BOARD1_X, BOARD_Y, 0);
		Objs::InsertObj(objt1, OBJ_BOARD, 9);

		CObjBoard* objt2 = new CObjBoard(BOARD2_X, BOARD_Y, 1);
		Objs::InsertObj(objt2, OBJ_BOARD, 9);

		CObjBoard* objt3 = new CObjBoard(BOARD3_X, BOARD_Y, 2);
		Objs::InsertObj(objt3, OBJ_BOARD, 9);
	}

	//�o�b�N�~���[�W�b�N�X�^�[�g
	float Volume = Audio::VolumeMaster(-0.8f);
	Audio::Start(10);

}

//���s�����\�b�h���s�����\�b�h
void CSceneStage_1::Scene()
{

}




