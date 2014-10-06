#ifndef __HELPER_H__
#define __HELPER_H__

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <functional>
#include <vector>
#include <limits>
#include <assert.h>
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "Eigen/Dense"
#include "Event.h"
#include "Kernel.h"
#include "Primitive.h"
#include "DisplayObjectBase.h"

#define PI 3.14285714286
#define RAD2DEG_ 57.2727272727
#define DEG2RAD_ 0.01746031746

#define RAD2DEG( a ) ( a * RAD2DEG_ )
#define DEG2RAD( a ) ( a * DEG2RAD_ )

#define SAFE_RELEASE(ptr)						\
	{											\
	 if ( ptr != nullptr )						\
	 {											\
	  delete ptr;								\
	  ptr = nullptr;							\
	  }											\
	 }

static inline bool isEqual( const float v1, const float v2 )
{
    return fabs( v1 - v2 ) < std::numeric_limits<float>::epsilon();
}

static inline void insertBaseDir(std::string& str)
{
	std::stringstream path;
	// std::cout << kernel.getBaseDir() << std::endl;
	path << kernel.getBaseDir() << "/" << str.c_str();
	str = path.str();
}

// t: current time, b: start value, c: change in value, d: duration
// if duration = 1 curent time = 1 is max
// chnage in value is the currnet value - start value

static inline float linearTween(float t, float b, float c, float d)
{
	return c*(t/d) + b;
}

static inline float easeOutQuart(float t, float b, float c, float d)
{
	t /= d;
	t--;
	return -c * (t*t*t*t - 1) + b;
}

static inline Uint32 RGBA2Int(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{        
	return (((((a << 8) + r) << 8) + g) << 8) + b;
}

static inline void int2RGBA( Uint32 color, Uint8& r, Uint8& g, Uint8& b, Uint8& a)
{
	r = color & 0xFF; color = color >> 8;
	g = color & 0xFF; color = color >> 8;
	b = color & 0xFF; color = color >> 8;
	a = color & 0xFF;
}

static inline int randInRange(int min, int max)
{
	return rand() % max + min;
}

static inline void showSDLError()
{
	std::cout << SDL_GetError() << std::endl;
}

template <class T>
std::function<bool(const Event&)> bindEventHandler(bool (T::*handler)(const Event&), T* invoker)
{
	return std::bind(handler, invoker, std::placeholders::_1);
}

static inline bool hitTestPointVSRect(const int x1, const int y1, const int x2, const int y2, const int width, const int height)
{
	if (x1 < x2)
	{
		return false;
	}

	if (y1 < y2)
	{
		return false;
	}

	if (x1 > (x2 + width))
	{
		return false;
	}

	if (y1 > (y2 + height))
	{
		return false;
	}
	
	return true;
}

static inline Eigen::Vector2f worldToLocalPos( const float x, const float y, DisplayObjectBase* displayObj )
{
	Eigen::Vector2f pos;
	float t_x = x - displayObj->transform().getStageX();
	float t_y = y - displayObj->transform().getStageY();
	pos[0] = t_x;
	pos[1] = t_y;	
	return pos;
}

#endif
