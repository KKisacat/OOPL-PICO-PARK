#pragma once
#include "stdafx.h"
#include "Button.h"

Button::Button() {

}

void Button::PressButton(Character &character1, Character &character2, int threshold) {

	//按下按鈕
	buttonOverlap = CMovingBitmap::IsOverlap(character1.image, button_image) || CMovingBitmap::IsOverlap(character2.image, button_image);

	//橋
	if (button_image.GetFrameIndexOfBitmap() == 1) {
		if (threshold - bridge.GetLeft() < 550) {
			bridgeP1Overlap = CMovingBitmap::IsOverlap(character1.image, bridge);
			bridgeP2Overlap = CMovingBitmap::IsOverlap(character2.image, bridge);
			if (bridgeP1Overlap) {
				character1.image.SetTopLeft(character1.image.GetLeft() - 3, character1.image.GetTop() + 10);
			}
			if (bridgeP2Overlap) {
				character2.image.SetTopLeft(character2.image.GetLeft() - 3, character2.image.GetTop() + 10);
			}
			bridge.SetTopLeft(bridge.GetLeft() - 3, bridge.GetTop());
		}
	}
}
	
//第三關橋跟閘門
void Button::PressButtonBridgeThree(Character &character1, Character &character2, int threshold, std::vector<CMovingBitmap> &button_blocks) {

	//按下按鈕
	button3Overlap = CMovingBitmap::IsOverlap(character1.image, button3) || CMovingBitmap::IsOverlap(character2.image, button3);

	//橋跟閘門
	if (button3.GetFrameIndexOfBitmap() == 1) {
		if (bridge3.GetLeft() - threshold > 0) {
			CheckMovable(bridge3, button_blocks, -5, 0);
		}
		if (rolling_wall3.GetTop() > -10) {
			CheckMovable(rolling_wall3, button_blocks, 0, -10);
		}
	}
}

//第三關的四個閘門按鈕
int Button::CheckButtonPressed(Character &character1, Character &character2, std::vector<CMovingBitmap> &button_blocks) {
	numOfButtonPressed = 0;
	for (int i = 0; i < 4; i++) {
		buttons_level3[i].SetFrameIndexOfBitmap(0);
		if (IsJumpable(buttons_level3[i], button_blocks, 0, -10)) {
			buttons_level3[i].SetFrameIndexOfBitmap(1);
			numOfButtonPressed++;
		}
	}
	return numOfButtonPressed;
}

//第三關的四個閘門
void Button::RollWall(int numOfButtonPressed, std::vector<CMovingBitmap> &button_blocks) {
	for (int i = 0; i < 4 - numOfButtonPressed; i++) {
		if (rolling_walls[i].GetTop() > -9) {
			CheckMovable(rolling_walls[i], button_blocks, 0, -10);
		}
	}
	for (int i = 3; i > 3 - numOfButtonPressed; i--) {
		if (rolling_walls[i].GetTop() < 270) {
			CheckMovable(rolling_walls[i], button_blocks, 0, 10);
		}
	}
}

void Button::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
{
	bool isMovable = true;

	for (CMovingBitmap target : targets) //遍歷所有會碰撞到的物件
	{
		//如果有任何重疊就不能走，a &= b 是 a = a & b
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable) {
			return;
		}
	}
	player.SetTopLeft(player.GetLeft() + dx, player.GetTop() + dy);
}

bool Button::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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
