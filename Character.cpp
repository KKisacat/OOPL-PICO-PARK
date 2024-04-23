#include "stdafx.h"
#include "Character.h"

Character::Character(vector<string> imgPaths, string name) {
	this->name = name;
	this->imgPaths = imgPaths;
}

void Character::OnInit() {
	image.LoadBitmapByString(imgPaths, RGB(0, 255, 0));
	image.SetTopLeft(1020, 810);
}
