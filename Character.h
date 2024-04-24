#pragma once

#include "../Library/gameutil.h"

using namespace game_framework;

class Character
{
public:
	CMovingBitmap image;
	string name;
	vector<string> imgPaths;
	//���k
	bool isRightRun = 0;
	bool isLeftRun = 0;
	//��
	int upTime = 0;
	bool isUpRun = 0;
	bool jumpOnce = 0;
	//���|
	bool buttonOverlap;
	bool keyOverlap;
	bool bridgeOverlap;
	bool platformOverlap;
	bool characterIsOverlap; // �֦b���Y�W
	bool doorIsOverlap;
	//�_�͸��H
	int staybyCharacter = 0;
	//�i�j��
	bool characterIgnore = false;
	//�I��
	std::vector<CMovingBitmap> wall;
	std::vector<CMovingBitmap> floor;

	Character(vector<string> imgPath, string name);
	void OnInit();
};

