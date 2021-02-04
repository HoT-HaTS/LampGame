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
#include "SceneClear.h"
#include "GameHead.h"
#include "ObjClear.h"

//�R���X�g���N�^
CSceneClear::CSceneClear()
{

}

//�f�X�g���N�^
CSceneClear::~CSceneClear()
{

}

//�Q�[�����C�����������\�b�h
void CSceneClear::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	Font::SetStrTex(L"�N���A");

	Draw::LoadImageW(L"graphic/Stage_Area0.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area1.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area2.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area3.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area4.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area5.png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Stage_Area6.png", 7, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/White.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/Game_clear_text.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"graphic/lamp Clear.png", 10, TEX_SIZE_512);

	//���y�f�[�^�ǂݍ��ݗp
	Audio::LoadAudio(0, L"BGM/Beta_Clear.wav", BACK_MUSIC);

	//SE�ǂݍ��ݗp
	//Audio::LoadAudio(0, L"SE/Cursor.wav", EFFECT);

	//�N���A�I�u�W�F�N�g�쐬
	CObjClear* objc = new CObjClear();
	Objs::InsertObj(objc, OBJ_CLEAR, 10);

	//�}�X�^�[�{�����[����1�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((0.4 - v));

	Audio::Start(11);
}

//�Q�[�����C�����s�����\�b�h
void CSceneClear::Scene()
{

}