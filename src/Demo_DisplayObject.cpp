#include "Demo_DisplayObject.h"

#include "DisplayObject.h"
#include "Primitive.h"
#include "TextureMgr.h"
#include "GUI_Label.h"
#include "Helper.h"

static DisplayObject* target_ = nullptr;
static float rot_ = 0.0f;

static void demo1( Demo_Base* container )
{
	container->releaseAllChildren();
	target_ = nullptr;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		SolidCircle shape( 0, 0, 50, 0xFF000000 );		
		Texture* texture = textureMgr.createPrimitiveTexture( shape );
		obj->setTexture( texture );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "primitive as display object", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

static void demo2( Demo_Base* container )
{
	container->releaseAllChildren();
	target_ = nullptr;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		// SolidCircle shape( 50, 50, 50, 0xFFFFFF00 );
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "image as display object", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

static void demo3( Demo_Base* container )
{
	container->releaseAllChildren();
	target_ = nullptr;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		target_ = new DisplayObject();
		DisplayObject* obj = target_;
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->transform().setPos( ( container->getFrameWidth() - obj->getWidth() ) / 2, ( container->getFrameHeight() - obj->getHeight() ) / 2 );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "rotate a display object without setting center", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

static void demo4( Demo_Base* container )
{
	container->releaseAllChildren();
	target_ = nullptr;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );

		
	{
		// draw shape to display object
		target_ = new DisplayObject();
		DisplayObject* obj = target_;
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->transform().setPos( ( container->getFrameWidth() - obj->getWidth() ) / 2, ( container->getFrameHeight() - obj->getHeight() ) / 2 );
		obj->setCenter( 0, 0 );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "rotate a display object with center ( 0, 0 )", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

Demo_DisplayObject::Demo_DisplayObject()
{
}

Demo_DisplayObject::~Demo_DisplayObject()
{
}

void Demo_DisplayObject::update(const double dt)
{
	Demo_Base::update( dt );
	if ( target_ != nullptr ) {
 		// std::cout << "dt: " << dt << std::endl;
		rot_ += dt * 100;
		// std::cout << "rot: " << rot_ << std::endl;

		target_->transform().setRot( rot_ );
	}
}

bool Demo_DisplayObject::resolved()
{
	addDemo( demo1 );
	addDemo( demo2 );
	addDemo( demo3 );
	addDemo( demo4 );			
	
	return Demo_Base::resolved();
}
