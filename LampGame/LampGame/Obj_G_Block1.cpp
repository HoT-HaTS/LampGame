//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "Obj_G_Block1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObj_G_Block::CObj_G_Block(float x, float y)
{
	m_px = x;	//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObj_G_Block::Init()
{

}

//�A�N�V����
void CObj_G_Block::Action()
{
		
}

//�h���[
void CObj_G_Block::Draw()
{
	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 320.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f; +m_px;
	dst.m_left = 0.0f; +m_py;
	dst.m_right = 32.0f; +m_px;
	dst.m_bottom = 320.0f; +m_py;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
}




//BlockHit�֐�(�����蔻��)
//����1	float* x			:������s��object��X�ʒu
//����2 float* y			:������s��object��Y�ʒu
//����3 bool	scroll_on	:������s��object�̓X�N���[���̉e����^���邩�ǂ���(true=�^���� false=�^���Ȃ�)
//����4 bool* up			:�㉺����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
//����5 bool* down			:�㉺����̉������ɂ������Ă��邩�ǂ�����Ԃ�
//����6 bool* left			:�㉺����̍������ɂ������Ă��邩�ǂ�����Ԃ�
//����7 bool* right			:�㉺����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
//����8 float* vx			:���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
//����9 float* vy			:�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
//����10 int* bt			:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
//void CObj_G_Block::BlockHit(
//	float* x, float* y, bool scroll_on,
//	bool* up, bool* down, bool* left, bool* right,
//	float* vx, float* vy, int* bt
//)
//{
//	//�Փˏ�Ԋm�F�p�t���O�̏�����
//	*up = false;
//	*down = false;
//	*left = false;
//	*right = false;
//
//	//����ł���block�̎�ނ̏�����
//	*bt = 0;
//
//	//m_map�̑S�v�f�ɃA�N�Z�X
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 100; j++)
//		{
//			if (m_map[i][j] > 0 && m_map[i][j] != 4)
//			{
//				//�v�f�ԍ������W�ɕύX
//				float bx = j * 64.0f;
//				float by = i * 64.0f;
//
//				//�X�N���[���̉e��
//				float scroll = scroll_on ? m_scroll : 0;
//
//				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
//				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
//				{
//					//�㉺���E����
//
//					//vector�̍쐬
//					float rvx = (*x + (-scroll)) - bx;
//					float rvy = *y - by;
//
//					//���������߂�
//					float len = sqrt(rvx * rvx + rvy * rvy);
//
//					//�p�x�����߂�
//					float r = atan2(rvy, rvx);
//					r = r * 180.0f / 3.14f;
//
//					if (r <= 0.0f)
//						r = abs(r);
//					else
//						r = 360.0f - abs(r);
//
//					//len��������̒����̂��Z���ꍇ�ɔ���ɓ���B
//					if (len < 88.0f)
//					{
//						//�p�x�ŏ㉺���E�𔻒�
//						if ((r < 45 && r>0) || r > 315)
//						{
//							//�E
//							*right = true;	//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
//							*x = bx + 64.0f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
//							*vx = -(*vx) * 0.1f;	//-VX*�����W��
//						}
//						if (r > 45 && r < 135)
//						{
//							//��
//							*down = true;	//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
//							*y = by - 64.0f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
//							//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
//							if (m_map[i][j] >= 2)
//								*bt = m_map[i][j];	//�u���b�N�̗v�f(type)���I�u�W�F�N�g�ɓn��
//							*vy = 0.0f;
//						}
//						if (r > 135 && r < 225)
//						{
//							//��
//							*left = true;	//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
//							*x = bx - 64.0f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
//							*vx = -(*vx) * 0.1f;	//-VX*�����W��
//						}
//						if (225 < r && r < 315)
//						{
//							//��
//							*up = true;	//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
//							*y = by + 64.0f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
//							if (*vy < 0)
//							{
//								*vy = 0.0f;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}