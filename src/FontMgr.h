#ifndef __FONTMGR_H__
#define __FONTMGR_H__

#include <string>
#include <map>
#include "SDL_ttf.h"

class FontMgr
{
public:
	static const int DEFAULT_FONT_SIZE = 20;
	static const char* DEFAULT_FONT_NAME;

public:
	static FontMgr& getInstance();

public:
	FontMgr();
	~FontMgr();

public:
	void releaseAllFonts();
	TTF_Font* createFont( const std::string& fontName, const int size );

private:
	TTF_Font* createFont_( const std::string& fontName, const int size );

	
//private:
//	TTF_Font* loadFont(const std::string& name, const int size);
private:
	std::map<std::string, TTF_Font*> fonts_;
};

#define fontMgr FontMgr::getInstance()
#endif
