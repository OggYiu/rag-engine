#include "Page_TestUI.h"

#include "GUI_Label.h"
#include "GUI_Image.h"
#include "GUI_Window.h"
#include "GUI_Button.h"
#include "Kernel.h"
#include "Graphics.h"
#include "Primitive.h"
#include "Helper.h"
#include "Texture.h"

static inline SDL_Texture* gg( const std::vector<Primitive*>& primitives )
{
	SDL_Texture* sdlTexture = nullptr;
	SDL_Renderer* renderer = kernel.getRenderer();
	int maxX = std::numeric_limits<int>::min();
	int minX = std::numeric_limits<int>::max();
	int maxY = std::numeric_limits<int>::min();
	int minY = std::numeric_limits<int>::max();

	std::vector<Primitive*>::const_iterator iter = primitives.begin();
	std::vector<Primitive*>::const_iterator endIter = primitives.end();

	BBox box;
	while ( iter != endIter ) {
		(*iter)->getBoundingBox( box );
		minX = std::min( minX, box.x1() );
		maxX = std::max( maxX, box.x2() );
		minY = std::min( minY, box.y1() );
		maxY = std::max( maxY, box.y2() );
		++iter;
	}

	// std::cout << "result: " << minX << ", " << minY << ", " << maxX << ", " << maxY << std::endl;

	if ( maxX <= minX || maxY <= minY ) {
		return nullptr;
	}

	// int width = maxX - minX;
	// int height = maxY - minY;
	// sdlTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height );
	sdlTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, maxX, maxY );
	
	// std::cout << "size: " << width << ", " << height << std::endl;
	if ( sdlTexture == nullptr ) {
		assert( false && "failed to create sdl texture" );
		return nullptr;
	}
	SDL_SetTextureBlendMode( sdlTexture, SDL_BLENDMODE_BLEND );
	
	SDL_SetRenderTarget( renderer, sdlTexture );
	// SDL_RenderClear( renderer );
	
	iter = primitives.begin();
	endIter = primitives.end();
	while ( iter != endIter ) {
		(*iter)->render();
		++iter;
	}

	SDL_SetRenderTarget( renderer, nullptr );
	// std::cout << "end createTextureFromPrimitives" << std::endl;
	return sdlTexture;
}

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

	{
		DisplayObjectContainer* container = new DisplayObjectContainer();
		container->setPos( kernel.getScreenWidth() / 2, kernel.getScreenHeight() / 2 );
		this->addChild( container );

		{
			GUI_Image* image = new GUI_Image( 0, 0, "assets/alex.png" );
			container->addChild( image );
			image->setPos( -image->getWidth() / 2.0f, -image->getHeight() / 2.0f );
		}

		{
			GUI_Image* image = new GUI_Image( 0, 0, "assets/girl.png" );
			container->addChild( image );
			image->setPos( 0.0f, 0.0f );
		}

		Graphics* graphics = new Graphics();
		graphics->setDrawColor( 255, 0, 0, 255 );
		container->updateAllBoundingBox();
		SDL_Rect* bbox = &container->getBBox();		
		std::cout << "container bounding: " << bbox->x << ", " << bbox->y << ", " << bbox->w << ", " << bbox->h << std::endl;
		// graphics->drawFrameRect( bbox->x, bbox->y, bbox->w, bbox->h );
		graphics->drawFrameRect( 0, 0, bbox->w, bbox->h );
		this->addChild( graphics );
		graphics->setPos( bbox->x, bbox->y );


		// {
		// 	GUI_Image* image = new GUI_Image( 0, 0, "assets/girl.png" );
		// 	this->addChild( image );
		// 	image->setPos( 0.0f, 0.0f );
		// }
		
		// GUI_Window* window = new GUI_Window( 0.0f, 0.0f, 300.0f, 300.0f );
		// this->addChild( window );
		
		// label without text
		// GUI_Label* label = new GUI_Label( 100.0f, 100.0f, "" );
		// this->addChild( label );

		// {
		// 	std::vector<Primitive*> primitives;
		// 	primitives.push_back( new FrameRect( bbox->x, bbox->y, bbox->w, bbox->h, RGBA2Int( 255, 0, 0, 255 ) ) );
		// 	SDL_Texture* texture = gg( primitives );
		// 	GUI_Image* image1 = new GUI_Image( 0, 0, new Texture( texture ) );
		// 	this->addChild( image1 );
		// }
	}
	
	return true;
}










