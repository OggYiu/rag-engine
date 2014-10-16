#include "GUI_VBox.h"

#include "GUI_VScrollBar.h"
#include "GUI_Image.h"
#include "Primitive.h"
#include "Logger.h"
#include "TextureMgr.h"
#include "Helper.h"

GUI_VBox::GUI_VBox( const int x, const int y, const int width, const int height )
	: itemsContainer_( nullptr )
	, bg_( nullptr )
	, nextPosY_( 0 )
	, marginY_( MARGIN_Y )
	, needRearrange_( false )
{
	setSize( width, height );
	transform().setPos( x, y );

	std::vector<Primitive*> primitives;
	primitives.push_back( new SolidRect ( 0, 0, width, height, RGBA2Int( 0, 0, 0, 100 ) ) );
	bg_ = new GUI_Image( 0, 0, primitives );
	addChild_( bg_ );
	
	itemsContainer_ = new GUI_BaseContainer();
	addChild_( itemsContainer_ );
}

GUI_VBox::~GUI_VBox()
{
}

void GUI_VBox::render()
{
	rearrangeChildren_();
	GUI_BaseContainer::render();
}

void GUI_VBox::addChild( DisplayObjectBase* const entity __attribute__((unused)) )
{
	logger.w( "GUI_VBox", "use addChild_ instead" );
}

void GUI_VBox::setClipRect( const int x, const int y, const int width, const int height )
{
	// std::cout << "vbox: " << x << ", " << y << ", " << width << ", " << height << std::endl;
	GUI_BaseContainer::setClipRect( x, y, width, height );
	itemsContainer_->setClipRect( x, y, width, height );
}

void GUI_VBox::addItem( DisplayObjectBase* const entity )
{
	itemsContainer_->addChild( entity );
	// this->addChild( entity );	
	rearrangeChildren();
}

bool GUI_VBox::resolved()
{		
	return true;
}

void GUI_VBox::addChild_( DisplayObjectBase* const entity __attribute__((unused)) )
{
	GUI_BaseContainer::addChild( entity );
}

void GUI_VBox::rearrangeChildren()
{
	needRearrange_ = true;
}

void GUI_VBox::rearrangeChildren_()
{
	if ( !needRearrange_ ) {
		return;
	}
	
	DisplayObjectVec::iterator iter = itemsContainer_->getChildren().begin();
	DisplayObjectVec::iterator endIter = itemsContainer_->getChildren().end();
	
	float nextX = 0;
	float nextY = 0;	
	while ( iter != endIter ) {
		(*iter)->transform().setPos( nextX, nextY );
		nextY += (*iter)->getHeight() + marginY_;
		++iter;
	}
	
	needRearrange_ = false;
}
