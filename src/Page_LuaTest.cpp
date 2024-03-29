#include "Page_LuaTest.h"

#include "boost/bind.hpp"
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

void Page_LuaTest::update(const double dt)
{
	Page::update(dt);
}

void Page_LuaTest::resolved()
{
	Page::resolved();
}

bool Page_LuaTest::eventHandler(const Event& event ATTR_UNUSED )
{
//	reload();
	{
		float x = randInRange(0, kernel.getScreenWidth());
		float y = randInRange(0, kernel.getScreenHeight());
		float distance = pow(image1_->transform().getX()-x, 2) + pow(image1_->transform().getY()-y, 2);
		image1_->tweener().moveTo(distance / 100000.0f, x, y, boost::bind(&Page_LuaTest::here, this));
	}

	{
		float x = randInRange(1, 5);
		float y = randInRange(1, 5);
		float distance = pow(image1_->transform().getX()-x, 2) + pow(image1_->transform().getY()-y, 2);
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
