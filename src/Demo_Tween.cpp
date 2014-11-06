#include "Demo_Tween.h"

#include "DisplayObject.h"
#include "TextureMgr.h"
#include "Texture.h"
#include "GUI_Label.h"

static void demo1( Demo_Base* container )
{
	container->releaseAllChildren();
	// target_ = nullptr;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/boy_bg.png" );
		obj->setTexture( texture );
		parent->addChild( obj );
	}

	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		Texture* texture = textureMgr.createImageTexture( "assets/boy.png" );
		obj->setTexture( texture );
		obj->transform().setPos( 0.0f, 320.0f );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "translation", 16 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

Demo_Tween::Demo_Tween()
{
}

Demo_Tween::~Demo_Tween()
{
}

void Demo_Tween::update(const double dt)
{
	Demo_Base::update( dt );
}

void Demo_Tween::resolved()
{
	addDemo( demo1 );
	
	Demo_Base::resolved();
}
