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
{
	itemsContainer_ = new GUI_BaseContainer();

	setSize( width, height );
	transform().setPos( x, y );

	// std::vector<Primitive*> primitives;
	// primitives.push_back( new SolidRect ( 0, 0, width, height, RGBA2Int( 0, 0, 0, 100 ) ) );
	// bg_ = new GUI_Image( 0, 0, primitives );
	// addChild_( bg_ );
	
	addChild_( itemsContainer_ );
	itemsContainer_->setSize( width, height );
}

GUI_VBox::~GUI_VBox()
{
}

void GUI_VBox::render()
{
	GUI_BaseContainer::render();
}

void GUI_VBox::addChild(DisplayObjectBase* const entity ATTR_UNUSED )
{
	logger.w( "GUI_VBox", "use addChild_ instead" );
}

void GUI_VBox::setClipRect( const int x, const int y, const int width, const int height )
{
	GUI_BaseContainer::setClipRect( x, y, width, height );
	itemsContainer_->setClipRect( x, y, width, height );
}

SDL_Rect& GUI_VBox::getBBox()
{
	return itemsContainer_->getBBox();
}

GUI_BaseContainer* GUI_VBox::get_itemsContainer()
{
	return itemsContainer_;
}

void GUI_VBox::addItem( DisplayObjectBase* const entity )
{
	itemsContainer_->addChild( entity );
	itemsContainer_->setClipRect( 0, 0, itemsContainer_->getWidth(), itemsContainer_->getHeight() );
	rearrangeChildren();
	// itemsContainer_->foo();

	// std::cout << std::endl;
	// std::cout << "-------------------- start update bounding box" << std::endl;
	// itemsContainer_->tryUpdateBoundingBox();
	// SDL_Rect& bbox = itemsContainer_->getBBox();
	// std::cout << "itemscontainer num children: " << itemsContainer_->getChildren().size() << std::endl;
	// std::cout << "boundingbox: " << bbox.x << ", " << bbox.y << ", " << bbox.w << ", " << bbox.h << std::endl;
	// std::cout << "-------------------- end update bounding box" << std::endl << std::endl;	
}

bool GUI_VBox::resolved()
{		
	return true;
}

void GUI_VBox::addChild_(DisplayObjectBase* const entity ATTR_UNUSED )
{
	GUI_BaseContainer::addChild( entity );
}

void GUI_VBox::rearrangeChildren()
{
	float nextX = 0;
	float nextY = 0;		
	DisplayObjectVec::iterator iter = itemsContainer_->getChildren().begin();
	DisplayObjectVec::iterator endIter = itemsContainer_->getChildren().end();
	while ( iter != endIter ) {
		(*iter)->transform().setPos( nextX, nextY );
		nextY += (*iter)->getHeight() + marginY_;
		++iter;
	}
}
