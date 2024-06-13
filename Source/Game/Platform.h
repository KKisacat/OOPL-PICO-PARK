#pragma once

#include "../Library/gameutil.h"
#include "Character.h"

using namespace game_framework;

class Platform
{
public:
	Platform();
	CMovingBitmap image;
	CMovingBitmap image2;
	CMovingBitmap pFlag;
	CMovingBitmap pFlag2;

	bool platformP1Overlap;
	bool platformP2Overlap;

	void MovePlatform(CMovingBitmap &platform_image, CMovingBitmap &pFlag, Character &character1, Character &character2, std::vector<CMovingBitmap> &box_blocks, int highest, int lowest, bool isPlatformUp);

	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
};