#pragma once
#include "stdafx.h"
#include "Platform.h"

Platform::Platform() {

}

void Platform::MovePlatform(CMovingBitmap &platform_image, CMovingBitmap &pFlag, Character &character1, Character &character2, std::vector<CMovingBitmap> &box_blocks, int highest, int lowest, bool isPlatformUp) { // isPlatformU在看平台是踩著往上or踩著往下
	//平台
	character2.characterIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop() - 10, character2.image.GetHeight(), character2.image.GetWidth());
	character1.characterIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() - 10, character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth());
	platformP1Overlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() + 10, character1.image.GetHeight(), character1.image.GetWidth(), platform_image.GetLeft(), platform_image.GetTop(), platform_image.GetHeight(), platform_image.GetWidth());
	platformP2Overlap = CMovingBitmap::IsOverlap(character2.image.GetLeft(), character2.image.GetTop() + 10, character2.image.GetHeight(), character2.image.GetWidth(), platform_image.GetLeft(), platform_image.GetTop(), platform_image.GetHeight(), platform_image.GetWidth());
	if ((platformP1Overlap && platformP2Overlap) || (character1.characterIsOverlap && platformP1Overlap) || (character2.characterIsOverlap && platformP2Overlap)) {
		if (isPlatformUp) { //踩著平台上升
			if (platform_image.GetTop() > highest) {
				if (!IsJumpable(platform_image, box_blocks, 0, -3)) {
					//偷用別的函式，如果平台碰到障礙物不動會回傳ture，讓旗子也不動。反之持續下降會回傳false，旗子也下降。
					pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() - 3);
				}
				CheckMovable(platform_image, box_blocks, 0, -3);
				CheckMovable(character1.image, character1.blocks, 0, -3);
				CheckMovable(character2.image, character2.blocks, 0, -3);
			}
		}
		else { //踩著平台下降
			if (platform_image.GetTop() < lowest) {
				if (!IsJumpable(platform_image, box_blocks, 0, 3)) {
					//偷用別的函式，如果平台碰到障礙物不動會回傳ture，讓旗子也不動。反之持續下降會回傳false，旗子也下降。
					pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() + 3);
				}
				CheckMovable(platform_image, box_blocks, 0, 3);
				CheckMovable(character1.image, character1.blocks, 0, 3);
				CheckMovable(character2.image, character2.blocks, 0, 3);
			}
		}
		pFlag.SetFrameIndexOfBitmap(0);
	}
	else {
		if (isPlatformUp) { //沒有踩著平台的自動下降
			if (platform_image.GetTop() < lowest) {
				if (!IsJumpable(platform_image, box_blocks, 0, 3)) {
					//偷用別的函式，如果平台碰到障礙物不動會回傳ture，讓旗子也不動。反之持續下降會回傳false，旗子也下降。
					pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() + 3);
				}
				CheckMovable(platform_image, box_blocks, 0, 3);
				CheckMovable(character1.image, character1.blocks, 0, 3);
				CheckMovable(character2.image, character2.blocks, 0, 3);
			}
		}
		else { //沒有踩著平台的自動上升
			if (platform_image.GetTop() > highest) {
				if (!IsJumpable(platform_image, box_blocks, 0, -3)) {
					//偷用別的函式，如果平台碰到障礙物不動會回傳ture，讓旗子也不動。反之持續下降會回傳false，旗子也下降。
					pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() - 3);
				}
				CheckMovable(platform_image, box_blocks, 0, -3);
				if (platformP1Overlap)
					CheckMovable(character1.image, character1.blocks, 0, -3);
				if (platformP2Overlap)
					CheckMovable(character2.image, character2.blocks, 0, -3);
			}
		}

		if (platformP1Overlap || platformP2Overlap) {
			pFlag.SetFrameIndexOfBitmap(1);
		}
		else {
			pFlag.SetFrameIndexOfBitmap(2);
		}
	}
}

void Platform::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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

//檢查是否可以跳躍
bool Platform::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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
