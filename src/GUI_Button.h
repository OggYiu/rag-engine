#ifndef __GUI_BUTTON_H__
#define __GUI_BUTTON_H__

#include <memory>
#include "claw/tween/single_tweener.hpp"
#include "claw/tween/tweener_group.hpp"
#include "claw/tween/tweener_sequence.hpp"
#include "claw/tween/easing/easing_linear.hpp"
//#include "boost/bind.hpp"
#include "SDL.h"

#include "GUI_BaseContainer.h"
#include "Event.h"

class Texture;
class MouseEvent;
class GUI_Label;
class GUI_Image;

enum ButtonState
{
	UP,
	DOWN,
	HOVER,
	COUNT,
};

class GUI_Button : public GUI_BaseContainer
{
public:
	static GUI_Button* createSimpleButton( const char* title, const int x, const int y, const int w, const int h, const Uint8 red = 255, const Uint8 green = 255, const Uint8 blue = 255, const Uint8 alpha = 255 );
	static GUI_Button* createImageButton( const int x, const int y, const std::string& path );
	// static GUI_Button* createPNDButton(const int x, const int y)
	
public:
	GUI_Button( const int x, const int y, Texture* texture );
	GUI_Button( const int x, const int y, const int width, const int height, const std::string& text );
	~GUI_Button();
	
public:
	void setText( const std::string& text );
	virtual void resolved();
	
private:
	void createEventListener();
	bool eventHandler( const Event& event );
	void update( const double dt );
	void onHover();
	void onHoverLost();
	void onClick();
	
private:
	bool clicked_;
	bool hovered_;
	GUI_Label* label_;
	std::map<ButtonState, GUI_Image*> images_;
	ButtonState state_;
	claw::tween::tweener_sequence tweenSeq_;
};

#endif

