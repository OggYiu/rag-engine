#include "GUI_ScrollVBox.h"

#include "GUI_Image.h"
#include "GUI_VBox.h"
#include "GUI_VScrollBar.h"
#include "ScrollBarEvent.h"
#include "Logger.h"
#include "Helper.h"

GUI_ScrollVBox::GUI_ScrollVBox( const int x, const int y, const int width, const int height )
	: box_( nullptr )
	, scrollBar_( nullptr )
	, bound_( 0 )
{
	setSize( width , height );
	transform().setPos( x, y );
	
	std::vector<Primitive*> primitives;
	primitives.push_back( new SolidRect ( 0, 0, width - GUI_VScrollBar::BAR_WIDTH, height, RGBA2Int( 0, 0, 0, 100 ) ) );
	GUI_Image* bg = new GUI_Image( 0, 0, primitives );
	addChild_( bg );

	box_ = new GUI_VBox( 0.0f, 0.0f, width, height );
	this->addChild_( box_ );

	scrollBar_ = new GUI_VScrollBar( width - GUI_VScrollBar::BAR_WIDTH, 0, GUI_VScrollBar::BAR_WIDTH, height );
	this->addChild_( scrollBar_ );
	scrollBar_->addEventListener( ScrollBarEvent::SCROLL_BAR_VALUE_CHANGED, bindEventHandler( &GUI_ScrollVBox::eventHandler, this ), this );
}

GUI_ScrollVBox::~GUI_ScrollVBox()
{
}

void GUI_ScrollVBox::addChild(DisplayObjectBase* const entity ATTR_UNUSED )
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
	
	SDL_Rect& boundingBox = box_->get_itemsContainer()->getBBox();
	// std::cout << "gui_scrollvbox::additem, numberof children: " << box_->getChildren().size() <<  ", " << boundingBox.x << ", " << boundingBox.y << ", " << boundingBox.w << ", " << boundingBox.h << std::endl;

	bound_ = boundingBox.h - this->getHeight();

	// std::stringstream ss;
	// ss << "children count: " << box_->get_itemsContainer()->getChildren().size() << ", box: " << boundingBox.x << ", " << boundingBox.y << ", " << boundingBox.w << ", " << boundingBox.h;
	// logger.getInstance().d( "xxxx", ss.str() );
}
		
void GUI_ScrollVBox::resolved()
{
	GUI_BaseContainer::resolved();
	
	// GUI_VScrollBar( const int width, const int height, const float curValue = 0.0f, const float maxValue = 100.0f );
}

void GUI_ScrollVBox::addChild_( DisplayObjectBase* const entity )
{
	GUI_BaseContainer::addChild( entity );
}

bool GUI_ScrollVBox::eventHandler( const Event& event )
{
	ScrollBarEvent* scrollBarEvent = (ScrollBarEvent*)&event;

	// std::cout << "gui scroll vbox event handler" << std::endl;
	if ( scrollBarEvent->isEqual( ScrollBarEvent::SCROLL_BAR_VALUE_CHANGED ) ) {
		GUI_VScrollBar* scrollBar = scrollBarEvent->getScrollBar();
		float percentage = scrollBar->getPercentage();
		box_->transform().setY( -bound_ * percentage );
		// box_->get_itemsContainer()->foo();
	}

	return true;
}
