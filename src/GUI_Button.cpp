#include "GUI_Button.h"

#include <iostream>
#include <functional>
#include <memory>

#include "Texture.h"
#include "Kernel.h"
#include "MouseEvent.h"
#include "Helper.h"
#include "Stage.h"
#include "GUI_Label.h"

static const float TWEEN_HIT_SCALE = 1.3f;
static const float TWEEN_HIT_DURATION = 0.07f;
static const float TWEEN_HOVER_DURATION = 0.07f;
static const float TWEEN_HOVER_SCALE = 1.1f;
//static const float TWEEN_HOVER_DURATION = 5.0;
//static const float TWEEN_HOVER_SCALE = 2.0f;


GUI_Button::GUI_Button( const int x, const int y, Texture* texture )
	: clicked_(false)
	, hovered_(false)
	, state_(ButtonState::UP)
{
	texture_ = texture;
	setPosition( x, y );
	setSize( texture_->getWidth(), texture_->getHeight() );
}

GUI_Button::~GUI_Button()
{
}

void GUI_Button::setText( const std::string& text __attribute__((unused)) )
{
	if ( label_ != nullptr ) {
//		this->removeChild( label_ );
		SAFE_RELEASE( label_ );
	}
//	GUI_Label* label = new GUI_Label( 0, 0, const std::string& text, const std::string& fontName = FontMgr::DEFAULT_FONT_NAME, const int fontSize = FontMgr::DEFAULT_FONT_SIZE, const Uint8 red = 0, const Uint8 green = 0, const Uint8 blue = 0 );
}

bool GUI_Button::resolved()
{
	GUI_Base::resolved();
	
	createEventListener();

	return true;
}

GUI_Button* GUI_Button::createSimpleButton( const char* title, const int x, const int y, const int w, const int h, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha )
{	
	Texture* texture = Texture::createEmptyTexture( w, h, red, green, blue, alpha );
	GUI_Button* button = new GUI_Button( x, y, texture );
	button->setText( title );
	return button;
}

GUI_Button* GUI_Button::createImageButton( const int x, const int y, const std::string& path )
{
	Texture* texture = Texture::createImageTexture( path );
	GUI_Button* button = new GUI_Button( x, y, texture );
	return button;
}

void GUI_Button::createEventListener()
{
	kernel.getStage().addEventListener(MouseEvent::MOUSE_MOVE, bindEventHandler(&GUI_Button::eventHandler, this), this);
	kernel.getStage().addEventListener(MouseEvent::MOUSE_DOWN, bindEventHandler(&GUI_Button::eventHandler, this), this);
	kernel.getStage().addEventListener(MouseEvent::MOUSE_UP, bindEventHandler(&GUI_Button::eventHandler, this), this);
}

bool GUI_Button::eventHandler( const Event& event )
{
	MouseEvent* mouseEvent = (MouseEvent*)(&event);
	int mouseX = mouseEvent->getMouseX();
	int mouseY = mouseEvent->getMouseY();
	
	// std::cout << mouseEvent->getMouseX() << std::endl;
	// std::cout << "gui button event handler: " << event.getType() << std::endl;
	if (event.getType().compare(MouseEvent::MOUSE_MOVE) == 0)
	{
		// std::cout << "mouse move " << mouseEvent->getMouseX() << ", " << mouseEvent->getMouseY() << std::endl;

		if (hitTest(mouseX, mouseY))
		{
			if (state_ != ButtonState::DOWN)
			{
				if (clicked_)
				{
					state_ = ButtonState::DOWN;
				}
				else
				{
					if (!hovered_)
					{
						hovered_ = true;

						// clicked handler
						claw::tween::tweener_group group;
						group.insert(
							claw::tween::single_tweener(1.0f, TWEEN_HOVER_SCALE, TWEEN_HOVER_DURATION, boost::bind(&DisplayObject::setScaleX, this, _1), claw::tween::easing_linear::ease_in )
							);
						group.insert(
							claw::tween::single_tweener(1.0f, TWEEN_HOVER_SCALE, TWEEN_HOVER_DURATION, boost::bind(&DisplayObject::setScaleY, this, _1), claw::tween::easing_linear::ease_in )
							);

						tweenSeq_.insert(group);

						this->dispatchEvent(Event(MouseEvent::MOUSE_HOVER));
					}
					state_ = ButtonState::HOVER;
				}
			}
		}
		else
		{
			state_ = ButtonState::UP;

			if (hovered_)
			{
				claw::tween::tweener_group group;
				group.insert(
					claw::tween::single_tweener(TWEEN_HOVER_SCALE, 1.0f, TWEEN_HOVER_DURATION, boost::bind(&DisplayObject::setScaleX, this, _1), claw::tween::easing_linear::ease_in )
					);
				group.insert(
					claw::tween::single_tweener(TWEEN_HOVER_SCALE, 1.0f, TWEEN_HOVER_DURATION, boost::bind(&DisplayObject::setScaleY, this, _1), claw::tween::easing_linear::ease_in )
					);

				tweenSeq_.insert(group);

				this->dispatchEvent(Event(MouseEvent::MOUSE_LOSE_HOVER ));
			}
			hovered_ = false;
		}
		// texture_ = textures_[state_];
	}
	else if (event.getType().compare(MouseEvent::MOUSE_DOWN) == 0)
	{
		// std::cout << "mouse down " << mouseEvent->getMouseX() << ", " << mouseEvent->getMouseY() << std::endl;

		if (hitTest(mouseX, mouseY))
		{
			state_ = ButtonState::DOWN;
			// texture_ = textures_[state_];

			if (!clicked_)
			{
				// std::cout << "click tween" << std::endl;
				claw::tween::tweener_group group1;
				claw::tween::tweener_group group2;
				group1.insert(
					claw::tween::single_tweener(TWEEN_HOVER_SCALE, TWEEN_HIT_SCALE, TWEEN_HIT_DURATION, boost::bind(&DisplayObject::setScaleX, this, _1), claw::tween::easing_linear::ease_in )
					);
				group1.insert(
					claw::tween::single_tweener(TWEEN_HOVER_SCALE, TWEEN_HIT_SCALE, TWEEN_HIT_DURATION, boost::bind(&DisplayObject::setScaleY, this, _1), claw::tween::easing_linear::ease_in )
					);
				group2.insert(
					claw::tween::single_tweener(TWEEN_HIT_SCALE, TWEEN_HOVER_SCALE, TWEEN_HIT_DURATION, boost::bind(&DisplayObject::setScaleX, this, _1), claw::tween::easing_linear::ease_in )
					);
				group2.insert(
					claw::tween::single_tweener(TWEEN_HIT_SCALE, TWEEN_HOVER_SCALE, TWEEN_HIT_DURATION, boost::bind(&DisplayObject::setScaleY, this, _1), claw::tween::easing_linear::ease_in )
					);

				tweenSeq_.insert(group1);
				tweenSeq_.insert(group2);

				this->dispatchEvent(Event(MouseEvent::MOUSE_DOWN));
			}
			clicked_ = true;
		}

	}
	else if (event.getType().compare(MouseEvent::MOUSE_UP) == 0)
	{
		// std::cout << "mouse hover " << mouseEvent->getMouseX() << ", " << mouseEvent->getMouseY() << std::endl;

		if (hitTest(mouseX, mouseY))
		{
			state_ = ButtonState::HOVER;
			this->dispatchEvent(Event(MouseEvent::MOUSE_UP));
			// handler
		}
		else
		{
			state_ = ButtonState::UP;
		}
		clicked_ = false;
		// texture_ = textures_[state_];
	}
	// SDL_MOUSEBUTTONDOWN
	// SDL_MOUSEBUTTONUP

	return true;
}

void GUI_Button::update(const double dt)
{
	GUI_Base::update(dt);

	if (!tweenSeq_.is_finished())
	{
		tweenSeq_.update(dt);
	}
}
