#ifndef __TWEENER_H__
#define __TWEENER_H__

#include "claw/tween/single_tweener.hpp"
#include "claw/tween/tweener_group.hpp"
#include "claw/tween/tweener_sequence.hpp"
#include "claw/tween/easing/easing_linear.hpp"
#include "boost/bind.hpp"

class DisplayObjectBase;
class Tweener
{
	typedef claw::tween::single_tweener::finish_callback finish_callback;
	typedef claw::tween::single_tweener::update_function update_function;	

//		typedef single_tweener::update_function update_functionboost::function<void (double)> update_function;

public:
	Tweener( DisplayObjectBase* owner );
	~Tweener();

public:
	void clear();
	void moveTo(const float duration, const float x, const float y, finish_callback finishCallback = nullptr);
	void scaleTo(const float duration, const float x, const float y, finish_callback finishCallback = nullptr);	
	//	void moveTo(const float duration, const float x, const float y, void* func);
	void update(const float dt);

protected:
	DisplayObjectBase
* owner_;
	claw::tween::tweener_sequence* tweenSeq_;
	claw::tween::tweener_group* tweenGroup_;
	claw::tween::single_tweener* tweenSingle_;	
};
#endif
