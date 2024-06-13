#pragma once
#include "stdafx.h"
#include "AutoObject.h"

AutoObject::AutoObject() {

}

//第四關自動平台
void AutoObject::MoveAutoFloor(Character &character1, Character &character2, std::vector<CMovingBitmap> &box_blocks) {
	character2.characterIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop() - 10, character2.image.GetHeight(), character2.image.GetWidth());
	character1.characterIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() - 10, character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth());
	autoFloorP1isOverlap = CMovingBitmap::IsOverlap(
		character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		auto_floor.GetLeft(), auto_floor.GetTop() - 8, auto_floor.GetHeight(), auto_floor.GetWidth()
	);
	autoFloorP2isOverlap = CMovingBitmap::IsOverlap(
		character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth(),
		auto_floor.GetLeft(), auto_floor.GetTop() - 8, auto_floor.GetHeight(), auto_floor.GetWidth()
	);

	// 到最高點 & 最低點
	if (auto_floor.GetTop() < 500) {
		isAutoFloorMoveUp = false;
	}
	if (auto_floor.GetTop() > 830) {
		isAutoFloorMoveUp = true;
	}
	if (isAutoFloorMoveUp) {
		if (autoFloorP1isOverlap) {
			CheckMovable(character1.image, character1.blocks, 0, -4);
			if (character1.characterIsOverlap) {
				CheckMovable(character2.image, character2.blocks, 0, -4);
			}
		}
		if (autoFloorP2isOverlap) {
			CheckMovable(character2.image, character2.blocks, 0, -4);
			if (character2.characterIsOverlap) {
				CheckMovable(character1.image, character1.blocks, 0, -4);
			}
		}
		CheckMovable(auto_floor, box_blocks, 0, -4);
	}
	else {
		CheckMovable(auto_floor, box_blocks, 0, 4);
		if (autoFloorP1isOverlap) {
			CheckMovable(character1.image, character1.blocks, 0, 4);
			if (character1.characterIsOverlap) {
				CheckMovable(character2.image, character2.blocks, 0, 4);
			}
		}
		if (autoFloorP2isOverlap) {
			CheckMovable(character2.image, character2.blocks, 0, 4);
			if (character2.characterIsOverlap) {
				CheckMovable(character1.image, character1.blocks, 0, 4);
			}
		}
	}
}

//第四關自動牆
void AutoObject::MoveAutoWall(Character &character1, Character &character2, int left_threshold, int right_threshold, std::vector<CMovingBitmap> &box_blocks) {
	bool P1onP2LeftIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft() - 8, character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth());
	bool P2onP1LeftIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft() - 8, character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth());
	autoWallP1isOverlapLeft = CMovingBitmap::IsOverlap(
		character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		auto_wall.GetLeft() - 8, auto_wall.GetTop(), auto_wall.GetHeight(), auto_wall.GetWidth()
	);
	autoWallP2isOverlapLeft = CMovingBitmap::IsOverlap(
		character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth(),
		auto_wall.GetLeft() - 8, auto_wall.GetTop(), auto_wall.GetHeight(), auto_wall.GetWidth()
	);
	autoWallP1isOverlapRight = CMovingBitmap::IsOverlap(
		character1.image.GetLeft() - 8, character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		auto_wall.GetLeft(), auto_wall.GetTop(), auto_wall.GetHeight(), auto_wall.GetWidth()
	);
	autoWallP2isOverlapRight = CMovingBitmap::IsOverlap(
		character2.image.GetLeft() - 8, character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth(),
		auto_wall.GetLeft(), auto_wall.GetTop(), auto_wall.GetHeight(), auto_wall.GetWidth()
	);
	// 最左 & 最右
	if (auto_wall.GetLeft() < left_threshold) {
		isAutoWallMoveLeft = false;
	}
	if (auto_wall.GetLeft() > right_threshold) {
		isAutoWallMoveLeft = true;
	}
	if (isAutoWallMoveLeft) {
		if (autoWallP1isOverlapLeft) {
			CheckMovable(character1.image, character1.blocks, -4, 0);
			if (P2onP1LeftIsOverlap) {
				CheckMovable(character2.image, character2.blocks, -4, 0);
			}
		}
		if (autoWallP2isOverlapLeft) {
			CheckMovable(character2.image, character2.blocks, -4, 0);
			if (P1onP2LeftIsOverlap) {
				CheckMovable(character1.image, character1.blocks, -4, 0);
			}
		}
		CheckMovable(auto_wall, box_blocks, -4, 0);
	}
	else {
		if (autoWallP1isOverlapRight) {
			CheckMovable(character1.image, character1.blocks, 4, 0);
			if (P1onP2LeftIsOverlap) {
				CheckMovable(character2.image, character2.blocks, 4, 0);
			}
		}
		if (autoWallP2isOverlapRight) {
			CheckMovable(character2.image, character2.blocks, 4, 0);
			if (P2onP1LeftIsOverlap) {
				CheckMovable(character1.image, character1.blocks, 4, 0);
			}
		}
		CheckMovable(auto_wall, box_blocks, 4, 0);
	}
}

void AutoObject::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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

