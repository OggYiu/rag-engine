#include "FontMgr.h"

#include <iostream>
#include <sstream>
#include "Helper.h"

const char* FontMgr::DEFAULT_FONT_NAME = "prstartk";

FontMgr::FontMgr()
{
}

FontMgr::~FontMgr()
{
	releaseAllFonts();
}

void FontMgr::releaseAllFonts()
{
	std::map<std::string, TTF_Font*>::iterator iter =  fonts_.begin();
	std::map<std::string, TTF_Font*>::iterator endIter = fonts_.end();
	while ( iter != endIter ) {
		TTF_CloseFont(iter->second);
		++iter;
	}

	fonts_.clear();
}

TTF_Font* FontMgr::createFont( const std::string& fontName, const int fontSize )
{
	std::stringstream fID;
	fID << fontName.c_str() << fontSize;
	std::string fontID = fID.str();
	TTF_Font* font = fonts_[fontID.c_str()];
	if ( font == nullptr ) {
		font = createFont_( fontName, fontSize );
		fonts_[fontID.c_str()] = font;
	}
	
	return font;
}

TTF_Font* FontMgr::createFont_( const std::string& fontName, const int fontSize )
{
	static std::string fontBasePath = "assets/font/";
	std::string fontPath = fontBasePath + fontName + ".ttf";
	insertBaseDir(fontPath);
	TTF_Font* font = TTF_OpenFont( fontPath.c_str(), fontSize );
	if ( font == nullptr ) {
		std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}

	return font;
}

FontMgr& FontMgr::getInstance()
{
	static FontMgr s_instance;
	return s_instance;
}
