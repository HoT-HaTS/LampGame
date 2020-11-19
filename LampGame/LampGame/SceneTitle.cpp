//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "GameHead.h"
#include "SceneTitle.h"
#include "ObjTitle.h"
#include "ObjBackGround.h"

//�R���X�g���N�^
CSceneTitle::CSceneTitle()
{

}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//�Q�[�����C�����������]�b�g
void CSceneTitle::InitScene()
{
	Draw::LoadImageW(L"graphic/Title.png", 14, TEX_SIZE_512);


	//���y�f�[�^�ǂݍ��ݗp
	Audio::LoadAudio(11, L"BGM/Sunrise_Title.wav", BACK_MUSIC);


	////�����������镶���̃O���t�B�b�N�쐬
	//Font::SetStrTex(L"�����v�̗d���Ɖe�̐��E");

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjTitle* obj = new CObjTitle();    //�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_TITLE, 6); 

	//�w�i�I�u�W�F�N�g�쐬
	CObjBackGround* objbg = new CObjBackGround();    //�w�i�I�u�W�F�N�g�쐬
	Objs::InsertObj(objbg, OBJ_TITLE, 6); 


	//�}�X�^�[�{�����[����1�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((1.0 - v));

	Audio::Start(11);
}

//�Q�[�����C�����s�����]�b�g
void CSceneTitle:: Scene()
{

}