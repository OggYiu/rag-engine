#include "Demo_DisplayContainer.h"

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

static void sharedemo( DisplayObjectContainer* container )
{
	{
		// add a background to container
		SolidRect rect( 0, 0, 200, 200, 0xFFFF9999 );
		Texture* texture = textureMgr.createPrimitiveTexture( rect );
		DisplayObject* bg = new DisplayObject();
		bg->setTexture( texture );
		container->addChild( bg );
	}

	{		
		// add more shape to the container
		FrameRect rect( 30, 50, 50, 100, 0xFF009999 );
		Texture* texture = textureMgr.createPrimitiveTexture( rect );
		DisplayObject* bg = new DisplayObject();
		bg->setTexture( texture );
		container->addChild( bg );
	}

	{		
		// add more shape to the container
		FrameCircle shape( 50, 50, 50, 0xFFFF0000 );
		Texture* texture = textureMgr.createPrimitiveTexture( shape );
		DisplayObject* obj = new DisplayObject();
		obj->setTexture( texture );
		container->addChild( obj );
	}

	{		
		// add more shape to the container
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		DisplayObject* obj = new DisplayObject();
		obj->setTexture( texture );
		obj->transform().setPos( -50, -50 );
		container->addChild( obj );
	}

}

static void demo1( Demo_Base* container )
{
	container->releaseAllChildren();

	// simple display container
	DisplayObjectContainer* c = new DisplayObjectContainer();
	container->addChild( c );
	c->transform().setPos( 200, 200 );
	
	sharedemo( c );

	// add text field
	GUI_Label* label = new GUI_Label( 0, 0, "simple container", 8 );
	label->transform().setPos( 30, 30 );
	container->addChild( label );	
}

static void demo2( Demo_Base* container )
{
	container->releaseAllChildren();

	DisplayObjectContainer* c = new DisplayObjectContainer();
	container->addChild( c );
	c->transform().setPos( 200, 200 );
	
	sharedemo( c );

	GUI_Label* label = new GUI_Label( 0, 0, "display container with clip rect", 8 );
	label->transform().setPos( 30, 30 );
	container->addChild( label );
	
	// container->resetAllClipRect();
}

Demo_DisplayContainer::Demo_DisplayContainer()
{
}

Demo_DisplayContainer::~Demo_DisplayContainer()
{
}

bool Demo_DisplayContainer::resolved()
{
	addDemo( demo1 );
	addDemo( demo2 );
	
	return Demo_Base::resolved();
}
