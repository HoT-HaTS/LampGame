//�g�p����w�b�_�[�t�@�C��
#include <math.h>
#include "GameL/DrawTexture.h"
#include "UtilityModule.h"

#include "GameHead.h"
#include "Obj_Block.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//---UnitVec�֐�
//����1�@float*vx	:�x�N�g����x�����̃|�C���^
//����2�@float*vy	:�x�N�g����y�����̃|�C���^
//�߂�l bool		:true=�v�Z����	false=�v�Z���s
//���e
//�����̃x�N�g���𐳋K�������̒l��vx,vy�ɕύX���܂��B
bool UnitVec(float* vx, float* vy)
{
	//�x�N�g���̒��������߂�i�O�����̒藝�j
	float r = 0.0f;
	r = (*vx) * (*vx) + (*vy) * (*vy);
	r = sqrt(r);

	//������0���ǂ������ׂ�
	if (r == 0.0f)
	{
		//0�Ȃ�v�Z���s
		return false;
	}
	else
	{
		//���K�����s��vx��vy�̎Q�Ɛ�̒l��ύX
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);
	}

	//�v�Z����
	return true;
}


//---CheckWindow�֐�
//����1	float pos_x		:�̈�O���ǂ������ׂ�x�ʒu
//����2	float pos_y		:�̈�O���ǂ������ׂ�y�ʒu
//����3	float window_x	:�̈��top�ʒu
//����4	float window_y	:�̈��left�ʒu
//����5	float window_w	:�̈��right�ʒu
//����6	float window_h	:�̈��bottom�ʒu
//�߂�l bool		:true=�̈�� false=�̈�O
//���e
//�̈�����ǂ������ׂ�ʒupos_(x,y)��window_(xywh)�̓����O���𒲂ׂ�B
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h)
{
	//�̈�`�F�b�N
	if (pos_x < window_x)
	{
		return false;	//�̈�O
	}
	if (pos_x > window_w)
	{
		return false;	//�̈�O
	}
	if (pos_y < window_y)
	{
		return false;	//�̈�O
	}
	if (pos_y > window_h)
	{
		return false;	//�̈�O
	}

	return true;		//�̈��
}

//BlockDrawMethod�֐�
//����1 float		x		:���\�[�X�؂���ʒux
//����2 float		y		:���\�[�X�؂���ʒuy
//����3 RECT_F* dst			:�`��ʒu
//����4 float		c[]		:�J���[���
//�u���b�N��64�~64����`��p�B���\�[�X�؂���ʒu�̂�x,y�Őݒ�ł���B
void BlockDraw(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//�`��
	Draw::Draw(0, &src, dst, c, 0.0f);
}

////BlockHit�֐�(�����蔻��)
////����1	float* x			:������s��object��X�ʒu
////����2 float* y			:������s��object��Y�ʒu
////����3 bool	scroll_on	:������s��object�̓X�N���[���̉e����^���邩�ǂ���(true=�^���� false=�^���Ȃ�)
////����4 bool* up			:�㉺����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
////����5 bool* down			:�㉺����̉������ɂ������Ă��邩�ǂ�����Ԃ�
////����6 bool* left			:�㉺����̍������ɂ������Ă��邩�ǂ�����Ԃ�
////����7 bool* right			:�㉺����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
////����8 float* vx			:���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
////����9 float* vy			:�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
////����10 int* bt			:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
////����11 int map[10][100]	:�}�b�v�f�[�^
////������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
////���̌��ʂ͈���4�`10�ɕԂ�
//void BlockHit(
//	float* x, float* y, bool scroll_on,
//	bool* up, bool* down, bool* left, bool* right,
//	float* vx, float* vy, int* bt
//)

