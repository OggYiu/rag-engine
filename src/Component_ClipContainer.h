#ifndef __COMPONENT_CLIP_CONTAINER_H__
#define __COMPONENT_CLIP_CONTAINER_H__

#include "Component_Base.h"

class DisplayObjectContainer;

class Component_ClipContainer : public Component_Base
{
public:
	static const std::string NAME;
	
public:
	Component_ClipContainer( DisplayObjectContainer* owner );
	virtual ~Component_ClipContainer();
};

#endif
