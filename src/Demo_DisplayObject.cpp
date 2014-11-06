#include "Demo_DisplayObject.h"

#include "DisplayObject.h"
#include "Primitive.h"
#include "TextureMgr.h"
#include "GUI_Label.h"
#include "Helper.h"

#define DEBUG_DISPLAYOBJECT

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
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		SolidRect shape( 0, 0, 80, 30, 0xFFFF0000 );		
		Texture* texture = textureMgr.createPrimitiveTexture( shape );
		obj->setTexture( texture );
		obj->transform().setPos( 100, 200 );
		parent->addChild( obj );
	}
	
	{
		// draw shape to display object
		target_ = new DisplayObject();
		DisplayObject* obj = target_;
		// DisplayObject* obj = new DisplayObject();
		FrameRect shape( 0, 0, 250, 300, 0xFFFFFF00 );		
		Texture* texture = textureMgr.createPrimitiveTexture( shape );
		obj->setTexture( texture );
		obj->transform().setPos( 300, 50 );
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
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->transform().setPos( ( container->getFrameWidth() - obj->getWidth() ) / 2, ( container->getFrameHeight() - obj->getHeight() ) / 2 );
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

static void demo5( Demo_Base* container )
{
	container->releaseAllChildren();
	target_ = nullptr;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->setClipRect( 6, 1, 116, 94 );
		obj->transform().setPos( 50, 50 );
		parent->addChild( obj );
	}
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->setClipRect( 6, 1, 116, 94 );
		obj->transform().setPos( 450, 50 );
		obj->transform().setScale( 0.3f, 0.6f );
		parent->addChild( obj );
	}

	{
		// draw shape to display object
		target_ = new DisplayObject();
		DisplayObject* obj = target_;
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->setClipRect( 6, 1, 116, 94 );
		obj->transform().setScale( 1.3f, 2.6f );
		obj->transform().setPos( ( container->getFrameWidth() - obj->getWidth() ) / 2, ( container->getFrameHeight() - obj->getHeight() ) / 2 );		
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "display object with clip rect", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

static void demo6( Demo_Base* container )
{
	container->releaseAllChildren();
	target_ = nullptr;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->transform().setScale( 0.5f, 0.5f );
		obj->transform().setPos( 50, 50 );
		parent->addChild( obj );
	}
	
	{
		target_ = new DisplayObject();
		DisplayObject* obj = target_;
		// DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->transform().setScale( 0.5f, 0.5f );
		obj->transform().setPos( ( container->getFrameWidth() - obj->getWidth() ) / 2, ( container->getFrameHeight() - obj->getHeight() ) / 2 );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "display object scaling", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

static void demo7( Demo_Base* container )
{
	container->releaseAllChildren();
	target_ = nullptr;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/wonderboy.png" );
		obj->setTexture( texture );
		obj->transform().setPos( 30, 30 );
		parent->addChild( obj );
	}

	int nextX = 30;
	int nextY = 250;
	int offsetX = 20;
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/wonderboy.png" );
		obj->setTexture( texture );
		obj->setClipRect( 114, 115, 20, 24 );
		obj->transform().setScale( 4.0f, 4.0f );
		obj->transform().setPos( nextX, nextY );
		parent->addChild( obj );

		nextX += obj->getWidth() + offsetX;
	}
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/wonderboy.png" );
		obj->setTexture( texture );
		obj->setClipRect( 136, 115, 20, 24 );
		obj->transform().setScale( 4.0f, 4.0f );
		obj->transform().setPos( nextX, nextY );
		parent->addChild( obj );
		
		nextX += obj->getWidth() + offsetX;
	}
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/wonderboy.png" );
		obj->setTexture( texture );
		obj->setClipRect( 158, 115, 20, 24 );
		obj->transform().setScale( 4.0f, 4.0f );
		obj->transform().setPos( nextX, nextY );
		parent->addChild( obj );
		
		nextX += obj->getWidth() + offsetX;
	}
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/wonderboy.png" );
		obj->setTexture( texture );
		obj->setClipRect( 180, 115, 20, 24 );
		obj->transform().setScale( 4.0f, 4.0f );
		obj->transform().setPos( nextX, nextY );
		parent->addChild( obj );
		
		nextX += obj->getWidth() + offsetX;
	}
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/wonderboy.png" );
		obj->setTexture( texture );
		obj->setClipRect( 202, 115, 20, 24 );
		obj->transform().setScale( 4.0f, 4.0f );
		obj->transform().setPos( nextX, nextY );
		parent->addChild( obj );
		
		nextX += obj->getWidth() + offsetX;
	}
	
	{
		GUI_Label* label = new GUI_Label( 0, 0, "another clip rect demo", 8 );
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

void Demo_DisplayObject::resolved()
{
	addDemo( demo1 );
	addDemo( demo2 );
	addDemo( demo3 );
	addDemo( demo4 );
	addDemo( demo5 );
	addDemo( demo6 );
	addDemo( demo7 );	
	
	Demo_Base::resolved();
}
