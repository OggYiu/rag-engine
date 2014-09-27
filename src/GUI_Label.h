#ifndef __GUI_LABEL_H__
#define __GUI_LABEL_H__

#include <string>
#include "SDL.h"
#include "GUI_Base.h"
#include "FontMgr.h"

class GUI_Label : public GUI_Base
{	
public:
	GUI_Label();
	GUI_Label( const float x, const float y, const std::string& text, const std::string& fontName = FontMgr::DEFAULT_FONT_NAME, const int fontSize = FontMgr::DEFAULT_FONT_SIZE, const Uint32 color = 0xFF000000 );
	virtual ~GUI_Label();

public:	
	virtual void update(const double dt);
	virtual void render();

	void setText(const std::string& text);
	void setFont(const std::string& font);
	void setFontSize(const int fontSize);
	
	//, const std::string& fontName, const int fontSize);
	
protected:
	void recreateTexture();
	virtual bool resolved();

protected:
	std::string text_;
	std::string fontName_;
	int fontSize_;	
	bool isDirty_;
	Uint32 color_;
};
	
#endif
