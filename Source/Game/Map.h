#pragma once

#include "../Library/gameutil.h"

using namespace game_framework;

class Map
{
public:
	Map(CMovingBitmap *block);
	CMovingBitmap *block;
	void SetMap1Block();
	void SetMap2Block();



};
