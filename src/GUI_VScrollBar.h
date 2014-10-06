#ifndef __GUI_VSCROLL_BAR_H__
#define __GUI_VSCROLL_BAR_H__

#include "GUI_BaseContainer.h"

class DisplayObject;
class Event;

class GUI_VScrollBar : public GUI_BaseContainer
{
public:
	// GUI_VScrollBar();
	GUI_VScrollBar( const int x, const int y, const int width, const int height, const float curValue = 0.0f, const float maxValue = 100.0f );
	virtual ~GUI_VScrollBar();

public:
	float getPercentage();

protected:
	bool dragEventHandler( const Event& event );

protected:
	float curValue_;
	float maxValue_;
	int margin_;
	DisplayObject* bg_;
	DisplayObject* btn_;
	float rangeInPixel_;
};
#endif
