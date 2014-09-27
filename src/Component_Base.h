#ifndef __COMPONENT_BASE_H__
#define __COMPONENT_BASE_H__

#include <string>
#include "Object.h"

class DisplayObjectBase;

class Component_Base : public Object
{
public:
	static const std::string NAME;
	
public:
	Component_Base( const std::string& componentName, DisplayObjectBase* owner );
	virtual ~Component_Base();

public:
	const std::string getComponentName() { return componentName_; }
	
protected:
	const std::string componentName_;
	DisplayObjectBase* owner_;
};

#endif
