#pragma once
#include "stdafx.h"
#include "Box.h"

Box::Box() {

}

void Box::TryFallBox(CMovingBitmap &box_image, int height, std::vector<CMovingBitmap> &box_blocks) {
	if (box_image.GetTop() <= height) {
		CheckMovable(box_image, box_blocks, 0, 10);
	}
}

//推箱子2
void Box::PushBox2(Character &character1, Character &character2, int x, std::vector<CMovingBitmap> &box_blocks) {

	boxP1isOverlap = CMovingBitmap::IsOverlap(
		character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		box2.GetLeft() - x, box2.GetTop(), box2.GetHeight(), box2.GetWidth()
	);
	boxP2isOverlap = CMovingBitmap::IsOverlap(
		character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth(),
		box2.GetLeft() - x, box2.GetTop(), box2.GetHeight(), box2.GetWidth()
	);
	P1P2isOverlap = CMovingBitmap::IsOverlap(
		character1.image.GetLeft() - x * 2, character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth()
	);
	P2P1isOverlap = CMovingBitmap::IsOverlap(
		character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		character2.image.GetLeft() - x * 2, character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth()
	);
	if (boxP1isOverlap && boxP2isOverlap) {
		CheckMovable(box2, box_blocks, x, 0);
		box2.SetFrameIndexOfBitmap(0);
	}
	else if (boxP1isOverlap && P1P2isOverlap) {
		CheckMovable(box2, box_blocks, x, 0);
		box2.SetFrameIndexOfBitmap(0);
	}
	else if (boxP2isOverlap && P2P1isOverlap) {
		CheckMovable(box2, box_blocks, x, 0);
		box2.SetFrameIndexOfBitmap(0);
	}
}

//推箱子2人換圖
void Box::PushBox2ChangeImage(Character &character1, Character &character2, int x) {

	boxP1isOverlap = CMovingBitmap::IsOverlap(
		character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		box2.GetLeft() - x, box2.GetTop(), box2.GetHeight(), box2.GetWidth()
	);
	boxP2isOverlap = CMovingBitmap::IsOverlap(
		character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth(),
		box2.GetLeft() - x, box2.GetTop(), box2.GetHeight(), box2.GetWidth()
	);
	P2P1isOverlap = CMovingBitmap::IsOverlap(
		character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		character2.image.GetLeft() - x * 2, character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth()
	);

	if (boxP1isOverlap) {
		box2.SetFrameIndexOfBitmap(1);
	}
	else if (boxP2isOverlap && P2P1isOverlap) {
		box2.SetFrameIndexOfBitmap(1);
	}
}

//推箱子1人
void Box::PushBox(Character &character, CMovingBitmap &box, int x, std::vector<CMovingBitmap> &box_blocks) {

	boxisOverlap = CMovingBitmap::IsOverlap(
		character.image.GetLeft(), character.image.GetTop(), character.image.GetHeight(), character.image.GetWidth(),
		box.GetLeft() - x, box.GetTop(), box.GetHeight(), box.GetWidth()
	);

	if (boxisOverlap) {
		CheckMovable(box, box_blocks, x, 0);
		box.SetFrameIndexOfBitmap(0);
	}
	if (!boxisOverlap) {
		box.SetFrameIndexOfBitmap(1);
	}
}

//第三關推箱子
void Box::PushBoxLevelThree(Character &character, CMovingBitmap &box, int x, int box_name) {
	boxisOverlap = CMovingBitmap::IsOverlap(
		character.image.GetLeft(), character.image.GetTop(), character.image.GetHeight(), character.image.GetWidth(),
		box.GetLeft() - x, box.GetTop(), box.GetHeight(), box.GetWidth()
	);
	box12isOverlap = CMovingBitmap::IsOverlap(
		box3_1.GetLeft(), box3_1.GetTop(), box3_1.GetHeight(), box3_1.GetWidth(),
		box3_2.GetLeft() - 16, box3_2.GetTop(), box3_2.GetHeight(), box3_2.GetWidth()
	);
	box23isOverlap = CMovingBitmap::IsOverlap(
		box3_2.GetLeft(), box3_2.GetTop(), box3_2.GetHeight(), box3_2.GetWidth(),
		box3_3.GetLeft() - 16, box3_3.GetTop(), box3_3.GetHeight(), box3_3.GetWidth()
	);
	if (boxisOverlap && box12isOverlap && box23isOverlap) {
		CheckMovable(box3_1, box3_1_blocks, x, 0);
		box3_1.SetFrameIndexOfBitmap(0);
		CheckMovable(box3_2, box3_2_blocks, x, 0);
		box3_2.SetFrameIndexOfBitmap(0);
		CheckMovable(box3_3, box3_3_blocks, x, 0);
		box3_3.SetFrameIndexOfBitmap(0);
	}
	else if (boxisOverlap && box12isOverlap && box_name != 3) {
		CheckMovable(box3_1, box3_1_blocks, x, 0);
		box3_1.SetFrameIndexOfBitmap(0);
		CheckMovable(box3_2, box3_2_blocks, x, 0);
		box3_2.SetFrameIndexOfBitmap(0);
	}
	else if (boxisOverlap && box23isOverlap && box_name != 1) {
		CheckMovable(box3_2, box3_2_blocks, x, 0);
		box3_2.SetFrameIndexOfBitmap(0);
		CheckMovable(box3_3, box3_3_blocks, x, 0);
		box3_3.SetFrameIndexOfBitmap(0);
	}
	else if (boxisOverlap) {
		CheckMovable(box, box3_1_blocks, x, 0);
		CheckMovable(box, box3_2_blocks, x, 0);
		CheckMovable(box, box3_3_blocks, x, 0);
		box.SetFrameIndexOfBitmap(0);
	}
}

//第三關箱子在頭上
void Box::MoveHeadBox(Character &character, int x, Character &character2) {
	box3_1isOnHead = CMovingBitmap::IsOverlap(
		character.image.GetLeft(), character.image.GetTop() - 8, character.image.GetHeight(), character.image.GetWidth(),
		box3_1.GetLeft(), box3_1.GetTop(), box3_1.GetHeight(), box3_1.GetWidth()
	);

	playerIsOnBox = CMovingBitmap::IsOverlap(
		box3_1.GetLeft(), box3_1.GetTop() - 8, box3_1.GetHeight(), box3_1.GetWidth(),
		character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth()
	);

	if (box3_1isOnHead && !IsJumpable(character.image, character.blocks, x, 0)) { //防止變成跑步機
		CheckMovable(box3_1, box3_1_blocks, x, 0);
		if (playerIsOnBox && !IsJumpable(box3_1, box3_1_blocks, x, 0)) {
			CheckMovable(character2.image, character2.blocks, x, 0);
		}
	}
	if (character.characterIsOverlap) {
		MoveHeadBox(character2, x, character);
	}
}

void Box::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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

bool Box::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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