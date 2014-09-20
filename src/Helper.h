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
#include "Event.h"
#include "Kernel.h"
#include "Primitive.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

#define SAFE_RELEASE(ptr)						\
	{											\
	 if ( ptr != nullptr )						\
	 {											\
	  delete ptr;								\
	  ptr = nullptr;							\
	  }											\
	 }

static inline SDL_Texture* createTextureFromPrimitives( const std::vector<Primitive*>& primitives )
{
	SDL_Texture* sdlTexture = nullptr;
	SDL_Renderer* renderer = kernel.getRenderer();
	int maxX = std::numeric_limits<int>::min();
	int minX = std::numeric_limits<int>::max();
	int maxY = std::numeric_limits<int>::min();
	int minY = std::numeric_limits<int>::max();

	std::vector<Primitive*>::const_iterator iter = primitives.begin();
	std::vector<Primitive*>::const_iterator endIter = primitives.end();

	BBox box;
	while ( iter != endIter ) {
		(*iter)->getBoundingBox( box );
		// std::cout << "primitive: " << box.x1() << ", " << box.y1() << ", " << box.x2() << ", " << box.y2() << std::endl;
		minX = std::min( minX, box.x1() );
		maxX = std::max( maxX, box.x2() );
		minY = std::min( minY, box.y1() );
		maxY = std::max( maxY, box.y2() );
		++iter;
	}

	// std::cout << "result: " << minX << ", " << minY << ", " << maxX << ", " << maxY << std::endl;

	if ( maxX <= minX || maxY <= minY ) {
		return nullptr;
	}

	// int width = maxX - minX;
	// int height = maxY - minY;	
	// sdlTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height );
	sdlTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, maxX, maxY );

	// std::cout << "create texture size: " << width << ", " << height << std::endl;
	if ( sdlTexture == nullptr ) {
		assert( false && "failed to create sdl texture" );
		return nullptr;
	}
	SDL_SetTextureBlendMode( sdlTexture, SDL_BLENDMODE_BLEND );
	
	SDL_SetRenderTarget( renderer, sdlTexture );
	// SDL_RenderClear( renderer );
	
	iter = primitives.begin();
	endIter = primitives.end();
	while ( iter != endIter ) {
		(*iter)->render();
		++iter;
	}

	SDL_SetRenderTarget( renderer, nullptr );
	// std::cout << "end createTextureFromPrimitives" << std::endl;
	return sdlTexture;
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
//	return (((((a << 8) + r) << 8) + g) << 8) + b;
	return (((((a << 8) + b) << 8) + g) << 8) + r;
}

static inline void int2RGBA(Uint32 color, Uint8& r, Uint8& g, Uint8& b, Uint8& a)
{
	b = color & 0xFF; color = color >> 8;
	g = color & 0xFF; color = color >> 8;
	r = color & 0xFF; color = color >> 8;
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

#endif
