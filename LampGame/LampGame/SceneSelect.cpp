//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneSelect.h"
#include "GameHead.h"
#include "ObjSelect.h"

//�R���X�g���N�^
CSceneSelect::CSceneSelect()
{

}

//�f�X�g���N�^
CSceneSelect::~CSceneSelect()
{

}

//�Q�[�����C�����������\�b�h
void CSceneSelect::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"LampGame");

	//�摜�f�[�^�ǂݍ���
	Draw::LoadImageW(L"graphic/tumb_0.png", 0, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_1.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_2.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_3.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_4.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_5.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/tumb_6.png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stageselect_cursor.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/St_Cleared_mark.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/BG_sellect.png", 10, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_desc.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_desc2.png", 12, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_desc3.png", 13, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Locked.png", 14, TEX_SIZE_512);

	//���y�f�[�^�ǂݍ��ݗp
	Audio::LoadAudio(11, L"BGM/Sunrise_Title.wav", BACK_MUSIC);

	//SE�ǂݍ��ݗp
	Audio::LoadAudio(0, L"SE/Cursor.wav", EFFECT);
	Audio::LoadAudio(1, L"SE/Switch.wav", EFFECT);

	//�X�e�[�W�Z���N�g�I�u�W�F�N�g�쐬
	CObjSelect* obj = new CObjSelect();   //�X�e�[�W�Z���N�g�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_SELECT, 10);

	//�X�e�[�W�Z���N�g�I�u�W�F�N�g�쐬
	CObjBackGround_Select* objs_bg = new CObjBackGround_Select();   //�X�e�[�W�Z���N�g�I�u�W�F�N�g�쐬
	Objs::InsertObj(objs_bg, OBJ_SELECT, 10);

	//�I�[�f�B�I�X�^�[�g
	Audio::Start(11);
}

//�Q�[�����C�����s�����\�b�h
void CSceneSelect::Scene()
{

}