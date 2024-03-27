#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

//還沒實際應用到角色上
//把所有碰撞寫成fuction
void CGameStateRun::CheckMovable(CMovingBitmap player, vector<CMovingBitmap> targets, int dx, int dy)
{
	bool isMovable = true;

	for (CMovingBitmap target : targets) //遍歷所有會碰撞到的物件
	{
		//可能有誤之後改，isMovable應該改成不能走
		//如果有任何重疊就不能走，a &= b 是 a = a & b
		isMovable &= CMovingBitmap::IsOverlap(player.GetLeft(), player.GetTop(), player.GetHeight() + dy, player.GetWidth() + dx, target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (isMovable) {
			player.SetTopLeft(player.GetLeft() + dx, 843 + dy);
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
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

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (_isRightRun == 1)
	{
		isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth() + 10, brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		P1P2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth() + 10, player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth());
		if (!isOverlap && !P1P2isOverlap) {
			player1.SetTopLeft(player1.GetLeft() + 10, 843);
		}
		else
		{
			player1.SetTopLeft(player1.GetLeft(), 843);
		}
	}
	else if (_isLeftRun == 1)
	{
		isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft() - 10, player1.GetTop(), player1.GetHeight(), player1.GetWidth(), brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		P1P2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft() - 10, player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth());
		if (!isOverlap && !P1P2isOverlap) {
			player1.SetTopLeft(player1.GetLeft() - 10, 843);
		}
		else
		{
			player1.SetTopLeft(player1.GetLeft(), 843);
		}
	}

	if (_isUpRun && _upTime <= 13)
	{
		if (_upTime == 13) //跳到一定高度就掉落
		{
			_isUpRun = 0;
		}
		else
		{
			_upTime++;
			player1.SetTopLeft(player1.GetLeft(), 823 - (10 * _upTime));
		}
	}
	else if (!_isUpRun) //跳完掉落
	{
		if (_upTime >= 0)
		{
			if (_upTime == 0)
			{
				player1.SetTopLeft(player1.GetLeft(), 823 - (10 * _upTime));
				_jumpOnce = 0;
			}
			else
			{
				player1.SetTopLeft(player1.GetLeft(), 823 - (10 * _upTime));
				_upTime--;
			}
		}
	}

	//player2 move
	if (_P2isRightRun == 1)
	{
		P2isOverlap = CMovingBitmap::IsOverlap(player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth() + 10, brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		P1P2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth() + 10);
		if (!P2isOverlap && !P1P2isOverlap) {
			player2.SetTopLeft(player2.GetLeft() + 10, 843);
		}
		else
		{
			player2.SetTopLeft(player2.GetLeft(), 843);
		}
	}
	else if (_P2isLeftRun == 1)
	{
		P2isOverlap = CMovingBitmap::IsOverlap(player2.GetLeft() - 10, player2.GetTop(), player2.GetHeight(), player2.GetWidth(), brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		P1P2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft() - 10, player2.GetTop(), player2.GetHeight(), player2.GetWidth());
		if (!P2isOverlap && !P1P2isOverlap) {
			player2.SetTopLeft(player2.GetLeft() - 10, 843);
		}
		else
		{
			player2.SetTopLeft(player2.GetLeft(), 843);
		}
	}

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
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
	player1.SetTopLeft(150, 823);

	player2.LoadBitmapByString({ "resources/giraffe.bmp" });
	player2.SetTopLeft(500, 843);

	brick.LoadBitmapByString({ "resources/gray.bmp" });
	brick.SetTopLeft(1000, 843);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_UP) {
		if (phase > 1 && phase <= 5) {	//關卡
			if (_jumpOnce == 0) //沒跳過才能跳，不然會連跳
			{
				_jumpOnce = 1;
				_isUpRun = 1;
			}
		}
	}

	if (nChar == VK_RIGHT) {

		if (phase == 1) {	//目錄 phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡 phase = 2~5
			_isRightRun = 1;
			player1.SetAnimation(125, false);
		}
	}

	if (nChar == VK_LEFT) {

		if (phase == 1) {	//目錄
			if(sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡
			_isLeftRun = 1;
			player1.SetAnimation(125, false);
		}
	}

	if (nChar == 0x57) {  //player2 上鍵 W
		//_upTime++;
		//player1.SetTopLeft(150 + (10 * _rightTime) - (10 * _leftTime), 265 - (10 * _upTime) + (10 * _downTime));
	}

	if (nChar == 0x44) {  //player2 右鍵 D

		if (phase == 1) {	//目錄 phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡 phase = 2~5
			_P2isRightRun = 1;
		}
	}

	if (nChar == 0x41) {  //player2 左鍵 A

		if (phase == 1) {	//目錄
			if (sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡
			_P2isLeftRun = 1;
		}
	}

	if (nChar == VK_RETURN) {
		if (phase == 1) { // phase1為目錄
			phase = sub_phase + 1; // 選擇關卡
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
		if (phase > 1 && phase <= 5) {	//關卡
			_isRightRun = 0;
			player1.StopAnimation();
		}
	}

	if (nChar == VK_LEFT) {
		if (phase > 1 && phase <= 5) {	//關卡
			_isLeftRun = 0;
			player1.StopAnimation();
		}
	}

	if (nChar == VK_UP) {
		_isUpRun = 0;
	}

	if (nChar == 0x44) {
		_P2isRightRun = 0;
	}

	if (nChar == 0x41) {
		_P2isLeftRun = 0;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
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
		brick.ShowBitmap();
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