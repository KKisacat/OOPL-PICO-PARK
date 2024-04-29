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
	//進大門 角色消失
	bool characterIgnore = false;

	//重疊
	bool characterIsOverlap; // 誰在誰頭上
	
	//碰撞
	std::vector<CMovingBitmap> blocks;

	Character(vector<string> imgPath, string name, int x, int y);
	void OnInit();
	void OnShow();
	void TryMoveRight(Character &other);
	void TryMoveLeft(Character &other);
	void TryMoveUp();
	void TryFall();
	void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);
	void SetWallAndFloor(vector<CMovingBitmap> blocks);
};

