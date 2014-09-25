#ifndef __TRANSFORM_EVENT_H__
#define __TRANSFORM_EVENT_H__

#include "Event.h"
#include "Transform.h"

class TransformEvent : public Event
{
public:
	static const std::string TRANSFORM_POSITION_CHANGED;
	static const std::string TRANSFORM_ROTATION_CHANGED;
	static const std::string TRANSFORM_SCALE_CHANGED;

public:
	TransformEvent( const std::string& type, const Transform& transform );

	const Transform& getTarget() { return transform_; }

private:
	const Transform& transform_;
};
	
#endif
