#include "Page_LuaTest.h"

#include <iostream>
#include "Helper.h"
#include "GUI_Button.h"
#include "GUI_Image.h"
#include "MouseEvent.h"

Page_LuaTest::Page_LuaTest()
{

}

Page_LuaTest::~Page_LuaTest()
{
	if (luaState_ != nullptr)
	{
		lua_close(luaState_);
	}
}
	
void Page_LuaTest::enter()
{
	Page::enter();
}

void Page_LuaTest::update(const double dt)
{
	Page::update(dt);
}

bool Page_LuaTest::resolved()
{
	Page::resolved();

//	reload();

	GUI_Button* button1 = GUI_Button::createImageButton(100, 100, "assets/ui/button1.png");
	this->addChild(button1);
	button1->addEventListener(MouseEvent::MOUSE_DOWN, bindEventHandler(&Page_LuaTest::eventHandler, this), this);

	image1_ = new GUI_Image(kernel.getScreenWidth()/2, kernel.getScreenHeight()/2, "assets/alex.png");
	this->addChild(image1_);

//	foo object;
//    somefunction(&forwarder, &object);
	return true;
}

bool Page_LuaTest::eventHandler(const Event& event __attribute__((unused)) )
{
//	reload();
	{
		float x = randInRange(0, kernel.getScreenWidth());
		float y = randInRange(0, kernel.getScreenHeight());
		float distance = pow(image1_->getX()-x, 2) + pow(image1_->getY()-y, 2);
		image1_->tweener().moveTo(distance / 100000.0f, x, y, boost::bind(&Page_LuaTest::here, this));
	}

	{
		float x = randInRange(1, 5);
		float y = randInRange(1, 5);
		float distance = pow(image1_->getX()-x, 2) + pow(image1_->getY()-y, 2);
		image1_->tweener().scaleTo(distance / 100000.0f, x, y, boost::bind(&Page_LuaTest::here, this));
	}

	return true;
}

void Page_LuaTest::here()
{
	std::cout << "here dude" << std::endl;
}

void Page_LuaTest::reload()
{
	if (luaState_ != nullptr)
	{
		lua_close(luaState_);		
	}
	
	{
		std::string filename = "scripts/hello.lua";
		insertBaseDir(filename);
		std::cout << filename << std::endl;
		luaState_ = luaL_newstate();
	
		// load the libs
		luaL_openlibs(luaState_);
	
		// if ( luaL_loadfile(luaState_, filename.c_str()) ||
		// 	 lua_pcall(luaState_, 0, 0, 0)) {
		int result = luaL_dofile(luaState_, filename.c_str());
		if ( result != 0 ) {		
			std::cout<<"Error: script not loaded ("<<filename<<")"<<std::endl;
			// luaState_ = nullptr;
		}

		if (luaState_ != nullptr)
		{
			lua_Debug info;
			int level = 0;
			while (lua_getstack(luaState_, level, &info)) {
				lua_getinfo(luaState_, "nSl", &info);
				fprintf(stderr, "  [%d] %s:%d -- %s [%s]\n",
						level, info.short_src, info.currentline,
						(info.name ? info.name : "<unknown>"), info.what);
				++level;
			}
		}		
	}
}
