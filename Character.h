#pragma once

#include "../Library/gameutil.h"

using namespace game_framework;

class Character
{
public:
	CMovingBitmap image;
	string name;
	vector<string> imgPaths;
	//左右
	bool isRightRun = 0;
	bool isLeftRun = 0;
	//跳
	int upTime = 0;
	bool isUpRun = 0;
	bool jumpOnce = 0;
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

	Character(vector<string> imgPath, string name);
	void OnInit();
};

