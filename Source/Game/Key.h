#pragma once

#include "../Library/gameutil.h"
#include "Character.h"

using namespace game_framework;

class Key
{
public:
	Key();
	CMovingBitmap image;

	bool keyP1Overlap;
	bool keyP2Overlap;
	//∆_∞Õ∏Ú¿H
	int staybyCharacter1 = 0;
	int staybyCharacter2 = 0;

	void GetKey(Character &character1, Character &character2);
};