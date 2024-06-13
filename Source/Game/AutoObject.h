#pragma once

#include "../Library/gameutil.h"
#include "Character.h"

using namespace game_framework;

class AutoObject 
{
public:
	AutoObject();
	//²Ä¥|Ãö
	CMovingBitmap auto_floor;
	CMovingBitmap auto_wall;
	bool isAutoFloorMoveUp = true;
	bool isAutoWallMoveLeft = true;
	bool autoFloorP1isOverlap;
	bool autoFloorP2isOverlap;
	bool autoWallP1isOverlapLeft;
	bool autoWallP2isOverlapLeft;
	bool autoWallP1isOverlapRight;
	bool autoWallP2isOverlapRight;

	void MoveAutoFloor(Character &character1, Character &character2, std::vector<CMovingBitmap> &box_blocks);
	void MoveAutoWall(Character &character1, Character &character2, int left_threshold, int right_threshold, std::vector<CMovingBitmap> &box_blocks);

	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);

};
