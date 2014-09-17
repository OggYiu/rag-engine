#ifndef __TEXTURE_MGR_H__
#define __TEXTURE_MGR_H__

#include "SDL.h"
#include <string>
#include <vector>
#include <map>
#include "FontMgr.h"

class TextureRef;
class Primitive;

class TextureMgr
{
public:
	TextureMgr();
	~TextureMgr();

public:
	static TextureMgr& getInstance();

public:
	SDL_Texture* createImageSDLTexture( const std::string& path, int* width = nullptr, int* height = nullptr );
	SDL_Texture* createEmptySDLTexture( const int width, const int height, const Uint8 red = 255, const Uint8 green = 255, const Uint8 blue = 255, const Uint8 alpha = 255 );
	SDL_Texture* createTTFTexture( const std::string& text, const std::string& fontName = FontMgr::DEFAULT_FONT_NAME, const int fontSize = FontMgr::DEFAULT_FONT_SIZE, const Uint8 red = 255, const Uint8 green = 255, const Uint8 blue = 255, const Uint8 alpha = 255, int* width = nullptr, int* height = nullptr );
	SDL_Texture* createPrimitiveTexture( const std::vector<Primitive*>& primitives );
	void releaseSDLTexture( SDL_Texture* sdlTexture );
	
//	Texture* createFromSDLTexture( const STexture* texture );

private:
	SDL_Texture* createSDLTextureFromImage( const std::string& path, int* width, int* height );
};

#define textureMgr TextureMgr::getInstance()

#endif


