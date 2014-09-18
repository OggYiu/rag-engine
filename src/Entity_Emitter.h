#ifndef __ENTITY_EMITTER_H__
#define __ENTITY_EMITTER_H__

#include "Entity.h"

class Entity_Emitter : public Entity
{
private:
	static const int ANIM_SPEED = 100;
	
private:
	typedef Entity Parent;
	
public:
	Entity_Emitter();
	Entity_Emitter(const float x, const float y, const float radius);	
	virtual ~Entity_Emitter();

public:
	virtual void update(const double dt);
	void setRadius(const float radius);
	float getRadius() const;
	float calculate(const float x, const float y);
	
protected:
	float radius_;
	float renderRadius_;
	bool animDir_;
};

#endif
