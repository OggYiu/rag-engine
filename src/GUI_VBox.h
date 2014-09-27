#ifndef __GUI_VBOX_H__
#define __GUI_VBOX_H__

#include "GUI_BaseContainer.h"

class DisplayObjectBase;
class GUI_VBox : public GUI_BaseContainer
{
public:
	static const int MARGIN_Y = 0;
	
public:
	GUI_VBox();
	~GUI_VBox();

public:
	void setMarginY();
	void rearrangeChildren();
	virtual void addChild( DisplayObjectBase* const entity );

protected:
	float nextPosY_;
	float marginY_;
};

#endif
