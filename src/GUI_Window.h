#ifndef __GUI_WINDOW_H__
#define __GUI_WINDOW_H__

#include "GUI_BaseContainer.h"
#include "Event.h"
#include "Eigen/Dense"

class Graphics;
class GUI_Window : public GUI_BaseContainer
{
public:
	GUI_Window();
	GUI_Window( const float x, const float y, const float width, const float height );
	virtual ~GUI_Window();

public:
	virtual void update(const double dt);
	virtual void render();
	
protected:
	virtual void resolved();
	bool eventHandler(const Event& event);

private:
	DisplayObjectContainer* bgContainer_;
	DisplayObjectContainer* itemsContainer_;
	DisplayObjectContainer* overlayContainer_;	

	Graphics* frame_;
	Eigen::Vector2i lastMousePos_;
	bool isDragging_;
};

#endif
