#include <iostream>

#include "Kernel.h"
#include "Settings.h"
//#include "Page_Test.h"
//#include "Page_Editor.h"
// #include "Page_UITest.h"
//#include "Page_LuaTest.h"
//#include "Page_GfxTest.h"
//#include "Page_Gameplay.h"
//#include "Page_TestFont.h"
#include "Page_TestUI.h"
//#include "Page_TestLinearAlgebra.h"

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
	Page_TestUI* startPage = new Page_TestUI();
//	Page_TestLinearAlgebra* startPage = new Page_TestLinearAlgebra();	
	return kernel.exec( argc, argv, settings, startPage ) ? 0 : 1;
}
