#pragma once
#include "stdafx.h"
#include "Button.h"

Button::Button() {

}

void Button::PressButton(Character &character1, Character &character2, int threshold) {

	//���U���s
	buttonOverlap = CMovingBitmap::IsOverlap(character1.image, button_image) || CMovingBitmap::IsOverlap(character2.image, button_image);

	//��
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
	
//�ĤT������h��
void Button::PressButtonBridgeThree(Character &character1, Character &character2, int threshold, std::vector<CMovingBitmap> &button_blocks) {

	//���U���s
	button3Overlap = CMovingBitmap::IsOverlap(character1.image, button3) || CMovingBitmap::IsOverlap(character2.image, button3);

	//����h��
	if (button3.GetFrameIndexOfBitmap() == 1) {
		if (bridge3.GetLeft() - threshold > 0) {
			CheckMovable(bridge3, button_blocks, -5, 0);
		}
		if (rolling_wall3.GetTop() > -10) {
			CheckMovable(rolling_wall3, button_blocks, 0, -10);
		}
	}
}

//�ĤT�����|�ӹh�����s
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

//�ĤT�����|�ӹh��
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

	for (CMovingBitmap target : targets) //�M���Ҧ��|�I���쪺����
	{
		//�p�G�������|�N���ਫ�Aa &= b �O a = a & b
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

	for (CMovingBitmap target : targets) //�M���Ҧ��|�I���쪺����
	{
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable) { //���ਫ�N��I��a�O �I��a�O�~���
			return true;
		}
	}
	return false;
}
