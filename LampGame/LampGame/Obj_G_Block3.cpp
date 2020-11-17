//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "Obj_G_Block3.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObj_G_Block3::CObj_G_Block3(float x, float y)
{
	m_px = x;	//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObj_G_Block3::Init()
{
	//false���e�Btrue����
	L_flag = true;

	m_px = 0;
	m_py = 0;
	m_scroll = 0;

	//HitBox�쐬
	Hits::SetHitBox(this, m_px, m_py, SBLOCK_INT_X_SIZE, SBLOCK_INT_Y_SIZE, ELEMENT_BLOCK, OBJ_G_BLOCK3, 1);
}

//�A�N�V����
void CObj_G_Block3::Action()
{
	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	m_scroll = scroll->GetScroll();


	//��l���̏��̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l���̏Փˊm�F�p�̃t���O�̏�����
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//��or�e�̏��������Ă���
	L_flag = hero->Get_L_flag();

	////HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + scroll->GetScroll(), m_py);

	////��l����G_Block�̂����蔻��`�F�b�N
	////�������Ă���ꍇ
	//if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	//{
	//	//��l���̈ʒu�擾
	//	float hx = hero->GetX();
	//	float hy = hero->GetY();

	//	hero->SetDown2(false);

	//	//G_Block�̏�or������Ȃ�����
	//	if (hy + 120 > m_py ) //|| m_py + 50 < hy)
	//	{
	//		//G_Block�̍������ɐڐG
	//		if (m_px + scroll->GetScroll() > hx)
	//		{
	//			hero->SetRight(true);
	//			hero->SetX(m_px - 64.5 + scroll->GetScroll());
	//			hero->SetVX(-0.8);
	//			hero->SetVY(0.0);
	//		}
	//		//G_Block�̉E�����ɐڐG
	//		if (hx > m_px + scroll->GetScroll())
	//		{
	//			hero->SetLeft(true);
	//			hero->SetX(m_px + 63.5 + scroll->GetScroll());
	//			hero->SetVX(0.0);
	//			hero->SetVY(0.0);
	//		}
	//	}
	//		//G_Block�̏㕔���ɐڐG
	//		if (hy + 125 < m_py)
	//		{
	//			hero->SetDown2(true);
	//			hero->SetY(m_py - 128.5);
	//			hero->SetVY(0.0);
	//		}
	//		//G_Block�̉������ɐڐG
	//		if (m_py + 55 < hy)
	//		{
	//			hero->SetUp(true);
	//			hero->SetY(m_py + 64.5);
	//			hero->SetVY(0.0);
	//		}
	//}


	//float h_px = hero->GetX();
	//float h_py = hero->GetY();
	//bool h_hit_up = hero->GetUp();
	//bool h_hit_down = hero->GetDown();
	//bool h_hit_right = hero->GetRight();
	//bool h_hit_left = hero->GetLeft();
	//float h_vx = hero->GetVX();
	//float h_vy = hero->GetVY();

	////G3�u���b�N�Ƃ̓����蔻����s(�e�X�g)
	//CObj_G_Block3* pb3 = (CObj_G_Block3*)Objs::GetObj(OBJ_G_BLOCK3);
	//pb3->BlockHit3(&h_px, &h_py, true,
	//	&h_hit_up, &h_hit_down, &h_hit_left, &h_hit_right, &h_vx, &h_vy
	//);
}

//�h���[
void CObj_G_Block3::Draw()
{
	//�X�N���[���̒l���擾
	CObjBlock* scroll = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���̏��̎擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	L_flag = hero->Get_L_flag();

	//�`��J���[��� R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float  c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + scroll->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	if (L_flag == false)
	{	
		//4�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec �̏������Ƃɕ`��
		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
}


////BlockHit�֐�(�����蔻��)
////����1	float* x			:������s��object(��l���Ȃ�)��X�ʒu
////����2 float* y			:������s��object(��l���Ȃ�)��Y�ʒu
////����3 bool	scroll_on	:������s��object�̓X�N���[���̉e����^���邩�ǂ���(true=�^���� false=�^���Ȃ�)
////����4 bool* up			:�㉺����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
////����5 bool* down			:�㉺����̉������ɂ������Ă��邩�ǂ�����Ԃ�
////����6 bool* left			:�㉺����̍������ɂ������Ă��邩�ǂ�����Ԃ�
////����7 bool* right			:�㉺����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
////����8 float* px			:���E���莞�A���Ε����ɍ��W��ύX���Ĉʒu��Ԃ�
////����9 float* py			:�㉺���莞�A���Ε����ɍ��W��ύX���Ĉʒu��Ԃ�
////����10 int* btu			:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
////����11 int* btr			:�E�������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
////������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
////���̌��ʂ͈���4�`10�ɕԂ�
//void CObj_G_Block3::BlockHit3(
//	float* x, float* y, bool scroll_on,
//	bool* up, bool* down, bool* left, bool* right,
//	float* vx, float* vy)
//{
//	//�Փˏ�Ԋm�F�p�t���O�̏�����
//	*up = false;
//	*down = false;
//	*left = false;
//	*right = false;
//
//	//�v�f�ԍ������W�ɕύX
//	float bx = 0 + m_px;
//	float by = 0 + m_py;
//
//	//�X�N���[���̉e��
//	float scroll = scroll_on ? m_scroll : 0;
//
//				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��(�u���b�N�̍�:�E:��:���̏�)
//				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 128.0f > by) && (*y < by + 64.0f))
//				{
//					//�㉺���E����
//
//					//��l���ƃu���b�N�̒��S��vector�쐬
//					float rvx = (*x + (-scroll) + 32.0f) - (bx + 32.0f);
//					float rvy = (*y + 64.0f) - (by + 32.0f);
//
//					//����len�����߂�
//					float len = sqrt(rvx * rvx + rvy * rvy);
//
//					//�p�xr�����߂�
//					float r = atan2(rvy, rvx);	//(���W�A��)
//					r = r * 180.0f / 3.14f;		//�x
//
//					if (r <= 0.0f)
//						r = abs(r);
//					else
//						r = 360.0f - abs(r);
//
//					//len��������̒������Z���ꍇ�ɔ���ɓ���B
//					if (len < 111.0f)
//					{
//						//�p�x�ŏ㉺���E�𔻒�
//						if ((r < 56 && r >= 0) || r > 304)
//						{
//							//�E
//							*right = true;				//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
//							*x = bx + 63.5f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
//							*vx = -(*vx) * 0.1f;			//-VX*�����W��
//						}
//						if (r > 56 && r < 124)
//						{
//							//��
//							*down = true;			//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
//							*y = by - 128.0f;		//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
//							*vy = 0.0f;
//						}
//						if (r > 124 && r < 236)
//						{
//							//��
//							*left = true;				//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
//							*x = bx - 64.5f + (scroll);	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
//							*vx = -(*vx) * 0.1f;			//-VX*�����W��
//						}
//						if (236 < r && r < 304)
//						{
//							//��
//							*up = true;			//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
//							*y = by + 63.5f;	//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
//							if (*vy < 0)
//							{
//								*vy = 0.0f;
//							}
//						}
//					}
//				}
//			}
