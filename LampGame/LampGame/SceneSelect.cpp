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
	Font::SetStrTex(L"LampGame");

	Draw::LoadImageW(L"graphic/Stageselect_cursor.png", 1, TEX_SIZE_512);

	//���y�f�[�^�ǂݍ��ݗp
	Audio::LoadAudio(11, L"BGM/Sunrise_Title.wav", BACK_MUSIC);

	//SE�ǂݍ��ݗp
	Audio::LoadAudio(0, L"SE/Cursor.wav", EFFECT);

	//�X�e�[�W�Z���N�g�I�u�W�F�N�g�쐬
	CObjSelect* obj = new CObjSelect();   //�X�e�[�W�Z���N�g�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_SELECT, 10); 

	//�}�X�^�[�{�����[����1�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((0.4 - v));

	Audio::Start(11);
}

//�Q�[�����C�����s�����\�b�h
void CSceneSelect::Scene()
{

}