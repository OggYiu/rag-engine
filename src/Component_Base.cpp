#include "Component_Base.h"
#include "DisplayObjectBase.h"

const std::string Component_Base::NAME = "Base";

Component_Base::Component_Base( const std::string& componentName, DisplayObjectBase* owner )
	: componentName_( componentName )
	, owner_( owner )
{
}

Component_Base::~Component_Base()
{
}
