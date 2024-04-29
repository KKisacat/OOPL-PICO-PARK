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
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

	//player1 move
	// ���k
	if (character1.isRightRun)
	{
		character1.TryMoveRight(character2);
	}
	else if (character1.isLeftRun)
	{
		character1.TryMoveLeft(character2);
	}

	// ���D
	if (character1.isUpRun && character1.upTime <= 13)
	{
		character1.TryMoveUp();
	}
	else if (!character1.isUpRun) //����
	{
		character1.TryFall();
	}

	// ��������
	if (character1.image.GetTop() > 1024) {
		character1.image.SetTopLeft(character1.image.GetLeft() - 700, 0);
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
		character2.TryFall();
	}

	//�Y���V�᭫��
	if (character2.image.GetTop() > 1024) {
		character2.image.SetTopLeft(character2.image.GetLeft() - 700, 0);
	}

	//�����s���X�{
	maps.PressButton(character1, character2);

	//�_�͸��H
	maps.GetKey(character1, character2);



	//���x
	maps.MovePlatform(character1, character2);


	//�j��
	maps.CheckDoorOverlap(character1, character2);


	//�e������
	maps.RollScreen(character1, character2);
}


void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{


	catalog.LoadBitmapByString({
		"resources/phase11_background.bmp",
		"resources/phase12_background.bmp",
		"resources/phase13_background.bmp",
		"resources/phase14_background.bmp"
		});
	catalog.SetTopLeft(0, 0);

	std::vector<CMovingBitmap> player1_floor = { character2.image, maps.bridge, maps.platform };
	std::vector<CMovingBitmap> player2_floor = { character1.image, maps.bridge, maps.platform };
	
	for (int i = 0; i < 131; i++) {
		player1_floor.push_back(maps.block[i]);
		player2_floor.push_back(maps.block[i]);
	}

	character1.SetWallAndFloor(character1.blocks);
	character2.SetWallAndFloor(character2.blocks);
	
	character1.OnInit();
	character2.OnInit();

	//�Ĥ@��
	if (phase <= 2)
	{
		button.LoadBitmapByString({ "resources/button1.bmp", "resources/button2.bmp" }, RGB(255, 255, 255));
		button.SetTopLeft(90 * 56, 859);
		button.SetFrameIndexOfBitmap(0);

		bridge.LoadBitmapByString({ "resources/bridge13.bmp" }, RGB(255, 255, 255));
		bridge.SetTopLeft(90 * 54 - 30, 900);

		platform.LoadBitmapByString({ "resources/platform.bmp" }, RGB(255, 255, 255));
		platform.SetTopLeft(90 * 73 + 50, 830);
		pFlag.LoadBitmapByString({
			"resources/pFlag0.bmp",
			"resources/pFlag1.bmp",
			"resources/pFlag2.bmp"
			}, RGB(255, 255, 255));
		pFlag.SetTopLeft(90 * 73 + 50, 688);
		pFlag.SetAnimation(1000, true);
		pFlag.SetFrameIndexOfBitmap(2);

		key.LoadBitmapByString({ "resources/key.bmp", "resources/key2.bmp", "resources/key3.bmp" , "resources/key4.bmp" }, RGB(255, 255, 255));
		key.SetTopLeft(90 * 71, 360);
		key.SetAnimation(300, false);

		door.LoadBitmapByString({ "resources/door.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
		door.SetTopLeft(90 * 85, 226);
		door.SetFrameIndexOfBitmap(0);
		maps.SetMap1Block();
	}

	else if (phase == 3) {
		for (int i = 0; i < 500; ++i) {
			block[i] = CMovingBitmap(); // �ϥιw�]�غc��
		}
		maps = Map(block);
		maps.SetMap2Block();
		door.LoadBitmapByString({ "resources/door.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
		door.SetTopLeft(1120, 810);
		door.SetFrameIndexOfBitmap(0);
	}

	for (int i = 0; i < 4; i++) {
		crown[i].LoadBitmapByString({ "resources/crown.bmp" });
		crown[i].SetTopLeft(270 + i * 300, 270);
	}

	clear .LoadBitmapByString({ "resources/clear.bmp" }, RGB(0, 255, 0));
	clear.SetTopLeft(-262, 430);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_UP) {
		if (phase > 1 && phase <= 5) {	//���d
			if (character1.checkJumpble == 1 ) //�S���L�~����A���M�|�s��
			{
				character1.checkJumpble = 0;
				character1.isUpRun = 1;
			}
		}
	}

	if (nChar == VK_RIGHT) {

		if (phase == 1) {	//�ؿ� phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//���d phase = 2~5
			character1.isRightRun = 1;
			character1.image.SetAnimation(125, false);
		}
	}

	if (nChar == VK_LEFT) {

		if (phase == 1) {	//�ؿ�
			if(sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//���d
			character1.isLeftRun = 1;
			character1.image.SetAnimation(125, false);
		}
	}

	if (nChar == 0x57) {  //player2 �W�� W
		if (phase > 1 && phase <= 5) {	//���d
			if (character2.checkJumpble == 1) //�S���L�~����A���M�|�s��
			{
				character2.checkJumpble = 0;
				character2.isUpRun = 1;
			}
		}
	}

	if (nChar == 0x44) {  //player2 �k�� D

		if (phase == 1) {	//�ؿ� phase = 1 
			if (sub_phase < 4)
				sub_phase = sub_phase + 1;
		}
		if (phase > 1 && phase <= 5) {	//���d phase = 2~5
			character2.isRightRun = 1;
			character2.image.SetAnimation(125, false);
		}
	}

	if (nChar == 0x41) {  //player2 ���� A

		if (phase == 1) {	//�ؿ�
			if (sub_phase > 1)
				sub_phase = sub_phase - 1;
		}
		if (phase > 1 && phase <= 5) {	//���d
			character2.isLeftRun = 1;
			character2.image.SetAnimation(125, false);
		}
	}

	if (nChar == VK_SPACE) {
		if (phase == 1) { // phase1���ؿ�
			phase = sub_phase + 1; // ������d
		}
		if (phase > 1 && phase <= 5) {	//���d
			if (door.GetFrameIndexOfBitmap() == 1&& doorP2isOverlap) {
				character2.characterIgnore = true;
			}
			if (doorP2isOverlap && staybyPlayer2 == 1) {
				door.SetFrameIndexOfBitmap(1);
				keyIgnore = true;
			}
		}
	}

	if (nChar == VK_RETURN) {
		if (phase == 1) { // phase1���ؿ�
			phase = sub_phase + 1; // ������d
			OnInit();
		}
		if (phase > 1 && phase <= 5) {	//���d
			if (door.GetFrameIndexOfBitmap() == 1 && doorP1isOverlap) {
				character1.characterIgnore = true;
			}
			if (doorP1isOverlap && staybyPlayer1 == 1) {
				door.SetFrameIndexOfBitmap(1);
				keyIgnore = true;
			}
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) {
		if (phase > 1 && phase <= 5) {	//���d
			character1.isRightRun = 0;
			character1.image.StopAnimation();
		}
	}

	if (nChar == VK_LEFT) {
		if (phase > 1 && phase <= 5) {	//���d
			character1.isLeftRun = 0;
			character1.image.StopAnimation();
		}
	}

	if (nChar == VK_UP) {
		character1.isUpRun = 0;
	}

	if (nChar == 0x44) { //P2�k
		character2.isRightRun = 0;
		character2.image.StopAnimation();
	}

	if (nChar == 0x41) { //P2��
		character2.isLeftRun = 0;
		character2.image.StopAnimation();
	}

	if (nChar == 0x57) {  //player2 �W�� W
		character2.isUpRun = 0;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
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
		if (level_one_completed) {
			crown[0].ShowBitmap();
		}
	}
	else if (phase == 2) {
		background.SetFrameIndexOfBitmap(phase - 2);
		background.ShowBitmap();
		if (buttonOverlap) {
			button.SetFrameIndexOfBitmap(1);
		}
		button.ShowBitmap();
		pFlag.ShowBitmap();
		door.ShowBitmap();

		character1.OnShow();
		character2.OnShow();
		
		for (int i = 0; i < 131; i++) {
			block[i].ShowBitmap();
		}
		bridge.ShowBitmap();
		platform.ShowBitmap();
		if (!keyIgnore) {
			key.ShowBitmap();
		}
		
	}
	else if (phase == 3) {
		background.SetFrameIndexOfBitmap(phase - 2);
		background.ShowBitmap();
		for (int i = 0; i < 122; i++) {
			block[i].ShowBitmap();
		}
		door.ShowBitmap();
		character1.OnShow();
		character2.OnShow();
	}

	if (character1.characterIgnore && character2.characterIgnore) {
		clear.ShowBitmap();
		if (clear.GetLeft() < 2101) {
			clear.SetTopLeft(clear.GetLeft() + 10, 430);
		}
		else if (clear.GetLeft() > 2101) {
			level_one_completed = true;
			phase = 1;
			character1.characterIgnore = false;
			character2.characterIgnore = false;
			keyIgnore = false;
			staybyPlayer1 = 0;
			staybyPlayer2 = 0;
			OnInit();
		}
	}
	if (phase == 4) {
		background.SetFrameIndexOfBitmap(phase - 2);
		background.ShowBitmap();

	}
	if (phase == 5) {
		background.SetFrameIndexOfBitmap(phase - 2);
		background.ShowBitmap();

	}
}

void CGameStateRun::show_text_by_phase() {

}