#include <iostream>

#include "Kernel.h"
#include "Settings.h"

#include "Page_TestDisplayObject.h"
#include "Page_LuaTest.h"
#include "Page_GfxTest.h"
#include "Page_Gameplay.h"
#include "Page_TestFont.h"
#include "Page_TestUI.h"
#include "Page_TestBtn.h"
#include "Page_TestLinearAlgebra.h"
#include "Page_TestCO.h"
#include "Demo_DisplayContainer.h"
#include "Demo_DisplayObject.h"
#include "Demo_Tween.h"

int main( int argc, char* argv[] )
{
	Settings settings;
	settings.bgRed = 150;
	settings.bgGreen = 150;
	settings.bgBlue = 150;
	settings.screenWidth = 640;
	settings.screenHeight = 480;
	settings.winName = "haha!";

//	Page_Test* startPage = new Page_Test();
//	Page_Editor* startPage = new Page_Editor();
//  Page_UITest* startPage = new Page_UITest();
//	Page_LuaTest* startPage = new Page_LuaTest();
	// Page_GfxTest* startPage = new Page_GfxTest();
	// Page_Gameplay* startPage = new Page_Gameplay();	
//	Page_TestFont* startPage = new Page_TestFont();
	// Page_TestUI* startPage = new Page_TestUI();
//	Page_TestBtn* startPage = new Page_TestBtn();
	// Demo_DisplayContainer* startPage = new Demo_DisplayContainer();
	// Demo_DisplayObject* startPage = new Demo_DisplayObject();
	Demo_Tween* startPage = new Demo_Tween();	
	// Page_TestCO* startPage = new Page_TestCO();	
	// Page_TestLinearAlgebra* startPage = new Page_TestLinearAlgebra();
	// Page_TestDisplayObject* startPage = new Page_TestDisplayObject();
	return kernel.exec( argc, argv, settings, startPage ) ? 0 : 1;
}
