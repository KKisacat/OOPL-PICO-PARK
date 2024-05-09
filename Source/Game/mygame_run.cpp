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
	maps.RefreshWall(character1, character2);

	if (phase > 1) {

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

		//�_�͸��H
		maps.GetKey(character1, character2);

		//�e������
		maps.RollScreen(character1, character2);

	}

	if (phase == 2)
	{
		
		// �p�Ŧ�������
		if (character1.image.GetTop() > 1024) {
			character1.image.SetTopLeft(character1.image.GetLeft() - 700, 0);
		}

		//�p���Y���V�᭫��
		if (character2.image.GetTop() > 1024) {
			character2.image.SetTopLeft(character2.image.GetLeft() - 700, 0);
		}

		//�j��
		maps.CheckDoorOverlap(character1, character2);

		//�����s���X�{
		maps.PressButton(character1, character2);

		//���x
		maps.MovePlatform(character1, character2);
	}
	else if (phase == 3) 
	{
		//�c�l2����
		maps.TryFallBox();
		//�T�O�c�l�S�Q�����ɭԫO����l
		maps.box1.SetFrameIndexOfBitmap(1);
		maps.box2.SetFrameIndexOfBitmap(1);

		//���c�l
		//�p��
		if (character1.isRightRun)
		{
			maps.PushBox(character1, maps.box1, 8);
			maps.PushBox(character1, maps.box2, 8);
		}
		else if (character1.isLeftRun)
		{
			maps.PushBox(character1, maps.box1, -8); 
			maps.PushBox(character1, maps.box2, -8);
		}
		//�p��
		if (character2.isRightRun)
		{
			maps.PushBox(character2, maps.box1, 8);
			maps.PushBox(character2, maps.box2, 8);
		}
		else if (character2.isLeftRun)
		{
			maps.PushBox(character2, maps.box1, -8);
			maps.PushBox(character2, maps.box2, -8);
		}
		//��H��������
		/*
		if (character1.isRightRun || character2.isRightRun) {
			maps.PushBox2(character1, character2, 8);
		}
		if (character1.isLeftRun || character2.isLeftRun) {
			maps.PushBox2(character1, character2, -8);
		}
		*/

	}
	else {

	}
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

	maps.OnInit(character1, character2, phase);
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
			OnInit();
		}
		if (phase > 1 && phase <= 5) {	//���d
			if (maps.door.GetFrameIndexOfBitmap() == 1 && maps.doorP2isOverlap) {
				character2.characterIgnore = true;
				character2.OnInit();
			}
			if (maps.doorP2isOverlap && maps.staybyCharacter2 == 1) {
				maps.door.SetFrameIndexOfBitmap(1);
				maps.keyIgnore = true;
			}
		}
	}

	if (nChar == VK_RETURN) {
		if (phase == 1) { // phase1���ؿ�
			phase = sub_phase + 1; // ������d
			OnInit();
		}
		if (phase > 1 && phase <= 5) {	//���d
			if (maps.door.GetFrameIndexOfBitmap() == 1 && maps.doorP1isOverlap) {
				character1.characterIgnore = true;
				character1.OnInit();
			}
			if (maps.doorP1isOverlap && maps.staybyCharacter1 == 1) {
				maps.door.SetFrameIndexOfBitmap(1);
				maps.keyIgnore = true;
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
		if (maps.level_one_completed) {
			maps.crown[0].ShowBitmap();
		}
	}
	else if (phase == 2) {
		maps.background.SetFrameIndexOfBitmap(phase - 2);
		maps.background.ShowBitmap();
		if (maps.buttonOverlap) {
			maps.button.SetFrameIndexOfBitmap(1);
		}
		maps.button.ShowBitmap();
		maps.pFlag.ShowBitmap();
		maps.door.ShowBitmap();

		character1.OnShow();
		character2.OnShow();
		
		for (int i = 0; i < 131; i++) {
			maps.block[i].ShowBitmap();
		}
		maps.bridge.ShowBitmap();
		maps.platform.ShowBitmap();
		if (!maps.keyIgnore) {
			maps.key.ShowBitmap();
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
		maps.box1.ShowBitmap();
		maps.box2.ShowBitmap();
		if (!maps.keyIgnore) {
			maps.key.ShowBitmap();
		}
	}

	if (character1.characterIgnore && character2.characterIgnore) {
		maps.clear.ShowBitmap();
		if (maps.clear.GetLeft() < 2101) {
			maps.clear.SetTopLeft(maps.clear.GetLeft() + 10, 430);
		}
		else if (maps.clear.GetLeft() > 2101) {
			maps.level_one_completed = true;
			phase = 1;
			maps.keyIgnore = false;
			character1.characterIgnore = false;
			character2.characterIgnore = false;
			maps.staybyCharacter1 = 0;
			maps.staybyCharacter2 = 0;
			OnInit();
		}
	}
	if (phase == 4) {
		maps.background.SetFrameIndexOfBitmap(phase - 2);
		maps.background.ShowBitmap();

	}
	if (phase == 5) {
		maps.background.SetFrameIndexOfBitmap(phase - 2);
		maps.background.ShowBitmap();

	}
}

void CGameStateRun::show_text_by_phase() {

}