#include "Entity_Emitter.h"

Entity_Emitter::Entity_Emitter()
	: radius_(1.0f)
	, renderRadius_(0)
	, animDir_(true)
{
}

Entity_Emitter::Entity_Emitter(const float x, const float y, const float radius)
	: radius_(radius)
	, renderRadius_(0)
	, animDir_(true)	  
{
	this->transform().setPos( x, y );
//	std::cout << "i am emitter and my id is " << this->getId() << std::endl;
}

Entity_Emitter::~Entity_Emitter()
{
//	std::cout << "emitter decon" << std::endl;
}

void Entity_Emitter::setRadius(const float radius)
{
	radius_ = radius;
}

float Entity_Emitter::getRadius() const
{
	return radius_;
}

float Entity_Emitter::calculate(const float x, const float y)
{
	return (renderRadius_ / sqrt( (x-this->transform().getX())*(x-this->transform().getX()) + (y-this->transform().getY())*(y-this->transform().getY()) ) );
}

void Entity_Emitter::update(const double dt)
{
	Parent::update(dt);

	renderRadius_ += dt * ANIM_SPEED * animDir_? 1 : -1;
//	std::cout << "renderRadius: " << renderRadius_ << std::endl;
//	std::cout << "radius: " << radius_ << std::endl;	
	if ( renderRadius_ >= radius_ || renderRadius_ <= 0 )
	{
		animDir_ = !animDir_;
//		renderRadius_ = 0;
	}
}
