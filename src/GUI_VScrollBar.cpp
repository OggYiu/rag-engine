#include "GUI_VScrollBar.h"
#include "Primitive.h"
#include "Helper.h"
#include "Texture.h"
#include "DisplayObject.h"
#include "Component_Dragging.h"

// GUI_VScrollBar::GUI_VScrollBar()
// {
// }

GUI_VScrollBar::GUI_VScrollBar( const int width, const int height, const float curValue, const float maxValue )
{
	setSize( width, height );
	curValue_ = curValue;
	maxValue_ = maxValue;

	{
		// background
		{
			std::vector<Primitive*> vec;
			SolidRect rect( 0, 0, getWidth(), getHeight(), RGBA2Int( 255, 0, 0, 100 ) );
			vec.push_back( &rect );
			SDL_Texture* sdlTexture = createTextureFromPrimitives( vec );
			Texture* texture = new Texture( sdlTexture );
			bg_ = new DisplayObject();
			bg_->setTexture( texture );
			addChild( bg_ );
		}

		// button
		{
			int margin = round( (float)getWidth() / 10.0 );
			std::vector<Primitive*> vec;
			SolidRect rect( 0, 0, getWidth() - margin * 2, 32, RGBA2Int( 0, 255, 0, 100 ) );
			vec.push_back( &rect );
			SDL_Texture* sdlTexture = createTextureFromPrimitives( vec );
			Texture* texture = new Texture( sdlTexture );
			btn_ = new DisplayObject();
			btn_->setTexture( texture );
			btn_->transform().setPos( margin, margin );
			btn_->addComponent( new Component_Dragging( btn_ ) );
			addChild( btn_ );
		}

	}
}

GUI_VScrollBar::~GUI_VScrollBar()
{
}
