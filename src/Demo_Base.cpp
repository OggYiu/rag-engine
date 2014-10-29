#include "Demo_Base.h"

#include "Kernel.h"
#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include "Primitive.h"
#include "TextureMgr.h"
#include "Texture.h"
#include "GUI_Label.h"
#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "Helper.h"

Demo_Base::Demo_Base()
	: demoIndex_( -1 )
	, startIndex_( 0 )
	, isFirstRun_( true )
	, frameMarginX_( 0 )
	, frameMarginY_( 0 )
{
}

Demo_Base::~Demo_Base()
{
}

void Demo_Base::update(const double dt)
{
	Page::update( dt );
}

void Demo_Base::render()
{
	Page::render();
}

void Demo_Base::addDemo( DemoFunc func )
{
	demoFuncs_.push_back( func );
}

void Demo_Base::drawFrame( DisplayObjectContainer* container )
{
	int frameWidth = frameW_ = (int)( kernel.getScreenWidth() - frameMarginX_ * 2 );
	int frameHeight = frameH_ = (int)( kernel.getScreenHeight() - frameMarginY_ * 2 );
	int x = frameMarginX_;
	int y = frameMarginY_;
	container->transform().setPos( x, y );

	{
		FrameRect rect( 0, 0, frameWidth, frameHeight, 0xFF00FF00 );
		Texture* texture = textureMgr.createPrimitiveTexture( rect );
		DisplayObject* obj = new DisplayObject();
		obj->setTexture( texture );
		container->addChild( obj );
	}
	
	{
		Line line( 0, frameHeight / 2, frameWidth, frameHeight / 2, 0xFF0000FF );
		Texture* texture = textureMgr.createPrimitiveTexture( line );
		DisplayObject* obj = new DisplayObject();
		obj->setTexture( texture );
		container->addChild( obj );
	}
	
	{
		// Line line( 0, kernel.getScreenHeight(), kernel.getScreenWidth(), kernel.getScreenHeight(), 0xFF00FF00 );
		Line line( frameWidth / 2, 0, frameWidth / 2, frameHeight, 0xFF0000FF );
		Texture* texture = textureMgr.createPrimitiveTexture( line );
		DisplayObject* obj = new DisplayObject();
		obj->setTexture( texture );
		container->addChild( obj );
	}
}

bool Demo_Base::resolved()
{
	Page::resolved();

	nextDemo();
	
	kernel.getStage().addEventListener( KeyboardEvent::KEY_DOWN, bindEventHandler( &Demo_Base::onKeyboardEvent, this ), this );

	return true;
}

void Demo_Base::nextDemo()
{
	if ( isFirstRun_ ) {
		isFirstRun_ = false;
		if ( startIndex_ < 0 || startIndex_ >= (int)demoFuncs_.size() ) {
			startIndex_ = 0;
		}
		demoIndex_ = startIndex_;
	} else {
		++demoIndex_;
	}
	
	if ( demoIndex_ < 0 ) {
		demoIndex_ = 0;
	}

	if ( demoIndex_ >= (int)demoFuncs_.size() ) {
		demoIndex_ = 0;
	}

	demoFuncs_[demoIndex_]( this );
}

bool Demo_Base::onKeyboardEvent( const Event& event ATTR_UNUSED )
{
	nextDemo();
	return true;
}
