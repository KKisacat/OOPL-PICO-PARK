#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

//��Ҧ��I���g��fuction
void CGameStateRun::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
{
	bool isMovable = true;

	for (CMovingBitmap target : targets) //�M���Ҧ��|�I���쪺����
	{
		//�p�G�������|�N���ਫ�Aa &= b �O a = a & b
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable ) {
			return;
		}
	}
	player.SetTopLeft(player.GetLeft() + dx, player.GetTop() + dy);
}

//�ˬd�O�_�i�H���D
bool CGameStateRun::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
{
	bool isMovable;

	for (CMovingBitmap target : targets) //�M���Ҧ��|�I���쪺����
	{
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable) { //���ਫ�N��I��a�O �I��a�O�~���
			return true;
		}
	}
	return false;
}

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
	std::vector<CMovingBitmap> player1_wall = { character2.image, bridge, platform, block[23], block[24], block[45], block[90], block[95], block[96], block[100] };
	std::vector<CMovingBitmap> player2_wall = { character1.image, bridge, platform, block[23], block[24], block[45], block[90], block[95], block[96], block[100] };
	std::vector<CMovingBitmap> player1_floor = { character2.image, bridge, platform };
	std::vector<CMovingBitmap> player2_floor = { character1.image, bridge, platform };
	std::vector<CMovingBitmap> platform_block = { character1.image, character2.image };

	for (int i = 116; i < 131; i++) {
		player1_wall.push_back(block[i]);
		player2_wall.push_back(block[i]);
	}

	for (int i = 101; i < 107; i++) {
		player1_wall.push_back(block[i]);
		player2_wall.push_back(block[i]);
	}

	for (int i = 106; i < 116; i++) {
		player1_floor.push_back(block[i]);
		player2_floor.push_back(block[i]);
	}

	for (int i = 0; i < 101; i++) {
		player1_floor.push_back(block[i]);
		player2_floor.push_back(block[i]);
	}

	character1.SetWallAndFloor(player1_wall, player1_floor);
	character2.SetWallAndFloor(player2_wall, player2_floor);


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

	//���U���s
	buttonOverlap = CMovingBitmap::IsOverlap(character1.image, button) || CMovingBitmap::IsOverlap(character2.image, button);

	//��
	if (button.GetFrameIndexOfBitmap() == 1) {
		if (block[45].GetLeft() - bridge.GetLeft() < 550) {
			bridgeP1Overlap = CMovingBitmap::IsOverlap(character2.image, bridge);
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

	//�_�͸��H
	keyP1Overlap = CMovingBitmap::IsOverlap(character1.image, key);
	keyP2Overlap = CMovingBitmap::IsOverlap(character2.image, key);
	if (keyP1Overlap) {
		staybyPlayer1 = 1;
		staybyPlayer2 = 0;
	}
	if (staybyPlayer1 == 1) {
		key.SetTopLeft(character1.image.GetLeft() - 70, character1.image.GetTop() - 80);
	}
	if (keyP2Overlap) {
		staybyPlayer2 = 1;
		staybyPlayer1 = 0;
	}
	if (staybyPlayer2 == 1) {
		key.SetTopLeft(character2.image.GetLeft() - 70, character2.image.GetTop() - 80);
	}


	//���x
	P1onP2isOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop() - 10, character2.image.GetHeight(), character2.image.GetWidth());
	P2onP1isOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() - 10, character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth());
	platformP1Overlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() + 10, character1.image.GetHeight(), character1.image.GetWidth(), platform.GetLeft(), platform.GetTop(), platform.GetHeight(), platform.GetWidth());
	platformP2Overlap = CMovingBitmap::IsOverlap(character2.image.GetLeft(), character2.image.GetTop() + 10, character2.image.GetHeight(), character2.image.GetWidth(), platform.GetLeft(), platform.GetTop(), platform.GetHeight(), platform.GetWidth());
	if ((platformP1Overlap && platformP2Overlap) || (P2onP1isOverlap && platformP1Overlap) || (P1onP2isOverlap && platformP2Overlap)) {
		//���x�W��
		if (platform.GetTop() > 370) {
			platform.SetTopLeft(platform.GetLeft(), platform.GetTop() - 3);
			pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() - 3);
			CheckMovable(character1.image, player1_floor, 0, -3);
			CheckMovable(character2.image, player2_floor, 0, -3);
		}
		pFlag.SetFrameIndexOfBitmap(0);
	}
	else {
		//���x�U��
		if (platform.GetTop() < 830) {
			if (!IsJumpable(platform, platform_block, 0, 3)) {
				//���ΧO���禡�A�p�G���x�I���ê�����ʷ|�^��ture�A���X�l�]���ʡC�Ϥ�����U���|�^��false�A�X�l�]�U���C
				pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() + 3);
			}
			CheckMovable(platform, platform_block, 0, 3);
			CheckMovable(character1.image, player1_floor, 0, 3);
			CheckMovable(character2.image, player2_floor, 0, 3);
		}
		if (platformP1Overlap || platformP2Overlap) {
			pFlag.SetFrameIndexOfBitmap(1);
		}
		else {
			pFlag.SetFrameIndexOfBitmap(2);
		}
	}


	//�j��
	doorP1isOverlap = CMovingBitmap::IsOverlap(character1.image, door);
	doorP2isOverlap = CMovingBitmap::IsOverlap(character2.image, door);


	//�e������
	if (((character1.image.GetLeft() + character2.image.GetLeft()) / 2) > 1000 )
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
	}
	else if(((character1.image.GetLeft() + character2.image.GetLeft()) / 2) < 800)
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
	}
}


void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	background.LoadBitmapByString({
		"resources/phase21_background.bmp",
		"resources/phase31_background.bmp",
		"resources/phase41_background.bmp",
		"resources/phase51_background.bmp"
		});
	background.SetTopLeft(0, 0);

	catalog.LoadBitmapByString({
		"resources/phase11_background.bmp",
		"resources/phase12_background.bmp",
		"resources/phase13_background.bmp",
		"resources/phase14_background.bmp"
		});
	catalog.SetTopLeft(0, 0);
	
	character1.OnInit();
	character2.OnInit();


	button.LoadBitmapByString({ "resources/button1.bmp", "resources/button2.bmp" }, RGB(255, 255, 255));
	button.SetTopLeft(90 * 56, 859);
	button.SetAnimation(1000, true);

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

	for (int i = 0; i < 4; i++) {
		crown[i].LoadBitmapByString({ "resources/crown.bmp" });
		crown[i].SetTopLeft(270 + i * 300, 270);
	}
	
	//�_�I���
	for (int i = 120; i < 131; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(0, 900 - 90 * (i - 120));
	}
	//�}�}�e���a�O
	for (int i = 0; i < 24; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * i, 900);
	}
	//�}�}�᪺�a�O
	for (int i = 24; i < 45; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (i + 2), 900);
	}
	//�Ĥ@�Ӷ���
	for (int i = 90; i < 96; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (41 + i - 90), (900 - 90));
	}
	//�ĤG�Ӷ���
	for (int i = 96; i < 101; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (42 + i - 96), (900 - 90 * 2));
	}
	//���ʥ��x�᪺�a�O
	for (int i = 45; i < 90; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (i + 8), 900);
	}
	//����
	for (int i = 101; i < 106; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * 78, 900 - 90 * (i - 100));
	}
	//���I���x
	for (int i = 106; i < 116; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * (78 + i - 106), 900 - 90 * 6);
	}
	//���I���
	for (int i = 116; i < 120; i++) {
		block[i].LoadBitmapByString({ "resources/block.bmp" }, RGB(255, 255, 255));
		block[i].SetTopLeft(90 + 90 * 87, 900 - 90 * (i - 109)); 
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
				player2Ignore = true;
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
		}
		if (phase > 1 && phase <= 5) {	//���d
			if (door.GetFrameIndexOfBitmap() == 1 && doorP1isOverlap) {
				player1Ignore = true;
			}
			if (doorP1isOverlap && staybyPlayer1 == 1) {
				door.SetFrameIndexOfBitmap(1);
				keyIgnore = true;
			}
		}
		

		/*
		else if (phase == 2) {
			ResetMovingTime();
			if (sub_phase == 1) {
				sub_phase += validate_phase_2();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}
		*/
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
	}
	if (phase > 1 && phase <= 5) {
		background.SetFrameIndexOfBitmap(phase - 2);
		background.ShowBitmap();
		if (buttonOverlap) {
			button.SetFrameIndexOfBitmap(1);
		}
		button.ShowBitmap();
		pFlag.ShowBitmap();
		door.ShowBitmap();

		character1.OnShow();
		if (!player1Ignore) 
			character1.image.ShowBitmap();
		if (!player2Ignore)
			character2.image.ShowBitmap();
		for (int i = 0; i < 131; i++) {
			block[i].ShowBitmap();
		}
		bridge.ShowBitmap();
		platform.ShowBitmap();
		if (!keyIgnore) {
			key.ShowBitmap();
		}
		
	}
	if (player1Ignore && player2Ignore) {
		clear.ShowBitmap();
		if (clear.GetLeft() < 2101) {
			clear.SetTopLeft(clear.GetLeft() + 10, 430);
		}
		else if (clear.GetLeft() > 2101) {
			phase = 1;
			crown[0].ShowBitmap();
		}
	}
}

void CGameStateRun::show_text_by_phase() {

}

bool CGameStateRun::validate_phase_1() {
	return character1.image.GetImageFileName() == "resources/giraffe.bmp";
}

bool CGameStateRun::validate_phase_2() {
	return character1.image.GetTop() > 204 && character1.image.GetTop() < 325 && character1.image.GetLeft() > 339 && character1.image.GetLeft() < 459;
}

/*
bool CGameStateRun::validate_phase_3() {
	
	return (
		
		player1.GetTop() + player1.GetHeight() >= chest_and_key.GetTop()
		&& player1.GetLeft() + player1.GetWidth() >= chest_and_key.GetLeft()
		&& chest_and_key.GetFrameIndexOfBitmap() == 1
		&& chest_and_key.GetFilterColor() == RGB(255, 255, 255)
	);
}

bool CGameStateRun::validate_phase_4() {
	return bee.IsAnimation() && bee.GetFrameSizeOfBitmap() == 2;
}

bool CGameStateRun::validate_phase_5() {
	
	bool check_all_door_is_open = true;
	for (int i = 0; i < 3; i++) {
		check_all_door_is_open &= (door[i].GetFrameIndexOfBitmap() == 1);
	}
	return check_all_door_is_open;
	
}

bool CGameStateRun::validate_phase_6() {
	return ball.IsAnimationDone() && !ball.IsAnimation() && ball.GetFrameIndexOfBitmap() == ball.GetFrameSizeOfBitmap() - 1;
}
*/