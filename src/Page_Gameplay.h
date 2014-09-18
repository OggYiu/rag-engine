#ifndef __PAGE_GAMEPLAY_H__
#define __PAGE_GAMEPLAY_H__

#include "Page.h"

class Graphics;
class Entity_Emitter;

class Page_Gameplay : public Page
{
private:
	typedef Page Parent;
	
public:
	Page_Gameplay();
	virtual ~Page_Gameplay();
	
public:
   	virtual void enter();
	virtual void update(const double dt);

protected:
	virtual bool resolved();

protected:
	Graphics* mapCanvas_;
	std::vector<Entity_Emitter*> emitters_;
	std::vector<std::vector<float>> values_;
	// Entity_Emitter* emitter_;
};

#endif
