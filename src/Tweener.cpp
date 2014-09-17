#include "Tweener.h"

#include <functional>
#include <memory>
#include "DisplayObject.h"
#include "Helper.h"

Tweener::Tweener( DisplayObject* owner )
	: owner_( owner )
	, tweenSeq_( nullptr )
	, tweenGroup_( nullptr )
	, tweenSingle_( nullptr )
{
}

Tweener::~Tweener()
{
	clear();
}

void Tweener::clear()
{
	SAFE_RELEASE(tweenSeq_);
	SAFE_RELEASE(tweenGroup_);
	SAFE_RELEASE(tweenSingle_);	
}

void Tweener::moveTo(const float duration, const float x, const float y, finish_callback finishCallback)
{
	clear();

	claw::tween::single_tweener t1 = claw::tween::single_tweener(owner_->getX(), x, duration, boost::bind(&DisplayObject::setX, owner_, _1), claw::tween::easing_linear::ease_in );
	claw::tween::single_tweener t2 = claw::tween::single_tweener(owner_->getY(), y, duration, boost::bind(&DisplayObject::setY, owner_, _1), claw::tween::easing_linear::ease_in );
	tweenGroup_ = new claw::tween::tweener_group();
	tweenGroup_->insert(t1);
	tweenGroup_->insert(t2);	

	if ( finishCallback != nullptr )
	{
		tweenGroup_->on_finished(finishCallback);
	}
}

void Tweener::scaleTo(const float duration, const float x, const float y, finish_callback finishCallback)
{
	clear();

	claw::tween::single_tweener t1 = claw::tween::single_tweener(owner_->getScaleX(), x, duration, boost::bind(&DisplayObject::setScaleX, owner_, _1), claw::tween::easing_linear::ease_in );
	claw::tween::single_tweener t2 = claw::tween::single_tweener(owner_->getScaleY(), y, duration, boost::bind(&DisplayObject::setScaleY, owner_, _1), claw::tween::easing_linear::ease_in );	

	tweenGroup_ = new claw::tween::tweener_group();
	tweenGroup_->insert(t1);
	tweenGroup_->insert(t2);	

	if ( finishCallback != nullptr )
	{
		tweenGroup_->on_finished(finishCallback);
	}
}

// void forwarder(void* context, int i0, int i1) {

//     static_cast<foo*>(context)->member(i0, i1);
// }
// // the function using the function pointers:
// void somefunction(void (*fptr)(void*, int, int), void* context) {
//     fptr(context, 17, 42);
// }

void Tweener::update(const float dt)
{
	if ( tweenSingle_ != nullptr )
	{
		if ( !tweenSingle_->is_finished() )
		{
			tweenSingle_->update(dt);
		}
	}
	else if ( tweenGroup_ != nullptr )
	{
		if ( !tweenGroup_->is_finished() )
		{
			tweenGroup_->update(dt);
		}
	}
	else if ( tweenSeq_ != nullptr )
	{
		if ( !tweenSeq_->is_finished() )
		{
			tweenSeq_->update(dt);
		}
	}

}
