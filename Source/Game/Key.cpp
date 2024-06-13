#pragma once
#include "stdafx.h"
#include "Key.h"

Key::Key() {

}

void Key::GetKey(Character &character1, Character &character2) {

	//∆_∞Õ∏Ú¿H
	keyP1Overlap = CMovingBitmap::IsOverlap(character1.image, image);
	keyP2Overlap = CMovingBitmap::IsOverlap(character2.image, image);
	if (keyP1Overlap) {
		staybyCharacter1 = 1;
		staybyCharacter2 = 0;
	}
	if (staybyCharacter1 == 1) {
		image.SetTopLeft(character1.image.GetLeft() - 70, character1.image.GetTop() - 80);
	}

	if (keyP2Overlap) {
		staybyCharacter2 = 1;
		staybyCharacter1 = 0;
	}
	if (staybyCharacter2 == 1) {
		image.SetTopLeft(character2.image.GetLeft() - 70, character2.image.GetTop() - 80);
	}
}
