#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

//�٨S������Ψ쨤��W
//��Ҧ��I���g��fuction
void CGameStateRun::CheckMovable(CMovingBitmap player, vector<CMovingBitmap> targets, int dx, int dy)
{
	bool isMovable = true;

	for (CMovingBitmap target : targets) //�M���Ҧ��|�I���쪺����
	{
		//�i�঳�~�����AisMovable���ӧ令���ਫ
		//�p�G�������|�N���ਫ�Aa &= b �O a = a & b
		isMovable &= CMovingBitmap::IsOverlap(player.GetLeft(), player.GetTop(), player.GetHeight() + dy, player.GetWidth() + dx, target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (isMovable) {
			player.SetTopLeft(player.GetLeft() + dx, 843 + dy);
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							
{
	//player1 move
	if (_isRightRun == 1)
	{
		isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth() + 10, brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		P1P2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth() + 10, player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth());
		if (!isOverlap && !P1P2isOverlap && player1.GetLeft()<1800 && player2.GetLeft() > 0)
		{
			player1.SetTopLeft(player1.GetLeft() + 8, player1.GetTop());
		}
		else
		{
			player1.SetTopLeft(player1.GetLeft(), player1.GetTop());
		}
	}
	else if (_isLeftRun == 1)
	{
		isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft() - 10, player1.GetTop(), player1.GetHeight(), player1.GetWidth(), brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		P1P2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft() - 10, player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth());
		if (!isOverlap && !P1P2isOverlap && player1.GetLeft() > 0 && player2.GetLeft() < 1800) {
			player1.SetTopLeft(player1.GetLeft() - 8, player1.GetTop());
		}
		else
		{
			player1.SetTopLeft(player1.GetLeft(), player1.GetTop());
		}
	}

	if (_isP1UpRun && _P1UpTime <= 13)
	{
		if (_P1UpTime == 13) //����@�w���״N����
		{
			_isP1UpRun = 0;
		}
		else
		{
			_P1UpTime++;
			player1.SetTopLeft(player1.GetLeft(), player1.GetTop() - 10);
		}
	}
	else if (!_isP1UpRun) //��������
	{
		if (_P1UpTime > 0)
		{
			player1.SetTopLeft(player1.GetLeft(), player1.GetTop() + 10);
			_P1UpTime--;
		}
		if (_P1UpTime == 0)
		{
			_P1JumpOnce = 0;
		}
	}

	//player2 move
	if (_P2isRightRun == 1)
	{
		P2isOverlap = CMovingBitmap::IsOverlap(player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth() + 10, brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		P1P2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth() + 10);
		if (!P2isOverlap && !P1P2isOverlap && player2.GetLeft() < 1800 && player1.GetLeft() > 0) {
			player2.SetTopLeft(player2.GetLeft() + 8, player2.GetTop());
		}
		else
		{
			player2.SetTopLeft(player2.GetLeft(), player2.GetTop());
		}
	}
	else if (_P2isLeftRun == 1)
	{
		P2isOverlap = CMovingBitmap::IsOverlap(player2.GetLeft() - 10, player2.GetTop(), player2.GetHeight(), player2.GetWidth(), brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		P1P2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft() - 10, player2.GetTop(), player2.GetHeight(), player2.GetWidth());
		if (!P2isOverlap && !P1P2isOverlap && player2.GetLeft() > 0 && player1.GetLeft() < 1800) {
			player2.SetTopLeft(player2.GetLeft() - 8, player2.GetTop());
		}
		else
		{
			player2.SetTopLeft(player2.GetLeft(), player2.GetTop());
		}
	}

	if (_isP2UpRun && _P2UpTime <= 13)
	{
		if (_P2UpTime == 13) //����@�w���״N����
		{
			_isP2UpRun = 0;
		}
		else
		{
			_P2UpTime++;
			player2.SetTopLeft(player2.GetLeft(), player2.GetTop() - 10);
		}
	}
	else if (!_isP2UpRun) //��������
	{
		if (_P2UpTime > 0)
		{
			player2.SetTopLeft(player2.GetLeft(), player2.GetTop() + 10);
			_P2UpTime--;
		}
		if (_P2UpTime == 0)
		{
			_P2JumpOnce = 0;
		}
	}

	//�e������
	if (((player1.GetLeft() + player2.GetLeft()) / 2) > 1000 )
	{
		background.SetTopLeft(background.GetLeft() - 3, 0);
		player1.SetTopLeft(player1.GetLeft() - 3, player1.GetTop());
		player2.SetTopLeft(player2.GetLeft() - 3, player2.GetTop());
	}
	else if(((player1.GetLeft() + player2.GetLeft()) / 2) < 800)
	{
		background.SetTopLeft(background.GetLeft() + 3, 0);
		player1.SetTopLeft(player1.GetLeft() + 3, player1.GetTop());
		player2.SetTopLeft(player2.GetLeft() + 3, player2.GetTop());
	}



}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	background.LoadBitmapByString({
		"resources/phase21_background.bmp",
		"resources/phase31_background.bmp",
		"resources/phase41_background.bmp",
		"resources/phase51_background.bmp"
		});
	background.SetTopLeft(0, 0);

	catalog.LoadBitmapByString({
		"resources/phase11_background.bmp",
		"resources/phase12_background.bmp",
		"resources/phase13_background.bmp",
		"resources/phase14_background.bmp"
		});
	catalog.SetTopLeft(0, 0);

	player1.LoadBitmapByString({
		"resources/player1Rightstand.bmp",
		"resources/player1RightRun1.bmp",
		"resources/player1RightRun2.bmp",
		"resources/player1RightRun3.bmp",
		"resources/player1RightRun4.bmp"
		}, RGB(0, 255, 0));
	player1.SetTopLeft(1020, 823);

	player2.LoadBitmapByString({ "resources/giraffe.bmp" });
	player2.SetTopLeft(900, 843);

	brick.LoadBitmapByString({ "resources/gray.bmp" });
	//brick.SetTopLeft(1400, 843);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_UP) {
		if (phase > 1 && phase <= 5) {	//���d
			if (_P1JumpOnce == 0) //�S���L�~����A���M�|�s��
			{
				_P1JumpOnce = 1;
				_isP1UpRun = 1;
			}
		}
	}

	if (nChar == VK_RIGHT) {

		if (phase == 1) {	//�ؿ� phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//���d phase = 2~5
			_isRightRun = 1;
			player1.SetAnimation(125, false);
		}
	}

	if (nChar == VK_LEFT) {

		if (phase == 1) {	//�ؿ�
			if(sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//���d
			_isLeftRun = 1;
			player1.SetAnimation(125, false);
		}
	}

	if (nChar == 0x57) {  //player2 �W�� W
		if (phase > 1 && phase <= 5) {	//���d
			if (_P2JumpOnce == 0) //�S���L�~����A���M�|�s��
			{
				_P2JumpOnce = 1;
				_isP2UpRun = 1;
			}
		}
	}

	if (nChar == 0x44) {  //player2 �k�� D

		if (phase == 1) {	//�ؿ� phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//���d phase = 2~5
			_P2isRightRun = 1;
			//player2.SetAnimation(125, false);
		}
	}

	if (nChar == 0x41) {  //player2 ���� A

		if (phase == 1) {	//�ؿ�
			if (sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//���d
			_P2isLeftRun = 1;
			//player2.SetAnimation(125, false);
		}
	}

	if (nChar == VK_RETURN) {
		if (phase == 1) { // phase1���ؿ�
			phase = sub_phase + 1; // ������d
		}

		/*
		else if (phase == 2) {
			ResetMovingTime();
			if (sub_phase == 1) {
				sub_phase += validate_phase_2();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}
		*/
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) {
		if (phase > 1 && phase <= 5) {	//���d
			_isRightRun = 0;
			player1.StopAnimation();
		}
	}

	if (nChar == VK_LEFT) {
		if (phase > 1 && phase <= 5) {	//���d
			_isLeftRun = 0;
			player1.StopAnimation();
		}
	}

	if (nChar == VK_UP) {
		_isP1UpRun = 0;
	}

	if (nChar == 0x44) { //P2�k
		_P2isRightRun = 0;
		//player2.StopAnimation();
	}

	if (nChar == 0x41) { //P2��
		_P2isLeftRun = 0;
		//player2.StopAnimation();
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	show_image_by_phase();
	show_text_by_phase();
}

void CGameStateRun::show_image_by_phase() {
	if (phase == 1) {
		catalog.SetFrameIndexOfBitmap(sub_phase - 1);
		catalog.ShowBitmap();
	}
	if (phase > 1 && phase <= 5) {
		background.SetFrameIndexOfBitmap(phase - 2);
		background.ShowBitmap();
		player1.ShowBitmap();
		player2.ShowBitmap();
		//brick.ShowBitmap();
	}	
}

void CGameStateRun::show_text_by_phase() {
	
}

bool CGameStateRun::validate_phase_1() {
	return player1.GetImageFileName() == "resources/giraffe.bmp";
}

bool CGameStateRun::validate_phase_2() {
	return player1.GetTop() > 204 && player1.GetTop() < 325 && player1.GetLeft() > 339 && player1.GetLeft() < 459;
}

/*
bool CGameStateRun::validate_phase_3() {
	
	return (
		
		player1.GetTop() + player1.GetHeight() >= chest_and_key.GetTop()
		&& player1.GetLeft() + player1.GetWidth() >= chest_and_key.GetLeft()
		&& chest_and_key.GetFrameIndexOfBitmap() == 1
		&& chest_and_key.GetFilterColor() == RGB(255, 255, 255)
	);
}

bool CGameStateRun::validate_phase_4() {
	return bee.IsAnimation() && bee.GetFrameSizeOfBitmap() == 2;
}

bool CGameStateRun::validate_phase_5() {
	
	bool check_all_door_is_open = true;
	for (int i = 0; i < 3; i++) {
		check_all_door_is_open &= (door[i].GetFrameIndexOfBitmap() == 1);
	}
	return check_all_door_is_open;
	
}

bool CGameStateRun::validate_phase_6() {
	return ball.IsAnimationDone() && !ball.IsAnimation() && ball.GetFrameIndexOfBitmap() == ball.GetFrameSizeOfBitmap() - 1;
}
*/