#ifndef __COMPONENT_DRAGGING_H__
#define __COMPONENT_DRAGGING_H__

#include "Eigen/Dense"
#include "Component_Base.h"

class Event;
class DisplayObjectBase;

class Component_Dragging : public Component_Base
{
public:
	static const std::string NAME;
	
public:
	Component_Dragging( DisplayObjectBase* owner );
	virtual ~Component_Dragging();

protected:
	bool mouseEventHandler( const Event& event );

protected:
	bool isDragging_;
	Eigen::Vector2i mouseOffsetPos_;
};

#endif
