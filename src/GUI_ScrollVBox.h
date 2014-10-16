#ifndef __GUI_SCROLL_VBOX_H__
#define __GUI_SCROLL_VBOX_H__

#include "GUI_BaseContainer.h"

class GUI_VBox;
class GUI_VScrollBar;
class DisplayObjectBase;
class Event;

class GUI_ScrollVBox : public GUI_BaseContainer
{
public:
	GUI_ScrollVBox( const int x, const int y, const int width, const int height );
	virtual ~GUI_ScrollVBox();

public:
	virtual void update( const double dt );
	virtual void addChild( DisplayObjectBase* const entity );
	void addItem( DisplayObjectBase* obj );
		
protected:
	virtual bool resolved();
	void addChild_( DisplayObjectBase* const entity );
	bool eventHandler( const Event& event );

private:
	GUI_VBox* box_;
	GUI_VScrollBar* scrollBar_;
	float bound_;
};

#endif
