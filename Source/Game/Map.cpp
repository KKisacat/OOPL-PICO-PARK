#pragma once
#include "stdafx.h"
#include "Map.h"

Map::Map() {
	
}

void Map::OnInit(Character &character1, Character &character2, int phase) {

	LoadAndResetAllBitmap();

	character1.OnInit();
	character2.OnInit();

	if (phase == 2)
	{
		button.SetTopLeft(90 * 56, 859);
		button.SetFrameIndexOfBitmap(0);

		bridge.SetTopLeft(90 * 54 - 30, 900);

		platform.SetTopLeft(90 * 73 + 80, 830);
		
		pFlag.SetTopLeft(90 * 73 + 80, 688);
		pFlag.SetAnimation(1000, true);
		pFlag.SetFrameIndexOfBitmap(2);

		key.SetTopLeft(90 * 71, 360);
		key.SetAnimation(300, false);

		door.SetTopLeft(90 * 85, 226);
		door.SetFrameIndexOfBitmap(0);

		SetMap1Block();

	}else if (phase == 3) {
		SetMap2Block();

		box1.SetTopLeft(400, 95);
		box1.SetFrameIndexOfBitmap(1);
		box2.SetTopLeft(1500, 95);
		box2.SetFrameIndexOfBitmap(2);
		box3.SetTopLeft(3000, 685);
		box3.SetFrameIndexOfBitmap(1);

		key.SetTopLeft(300, 550);
		key.SetAnimation(300, false);

		door.SetTopLeft(90 * 40, 675);
		door.SetFrameIndexOfBitmap(0);

	}

	for (int i = 0; i < 4; i++) {
		crown[i].LoadBitmapByString({ "resources/crown.bmp" });
		crown[i].SetTopLeft(270 + i * 420, 270);
	}

	clear.SetTopLeft(-262, 430);
}

void  Map::LoadAndResetAllBitmap() {
	background.LoadBitmapByString({
	"resources/map1_background.bmp",
	"resources/map2_background.bmp",
	"resources/map3_background.bmp",
	"resources/map4_background.bmp"
		});
	background.SetTopLeft(0, 0);

	clear.LoadBitmapByString({ "resources/clear.bmp" }, RGB(0, 255, 0));

	//第一關
	button.LoadBitmapByString({ "resources/button1.bmp", "resources/button2.bmp" }, RGB(255, 255, 255));
	button.SetTopLeft(-10000, -10000);

	bridge.LoadBitmapByString({ "resources/bridge13.bmp" }, RGB(255, 255, 255));
	bridge.SetTopLeft(-10000, -10000);

	platform.LoadBitmapByString({ "resources/platform.bmp" }, RGB(255, 255, 255));
	platform.SetTopLeft(-10000, -10000);

	pFlag.LoadBitmapByString({
			"resources/pFlag0.bmp",
			"resources/pFlag1.bmp",
			"resources/pFlag2.bmp"
		}, RGB(255, 255, 255));
	pFlag.SetTopLeft(-10000, -10000);

	key.LoadBitmapByString({ "resources/key.bmp", "resources/key2.bmp", "resources/key3.bmp" , "resources/key4.bmp" }, RGB(255, 255, 255));
	key.SetTopLeft(-10000, -10000);

	door.LoadBitmapByString({ "resources/door.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
	door.SetTopLeft(-10000, -10000);

	//第二關
	box1.LoadBitmapByString({ "resources/box2_0.bmp", "resources/box2_1.bmp" }, RGB(0, 255, 0));
	box1.SetTopLeft(-10000, -10000);
	box2.LoadBitmapByString({ "resources/box2_0.bmp", "resources/box2_1.bmp", "resources/box2_2.bmp" }, RGB(0, 255, 0));
	box2.SetTopLeft(-10000, -10000);
	box3.LoadBitmapByString({ "resources/box3_0.bmp", "resources/box3_1.bmp" }, RGB(0, 255, 0));
	box3.SetTopLeft(-10000, -10000);
}



void Map::SetMap1Block() {
	//起點牆壁
	for (int i = 120; i < 131; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(0, 900 - 90 * (i - 120));
	}
	//洞洞前的地板
	for (int i = 0; i < 24; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * i, 900);
	}
	//洞洞後的地板
	for (int i = 24; i < 45; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (i + 2), 900);
	}
	//第一個階梯
	for (int i = 90; i < 96; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (41 + i - 90), (900 - 90));
	}
	//第二個階梯
	for (int i = 96; i < 101; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (42 + i - 96), (900 - 90 * 2));
	}
	//移動平台後的地板
	for (int i = 45; i < 90; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (i + 8), 900);
	}
	//高牆
	for (int i = 101; i < 106; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * 78, 900 - 90 * (i - 100));
	}
	//終點平台
	for (int i = 106; i < 116; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (78 + i - 106), 900 - 90 * 6);
	}
	//終點牆壁
	for (int i = 116; i < 120; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * 87, 900 - 90 * (i - 109));
	}


}

void Map::SetMap2Block() {

	//洞洞前的地板
	for (int i = 0; i < 22; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * i, 900);
	}

	//洞洞後的地板
	for (int i = 22; i < 46; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i + 1), 900);
	}

	//天花板
	for (int i = 46; i < 91; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 46), 0);
	}

	//階梯
	for (int i = 91; i < 93; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 68), 810);
	}
	block[93].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
	block[93].SetTopLeft(90 * 23, 720);

	//終點平台
	for (int i = 94; i < 100; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 57), 810);
	}

	//起點牆壁
	for (int i = 100; i < 111; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90, 90 * (i - 100));
	}

	//終點牆壁
	for (int i = 111; i < 131; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * 43, 90 * (i - 111));
	}

}


void Map::PressButton(Character &character1, Character &character2) {

	//按下按鈕
	buttonOverlap = CMovingBitmap::IsOverlap(character1.image, button) || CMovingBitmap::IsOverlap(character2.image, button);

	//橋
	if (button.GetFrameIndexOfBitmap() == 1) {
		if (block[45].GetLeft() - bridge.GetLeft() < 550) {
			bridgeP1Overlap = CMovingBitmap::IsOverlap(character1.image, bridge);
			bridgeP2Overlap = CMovingBitmap::IsOverlap(character2.image, bridge);
			if (bridgeP1Overlap) {
				character1.image.SetTopLeft(character1.image.GetLeft() - 3, character1.image.GetTop() + 10);
			}
			if (bridgeP2Overlap) {
				character2.image.SetTopLeft(character2.image.GetLeft() - 3, character2.image.GetTop() + 10);
			}
			bridge.SetTopLeft(bridge.GetLeft() - 3, bridge.GetTop());
		}

	}
}


void Map::GetKey(Character &character1, Character &character2) {

	//鑰匙跟隨
	keyP1Overlap = CMovingBitmap::IsOverlap(character1.image, key);
	keyP2Overlap = CMovingBitmap::IsOverlap(character2.image, key);
	if (keyP1Overlap) {
		staybyCharacter1 = 1;
		staybyCharacter2 = 0;
	}
	if (staybyCharacter1 == 1) {
		key.SetTopLeft(character1.image.GetLeft() - 70, character1.image.GetTop() - 80);
	}

	if (keyP2Overlap) {
		staybyCharacter2 = 1;
		staybyCharacter1 = 0;
	}
	if (staybyCharacter2 == 1) {
		key.SetTopLeft(character2.image.GetLeft() - 70, character2.image.GetTop() - 80);
	}
}

void Map::MovePlatform(Character &character1, Character &character2) {

	std::vector<CMovingBitmap> platform_block = { character1.image, character2.image };

	//平台
	character2.characterIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop() - 10, character2.image.GetHeight(), character2.image.GetWidth());
	character1.characterIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() - 10, character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth());
	platformP1Overlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() + 10, character1.image.GetHeight(), character1.image.GetWidth(), platform.GetLeft(), platform.GetTop(), platform.GetHeight(), platform.GetWidth());
	platformP2Overlap = CMovingBitmap::IsOverlap(character2.image.GetLeft(), character2.image.GetTop() + 10, character2.image.GetHeight(), character2.image.GetWidth(), platform.GetLeft(), platform.GetTop(), platform.GetHeight(), platform.GetWidth());
	if ((platformP1Overlap && platformP2Overlap) || (character1.characterIsOverlap && platformP1Overlap) || (character1.characterIsOverlap && platformP2Overlap)) {
		//平台上升
		if (platform.GetTop() > 370) {
			platform.SetTopLeft(platform.GetLeft(), platform.GetTop() - 3);
			pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() - 3);
			CheckMovable(character1.image, character1.blocks, 0, -3);
			CheckMovable(character2.image, character2.blocks, 0, -3);
		}
		pFlag.SetFrameIndexOfBitmap(0);
	}
	else {
		//平台下降
		if (platform.GetTop() < 830) {
			if (!IsJumpable(platform, platform_block, 0, 3)) {
				//偷用別的函式，如果平台碰到障礙物不動會回傳ture，讓旗子也不動。反之持續下降會回傳false，旗子也下降。
				pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() + 3);
			}
			CheckMovable(platform, platform_block, 0, 3);
			CheckMovable(character1.image, character1.blocks, 0, 3);
			CheckMovable(character2.image, character2.blocks, 0, 3);
		}
		if (platformP1Overlap || platformP2Overlap) {
			pFlag.SetFrameIndexOfBitmap(1);
		}
		else {
			pFlag.SetFrameIndexOfBitmap(2);
		}
	}
}

//箱子2掉落
void Map::TryFallBox() {

	if (box2.GetTop() <= 810) {
		CheckMovable(box2, box_blocks, 0, 10);
	}

}

//推箱子2
void Map::PushBox2(Character &character1, Character &character2, int x) {

	boxP1isOverlap = CMovingBitmap::IsOverlap(
		character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(),
		box2.GetLeft() - x, box2.GetTop(), box2.GetHeight(), box2.GetWidth()
	);
	boxP2isOverlap = CMovingBitmap::IsOverlap(
		character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth(),
		box2.GetLeft() - x, box2.GetTop(), box2.GetHeight(), box2.GetWidth()
	);
	if (boxP1isOverlap && boxP2isOverlap) {
		CheckMovable(box2, box_blocks, x, 0);
		box2.SetFrameIndexOfBitmap(0);
	}
	else if (boxP1isOverlap || boxP2isOverlap) {
		box2.SetFrameIndexOfBitmap(1);
	}
	else {
		box2.SetFrameIndexOfBitmap(2);
	}
}

//推箱子1人
void Map::PushBox(Character &character,CMovingBitmap &box, int x) {

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

//進門
void Map::CheckDoorOverlap(Character &character1, Character &character2) {
	doorP1isOverlap = CMovingBitmap::IsOverlap(character1.image, door);
	doorP2isOverlap = CMovingBitmap::IsOverlap(character2.image, door);
}

void Map::RollScreen(Character &character1, Character &character2) {

	//畫面移動
	if (((character1.image.GetLeft() + character2.image.GetLeft()) / 2) > 1000)
	{
		background.SetTopLeft(background.GetLeft() - 5, 0);
		for (int i = 0; i < 131; i++) {
			block[i].SetTopLeft(block[i].GetLeft() - 5, block[i].GetTop());
		}
		character1.image.SetTopLeft(character1.image.GetLeft() - 5, character1.image.GetTop());
		character2.image.SetTopLeft(character2.image.GetLeft() - 5, character2.image.GetTop());
		button.SetTopLeft(button.GetLeft() - 5, button.GetTop());
		bridge.SetTopLeft(bridge.GetLeft() - 5, bridge.GetTop());
		key.SetTopLeft(key.GetLeft() - 5, key.GetTop());
		platform.SetTopLeft(platform.GetLeft() - 5, platform.GetTop());
		pFlag.SetTopLeft(pFlag.GetLeft() - 5, pFlag.GetTop());
		door.SetTopLeft(door.GetLeft() - 5, door.GetTop());
		box1.SetTopLeft(box1.GetLeft() - 5, box1.GetTop());
		box2.SetTopLeft(box2.GetLeft() - 5, box2.GetTop());
		box3.SetTopLeft(box3.GetLeft() - 5, box3.GetTop());
	}
	else if (((character1.image.GetLeft() + character2.image.GetLeft()) / 2) < 800)
	{
		background.SetTopLeft(background.GetLeft() + 5, 0);
		for (int i = 0; i < 131; i++) {
			block[i].SetTopLeft(block[i].GetLeft() + 5, block[i].GetTop());
		}
		character1.image.SetTopLeft(character1.image.GetLeft() + 5, character1.image.GetTop());
		character2.image.SetTopLeft(character2.image.GetLeft() + 5, character2.image.GetTop());
		button.SetTopLeft(button.GetLeft() + 5, button.GetTop());
		bridge.SetTopLeft(bridge.GetLeft() + 5, bridge.GetTop());
		key.SetTopLeft(key.GetLeft() + 5, key.GetTop());
		platform.SetTopLeft(platform.GetLeft() + 5, platform.GetTop());
		pFlag.SetTopLeft(pFlag.GetLeft() + 5, pFlag.GetTop());
		door.SetTopLeft(door.GetLeft() + 5, door.GetTop());
		box1.SetTopLeft(box1.GetLeft() + 5, box1.GetTop());
		box2.SetTopLeft(box2.GetLeft() + 5, box2.GetTop());
		box3.SetTopLeft(box3.GetLeft() + 5, box3.GetTop());
	}
}


//把所有碰撞寫成fuction
void Map::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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
bool Map::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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

void Map::RefreshWall(Character &character1, Character &character2) {
	std::vector<CMovingBitmap> player1_floor = { character2.image, bridge, platform, box1, box2, box3 };
	std::vector<CMovingBitmap> player2_floor = { character1.image, bridge, platform, box1, box2, box3 };
	box_blocks = { character1.image, character2.image };

	for (int i = 0; i < 131; i++) {
		player1_floor.push_back(block[i]);
		player2_floor.push_back(block[i]);
		box_blocks.push_back(block[i]);
	}

	character1.SetWallAndFloor(player1_floor);
	character2.SetWallAndFloor(player2_floor);
}