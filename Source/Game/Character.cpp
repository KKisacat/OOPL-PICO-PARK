#include "stdafx.h"
#include "Character.h"

Character::Character(vector<string> imgPaths, vector<string> imgPaths2, string name, int x, int y) {
	this->name = name;
	this->imgPaths = imgPaths;
	this->imgPaths2 = imgPaths2;
	this->x = x;
	this->y = y;
}

void Character::OnInit() {
	image.LoadBitmapByString(imgPaths, RGB(0, 255, 0));
	image.SetTopLeft(x, y);
	image2.LoadBitmapByString(imgPaths2, RGB(0, 255, 0));
	image.SetTopLeft(x, y);
	isCharacterLeftAnimation = false;
}

void Character::OnShow() {
	image2.SetTopLeft(image.GetLeft(), image.GetTop());
	if (!characterIgnore && isCharacterLeftAnimation) {
		image2.ShowBitmap();
	}
	if (!characterIgnore && !isCharacterLeftAnimation)
		image.ShowBitmap();
}

//���k��
void Character::TryMoveRight(Character &other) {
	if (this->image.GetLeft() < 1800 && other.image.GetLeft() > 0) {
		//�b�����Y�W�i�H�@�_���� (this�Y�W���S��other)
		characterIsOverlap = CMovingBitmap::IsOverlap(
			this->image.GetLeft(), this->image.GetTop() - 8, this->image.GetHeight(), this->image.GetWidth(), 
			other.image.GetLeft(), other.image.GetTop(), other.image.GetHeight(), other.image.GetWidth()
		);
		if (characterIsOverlap && !IsJumpable(this->image, this->blocks, 8, 0)) { //�����ܦ��]�B��
			CheckMovable(other.image, other.blocks, 8, 0);
		}
		CheckMovable(this->image, this->blocks, 8, 0);
	}
}

//������
void Character::TryMoveLeft(Character &other) {
	if (this->image.GetLeft() > 0 && other.image.GetLeft() < 1800) {
		characterIsOverlap = CMovingBitmap::IsOverlap(
			this->image.GetLeft(), this->image.GetTop() - 8, this->image.GetHeight(), this->image.GetWidth(),
			other.image.GetLeft(), other.image.GetTop(), other.image.GetHeight(), other.image.GetWidth()
		);
		if (characterIsOverlap && !IsJumpable(this->image, this->blocks, -8, 0)) {
			CheckMovable(other.image, other.blocks, -8, 0);
		}
		CheckMovable(this->image, this->blocks, -8, 0);
	}
}

//��
void Character::TryMoveUp() {
	if (this->upTime == 13) //����@�w���״N����
	{
		this->isUpRun = 0;
	}
	else
	{
		this->upTime++;
		CheckMovable(this->image, this->blocks, 0, -10);
	}
}

//����
void Character::TryFall(bool menuShow) {
	if (!menuShow) {
		this->upTime = 0;
		this->checkJumpble = IsJumpable(this->image, this->blocks, 0, 10); //����s��
		CheckMovable(this->image, this->blocks, 0, 10);
	}
}


//��Ҧ��I���g��fuction
void Character::CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
{
	bool isMovable = true;

	for (int i = 0; i < (int) targets.size(); i++) //�M���Ҧ��|�I���쪺����
	{
		CMovingBitmap target = targets[i];
		//�p�G�������|�N���ਫ�Aa &= b �O a = a & b
		isMovable = !CMovingBitmap::IsOverlap(player.GetLeft() + dx, player.GetTop() + dy, player.GetHeight(), player.GetWidth(), target.GetLeft(), target.GetTop(), target.GetHeight(), target.GetWidth());
		if (i >= 120 && i < 131) {
			TRACE("%d %d %d %d\n", i, target.GetLeft(), target.GetTop(), isMovable);
		}
		if (!isMovable) {
			return;
		}
	}
	player.SetTopLeft(player.GetLeft() + dx, player.GetTop() + dy);
}

bool Character::IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy)
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

void Character::SetWallAndFloor(vector<CMovingBitmap> blocks) {
	this->blocks = blocks;
}