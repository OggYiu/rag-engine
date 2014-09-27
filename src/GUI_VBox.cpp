#include "GUI_VBox.h"

GUI_VBox::GUI_VBox()
	: nextPosY_( 0 )
	, marginY_( MARGIN_Y )
{
}

GUI_VBox::~GUI_VBox()
{
}

void GUI_VBox::rearrangeChildren()
{
	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectVec::iterator endIter = _entityVec.end();
	
	float nextX = 0;
	float nextY = 0;	
	while ( iter != endIter ) {
		(*iter)->transform().setPos( nextX, nextY );
		nextY += (*iter)->getHeight() + marginY_;
		++iter;
	}
}

void GUI_VBox::addChild( DisplayObjectBase* const entity )
{
	GUI_BaseContainer::addChild( entity );
	rearrangeChildren();
}
