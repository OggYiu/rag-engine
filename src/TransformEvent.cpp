#include "TransformEvent.h"

const std::string TransformEvent::TRANSFORM_POSITION_CHANGED = "TRANSFORM_POSITION_CHANGED";
const std::string TransformEvent::TRANSFORM_ROTATION_CHANGED = "TRANSFORM_ROTATION_CHANGED";
const std::string TransformEvent::TRANSFORM_SCALE_CHANGED = "TRANSFORM_SCALE_CHANGED";

TransformEvent::TransformEvent( const std::string& type, const Transform& transform )
	: Event( type )
	, transform_( transform )
{
}
