#include "Component_ClipContainer.h"

#include "DisplayObjectContainer.h"

const std::string Component_ClipContainer::NAME = "ClipContainer";

Component_ClipContainer::Component_ClipContainer( DisplayObjectContainer* owner )
	: Component_Base( Component_ClipContainer::NAME, owner )
{
}

Component_ClipContainer::~Component_ClipContainer()
{
}
