#include "stdafx.h"
#include "Character.h"

Character::Character(vector<string> imgPaths, string name, int x, int y) {
	this->name = name;
	this->imgPaths = imgPaths;
	this->x = x;
	this->y = y;
}

void Character::OnInit() {
	image.LoadBitmapByString(imgPaths, RGB(0, 255, 0));
	image.SetTopLeft(x, y);
}

void Character::OnShow() {
	if (!characterIgnore)
		image.ShowBitmap();
}

//往右走
void Character::TryMoveRight(Character &other) {
	if (this->image.GetLeft() < 1800 && other.image.GetLeft() > 0) {
		//在角色頭上可以一起移動 (this頭上有沒有other)
		characterIsOverlap = CMovingBitmap::IsOverlap(
			this->image.GetLeft(), this->image.GetTop() - 8, this->image.GetHeight(), this->image.GetWidth(), 
			other.image.GetLeft(), other.image.GetTop(), other.image.GetHeight(), other.image.GetWidth()
		);
		if (characterIsOverlap && !IsJumpable(this->image, this->blocks, 8, 0)) { //防止變成跑步機
			CheckMovable(other.image, other.blocks, 8, 0);
		}
		CheckMovable(this->image, this->blocks, 8, 0);
	}
}

//往左走
void Character::TryMoveLeft(Character &other) {
	if (this->image.GetLeft() > 0 && other.image.GetLeft() < 1800) {
		characterIsOverlap = CMovingBitmap::IsOverlap(
			this->image.GetLeft(), this->image.GetTop() - 8, this->image.GetHeight(), this->image.GetWidth(),
			other.image.GetLeft(), other.image.GetTop(), other.image.GetHeight(), other.image.GetWidth()
		);
		if (characterIsOverlap && !IsJumpable(this->image, this->blocks, -8, 0)) {
			CheckMovable(other.image, other.blocks, -8, 0);
		}
		CheckMovable(this->image, this->blocks, -8, 0);
	}
}

//跳
void Character::TryMoveUp() {
	if (this->upTime == 13) //跳到一定高度就掉落
	{
		this->isUpRun = 0;
	}
	else
	{
		this->upTime++;
		CheckMovable(this->image, this->blocks, 0, -10);
	}
}

//掉落
void Character::TryFall() {
	this->upTime = 0;
	this->checkJumpble = IsJumpable(this->image, this->blocks, 0, 10); //不能連跳
	CheckMovable(this->image, this->blocks, 0, 10);
}

//把所有碰撞寫成fuction
void Character::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
{
	bool isMovable = true;

	for (CMovingBitmap target : targets) //遍歷所有會碰撞到的物件
	{
		//如果有任何重疊就不能走，a &= b 是 a = a & b
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable) {
			return;
		}
	}
	player.SetTopLeft(player.GetLeft() + dx, player.GetTop() + dy);
}

bool Character::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
{
	bool isMovable;

	for (CMovingBitmap target : targets) //遍歷所有會碰撞到的物件
	{
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable) { //不能走代表碰到地板 碰到地板才能跳
			return true;
		}
	}
	return false;
}

void Character::SetWallAndFloor(vector<CMovingBitmap> blocks) {
	this->blocks = blocks;
}