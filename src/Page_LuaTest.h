#ifndef __PAGE_LUATEST_H__
#define __PAGE_LUATEST_H__

#include "Page.h"
#include "Event.h"

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

class GUI_Image;

class Page_LuaTest : public Page
{
public:
	Page_LuaTest();
	~Page_LuaTest();
	
public:
	virtual void update(const double dt);

protected:
	virtual bool resolved();
	void reload();
	bool eventHandler(const Event& event);
	void here();

private:
	lua_State* luaState_;
	GUI_Image* image1_;
};

#endif
