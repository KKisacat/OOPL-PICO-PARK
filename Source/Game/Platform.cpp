#pragma once
#include "stdafx.h"
#include "Platform.h"

Platform::Platform() {

}

void Platform::MovePlatform(CMovingBitmap &platform_image, CMovingBitmap &pFlag, Character &character1, Character &character2, std::vector<CMovingBitmap> &box_blocks, int highest, int lowest, bool isPlatformUp) { // isPlatformU�b�ݥ��x�O��۩��Wor��۩��U
	//���x
	character2.characterIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop(), character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop() - 10, character2.image.GetHeight(), character2.image.GetWidth());
	character1.characterIsOverlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() - 10, character1.image.GetHeight(), character1.image.GetWidth(), character2.image.GetLeft(), character2.image.GetTop(), character2.image.GetHeight(), character2.image.GetWidth());
	platformP1Overlap = CMovingBitmap::IsOverlap(character1.image.GetLeft(), character1.image.GetTop() + 10, character1.image.GetHeight(), character1.image.GetWidth(), platform_image.GetLeft(), platform_image.GetTop(), platform_image.GetHeight(), platform_image.GetWidth());
	platformP2Overlap = CMovingBitmap::IsOverlap(character2.image.GetLeft(), character2.image.GetTop() + 10, character2.image.GetHeight(), character2.image.GetWidth(), platform_image.GetLeft(), platform_image.GetTop(), platform_image.GetHeight(), platform_image.GetWidth());
	if ((platformP1Overlap && platformP2Overlap) || (character1.characterIsOverlap && platformP1Overlap) || (character2.characterIsOverlap && platformP2Overlap)) {
		if (isPlatformUp) { //��ۥ��x�W��
			if (platform_image.GetTop() > highest) {
				if (!IsJumpable(platform_image, box_blocks, 0, -3)) {
					//���ΧO���禡�A�p�G���x�I���ê�����ʷ|�^��ture�A���X�l�]���ʡC�Ϥ�����U���|�^��false�A�X�l�]�U���C
					pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() - 3);
				}
				CheckMovable(platform_image, box_blocks, 0, -3);
				CheckMovable(character1.image, character1.blocks, 0, -3);
				CheckMovable(character2.image, character2.blocks, 0, -3);
			}
		}
		else { //��ۥ��x�U��
			if (platform_image.GetTop() < lowest) {
				if (!IsJumpable(platform_image, box_blocks, 0, 3)) {
					//���ΧO���禡�A�p�G���x�I���ê�����ʷ|�^��ture�A���X�l�]���ʡC�Ϥ�����U���|�^��false�A�X�l�]�U���C
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
		if (isPlatformUp) { //�S����ۥ��x���۰ʤU��
			if (platform_image.GetTop() < lowest) {
				if (!IsJumpable(platform_image, box_blocks, 0, 3)) {
					//���ΧO���禡�A�p�G���x�I���ê�����ʷ|�^��ture�A���X�l�]���ʡC�Ϥ�����U���|�^��false�A�X�l�]�U���C
					pFlag.SetTopLeft(pFlag.GetLeft(), pFlag.GetTop() + 3);
				}
				CheckMovable(platform_image, box_blocks, 0, 3);
				CheckMovable(character1.image, character1.blocks, 0, 3);
				CheckMovable(character2.image, character2.blocks, 0, 3);
			}
		}
		else { //�S����ۥ��x���۰ʤW��
			if (platform_image.GetTop() > highest) {
				if (!IsJumpable(platform_image, box_blocks, 0, -3)) {
					//���ΧO���禡�A�p�G���x�I���ê�����ʷ|�^��ture�A���X�l�]���ʡC�Ϥ�����U���|�^��false�A�X�l�]�U���C
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

	for (CMovingBitmap target : targets) //�M���Ҧ��|�I���쪺����
	{
		//�p�G�������|�N���ਫ�Aa &= b �O a = a & b
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (!isMovable) {
			return;
		}
	}
	player.SetTopLeft(player.GetLeft() + dx, player.GetTop() + dy);
}

//�ˬd�O�_�i�H���D
bool Platform::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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
