#pragma once

#include "../Library/gameutil.h"
#include "Character.h"

using namespace game_framework;

class Box
{
public:
	Box();
	//第二關
	CMovingBitmap box1;
	CMovingBitmap box2;
	CMovingBitmap box3;
	bool boxisOverlap;
	bool boxP1isOverlap;
	bool boxP2isOverlap;
	bool P1P2isOverlap;
	bool P2P1isOverlap;
	//第三關
	CMovingBitmap box3_1;
	CMovingBitmap box3_2;
	CMovingBitmap box3_3;
	std::vector<CMovingBitmap> box3_1_blocks;
	std::vector<CMovingBitmap> box3_2_blocks;
	std::vector<CMovingBitmap> box3_3_blocks;
	bool box3_1isOnHead;
	bool boxLevel3isOverlap;
	bool box12isOverlap;
	bool box23isOverlap;
	bool playerIsOnBox;

	//第二關
	void TryFallBox(CMovingBitmap &box, int height, std::vector<CMovingBitmap> &box_blocks);
	void PushBox2(Character &character1, Character &character2, int x, std::vector<CMovingBitmap> &box_blocks);
	void PushBox2ChangeImage(Character &character, Character &character2, int x);
	void PushBox(Character &character, CMovingBitmap &box, int x, std::vector<CMovingBitmap> &box_blocks);
	//第三關
	void PushBoxLevelThree(Character &character, CMovingBitmap &box, int x, int box_name);
	void MoveHeadBox(Character &character, int x, Character &character2);

	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
};