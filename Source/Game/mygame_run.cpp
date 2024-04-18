#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

//把所有碰撞寫成fuction
void CGameStateRun::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
{
	bool isMovable = true;

	for (CMovingBitmap target : targets) //遍歷所有會碰撞到的物件
	{
		//如果有任何重疊就不能走，a &= b 是 a = a & b
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable ) {
			return;
		}
	}
	player.SetTopLeft(player.GetLeft() + dx, player.GetTop() + dy);
}

//檢查是否可以跳躍
bool CGameStateRun::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
{
	bool isMovable;

	for (CMovingBitmap target : targets) //遍歷所有會碰撞到的物件
	{
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable) { //不能走代表碰到地板 碰到地板才能跳
			return true;
		}
	}
	return false;
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

void CGameStateRun::OnMove()							
{
	std::vector<CMovingBitmap> player1_wall = { player2, bridge, platform, block[23], block[24], block[45], block[90], block[95], block[96], block[100] };
	std::vector<CMovingBitmap> player2_wall = { player1, bridge, platform, block[23], block[24], block[45], block[90], block[95], block[96], block[100] };
	std::vector<CMovingBitmap> player1_floor = { player2, bridge, platform };
	std::vector<CMovingBitmap> player2_floor = { player1, bridge, platform };
	std::vector<CMovingBitmap> platform_block = { player1, player2 };

	for (int i = 116; i < 131; i++) {
		player1_wall.push_back(block[i]);
		player2_wall.push_back(block[i]);
	}

	for (int i = 101; i < 107; i++) {
		player1_wall.push_back(block[i]);
		player2_wall.push_back(block[i]);
	}

	for (int i = 106; i < 116; i++) {
		player1_floor.push_back(block[i]);
		player2_floor.push_back(block[i]);
	}

	for (int i = 0; i < 101; i++) {
		player1_floor.push_back(block[i]);
		player2_floor.push_back(block[i]);
	}


	//player1 move
	// 左右
	if (_isRightRun == 1)
	{
		if (player1.GetLeft() < 1800 && player2.GetLeft() > 0) {
			//在角色頭上可以一起移動
			P2onP1isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop() - 8, player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth());
			if (P2onP1isOverlap && !IsJumpable(player1, player1_wall, 8, 0)) {
				CheckMovable(player2, player2_wall, 8, 0);
			}
			CheckMovable(player1, player1_wall, 8, 0);
		}
		else {
			player1.SetTopLeft(player1.GetLeft(), player1.GetTop());
		}
		
	}
	else if (_isLeftRun == 1)
	{
		if (player1.GetLeft() > 0 && player2.GetLeft() < 1800) {
			P2onP1isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop() - 8, player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth());
			if (P2onP1isOverlap && !IsJumpable(player1, player1_wall, -8, 0)) {
				CheckMovable(player2, player2_wall, -8, 0);
			}
			CheckMovable(player1, player1_wall, -8, 0);
		}
		else {
			player1.SetTopLeft(player1.GetLeft(), player1.GetTop());
		}
	}

	// 跳躍
	if (_isP1UpRun && _P1UpTime <= 13)
	{
		if (_P1UpTime == 13) //跳到一定高度就掉落
		{
			_isP1UpRun = 0;
		}
		else
		{
			_P1UpTime++;
			CheckMovable(player1, player1_wall, 0, -10);
		}
	}
	else if (!_isP1UpRun) //掉落
	{
		_P1UpTime = 0;
		_P1JumpOnce = !IsJumpable(player1, player1_floor, 0, 10); //不能連跳
		CheckMovable(player1, player1_floor, 0, 10);	
	}

	// 死掉重生
	if (player1.GetTop() > 1024) {
		player1.SetTopLeft(player1.GetLeft() - 700, 0);
	}

	//player2 move
	if (_P2isRightRun == 1)
	{
		if (player2.GetLeft() < 1800 && player1.GetLeft() > 0) {
			P1onP2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop() - 8, player2.GetHeight(), player2.GetWidth());
			if (P1onP2isOverlap && !IsJumpable(player2, player2_wall, 8, 0)) {
				CheckMovable(player1, player1_wall, 8, 0);
			}
			CheckMovable(player2, player2_wall, 8, 0);
		}
		else {
			player2.SetTopLeft(player2.GetLeft(), player2.GetTop());
		}
		
	}
	else if (_P2isLeftRun == 1)
	{
		if (player2.GetLeft() > 0  && player1.GetLeft() < 1800) {
			P1onP2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop() - 8, player2.GetHeight(), player2.GetWidth());
			if (P1onP2isOverlap && !IsJumpable(player2, player2_wall, -8, 0)) {
				CheckMovable(player1, player1_wall, -8, 0);
			}
			CheckMovable(player2, player2_wall, -8, 0);
		}
		else {
			player2.SetTopLeft(player2.GetLeft(), player2.GetTop());
		}
		
	}

	if (_isP2UpRun && _P2UpTime <= 13)
	{
		if (_P2UpTime == 13) //跳到一定高度就掉落
		{
			_isP2UpRun = 0;
		}
		else
		{
			_P2UpTime++;
			CheckMovable(player2, player2_wall, 0, -10);
		}
	}
	else if (!_isP2UpRun) //掉落
	{
		_P2UpTime = 0;
		_P2JumpOnce = !IsJumpable(player2, player2_floor, 0, 10);
		CheckMovable(player2, player2_floor, 0, 10);
	}

	//墜落向後重生
	if (player2.GetTop() > 1024) {
		player2.SetTopLeft(player2.GetLeft() - 700, 0);
	}

	//按下按鈕
	buttonOverlap = CMovingBitmap::IsOverlap(player1, button) || CMovingBitmap::IsOverlap(player2, button);

	//橋
	if (button.GetFrameIndexOfBitmap() == 1) {
		if (block[45].GetLeft() - bridge.GetLeft() < 550) {
			bridgeP1Overlap = CMovingBitmap::IsOverlap(player1, bridge);
			bridgeP2Overlap = CMovingBitmap::IsOverlap(player2, bridge);
			if (bridgeP1Overlap) {
				player1.SetTopLeft(player1.GetLeft() - 3, player1.GetTop() + 10);
			}
			if (bridgeP2Overlap) {
				player2.SetTopLeft(player2.GetLeft() - 3, player2.GetTop() + 10);
			}
			bridge.SetTopLeft(bridge.GetLeft() - 3, bridge.GetTop());
		}

	}

	//鑰匙跟隨
	keyP1Overlap = CMovingBitmap::IsOverlap(player1, key);
	keyP2Overlap = CMovingBitmap::IsOverlap(player2, key);
	if (keyP1Overlap) {
		staybyPlayer1 = 1;
		staybyPlayer2 = 0;
	}
	if (staybyPlayer1 == 1) {
		key.SetTopLeft(player1.GetLeft() - 70, player1.GetTop() - 80);
	}
	if (keyP2Overlap) {
		staybyPlayer2 = 1;
		staybyPlayer1 = 0;
	}
	if (staybyPlayer2 == 1) {
		key.SetTopLeft(player2.GetLeft() - 70, player2.GetTop() - 80);
	}


	//平台
	P1onP2isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop(), player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop() - 10, player2.GetHeight(), player2.GetWidth());
	P2onP1isOverlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop() - 10, player1.GetHeight(), player1.GetWidth(), player2.GetLeft(), player2.GetTop(), player2.GetHeight(), player2.GetWidth());
	platformP1Overlap = CMovingBitmap::IsOverlap(player1.GetLeft(), player1.GetTop() + 10, player1.GetHeight(), player1.GetWidth(), platform.GetLeft(), platform.GetTop(), platform.GetHeight(), platform.GetWidth());
	platformP2Overlap = CMovingBitmap::IsOverlap(player2.GetLeft(), player2.GetTop() + 10, player2.GetHeight(), player2.GetWidth(), platform.GetLeft(), platform.GetTop(), platform.GetHeight(), platform.GetWidth());
	if ((platformP1Overlap && platformP2Overlap) || (P2onP1isOverlap && platformP1Overlap) || (P1onP2isOverlap && platformP2Overlap)) {
		//平台上升
		if (platform.GetTop() > 370) {
			platform.SetTopLeft(platform.GetLeft(), platform.GetTop() - 3);
			pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() - 3);
			CheckMovable(player1, player1_floor, 0, -3);
			CheckMovable(player2, player2_floor, 0, -3);
		}
		pFlag.SetFrameIndexOfBitmap(0);
	}
	else {
		//平台下降
		if (platform.GetTop() < 830) {
			if (!IsJumpable(platform, platform_block, 0, 3)) {
				//偷用別的函式，如果平台碰到障礙物不動會回傳ture，讓旗子也不動。反之持續下降會回傳false，旗子也下降。
				pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() + 3);
			}
			CheckMovable(platform, platform_block, 0, 3);
			CheckMovable(player1, player1_floor, 0, 3);
			CheckMovable(player2, player2_floor, 0, 3);
		}
		if (platformP1Overlap || platformP2Overlap) {
			pFlag.SetFrameIndexOfBitmap(1);
		}
		else {
			pFlag.SetFrameIndexOfBitmap(2);
		}
	}


	//大門
	doorP1isOverlap = CMovingBitmap::IsOverlap(player1, door);
	doorP2isOverlap = CMovingBitmap::IsOverlap(player2, door);


	//畫面移動
	if (((player1.GetLeft() + player2.GetLeft()) / 2) > 1000 )
	{
		background.SetTopLeft(background.GetLeft() - 5, 0);
		for (int i = 0; i < 131; i++) {
			block[i].SetTopLeft(block[i].GetLeft() - 5, block[i].GetTop());
		}
		player1.SetTopLeft(player1.GetLeft() - 5, player1.GetTop());
		player2.SetTopLeft(player2.GetLeft() - 5, player2.GetTop());
		button.SetTopLeft(button.GetLeft() - 5, button.GetTop());
		bridge.SetTopLeft(bridge.GetLeft() - 5, bridge.GetTop());
		key.SetTopLeft(key.GetLeft() - 5, key.GetTop());
		platform.SetTopLeft(platform.GetLeft() - 5, platform.GetTop());
		pFlag.SetTopLeft(pFlag.GetLeft() - 5, pFlag.GetTop());
		door.SetTopLeft(door.GetLeft() - 5, door.GetTop());
	}
	else if(((player1.GetLeft() + player2.GetLeft()) / 2) < 800)
	{
		background.SetTopLeft(background.GetLeft() + 5, 0);
		for (int i = 0; i < 131; i++) {
			block[i].SetTopLeft(block[i].GetLeft() + 5, block[i].GetTop());
		}
		player1.SetTopLeft(player1.GetLeft() + 5, player1.GetTop());
		player2.SetTopLeft(player2.GetLeft() + 5, player2.GetTop());
		button.SetTopLeft(button.GetLeft() + 5, button.GetTop());
		bridge.SetTopLeft(bridge.GetLeft() + 5, bridge.GetTop());
		key.SetTopLeft(key.GetLeft() + 5, key.GetTop());
		platform.SetTopLeft(platform.GetLeft() + 5, platform.GetTop());
		pFlag.SetTopLeft(pFlag.GetLeft() + 5, pFlag.GetTop());
		door.SetTopLeft(door.GetLeft() + 5, door.GetTop());
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
	player1.SetTopLeft(1020, 810);
	
	player2.LoadBitmapByString({ 
		"resources/player2Rightstand.bmp",
		"resources/player2RightRun1.bmp",
		"resources/player2RightRun2.bmp",
		"resources/player2RightRun3.bmp",
		"resources/player2RightRun4.bmp"
		}, RGB(0, 255, 0));
	player2.SetTopLeft(900, 810);

	button.LoadBitmapByString({ "resources/button1.bmp", "resources/button2.bmp" }, RGB(255, 255, 255));
	button.SetTopLeft(90 * 56, 859);
	button.SetAnimation(1000, true);

	bridge.LoadBitmapByString({ "resources/bridge13.bmp" }, RGB(255, 255, 255));
	bridge.SetTopLeft(90 * 54 - 30, 900);

	platform.LoadBitmapByString({ "resources/platform.bmp" }, RGB(255, 255, 255));
	platform.SetTopLeft(90 * 73 + 50, 830);
	pFlag.LoadBitmapByString({
		"resources/pFlag0.bmp",
		"resources/pFlag1.bmp",
		"resources/pFlag2.bmp"
		}, RGB(255, 255, 255));
	pFlag.SetTopLeft(90 * 73 + 50, 688);
	pFlag.SetAnimation(1000, true);
	pFlag.SetFrameIndexOfBitmap(2);

	key.LoadBitmapByString({ "resources/key.bmp", "resources/key_ignore.bmp"}, RGB(255, 255, 255));
	key.SetTopLeft(90 * 71, 360);

	door.LoadBitmapByString({ "resources/door.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
	door.SetTopLeft(90 * 85, 226);

	for (int i = 0; i < 4; i++) {
		crown[i].LoadBitmapByString({ "resources/crown.bmp" });
		crown[i].SetTopLeft(270 + i * 300, 270);
	}
	
	//起點牆壁
	for (int i = 120; i < 131; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(0, 900 - 90 * (i - 120));
	}
	//洞洞前的地板
	for (int i = 0; i < 24; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * i, 900);
	}
	//洞洞後的地板
	for (int i = 24; i < 45; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (i + 2), 900);
	}
	//第一個階梯
	for (int i = 90; i < 96; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (41 + i - 90), (900 - 90));
	}
	//第二個階梯
	for (int i = 96; i < 101; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (42 + i - 96), (900 - 90 * 2));
	}
	//移動平台後的地板
	for (int i = 45; i < 90; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (i + 8), 900);
	}
	//高牆
	for (int i = 101; i < 106; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * 78, 900 - 90 * (i - 100));
	}
	//終點平台
	for (int i = 106; i < 116; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (78 + i - 106), 900 - 90 * 6);
	}
	//終點牆壁
	for (int i = 116; i < 120; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * 87, 900 - 90 * (i - 109)); 
	}

	clear .LoadBitmapByString({ "resources/clear.bmp" }, RGB(0, 255, 0));
	clear.SetTopLeft(-262, 430);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_UP) {
		if (phase > 1 && phase <= 5) {	//關卡
			if (_P1JumpOnce == 0 ) //沒跳過才能跳，不然會連跳
			{
				_P1JumpOnce = 1;
				_isP1UpRun = 1;
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
		if (phase > 1 && phase <= 5) {	//關卡
			if (_P2JumpOnce == 0) //沒跳過才能跳，不然會連跳
			{
				_P2JumpOnce = 1;
				_isP2UpRun = 1;
			}
		}
	}

	if (nChar == 0x44) {  //player2 右鍵 D

		if (phase == 1) {	//目錄 phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡 phase = 2~5
			_P2isRightRun = 1;
			player2.SetAnimation(125, false);
		}
	}

	if (nChar == 0x41) {  //player2 左鍵 A

		if (phase == 1) {	//目錄
			if (sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡
			_P2isLeftRun = 1;
			player2.SetAnimation(125, false);
		}
	}

	if (nChar == VK_SPACE) {
		if (phase == 1) { // phase1為目錄
			phase = sub_phase + 1; // 選擇關卡
		}
		if (phase > 1 && phase <= 5) {	//關卡
			if (door.GetFrameIndexOfBitmap() == 1&& doorP2isOverlap) {
				player2Ignore = true;
			}
			if (doorP2isOverlap && staybyPlayer2 == 1) {
				door.SetFrameIndexOfBitmap(1);
				key.SetFrameIndexOfBitmap(1);
			}
		}
	}

	if (nChar == VK_RETURN) {
		if (phase == 1) { // phase1為目錄
			phase = sub_phase + 1; // 選擇關卡
		}
		if (phase > 1 && phase <= 5) {	//關卡
			if (door.GetFrameIndexOfBitmap() == 1 && doorP1isOverlap) {
				player1Ignore = true;
			}
			if (doorP1isOverlap && staybyPlayer1 == 1) {
				door.SetFrameIndexOfBitmap(1);
				key.SetFrameIndexOfBitmap(1);
			}
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
		_isP1UpRun = 0;
	}

	if (nChar == 0x44) { //P2右
		_P2isRightRun = 0;
		player2.StopAnimation();
	}

	if (nChar == 0x41) { //P2左
		_P2isLeftRun = 0;
		player2.StopAnimation();
	}

	if (nChar == 0x57) {  //player2 上鍵 W
		_isP2UpRun = 0;
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
		if (buttonOverlap) {
			button.SetFrameIndexOfBitmap(1);
		}
		button.ShowBitmap();
		pFlag.ShowBitmap();
		door.ShowBitmap();
		if (!player1Ignore) 
			player1.ShowBitmap();
		if (!player2Ignore)
			player2.ShowBitmap();
		for (int i = 0; i < 131; i++) {
			block[i].ShowBitmap();
		}
		bridge.ShowBitmap();
		platform.ShowBitmap();
		key.ShowBitmap();
		
	}
	if (player1Ignore && player2Ignore) {
		clear.ShowBitmap();
		if (clear.GetLeft() < 2101) {
			clear.SetTopLeft(clear.GetLeft() + 10, 430);
		}
		else if (clear.GetLeft() > 2101) {
			phase = 1;
			crown[0].ShowBitmap();
		}
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