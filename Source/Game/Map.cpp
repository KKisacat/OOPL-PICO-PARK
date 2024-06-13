#pragma once
#include "stdafx.h"
#include "Map.h"

Map::Map() {
	
}

void Map::OnInit(Character &character1, Character &character2, int phase) {

	//初始參數
	keyIgnore = false;
	character1.characterIgnore = false;
	character2.characterIgnore = false;
	key.staybyCharacter1 = 0;
	key.staybyCharacter2 = 0;

	LoadAndResetAllBitmap();

	character1.OnInit();
	character2.OnInit();

	if (phase == 2)
	{
		button.SetTopLeft(90 * 56, 867);
		button.SetFrameIndexOfBitmap(0);

		bridge.SetTopLeft(90 * 54 - 30, 900);

		platforms.image.SetTopLeft(90 * 73 + 80, 830);
		platforms.pFlag.SetTopLeft(90 * 73 + 80, 688);
		platforms.pFlag.SetAnimation(1000, true);
		platforms.pFlag.SetFrameIndexOfBitmap(2);

		key.image.SetTopLeft(90 * 71, 360);
		key.image.SetAnimation(300, false);

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

		key.image.SetTopLeft(300, 550);
		key.image.SetAnimation(300, false);

		door.SetTopLeft(90 * 40, 675);
		door.SetFrameIndexOfBitmap(0);

	}
	else if (phase == 4) {
		SetMap3Block();
		key.image.SetTopLeft(90 * 25, 40);
		key.image.SetAnimation(300, false);
		character1.image.SetTopLeft(900, 720);
		for (int i = 0; i < 4; i++) {
			buttons[i].SetTopLeft(90 * (35 + i) + 85 * i, 865);
			buttons[i].SetFrameIndexOfBitmap(0);
			rolling_walls[i].SetTopLeft(90 * (35 + i), -10);
		}

		box3_1.SetTopLeft(900, 630);
		box3_1.SetFrameIndexOfBitmap(1);
		box3_2.SetTopLeft(2700, 810);
		box3_2.SetFrameIndexOfBitmap(1);
		box3_3.SetTopLeft(3000, 810);
		box3_3.SetFrameIndexOfBitmap(1);

		bridge3.SetTopLeft(90 * 20, 900);
		button3.SetTopLeft(90 * 22, 237);
		button3.SetFrameIndexOfBitmap(0);
		rolling_wall3.SetTopLeft(90 * 17 + 40, 270);
		wall_ignore[0].SetTopLeft(90 * 17 + 40, 360);
		wall_ignore[1].SetTopLeft(90 * 35, 360);

		door.SetTopLeft(90 * 45, 764);
		door.SetFrameIndexOfBitmap(0);
	}
	else if (phase == 5) {
		SetMap4Block();
		key.image.SetTopLeft(90 * 35, 700);
		key.image.SetAnimation(300, false);
		auto_floor.SetTopLeft(90 * 14 , 700);
		auto_wall.SetTopLeft(90 * 25, 90);
		platforms.image.SetTopLeft(90 * 24 + 15, 450);
		platforms.pFlag.SetTopLeft(90 * 24 + 15, 308);
		platforms.image2.SetTopLeft(90 * 48, 800);
		platforms.pFlag2.SetTopLeft(90 * 48, 658);
		door.SetTopLeft(90 * 56, 317);
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

	menu.LoadBitmapByString({
	"resources/menu_1.bmp",
	"resources/menu_2.bmp",
	"resources/menu_3.bmp"
		}, RGB(0, 255, 0));
	menu.SetTopLeft(650, 200);
	menu.SetFrameIndexOfBitmap(0);

	clear.LoadBitmapByString({ "resources/clear.bmp" }, RGB(0, 255, 0));

	//第一關
	button.LoadBitmapByString({ "resources/button1.bmp", "resources/button2.bmp" }, RGB(255, 255, 255));
	button.SetTopLeft(-10000, -10000);

	bridge.LoadBitmapByString({ "resources/bridge13.bmp" }, RGB(255, 255, 255));
	bridge.SetTopLeft(-10000, -10000);

	platforms.image.LoadBitmapByString({ "resources/platform.bmp" }, RGB(255, 255, 255));
	platforms.image.SetTopLeft(-10000, -10000);
	platforms.pFlag.LoadBitmapByString({
			"resources/pFlag0.bmp",
			"resources/pFlag1.bmp",
			"resources/pFlag2.bmp"
		}, RGB(255, 255, 255));
	platforms.pFlag.SetTopLeft(-10000, -10000);

	platforms.image2.LoadBitmapByString({ "resources/platform.bmp" }, RGB(255, 255, 255));
	platforms.image2.SetTopLeft(-10000, -10000);
	platforms.pFlag2.LoadBitmapByString({
			"resources/pFlag0.bmp",
			"resources/pFlag1.bmp",
			"resources/pFlag2.bmp"
		}, RGB(255, 255, 255));
	platforms.pFlag2.SetTopLeft(-10000, -10000);

	key.image.LoadBitmapByString({ "resources/key.bmp", "resources/key2.bmp", "resources/key3.bmp" , "resources/key4.bmp" }, RGB(255, 255, 255));
	key.image.SetTopLeft(-10000, -10000);

	door.LoadBitmapByString({ "resources/door.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
	door.SetTopLeft(-10000, -10000);

	//第二關
	box1.LoadBitmapByString({ "resources/box2_0.bmp", "resources/box2_1.bmp" }, RGB(0, 255, 0));
	box1.SetTopLeft(-10000, -10000);
	box2.LoadBitmapByString({ "resources/box2_0.bmp", "resources/box2_1.bmp", "resources/box2_2.bmp" }, RGB(0, 255, 0));
	box2.SetTopLeft(-10000, -10000);
	box3.LoadBitmapByString({ "resources/box3_0.bmp", "resources/box3_1.bmp" }, RGB(0, 255, 0));
	box3.SetTopLeft(-10000, -10000);

	//第三關
	for (int i = 0; i < 4; i++) {
		buttons[i].LoadBitmapByString({ "resources/button1.bmp", "resources/button2.bmp" }, RGB(255, 255, 255));
		buttons[i].SetTopLeft(-10000, -10000);
		rolling_walls[i].LoadBitmapByString({ "resources/rolling_wall.bmp" }, RGB(255, 255, 255));
		rolling_walls[i].SetTopLeft(-10000, -10000);
	}
	box3_1.LoadBitmapByString({ "resources/box_level3_0.bmp", "resources/box_level3_1.bmp" }, RGB(0, 255, 0));
	box3_1.SetTopLeft(-10000, -10000);
	box3_2.LoadBitmapByString({ "resources/box_level3_0.bmp", "resources/box_level3_1.bmp" }, RGB(0, 255, 0));
	box3_2.SetTopLeft(-10000, -10000);
	box3_3.LoadBitmapByString({ "resources/box_level3_0.bmp", "resources/box_level3_1.bmp" }, RGB(0, 255, 0));
	box3_3.SetTopLeft(-10000, -10000);
	bridge3.LoadBitmapByString({ "resources/bridge3.bmp" }, RGB(255, 255, 255));
	bridge3.SetTopLeft(-10000, -10000);
	button3.LoadBitmapByString({ "resources/button1.bmp", "resources/button2.bmp" }, RGB(255, 255, 255));
	button3.SetTopLeft(-10000, -10000);
	rolling_wall3.LoadBitmapByString({ "resources/rolling_wall.bmp" }, RGB(255, 255, 255));
	rolling_wall3.SetTopLeft(-10000, -10000);
	for (int i = 0; i < 2; i++) {
		wall_ignore[i].LoadBitmapByString({ "resources/wall_ignore.bmp" });
		wall_ignore[i].SetTopLeft(-10000, -10000);
	}
	auto_floor.LoadBitmapByString({ "resources/platform.bmp" }, RGB(255, 255, 255));
	auto_floor.SetTopLeft(-10000, -10000);
	auto_wall.LoadBitmapByString({ "resources/auto_wall.bmp" }, RGB(255, 255, 255));
	auto_wall.SetTopLeft(-10000, -10000);
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

	//多餘的
	for (int i = 131; i < 181; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(-100, -100);
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

	//多餘的
	for (int i = 131; i < 181; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(-100, -100);
	}
}

void Map::SetMap3Block() {

	//輔助用
	block[130].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
	block[130].SetTopLeft(90 * 11, 900);
	/*
	for (int i = 121; i < 130; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 109), 900);
	}
	*/
	
	//起點地板
	block[0].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
	block[0].SetTopLeft(90 * 10, 900);

	//階梯
	for (int i = 1; i < 5; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (12 + i), 720 - (90 * i));
	}

	//二樓
	for (int i = 5; i < 28; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (12 + i), 270);
	}
	//一樓
	for (int i = 28; i < 58; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 8), 900);
	}
	//障礙物
	block[58].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
	block[58].SetTopLeft(90 * 27, 720);

	//起點牆壁
	for (int i = 59; i < 70; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90, 90 * (i - 59));
	}
	//終點牆壁
	for (int i = 70; i < 81; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * 49, 90 * (i - 70));
	}


	//多餘的
	for (int i = 81; i < 181; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(-100, -100);
	}

}

void Map::SetMap4Block() {

	//起點牆壁
	for (int i = 0; i < 11; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90, 90 * i);
	}

	//地板
	for (int i = 11; i < 71; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 11), 900);
	}

	//天花板
	for (int i = 71; i < 141; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 70), 0);
	}

	//平台一
	for (int i = 141; i < 146; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 122), 450);
	}

	//平台二
	for (int i = 146; i < 156; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 117), 450);
	}

	//障礙牆
	for (int i = 156; i < 160; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * 38, 540 + 90 * (i - 156));
	}

	//階梯
	for (int i = 160; i < 165; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 121), 450 + 90 * (i - 160));
	}

	//終點平台
	for (int i = 165; i < 170; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * (i - 111), 450);
	}

	//終點牆壁
	for (int i = 170; i < 181; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 * 59, 90 * (i - 170));
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

	key.GetKey(character1, character2);
}

void Map::MovePlatform(CMovingBitmap &platform_image, CMovingBitmap &pFlag, Character &character1, Character &character2, int highest, int lowest, bool isPlatformUp) {

	platforms.MovePlatform(platform_image, pFlag, character1, character2, box_blocks, highest, lowest, isPlatformUp);
}

//箱子2掉落
void Map::TryFallBox(CMovingBitmap &box, int height) {
	if (box.GetTop() <= height) {
		CheckMovable(box, box_blocks, 0, 10);
	}
}

void Map::MoveHeadBox(Character &character, int x, Character &character2) {
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
void Map::PushBox2ChangeImage(Character &character1, Character &character2, int x) {

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

//第三關推箱子
void Map::PushBoxLevelThree(Character &character, CMovingBitmap &box, int x, int box_name) {
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

//第三關橋跟閘門
void Map::PressButtonBridgeThree(Character &character1, Character &character2) {

	//按下按鈕
	button3Overlap = CMovingBitmap::IsOverlap(character1.image, button3) || CMovingBitmap::IsOverlap(character2.image, button3);

	//橋跟閘門
	if (button3.GetFrameIndexOfBitmap() == 1) {
		if (bridge3.GetLeft() - block[0].GetLeft() > 0) {
			CheckMovable(bridge3, button_blocks, -5, 0);
		}
		if (rolling_wall3.GetTop() > -10) {
			CheckMovable(rolling_wall3, button_blocks, 0, -10);
		}	 
	}
}

int Map::CheckButtonPressed(Character &character1, Character &character2) { 
	numOfButtonPressed = 0;
	for (int i = 0; i < 4; i++) {
		buttons[i].SetFrameIndexOfBitmap(0);
		if (IsJumpable(buttons[i], button_blocks, 0, -10)) {
			buttons[i].SetFrameIndexOfBitmap(1);
			numOfButtonPressed++;
		}
	}
	return numOfButtonPressed;
}

void Map::RollWall(int numOfButtonPressed) {
	for (int i = 0; i < 4 - numOfButtonPressed; i++) {
		if (rolling_walls[i].GetTop() > -9) {
			CheckMovable(rolling_walls[i], button_blocks, 0, -10);
		}
	}
	for (int i = 3; i > 3 - numOfButtonPressed; i--) {
		if (rolling_walls[i].GetTop() < 270) {
			CheckMovable(rolling_walls[i], button_blocks, 0, 10);
		}
	}
}

void Map::MoveAutoFloor(Character &character1, Character &character2) {
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

void Map::MoveAutoWall(Character &character1, Character &character2) {
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
	if (auto_wall.GetLeft() < block[141].GetLeft()) {
		isAutoWallMoveLeft = false;
	}
	if (auto_wall.GetLeft() > block[148].GetLeft()) {
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
		for (int i = 0; i < 181; i++) {
			block[i].SetTopLeft(block[i].GetLeft() - 5, block[i].GetTop());
		}
		character1.image.SetTopLeft(character1.image.GetLeft() - 5, character1.image.GetTop());
		character2.image.SetTopLeft(character2.image.GetLeft() - 5, character2.image.GetTop());
		button.SetTopLeft(button.GetLeft() - 5, button.GetTop());
		bridge.SetTopLeft(bridge.GetLeft() - 5, bridge.GetTop());
		key.image.SetTopLeft(key.image.GetLeft() - 5, key.image.GetTop());
		platforms.image.SetTopLeft(platforms.image.GetLeft() - 5, platforms.image.GetTop());
		platforms.pFlag.SetTopLeft(platforms.pFlag.GetLeft() - 5, platforms.pFlag.GetTop());
		door.SetTopLeft(door.GetLeft() - 5, door.GetTop());
		box1.SetTopLeft(box1.GetLeft() - 5, box1.GetTop());
		box2.SetTopLeft(box2.GetLeft() - 5, box2.GetTop());
		box3.SetTopLeft(box3.GetLeft() - 5, box3.GetTop());
		for (int i = 0; i < 4; i++) {
			buttons[i].SetTopLeft(buttons[i].GetLeft() - 5, buttons[i].GetTop());
			rolling_walls[i].SetTopLeft(rolling_walls[i].GetLeft() - 5, rolling_walls[i].GetTop());
		}
		box3_1.SetTopLeft(box3_1.GetLeft() - 5, box3_1.GetTop());
		box3_2.SetTopLeft(box3_2.GetLeft() - 5, box3_2.GetTop());
		box3_3.SetTopLeft(box3_3.GetLeft() - 5, box3_3.GetTop());
		bridge3.SetTopLeft(bridge3.GetLeft() - 5, bridge3.GetTop());
		button3.SetTopLeft(button3.GetLeft() - 5, button3.GetTop());
		rolling_wall3.SetTopLeft(rolling_wall3.GetLeft() - 5, rolling_wall3.GetTop());
		wall_ignore[0].SetTopLeft(wall_ignore[0].GetLeft() - 5, wall_ignore[0].GetTop());
		wall_ignore[1].SetTopLeft(wall_ignore[1].GetLeft() - 5, wall_ignore[1].GetTop());
		auto_floor.SetTopLeft(auto_floor.GetLeft() - 5, auto_floor.GetTop());
		auto_wall.SetTopLeft(auto_wall.GetLeft() - 5, auto_wall.GetTop());
		platforms.image2.SetTopLeft(platforms.image2.GetLeft() - 5, platforms.image2.GetTop());
		platforms.pFlag2.SetTopLeft(platforms.pFlag2.GetLeft() - 5, platforms.pFlag2.GetTop());
	}
	else if (((character1.image.GetLeft() + character2.image.GetLeft()) / 2) < 800)
	{
		background.SetTopLeft(background.GetLeft() + 5, 0);
		for (int i = 0; i < 181; i++) {
			block[i].SetTopLeft(block[i].GetLeft() + 5, block[i].GetTop());
		}
		character1.image.SetTopLeft(character1.image.GetLeft() + 5, character1.image.GetTop());
		character2.image.SetTopLeft(character2.image.GetLeft() + 5, character2.image.GetTop());
		button.SetTopLeft(button.GetLeft() + 5, button.GetTop());
		bridge.SetTopLeft(bridge.GetLeft() + 5, bridge.GetTop());
		key.image.SetTopLeft(key.image.GetLeft() + 5, key.image.GetTop());
		platforms.image.SetTopLeft(platforms.image.GetLeft() + 5, platforms.image.GetTop());
		platforms.pFlag.SetTopLeft(platforms.pFlag.GetLeft() + 5, platforms.pFlag.GetTop());
		door.SetTopLeft(door.GetLeft() + 5, door.GetTop());
		box1.SetTopLeft(box1.GetLeft() + 5, box1.GetTop());
		box2.SetTopLeft(box2.GetLeft() + 5, box2.GetTop());
		box3.SetTopLeft(box3.GetLeft() + 5, box3.GetTop());
		for (int i = 0; i < 4; i++) {
			buttons[i].SetTopLeft(buttons[i].GetLeft() + 5, buttons[i].GetTop());
			rolling_walls[i].SetTopLeft(rolling_walls[i].GetLeft() + 5, rolling_walls[i].GetTop());
		}
		box3_1.SetTopLeft(box3_1.GetLeft() + 5, box3_1.GetTop());
		box3_2.SetTopLeft(box3_2.GetLeft() + 5, box3_2.GetTop());
		box3_3.SetTopLeft(box3_3.GetLeft() + 5, box3_3.GetTop());
		bridge3.SetTopLeft(bridge3.GetLeft() + 5, bridge3.GetTop());
		button3.SetTopLeft(button3.GetLeft() + 5, button3.GetTop());
		rolling_wall3.SetTopLeft(rolling_wall3.GetLeft() + 5, rolling_wall3.GetTop());
		wall_ignore[0].SetTopLeft(wall_ignore[0].GetLeft() + 5, wall_ignore[0].GetTop());
		wall_ignore[1].SetTopLeft(wall_ignore[1].GetLeft() + 5, wall_ignore[1].GetTop());
		auto_floor.SetTopLeft(auto_floor.GetLeft() + 5, auto_floor.GetTop());
		auto_wall.SetTopLeft(auto_wall.GetLeft() + 5, auto_wall.GetTop());
		platforms.image2.SetTopLeft(platforms.image2.GetLeft() + 5, platforms.image2.GetTop());
		platforms.pFlag2.SetTopLeft(platforms.pFlag2.GetLeft() + 5, platforms.pFlag2.GetTop());
	}
}

//選單
void Map::RunMenuOptions(Character &character1, Character &character2, int &phase) {
	if (menuShow) {
		if (menu_options == 3) {
			phase = 1;
			OnInit(character1, character2, phase);

		}
		else if (menu_options == 2) {
			OnInit(character1, character2, phase);
		}
		menuShow = false;
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
	std::vector<CMovingBitmap> player1_floor = { character2.image, bridge, platforms.image, box1, box2, box3, box3_1, box3_2, box3_3, bridge3, rolling_wall3, auto_floor, auto_wall, platforms.image2 };
	std::vector<CMovingBitmap> player2_floor = { character1.image, bridge, platforms.image, box1, box2, box3, box3_1, box3_2, box3_3, bridge3, rolling_wall3, auto_floor, auto_wall, platforms.image2 };
	box_blocks = { character1.image, character2.image, bridge3 };
	box3_1_blocks = { character1.image, character2.image, box3_2, box3_3, bridge3 };
	box3_2_blocks = { character1.image, character2.image, box3_1, box3_3, bridge3 };
	box3_3_blocks = { character1.image, character2.image, box3_1, box3_2, bridge3 };
	button_blocks = { character1.image, character2.image, box3_1, box3_2, box3_3 };

	for (int i = 0; i < 181; i++) {
		player1_floor.push_back(block[i]);
		player2_floor.push_back(block[i]);
		box_blocks.push_back(block[i]);
		box3_1_blocks.push_back(block[i]);
		box3_2_blocks.push_back(block[i]);
		box3_3_blocks.push_back(block[i]);
	}
	for (int i = 0; i < 4; i++) {
		player1_floor.push_back(rolling_walls[i]);
		player2_floor.push_back(rolling_walls[i]);
	}

	character1.SetWallAndFloor(player1_floor);
	character2.SetWallAndFloor(player2_floor);
}
