#ifndef __TEXTURE_MGR_H__
#define __TEXTURE_MGR_H__

#include "SDL.h"
#include <string>
#include <vector>
#include <map>
#include "FontMgr.h"

class TextureRef;
class Primitive;
class Texture;

class TextureMgr
{
public:
	TextureMgr();
	~TextureMgr();

public:
	static TextureMgr& getInstance();

public:
	void releaseSDLTexture( SDL_Texture* sdlTexture );
	Texture* createImageTexture( const std::string& path, int* width = nullptr, int* height = nullptr );
	Texture* createEmptyTexture( const int width, const int height, const Uint8 red = 255, const Uint8 green = 255, const Uint8 blue = 255, const Uint8 alpha = 255 );
	Texture* createTTFTexture( const std::string& text, const std::string& fontName = FontMgr::DEFAULT_FONT_NAME, const int fontSize = FontMgr::DEFAULT_FONT_SIZE, const Uint32 color = 0xFFFFFFFF, int* width = nullptr, int* height = nullptr );
	Texture* createPrimitivesTexture( const std::vector<Primitive*>& primitives );
	
private:
	SDL_Texture* createImageSDLTexture( const std::string& path, int* width = nullptr, int* height = nullptr );
	SDL_Texture* createEmptySDLTexture( const int width, const int height, const Uint8 red = 255, const Uint8 green = 255, const Uint8 blue = 255, const Uint8 alpha = 255 );
	SDL_Texture* createTTFSDLTexture( const std::string& text, const std::string& fontName = FontMgr::DEFAULT_FONT_NAME, const int fontSize = FontMgr::DEFAULT_FONT_SIZE, const Uint32 color = 0xFFFFFFFF, int* width = nullptr, int* height = nullptr );
	SDL_Texture* createPrimitivesSDLTexture( const std::vector<Primitive*>& primitives );
};

#define textureMgr TextureMgr::getInstance()

#endif


