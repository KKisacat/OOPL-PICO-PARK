
#pragma once

#include "../Library/gameutil.h"
#include "Character.h"
#include "Key.h"
#include "Platform.h"
#include "Box.h"
#include "AutoObject.h"
#include "Button.h"

using namespace game_framework;

class Map
{
public:
	Map();
	Key key = Key();
	Platform platforms = Platform();
	Box boxes = Box();
	AutoObject autoObjects = AutoObject();
	Button buttonClass = Button();

	CMovingBitmap background;
	CMovingBitmap block[500];
	
	CMovingBitmap door;
	CMovingBitmap clear;
	CMovingBitmap crown[4];	
	
	CMovingBitmap wall_ignore[2];
	CMovingBitmap menu;
	
	std::vector<CMovingBitmap> box_blocks;
	std::vector<CMovingBitmap> button_blocks;

	//選單
	bool menuShow = false;
	int menu_options = 1;
	//鑰匙
	bool keyIgnore = false;
	//通關
	bool level_one_completed = 0;
	bool level_two_completed = 0;
	bool level_three_completed = 0;
	bool level_four_completed = 0;
	//重疊
	bool doorP1isOverlap;
	bool doorP2isOverlap;	
	
	void OnInit(Character &character1, Character &character2, int phase);
	void LoadAndResetAllBitmap();
	void SetMap1Block();
	void SetMap2Block();
	void SetMap3Block();
	void SetMap4Block();
	void PressButton(Character &character1, Character &character2);
	void GetKey(Character &character1, Character &character2);
	void MovePlatform(CMovingBitmap &platform_image, CMovingBitmap &pFlag, Character &character1, Character &character2, int highest, int lowest, bool isPlatformUp);
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
	void MoveAutoFloor(Character &character1, Character &character2);
	void MoveAutoWall(Character &character1, Character &character2);
	void RunMenuOptions(Character &character1, Character &character2, int &phase);

	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	void RefreshWall(Character &character1, Character &character2);
};
