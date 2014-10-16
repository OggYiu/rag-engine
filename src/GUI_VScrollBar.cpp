#include "GUI_VScrollBar.h"
#include "Primitive.h"
#include "Helper.h"
#include "Texture.h"
#include "DisplayObject.h"
#include "Component_Dragging.h"
#include "DragEvent.h"
#include "ScrollBarEvent.h"
#include "TextureMgr.h"

GUI_VScrollBar::GUI_VScrollBar( const int x, const int y, const int width, const int height, const float curValue, const float maxValue )
	: curValue_( curValue )
	, maxValue_( maxValue )
	, margin_( (int)( round( (float)width / 10.0 ) ) )
	, bg_( nullptr )
	, btn_( nullptr )	  
	, rangeInPixel_( 0.0f )
{
	setSize( width, height );
	transform().setPos( x, y );
	
	// std::cout << "pos: " << x << ", " << y << std::endl;

	{
		// background
		{
			std::vector<Primitive*> vec;
			SolidRect rect( 0, 0, getWidth(), getHeight(), RGBA2Int( 255, 0, 0, 100 ) );
			vec.push_back( &rect );
			Texture* texture = textureMgr.getInstance().createPrimitivesTexture( vec );
			// Texture* texture = new Texture( sdlTexture );
			bg_ = new DisplayObject();
			bg_->setTexture( texture );
			addChild( bg_ );
		}

		// button
		{
			std::vector<Primitive*> vec;
			SolidRect rect( 0, 0, getWidth() - margin_ * 2, 32, RGBA2Int( 0, 255, 0, 100 ) );
			vec.push_back( &rect );
			Texture* texture = textureMgr.getInstance().createPrimitivesTexture( vec );
			btn_ = new DisplayObject();
			btn_->setTexture( texture );
			btn_->transform().setPos( margin_, margin_ );
			btn_->addComponent( new Component_Dragging( btn_, margin_, margin_, 0, bg_->getHeight() - btn_->getHeight() - margin_ * 2 ) );
			addChild( btn_ );
	
			btn_->addEventListener( DragEvent::DRAG_BEGAN, bindEventHandler( &GUI_VScrollBar::dragEventHandler, this ), this );
			btn_->addEventListener( DragEvent::DRAG_MOVE, bindEventHandler( &GUI_VScrollBar::dragEventHandler, this ), this );
			btn_->addEventListener( DragEvent::DRAG_ENDED, bindEventHandler( &GUI_VScrollBar::dragEventHandler, this ), this );
			
			rangeInPixel_ = bg_->getHeight() - margin_ * 2 - btn_->getHeight();
		}

	}
}

GUI_VScrollBar::~GUI_VScrollBar()
{
	btn_->removeEventListener( DragEvent::DRAG_BEGAN, this );
	btn_->removeEventListener( DragEvent::DRAG_MOVE, this );
	btn_->removeEventListener( DragEvent::DRAG_ENDED, this );
}

float GUI_VScrollBar::getPercentage()
{
	float percentage = 0.0f;

	float btnY = btn_->transform().getY() - margin_;
	percentage = btnY / rangeInPixel_;

	if ( percentage < 0.0f ) {
		percentage = 0.0f;
	} else if ( percentage > 1.0f ) {
		percentage = 1.0f;
	}
	return percentage;
}

bool GUI_VScrollBar::dragEventHandler( const Event& event )
{
	// std::cout << "gui vscrollbar, dragEventHandler" << std::endl;
	DragEvent* dragEvent = ( DragEvent* )&event;
	if ( dragEvent->getType() == DragEvent::DRAG_BEGAN ) {
	}
	else if ( dragEvent->getType() == DragEvent::DRAG_MOVE ) {
		ScrollBarEvent scrollBarEvent( ScrollBarEvent::SCROLL_BAR_VALUE_CHANGED, this );
		this->dispatchEvent( scrollBarEvent );
	}
	else if ( dragEvent->getType() == DragEvent::DRAG_ENDED ) {
	}

	return true;
}
