#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
int _upTime;
int _downTime;
int _rightTime;
int _leftTime;
bool _isRightRun = 0;
bool _isLeftRun = 0;

void ResetMovingTime()
{
	_upTime = 0;
	_downTime = 0;
	_rightTime = 0;
	_leftTime = 0;
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
		if (_rightCrash == 0) {
			player1.SetTopLeft(player1.GetLeft() + 10, 843);
		}
		else if (_rightCrash == 1) {
			player1.SetTopLeft(player1.GetLeft(), 843);
		}

		isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		
		if (isOverlap) {
			_rightCrash = 1;
		}
		else if (!isOverlap) {
			_rightCrash = 0;
		}
		
		
	}
	else if (_isLeftRun == 1)
	{
		if (_leftCrash == 0) {
			player1.SetTopLeft(player1.GetLeft() - 10, 843);
		}
		else if (_leftCrash == 1) {
			player1.SetTopLeft(player1.GetLeft(), 843);
		}

		isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), brick.GetLeft(), brick.GetTop(), brick.GetHeight(), brick.GetWidth());
		
		if (isOverlap) {
			_leftCrash = 1;
		}
		else if (!isOverlap) {
			_leftCrash = 0;
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

	player1.LoadBitmapByString({ "resources/giraffe.bmp" });
	player1.SetTopLeft(350, 843);

	player2.LoadBitmapByString({ "resources/giraffe.bmp" });
	player2.SetTopLeft(210, 843);

	brick.LoadBitmapByString({ "resources/gray.bmp" });
	brick.SetTopLeft(280, 843);

	chest_and_key.LoadBitmapByString({ "resources/chest.bmp", "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
	chest_and_key.SetTopLeft(150, 430);

	bee.LoadBitmapByString({ "resources/bee_1.bmp", "resources/bee_2.bmp" });
	bee.SetTopLeft(462, 265);

	ball.LoadBitmapByString({ "resources/ball-3.bmp", "resources/ball-3.bmp", "resources/ball-2.bmp", "resources/ball-1.bmp", "resources/ball-ok.bmp" });
	ball.SetTopLeft(150, 430);

	for (int i = 0; i < 3; i++) {
		door[i].LoadBitmapByString({ "resources/door_close.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
		door[i].SetTopLeft(462 - 100 * i, 265);
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_UP) {
		//_upTime++;
		//player1.SetTopLeft(150 + (10 * _rightTime) - (10 * _leftTime), 265 - (10 * _upTime) + (10 * _downTime));
	}

	if (nChar == VK_RIGHT) {

		if (phase == 1) {	//目錄 phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡 phase = 2~5
			_isRightRun = 1;
		}
	}

	if (nChar == VK_LEFT) {

		if (phase == 1) {	//目錄
			if(sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡
			_isLeftRun = 1;
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
		}else if (phase == 3) {
			ResetMovingTime();
			if (sub_phase == 1) {
				sub_phase += validate_phase_3();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 4) {
			ResetMovingTime();
			if (sub_phase == 1) {
				sub_phase += validate_phase_4();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 5) {
			ResetMovingTime();
			if (sub_phase == 1) {
				sub_phase += validate_phase_5();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 6) {
			ResetMovingTime();
			if (sub_phase == 1) {
				sub_phase += validate_phase_6();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
				GotoGameState(GAME_STATE_OVER);
			}
		}
		*/
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) {
		_isRightRun = 0;
	}

	if (nChar == VK_LEFT) {
		_isLeftRun = 0;
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