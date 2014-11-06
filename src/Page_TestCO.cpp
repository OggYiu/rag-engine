#include "Page_TestCO.h"

#include "Entity_Bot.h"
#include "Helper.h"

Page_TestCO::Page_TestCO()
{
}

Page_TestCO::~Page_TestCO()
{
	std::vector<Entity_Bot*>::iterator iter = bots_.begin();
	std::vector<Entity_Bot*>::iterator endIter = bots_.end();
	while ( iter != endIter ) {
		SAFE_RELEASE( *iter );
		++iter;
	}
}

void Page_TestCO::update(const double dt)
{
	Page::update( dt );
}

void Page_TestCO::resolved()
{
	Page::resolved();
	
	{
		Entity_Bot* bot = new Entity_Bot();
		bots_.push_back( bot );
	}
}
