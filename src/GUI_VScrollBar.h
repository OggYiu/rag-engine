#ifndef __GUI_VSCROLL_BAR_H__
#define __GUI_VSCROLL_BAR_H__

#include "GUI_BaseContainer.h"

class DisplayObject;

class GUI_VScrollBar : public GUI_BaseContainer
{
public:
	// GUI_VScrollBar();
	GUI_VScrollBar( const int width, const int height, const float curValue = 0.0f, const float maxValue = 100.0f );
	virtual ~GUI_VScrollBar();

protected:
	float curValue_;
	float maxValue_;
	DisplayObject* bg_;
	DisplayObject* btn_;	
};
#endif
