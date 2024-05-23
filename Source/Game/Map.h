
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
	CMovingBitmap crown[4];
	CMovingBitmap box1;
	CMovingBitmap box2;
	CMovingBitmap box3;
	std::vector<CMovingBitmap> buttons = { CMovingBitmap(), CMovingBitmap(), CMovingBitmap(), CMovingBitmap() };
	std::vector<CMovingBitmap> rolling_walls = { CMovingBitmap(), CMovingBitmap(), CMovingBitmap(), CMovingBitmap() };
	CMovingBitmap box3_1;
	CMovingBitmap box3_2;
	CMovingBitmap box3_3;
	CMovingBitmap bridge3;
	CMovingBitmap button3;
	CMovingBitmap rolling_wall3;
	CMovingBitmap wall_ignore[2];
	

	std::vector<CMovingBitmap> box_blocks;
	std::vector<CMovingBitmap> box3_1_blocks;
	std::vector<CMovingBitmap> box3_2_blocks;
	std::vector<CMovingBitmap> box3_3_blocks;
	std::vector<CMovingBitmap> button_blocks;


	//鑰匙
	bool keyIgnore = false;
	//通關
	bool level_one_completed = 0;
	bool level_two_completed = 0;
	bool level_three_completed = 0;
	//重疊
	bool buttonOverlap;
	bool keyP1Overlap;
	bool keyP2Overlap;
	bool bridgeP1Overlap;
	bool bridgeP2Overlap;
	bool platformP1Overlap;
	bool platformP2Overlap;
	bool doorP1isOverlap;
	bool doorP2isOverlap;
	//第二關
	bool boxisOverlap;
	bool boxP1isOverlap;
	bool boxP2isOverlap;
	bool P1P2isOverlap;
	bool P2P1isOverlap;
	//第三關
	bool box3_1isOnHead;
	bool box12isOverlap;
	bool box23isOverlap;
	bool playerIsOnBox;
	int numOfButtonPressed = 0;
	bool button3Overlap;

	//鑰匙跟隨
	int staybyCharacter1 = 0;
	int staybyCharacter2 = 0;
	
	void OnInit(Character &character1, Character &character2, int phase);
	void LoadAndResetAllBitmap();
	void SetMap1Block();
	void SetMap2Block();
	void SetMap3Block();
	void PressButton(Character &character1, Character &character2);
	void GetKey(Character &character1, Character &character2);
	void MovePlatform(Character &character1, Character &character2);
	void CheckDoorOverlap(Character &character1, Character &character2);
	void RollScreen(Character &character1, Character &character2);
	void TryFallBox(CMovingBitmap &box, int height);
	void PushBox(Character &character,CMovingBitmap &box, int x);
	void PushBox2(Character &character1, Character &character2, int x);
	void PushBox2ChangeImage(Character &character, Character &character2, int x);
	void MoveHeadBox(Character &character, int x, Character &character2);
	int CheckButtonPressed(Character &character1, Character &character2);
	void PushBoxLevelThree(Character &character, CMovingBitmap &box, int x, int box_name);
	void RollWall(int numOfButtonPressed);
	void PressButtonBridgeThree(Character &character1, Character &character2);


	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	void RefreshWall(Character &character1, Character &character2);






};
