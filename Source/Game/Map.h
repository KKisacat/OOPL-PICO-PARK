#pragma once

#include "../Library/gameutil.h"
#include "Character.h"

using namespace game_framework;

class Map
{
public:
	Map();
	CMovingBitmap background;
	CMovingBitmap block[500];
	CMovingBitmap button;
	CMovingBitmap bridge;
	CMovingBitmap platform;
	CMovingBitmap pFlag;
	CMovingBitmap key;
	CMovingBitmap door;
	CMovingBitmap clear;


	//Æ_°Í
	bool keyIgnore = false;
	//³qÃö
	bool level_one_completed = 0;
	//­«Å|
	bool buttonOverlap;
	bool keyP1Overlap;
	bool keyP2Overlap;
	bool bridgeP1Overlap;
	bool bridgeP2Overlap;
	bool platformP1Overlap;
	bool platformP2Overlap;
	bool doorP1isOverlap;
	bool doorP2isOverlap;
	//Æ_°Í¸òÀH
	int staybyCharacter1 = 0;
	int staybyCharacter2 = 0;
	
	void OnInit();
	void SetMap1Block();
	void SetMap2Block();
	void PressButton(Character &character1, Character &character2);
	void GetKey(Character &character1, Character &character2);
	void MovePlatform(Character &character1, Character &character2);
	void CheckDoorOverlap(Character &character1, Character &character2);
	void RollScreen(Character &character1, Character &character2);


	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);







};
