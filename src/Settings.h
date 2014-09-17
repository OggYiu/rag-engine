#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <string>
#include "SDL.h"

struct Settings
{
	std::string winName = "change this window name!";
	int screenWidth = 32;
	int screenHeight = 32;
	Uint8 bgRed = 0;
	Uint8 bgGreen = 0;
	Uint8 bgBlue = 0;
	int frameRate = 30;
};
	
#endif
