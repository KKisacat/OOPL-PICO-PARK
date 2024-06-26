#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;



/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}


void CGameStateRun::OnBeginState()
{
	
}

void CGameStateRun::OnMove()							
{
	maps.RefreshWall(character1, character2);

	if (phase > 1) {

		//player1 move
		// 左右
		if (character1.isRightRun)
		{
			character1.TryMoveRight(character2);
		}
		else if (character1.isLeftRun)
		{
			character1.TryMoveLeft(character2);
		}

		// 跳躍
		if (character1.isUpRun && character1.upTime <= 13)
		{
			character1.TryMoveUp();
		}
		else if (!character1.isUpRun) //掉落
		{
			character1.TryFall(maps.menuShow);
		}

		//player2 move
		if (character2.isRightRun)
		{
			character2.TryMoveRight(character1);
		}
		else if (character2.isLeftRun)
		{
			character2.TryMoveLeft(character1);
		}

		if (character2.isUpRun && character2.upTime <= 13)
		{
			character2.TryMoveUp();
		}
		else if (!character2.isUpRun)
		{
			character2.TryFall(maps.menuShow);
		}

		//鑰匙跟隨
		maps.GetKey(character1, character2);

		//畫面移動
		maps.RollScreen(character1, character2);

	}

	if (phase == 2)
	{
		
		// 小藍死掉重生
		if (character1.image.GetTop() > 1024) {
			character1.image.SetTopLeft(character1.image.GetLeft() - 800, 0);
		}

		//小紅墜落向後重生
		if (character2.image.GetTop() > 1024) {
			character2.image.SetTopLeft(character2.image.GetLeft() - 800, 0);
		}

		//大門
		maps.CheckDoorOverlap(character1, character2);

		//按按鈕橋出現
		maps.PressButton(character1, character2);

		//平台
		maps.MovePlatform(maps.platforms.image, maps.platforms.pFlag, character1, character2, 370, 830, true);
	}
	else if (phase == 3) 
	{
		//箱子2掉落
		maps.TryFallBox(maps.boxes.box2, 810);
		//確保箱子沒被推的時候保持初始
		maps.boxes.box1.SetFrameIndexOfBitmap(1);
		maps.boxes.box2.SetFrameIndexOfBitmap(2);
		maps.boxes.box3.SetFrameIndexOfBitmap(1);

		//推箱子
		//小藍
		if (character1.isRightRun)
		{
			maps.PushBox(character1, maps.boxes.box1, 8);
			maps.PushBox(character1, maps.boxes.box3, 8);
			maps.PushBox2ChangeImage(character1, character2, 8); //Box2換圖片
		}
		else if (character1.isLeftRun)
		{
			maps.PushBox(character1, maps.boxes.box1, -8);
			maps.PushBox(character1, maps.boxes.box3, -8);
			maps.PushBox2ChangeImage(character1, character2, -8);
		}
		//小紅
		if (character2.isRightRun)
		{
			maps.PushBox(character2, maps.boxes.box1, 8);
			maps.PushBox(character2, maps.boxes.box3, 8);
			maps.PushBox2ChangeImage(character2, character1, 8);
		}
		else if (character2.isLeftRun)
		{
			maps.PushBox(character2, maps.boxes.box1, -8);
			maps.PushBox(character2, maps.boxes.box3, -8);
			maps.PushBox2ChangeImage(character2, character1, -8);
		}
		//兩人推箱
		if (character1.isRightRun && character2.isRightRun) {
			maps.PushBox2(character1, character2, 8);
		}
		if (character1.isLeftRun && character2.isLeftRun) {
			maps.PushBox2(character1, character2, -8);
		}

		//大門
		maps.CheckDoorOverlap(character1, character2);

	}
	else if (phase == 4) {
		//箱子掉落
		maps.TryFallBox(maps.boxes.box3_1, 1024);
		if (maps.boxes.box3_1.GetTop() > 1024) {
			maps.boxes.box3_1.SetTopLeft(maps.block[0].GetLeft(), 0);
		}
		// 小藍死掉重生
		if (character1.image.GetTop() > 1024) {
			character1.image.SetTopLeft(maps.block[0].GetLeft() - 100, 0);
		}
		//小紅墜落向後重生
		if (character2.image.GetTop() > 1024) {
			character2.image.SetTopLeft(maps.block[0].GetLeft() + 100, 0);
		}
		//推箱子
		//小藍
		maps.boxes.box3_1.SetFrameIndexOfBitmap(1);
		maps.boxes.box3_2.SetFrameIndexOfBitmap(1);
		maps.boxes.box3_3.SetFrameIndexOfBitmap(1);
		if (character1.isRightRun)
		{
			maps.MoveHeadBox(character1, 8, character2);
			maps.PushBoxLevelThree(character1, maps.boxes.box3_1, 8, 1);
			maps.PushBoxLevelThree(character1, maps.boxes.box3_2, 8, 2);
			maps.PushBoxLevelThree(character1, maps.boxes.box3_3, 8, 3);
		}
		else if (character1.isLeftRun)
		{
			maps.MoveHeadBox(character1, -8, character2);
			maps.PushBoxLevelThree(character1, maps.boxes.box3_1, -8, 1);
			maps.PushBoxLevelThree(character1, maps.boxes.box3_2, -8, 2);
			maps.PushBoxLevelThree(character1, maps.boxes.box3_3, -8, 3);
		}
		//小紅
		if (character2.isRightRun)
		{
			maps.MoveHeadBox(character2, 8, character1);
			maps.PushBoxLevelThree(character2, maps.boxes.box3_1, 8, 1);
			maps.PushBoxLevelThree(character2, maps.boxes.box3_2, 8, 2);
			maps.PushBoxLevelThree(character2, maps.boxes.box3_3, 8, 3);
		}
		else if (character2.isLeftRun)
		{
			maps.MoveHeadBox(character2, -8, character1);
			maps.PushBoxLevelThree(character2, maps.boxes.box3_1, -8, 1);
			maps.PushBoxLevelThree(character2, maps.boxes.box3_2, -8, 2);
			maps.PushBoxLevelThree(character2, maps.boxes.box3_3, -8, 3);
		}

		//按四個按鈕
		maps.RollWall(maps.CheckButtonPressed(character1, character2));
		//橋跟閘門
		maps.PressButtonBridgeThree(character1, character2);

		//大門
		maps.CheckDoorOverlap(character1, character2);
	}
	else if (phase == 5) {
		maps.MoveAutoFloor(character1, character2);
		maps.MoveAutoWall(character1, character2);
		maps.MovePlatform(maps.platforms.image, maps.platforms.pFlag, character1, character2, 450, 800, false);
		maps.MovePlatform(maps.platforms.image2, maps.platforms.pFlag2, character1, character2, 450, 800, true);
		maps.CheckDoorOverlap(character1, character2);
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	catalog.LoadBitmapByString({
		"resources/phase11_background.bmp",
		"resources/phase12_background.bmp",
		"resources/phase13_background.bmp",
		"resources/phase14_background.bmp"
		});
	catalog.SetTopLeft(0, 0);

	maps.OnInit(character1, character2, phase);

	if (phase == 1) {
		CAudio::Instance()->Pause();
		CAudio::Instance()->Play(1, true);
	}
	else if (phase > 1) {
		CAudio::Instance()->Pause();
		CAudio::Instance()->Play(2, true);
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_UP) {
		if (phase > 1 && phase <= 5) {	//關卡
			if (!maps.menuShow) {
				if (character1.checkJumpble == 1) //沒跳過才能跳，不然會連跳
				{
					character1.checkJumpble = 0;
					character1.isUpRun = 1;
				}
			}
			else {
				if (maps.menu_options > 1) {
					maps.menu_options -= 1;
				}
			}
		}
	}

	if (nChar == VK_DOWN) {
		if (maps.menuShow) {
			if (maps.menu_options < 3) {
				maps.menu_options += 1;
			}
		}
	}

	if (nChar == VK_RIGHT) {
		if (phase == 1) {	//目錄 phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡 phase = 2~5
			if (!maps.menuShow) {
				character1.isRightRun = 1;
				character1.isCharacterLeftAnimation = false;
				character1.image.SetAnimation(125, false);
			}
		}
	}

	if (nChar == VK_LEFT) {
		if (phase == 1) {	//目錄
			if(sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡
			if (!maps.menuShow) {
				character1.isLeftRun = 1;
				character1.isCharacterLeftAnimation = true;
				character1.image2.SetAnimation(125, false);
			}
		}
	}

	if (nChar == 0x57) {  //player2 上鍵 W
		if (phase > 1 && phase <= 5) {	//關卡
			if (!maps.menuShow) { 
				if (character2.checkJumpble == 1) //沒跳過才能跳，不然會連跳
				{
					character2.checkJumpble = 0;
					character2.isUpRun = 1;
				}
			}
			else { //menu 打開
				if (maps.menu_options > 1) {
					maps.menu_options -= 1;
				}
			}
		}
	}

	if (nChar == 0x53) { //player2 下鍵 S
		if (maps.menuShow) {
			if (maps.menu_options < 3) {
				maps.menu_options += 1;
			}
		}
	}

	if (nChar == 0x44) {  //player2 右鍵 D

		if (phase == 1) {	//目錄 phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡 phase = 2~5
			if (!maps.menuShow) {
				character2.isRightRun = 1;
				character2.isCharacterLeftAnimation = false;
				character2.image.SetAnimation(125, false);
			}
		}
	}

	if (nChar == 0x41) {  //player2 左鍵 A

		if (phase == 1) {	//目錄
			if (sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//關卡
			if (!maps.menuShow) {
				character2.isLeftRun = 1;
				character2.isCharacterLeftAnimation = true;
				character2.image2.SetAnimation(125, false);
			}
		}
	}

	if (nChar == VK_SPACE) {
		if (phase == 1) { // phase1為目錄
			phase = sub_phase + 1; // 選擇關卡
			OnInit();
		}
		if (phase > 1 && phase <= 5) {	//關卡
			if (maps.door.GetFrameIndexOfBitmap() == 1 && maps.doorP2isOverlap) {
				character2.characterIgnore = true;
				character2.image.SetTopLeft(900, 900);
			}
			if (maps.doorP2isOverlap && maps.key.staybyCharacter2 == 1) {
				maps.door.SetFrameIndexOfBitmap(1);
				maps.keyIgnore = true;
			}
			maps.RunMenuOptions(character1, character2, phase);
		}
	}

	if (nChar == VK_RETURN) {
		if (phase == 1) { // phase1為目錄
			phase = sub_phase + 1; // 選擇關卡
			OnInit();
		}
		if (phase > 1 && phase <= 5) {	//關卡
			if (maps.door.GetFrameIndexOfBitmap() == 1 && maps.doorP1isOverlap) {
				character1.characterIgnore = true;
				character1.image.SetTopLeft(1020, 900);
			}
			if (maps.doorP1isOverlap && maps.key.staybyCharacter1 == 1) {
				maps.door.SetFrameIndexOfBitmap(1);
				maps.keyIgnore = true;
			}
			maps.RunMenuOptions(character1, character2, phase);
		}
	}

	if (nChar == VK_ESCAPE) {
		if (phase > 1) { //選單開關
			if (maps.menuShow) {
				maps.menuShow = false;
			}
			else {
				maps.menu_options = 1;
				maps.menuShow = true;
			}
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) {
		if (phase > 1 && phase <= 5) {	//關卡
			character1.isRightRun = 0;
			character1.image.StopAnimation();
		}
	}

	if (nChar == VK_LEFT) {
		if (phase > 1 && phase <= 5) {	//關卡
			character1.isLeftRun = 0;
			character1.image2.StopAnimation();
		}
	}

	if (nChar == VK_UP) {
		character1.isUpRun = 0;
	}

	if (nChar == 0x44) { //P2右
		if (phase > 1 && phase <= 5) {
			character2.isRightRun = 0;
			character2.image.StopAnimation();
		}
	}

	if (nChar == 0x41) { //P2左
		if (phase > 1 && phase <= 5) {
			character2.isLeftRun = 0;
			character2.image2.StopAnimation();
		}
	}

	if (nChar == 0x57) {  //player2 上鍵 W
		character2.isUpRun = 0;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	show_image_by_phase();
	show_text_by_phase();
}

void CGameStateRun::show_image_by_phase() {
	if (phase == 1) {
		catalog.SetFrameIndexOfBitmap(sub_phase - 1);
		catalog.ShowBitmap();
		if (maps.level_one_completed) {
			maps.crown[0].ShowBitmap();
		}
		if (maps.level_two_completed) {
			maps.crown[1].ShowBitmap();
		}
		if (maps.level_three_completed) {
			maps.crown[2].ShowBitmap();
		}
		if (maps.level_four_completed) {
			maps.crown[3].ShowBitmap();
		}

	}
	else if (phase == 2) {
		maps.background.SetFrameIndexOfBitmap(phase - 2);
		maps.background.ShowBitmap();
		if (maps.buttons.buttonOverlap) {
			maps.buttons.button_image.SetFrameIndexOfBitmap(1);
		}
		maps.buttons.button_image.ShowBitmap();
		maps.platforms.image.ShowBitmap();
		maps.platforms.pFlag.ShowBitmap();
		for (int i = 0; i < 131; i++) {
			maps.block[i].ShowBitmap();
		}
		maps.door.ShowBitmap();

		character1.OnShow();
		character2.OnShow();
		
		maps.buttons.bridge.ShowBitmap();
		
		if (!maps.keyIgnore) {
			maps.key.image.ShowBitmap();
		}
		if (character1.characterIgnore && character2.characterIgnore) {
			maps.level_one_completed = true;
		}
	}
	else if (phase == 3) {
		maps.background.SetFrameIndexOfBitmap(phase - 2);
		maps.background.ShowBitmap();
		for (int i = 0; i < 122; i++) {
			maps.block[i].ShowBitmap();
		}
		maps.door.ShowBitmap();
		character1.OnShow();
		character2.OnShow();
		maps.boxes.box1.ShowBitmap();
		maps.boxes.box2.ShowBitmap();
		maps.boxes.box3.ShowBitmap();
		if (!maps.keyIgnore) {
			maps.key.image.ShowBitmap();
		}
		if (character1.characterIgnore && character2.characterIgnore) {
			maps.level_two_completed = true;
		}
	}
	else if (phase == 4) {
		maps.background.SetFrameIndexOfBitmap(phase - 2);
		maps.background.ShowBitmap();
		for (int i = 0; i < 131; i++) {
			maps.block[i].ShowBitmap();
		}
		maps.door.ShowBitmap();
		for (int i = 0; i < 4; i++) {
			maps.buttons.buttons_level3[i].ShowBitmap();
			maps.buttons.rolling_walls[i].ShowBitmap();
		}
		maps.boxes.box3_1.ShowBitmap();
		maps.boxes.box3_2.ShowBitmap();
		maps.boxes.box3_3.ShowBitmap();
		maps.buttons.bridge3.ShowBitmap();
		maps.buttons.rolling_wall3.ShowBitmap();
		if (maps.buttons.button3Overlap) {
			maps.buttons.button3.SetFrameIndexOfBitmap(1);
		}
		maps.buttons.button3.ShowBitmap();
		for (int i = 0; i < 2; i++) {
			maps.wall_ignore[i].ShowBitmap();
		}

		character1.OnShow();
		character2.OnShow();
		
		if (!maps.keyIgnore) {
			maps.key.image.ShowBitmap();
		}
		if (character1.characterIgnore && character2.characterIgnore) {
			maps.level_three_completed = true;
		}
	}
	else if (phase == 5) {
		maps.background.SetFrameIndexOfBitmap(phase - 2);
		maps.background.ShowBitmap();
		for (int i = 0; i < 181; i++) {
			maps.block[i].ShowBitmap();
		}
		maps.door.ShowBitmap();
		maps.platforms.image.ShowBitmap();
		maps.platforms.pFlag.ShowBitmap();
		maps.platforms.image2.ShowBitmap();
		maps.platforms.pFlag2.ShowBitmap();
		character1.OnShow();
		character2.OnShow();
		maps.autoObjects.auto_floor.ShowBitmap();
		maps.autoObjects.auto_wall.ShowBitmap();

		if (!maps.keyIgnore) {
			maps.key.image.ShowBitmap();
		}
		if (character1.characterIgnore && character2.characterIgnore) {
			maps.level_four_completed = true;
		}
	}

	if (character1.characterIgnore && character2.characterIgnore) {
		maps.clear.ShowBitmap();
		if (maps.clear.GetLeft() < 2101) {
			maps.clear.SetTopLeft(maps.clear.GetLeft() + 10, 430);
		}
		else if (maps.clear.GetLeft() > 2101) {
			phase = 1;
			maps.keyIgnore = false;
			character1.characterIgnore = false;
			character2.characterIgnore = false;
			maps.key.staybyCharacter1 = 0;
			maps.key.staybyCharacter2 = 0;
			OnInit();
		}
	}
	
	//選單
	if (maps.menuShow) {
		maps.menu.SetFrameIndexOfBitmap(maps.menu_options - 1);
		maps.menu.ShowBitmap();
	}

}

void CGameStateRun::show_text_by_phase() {

}