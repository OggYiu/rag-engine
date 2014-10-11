#include "GUI_ScrollVBox.h"

#include "GUI_VBox.h"
#include "GUI_VScrollBar.h"
#include "Logger.h"

GUI_ScrollVBox::GUI_ScrollVBox( const int x, const int y, const int width, const int height )
	: box_( nullptr )
	, scrollBar_( nullptr )
{
	setSize( width , height );
	transform().setPos( x, y );
	
	box_ = new GUI_VBox( 0.0f, 0.0f, width, height );
	this->addChild_( box_ );

	const int scrollBarSize = 16;
	scrollBar_ = new GUI_VScrollBar( width - scrollBarSize, 0, scrollBarSize, height );
	this->addChild_( scrollBar_ );
}

GUI_ScrollVBox::~GUI_ScrollVBox()
{
}

void GUI_ScrollVBox::addChild( DisplayObjectBase* const entity __attribute__((unused)) )
{
	logger.getInstance().e( "GUI_ScrollVBox", "please use addChild_ instead" );
}

void GUI_ScrollVBox::update(const double dt)
{
	GUI_BaseContainer::update( dt );
}

void GUI_ScrollVBox::addItem( DisplayObjectBase* obj )
{
	box_->addItem( obj );
}
		
bool GUI_ScrollVBox::resolved()
{
	GUI_BaseContainer::resolved();
	
	// GUI_VScrollBar( const int width, const int height, const float curValue = 0.0f, const float maxValue = 100.0f );

	return true;
}

void GUI_ScrollVBox::addChild_( DisplayObjectBase* const entity )
{
	GUI_BaseContainer::addChild( entity );
}
