#ifndef __DEMO_BASE_H__
#define __DEMO_BASE_H__

#include "Page.h"

class DisplayObjectContainer;

class Demo_Base : public Page
{
private:
	typedef void(*DemoFunc)(Demo_Base*);

public:
	Demo_Base();
	virtual ~Demo_Base();

public:	
	virtual void update(const double dt);
	virtual void render();
	void addDemo( DemoFunc func );
	void drawFrame( DisplayObjectContainer* container );

protected:
	virtual bool resolved();
	void nextDemo();
	bool onKeyboardEvent( const Event& event );

protected:
	std::vector<DemoFunc> demoFuncs_;
	int demoIndex_;
	int startIndex_;
	bool isFirstRun_;
	int frameMarginX_;
	int frameMarginY_;
	int frameW_;
	int frameH_;
};
#endif
