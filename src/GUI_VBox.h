#ifndef __GUI_VBOX_H__
#define __GUI_VBOX_H__

#include "GUI_BaseContainer.h"

class DisplayObjectBase;
class GUI_Image;

class GUI_VBox : public GUI_BaseContainer
{
public:
	static const int MARGIN_Y = 0;
	
public:
	GUI_VBox( const int x, const int y, const int width, const int height );
	~GUI_VBox();

public:
	void setMarginY();
	void rearrangeChildren();
	void addItem( DisplayObjectBase* const entity );
	
protected:
	virtual bool resolved();
	
protected:
	GUI_BaseContainer* itemsContainer_;
	GUI_Image* bg_;
	float nextPosY_;
	float marginY_;
};

#endif
