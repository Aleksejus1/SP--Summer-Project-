#include "variables.h"
#include "libs.h"
#include "character.h"
#include "map.h"
#include "spell.h"

variables::variables(){
	messageColorPressed = { 215, 215, 215, 255 };
	additionColor = { 14, 90, 0, 255 };
	levelColor = { 185, 0, 4, 255 };
	offset = { 0, 0 };
	mouseOffsetFromMovableObject = { 0, 0 };
}
