#include "TextureMgr.h"

#include <sstream>
#include "SDL_image.h"
#include "Kernel.h"
#include "Texture.h"
#include "Helper.h"

static SDL_Texture* createSDLTextureFromImage( const std::string& path, int* width = nullptr, int* height = nullptr )
{
	std::string filepath = path.c_str();
	insertBaseDir(filepath);
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if ( surface == nullptr ) {
		showSDLError();
		return nullptr;
	}
		
	texture = SDL_CreateTextureFromSurface(kernel.getRenderer(), surface);
	if ( texture == nullptr ) {
		showSDLError();
		return nullptr;
	}

	if ( width != nullptr ) {
		*width = surface->w;
	}

	if ( height != nullptr ) {
		*height = surface->h;
	}
	
	SDL_FreeSurface(surface);
	
	return texture;
}

static inline SDL_Texture* createTextureFromPrimitives( const std::vector<Primitive*>& primitives )
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
		// std::cout << "primitive: " << box.x1() << ", " << box.y1() << ", " << box.x2() << ", " << box.y2() << std::endl;
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

	// std::cout << "create texture size: " << width << ", " << height << std::endl;
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

TextureMgr::TextureMgr()
{
}

TextureMgr::~TextureMgr()
{
}

TextureMgr& TextureMgr::getInstance()
{
	static TextureMgr s_instance;
	return s_instance;
}

Texture* TextureMgr::createImageTexture( const std::string& path, int* width, int* height )
{
	return new Texture( createImageSDLTexture( path, width, height ) );
}

Texture* TextureMgr::createEmptyTexture( const int width, const int height, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha )
{
	return new Texture( createEmptySDLTexture( width, height, red, green, blue, alpha ) );
}

Texture* TextureMgr::createTTFTexture( const std::string& text, const std::string& fontName, const int fontSize, const Uint32 color, int* width, int* height )
{
	return new Texture( createTTFSDLTexture( text, fontName, fontSize, color, width, height ) );
}

SDL_Texture* TextureMgr::createImageSDLTexture( const std::string& path, int* width, int* height )
{
	SDL_Texture* sdlTexture = nullptr;
	sdlTexture = createSDLTextureFromImage( path, width, height );
	return sdlTexture;
}

SDL_Texture* TextureMgr::createEmptySDLTexture( const int width, const int height, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha )
{
	SDL_Texture* sdlTexture = nullptr;
	SDL_Surface* surface = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0 );
	// SDL_Rect rect;
	int result;
	// rect = { 0, 0, width, height };
	result = SDL_FillRect( surface, nullptr, SDL_MapRGB( surface->format, red, green, blue ) );
	if (result != 0) {
		showSDLError();
		return nullptr;
	}

	sdlTexture = SDL_CreateTextureFromSurface( kernel.getRenderer(), surface );
	if ( sdlTexture == nullptr ) {
		showSDLError();
		return nullptr;
	}
	if ( alpha < 255 ) {
		SDL_SetTextureBlendMode( sdlTexture, SDL_BLENDMODE_BLEND );
		SDL_SetTextureAlphaMod( sdlTexture, alpha );
	}

	SDL_FreeSurface( surface );
	return sdlTexture;
}

SDL_Texture* TextureMgr::createTTFSDLTexture( const std::string& text, const std::string& fontName, const int fontSize, const Uint32 color, int* width, int* height )
{
	SDL_Texture* texture = nullptr;
	TTF_Font* font = fontMgr.createFont( fontName, fontSize );
	Uint8 red, green, blue, alpha;
	int2RGBA( color, red, green, blue, alpha );
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), { red, green, blue, alpha } );
	if( textSurface == nullptr )
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	} else {
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface( kernel.getRenderer(), textSurface );
		if( texture == nullptr )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		} else {
			//Get image dimensions
			if ( width != nullptr ) {
				*width = textSurface->w;
			}
			if ( height != nullptr ) {
				*height = textSurface->h;
			}
		}
		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	return texture;
}

void TextureMgr::releaseSDLTexture( SDL_Texture* sdlTexture )
{
	//Free texture if it exists
	if ( sdlTexture != nullptr )
	{
		SDL_DestroyTexture( sdlTexture );
		sdlTexture = nullptr;
	}
}

Texture* TextureMgr::createPrimitivesTexture( const std::vector<Primitive*>& primitives )
{
	return new Texture( createPrimitivesSDLTexture( primitives ) );
}

SDL_Texture* TextureMgr::createPrimitivesSDLTexture( const std::vector<Primitive*>& primitives )
	
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
		// std::cout << "primitive: " << box.x1() << ", " << box.y1() << ", " << box.x2() << ", " << box.y2() << std::endl;
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

	// std::cout << "create texture size: " << width << ", " << height << std::endl;
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
// {
// 	SDL_Texture* sdlTexture = nullptr;
// 	SDL_SetRenderTarget( kernel.getRenderer(), sdlTexture );
// 	std::vector<Primitive*>::const_iterator iter = primitives.begin();
// 	std::vector<Primitive*>::const_iterator endIter = primitives.end();
// 	while ( iter != endIter ) {
// 		(*iter)->render();
// 		++iter;
// 	}
// 	return sdlTexture;
// }
