#pragma once

#include "../Library/gameutil.h"

using namespace game_framework;

class Character
{
public:
	CMovingBitmap image;
	string name;
	vector<string> imgPaths;
	int x;
	int y;
	//左右
	bool isRightRun = 0;
	bool isLeftRun = 0;
	//跳
	int upTime = 0;
	bool isUpRun = 0;
	bool checkJumpble = 1; //不能連跳
	//重疊
	bool buttonOverlap;
	bool keyOverlap;
	bool bridgeOverlap;
	bool platformOverlap;
	bool characterIsOverlap; // 誰在誰頭上
	bool doorIsOverlap;
	//鑰匙跟隨
	int staybyCharacter = 0;
	//進大門
	bool characterIgnore = false;
	//碰撞
	std::vector<CMovingBitmap> wall;
	std::vector<CMovingBitmap> floor;

	Character(vector<string> imgPath, string name, int x, int y);
	void OnInit();
	void OnShow();
	void TryMoveRight(Character &other);
	void TryMoveLeft(Character &other);
	void TryMoveUp();
	void TryFall();
	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	void SetWallAndFloor(vector<CMovingBitmap> wall, vector<CMovingBitmap> floor);
};

