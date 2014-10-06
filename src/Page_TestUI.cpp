#include "Page_TestUI.h"

#include "GUI_Label.h"
#include "GUI_Image.h"
#include "GUI_Window.h"
#include "GUI_Button.h"
#include "GUI_VBox.h"
#include "Kernel.h"
#include "Graphics.h"
#include "Primitive.h"
#include "Helper.h"
#include "Texture.h"
#include "TextureMgr.h"
#include "GradientRect.h"
#include "GUI_VScrollBar.h"
#include "GUI_ScrollVBox.h"

Page_TestUI::Page_TestUI()
{
}

Page_TestUI::~Page_TestUI()
{
}

void Page_TestUI::update(const double dt)
{
	Page::update(dt);
}

void Page_TestUI::render()
{
	Page::render();
}

bool Page_TestUI::resolved()
{
	Page::resolved();

	// vbox example
	{
		GUI_VBox* box = new GUI_VBox( 0.0f, 0.0f, 100.0f, 200.0f );
		this->addChild( box );
		box->tweener().moveTo( 1.0f, 100.0f, 100.0f, boost::bind(&Page_TestUI::here, this));

		{
			const int count = 10;
			// const int w = 128;
			// const int h = 64;

			for ( int i = 0; i < count; ++i ) {
				DisplayObject* displayObject = new DisplayObject();
				Texture* texture = textureMgr.createImageTexture( "assets/test1.png" );
				// Texture* texture = textureMgr.createEmptyTexture( w, h, round( rand() * 255 ), round( rand() * 255 ), round( rand() * 255 ), 100 );
				displayObject->setTexture( texture );
				box->addItem( displayObject );
			}
		}
	}

	{
		std::vector<Primitive*> vec;
		GradientRect rect( 0, 0, 100, 200, RGBA2Int( 255, 0, 0, 0 ), RGBA2Int( 255, 0, 0, 255 ) );
		vec.push_back( &rect );
		Texture* texture = textureMgr.getInstance().createPrimitivesTexture( vec );
		DisplayObject* object = new DisplayObject();
		object->setTexture( texture );
		this->addChild( object );
	}

	{
		GUI_VScrollBar* bar = new GUI_VScrollBar( 150.0f, 100.0f, 16.0f, 200.0f );
		this->addChild( bar );
	}

	{
		GUI_ScrollVBox* vbox = new GUI_ScrollVBox( 300.0f, 100.0f, 300.0f, 300.0f );
		this->addChild( vbox );
	}
	return true;
}

void Page_TestUI::here()
{
}






