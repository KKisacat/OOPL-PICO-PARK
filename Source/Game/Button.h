#pragma once

#include "../Library/gameutil.h"
#include "Character.h"

using namespace game_framework;

class Button
{
public:
	Button();
	//第一關
	CMovingBitmap button_image;
	CMovingBitmap bridge;
	bool buttonOverlap;
	bool bridgeP1Overlap;
	bool bridgeP2Overlap;
	//第三關
	bool button3Overlap;
	CMovingBitmap bridge3;
	CMovingBitmap button3;
	CMovingBitmap rolling_wall3;
	std::vector<CMovingBitmap> buttons_level3 = { CMovingBitmap(), CMovingBitmap(), CMovingBitmap(), CMovingBitmap() };
	std::vector<CMovingBitmap> rolling_walls = { CMovingBitmap(), CMovingBitmap(), CMovingBitmap(), CMovingBitmap() };
	int numOfButtonPressed = 0;

	void PressButton(Character &character1, Character &character2, int threshold);
	void PressButtonBridgeThree(Character &character1, Character &character2, int threshold, std::vector<CMovingBitmap> &button_blocks);
	int CheckButtonPressed(Character &character1, Character &character2, std::vector<CMovingBitmap> &button_blocks);
	void RollWall(int numOfButtonPressed, std::vector<CMovingBitmap> &button_blocks);

	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
};