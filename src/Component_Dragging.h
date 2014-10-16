#ifndef __COMPONENT_DRAGGING_H__
#define __COMPONENT_DRAGGING_H__

#include "Eigen/Dense"
#include "Component_Base.h"
#include "Types.h"

class Event;
class DisplayObjectBase;

class Component_Dragging : public Component_Base
{
public:
	static const std::string NAME;
	
public:
	Component_Dragging( DisplayObjectBase* owner, const int boundX, const int boundY, const int boundWidth, const int boundHeight );
	virtual ~Component_Dragging();

protected:
	bool mouseEventHandler( const Event& event );

protected:
	Eigen::Vector2f mouseOffsetPos_;
	Eigen::Vector2f lastMousePos_;	
	bool isDragging_;
	BBox bound_;
};

#endif
