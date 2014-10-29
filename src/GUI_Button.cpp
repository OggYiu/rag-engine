#include "GUI_Button.h"

#include <iostream>
#include <functional>
#include <memory>
#include "boost/bind.hpp"

#include "Texture.h"
#include "Kernel.h"
#include "MouseEvent.h"
#include "Helper.h"
#include "Stage.h"
#include "GUI_Image.h"
#include "GUI_Label.h"
#include "TextureMgr.h"

static const float TWEEN_HIT_SCALE = 1.3f;
static const float TWEEN_HIT_DURATION = 0.07f;
static const float TWEEN_HOVER_DURATION = 0.07f;
static const float TWEEN_HOVER_SCALE = 1.1f;
//static const float TWEEN_HOVER_DURATION = 5.0;
//static const float TWEEN_HOVER_SCALE = 2.0f;


GUI_Button::GUI_Button( const int x, const int y, Texture* texture )
	: clicked_(false)
	, hovered_(false)
	, label_( nullptr )
	, state_(ButtonState::UP)
{
	GUI_Image* image = new GUI_Image( 0, 0, texture );
	this->addChild( image );
	transform().setPos( x, y );
	setSize( texture->getWidth(), texture->getHeight() );
}

GUI_Button::GUI_Button( const int x, const int y, const int width, const int height, const std::string& text )
	: clicked_(false)
	, hovered_(false)
	, label_( nullptr )
	, state_(ButtonState::UP)
{
	// std::cout << "button new" << std::endl;
	setSize( width, height );
	
	{
		Uint32 color = 0xFFFF0000;
		SolidRect rect( 0, 0, width, height, color );
		Texture* texture = textureMgr.getInstance().createPrimitiveTexture( rect );
		images_[ButtonState::UP] = new GUI_Image( 0, 0, texture );
		this->addChild( images_[ButtonState::UP] );
	}
		
	{
		Uint32 color = 0xFF00FF00;
		SolidRect rect( 0, 0, width, height, color );
		Texture* texture = textureMgr.getInstance().createPrimitiveTexture( rect );
		images_[ButtonState::DOWN] = new GUI_Image( 0, 0, texture );
		this->addChild( images_[ButtonState::DOWN] );
		images_[ButtonState::DOWN]->setVisible( false );
	}
	
	{
		Uint32 color = 0xFF0000FF;
		SolidRect rect( 0, 0, width, height, color );
		Texture* texture = textureMgr.getInstance().createPrimitiveTexture( rect );
		images_[ButtonState::HOVER] = new GUI_Image( 0, 0, texture );
		this->addChild( images_[ButtonState::HOVER] );
		images_[ButtonState::HOVER]->setVisible( false );
	}
	
	setText( text );
	this->transform().setPos( x, y );
}

GUI_Button::~GUI_Button()
{
}

void GUI_Button::setText(const std::string& text ATTR_UNUSED )
{
	if ( label_ != nullptr ) {
		this->removeChild( label_ );
		SAFE_RELEASE( label_ );
	}

	// const int marginnn = round( this->getWidth() / 10 );
	label_ = new GUI_Label( getWidth()/2, getHeight()/2, text );
	label_->setAnchor( 0.5f, 0.5f );
	// float factorX = (float)( this->getWidth() - margin * 2 ) / (float)label_->getWidth();
	// float factorY = (float)( this->getHeight() - margin * 2 ) / (float)label_->getHeight();
	// float scaleFactor = factorX < factorY? factorX : factorY;
	// std::cout << "width: " << this->getWidth() << ", height: " << this->getHeight() << ", label width: " << label_->getWidth() << ", label height: " << label_->getHeight() << std::endl;
	// std::cout << "margin: " << margin << ", factorX: " << factorX << ", factorY: " << factorY << std::endl;
	// label_->setWidth( round( label_->getWidth() * scaleFactor ) );
	// label_->setHeight( round( label_->getHeight() * scaleFactor ) );	
	this->addChild( label_ );
}

bool GUI_Button::resolved()
{
	GUI_BaseContainer::resolved();
	
	createEventListener();

	return true;
}

GUI_Button* GUI_Button::createSimpleButton( const char* title, const int x, const int y, const int w, const int h, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha )
{	
	Texture* texture = textureMgr.getInstance().createEmptyTexture( w, h, red, green, blue, alpha );
	GUI_Button* button = new GUI_Button( x, y, texture );
	button->setText( title );
	return button;
}

GUI_Button* GUI_Button::createImageButton( const int x, const int y, const std::string& path )
{
	Texture* texture = textureMgr.getInstance().createImageTexture( path );
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

	DisplayObject* target = nullptr;
	if ( images_[ButtonState::UP]->isVisible() ) {
		target = images_[ButtonState::UP];
	}
	else if ( images_[ButtonState::DOWN]->isVisible() ) {
		target = images_[ButtonState::DOWN];
	}
	else if ( images_[ButtonState::HOVER]->isVisible() ) {
		target = images_[ButtonState::HOVER];
	}
	
	if (event.getType().compare(MouseEvent::MOUSE_MOVE) == 0)
	{
		if ( target->hitTest( mouseX, mouseY ) )
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

						onHover();
						
						MouseEvent mouseEvent( MouseEvent::MOUSE_HOVER, mouseX, mouseY );
						this->dispatchEvent( mouseEvent );
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
				onHoverLost();
				
				MouseEvent mouseEvent( MouseEvent::MOUSE_LOSE_HOVER, mouseX, mouseY );
				this->dispatchEvent( mouseEvent );
			}
			hovered_ = false;
		}
	}
	else if ( event.getType().compare( MouseEvent::MOUSE_DOWN ) == 0 )
	{
		if ( target->hitTest( mouseX, mouseY ) )
		{
			state_ = ButtonState::DOWN;

			if (!clicked_)
			{
				onClick();
				
				MouseEvent mouseEvent( MouseEvent::MOUSE_DOWN, mouseX, mouseY );
				this->dispatchEvent( mouseEvent );
			}
			clicked_ = true;
		}

	}
	else if ( event.getType().compare( MouseEvent::MOUSE_UP ) == 0 )
	{
		if ( target->hitTest( mouseX, mouseY ) )
		{
			state_ = ButtonState::HOVER;

			onHover();
			
			MouseEvent mouseEvent( MouseEvent::MOUSE_UP, mouseX, mouseY );
			this->dispatchEvent( mouseEvent );
		}
		else
		{
			state_ = ButtonState::UP;
		}
		clicked_ = false;
	}

	return true;
}

void GUI_Button::update(const double dt)
{
	GUI_BaseContainer::update(dt);

	if (!tweenSeq_.is_finished())
	{
		tweenSeq_.update(dt);
	}
}

void GUI_Button::onHover()
{
	images_[ButtonState::UP]->setVisible( false );
	images_[ButtonState::HOVER]->setVisible( true );	
	images_[ButtonState::DOWN]->setVisible( false );
	
	// claw::tween::tweener_group group;
	// group.insert(
	// 	claw::tween::single_tweener( 1.0f, TWEEN_HOVER_SCALE, TWEEN_HOVER_DURATION, boost::bind( &Transform::setScaleX, &transform(), _1 ), claw::tween::easing_linear::ease_in )
	// );
	// group.insert(
	// 	claw::tween::single_tweener( 1.0f, TWEEN_HOVER_SCALE, TWEEN_HOVER_DURATION, boost::bind( &Transform::setScaleY, &transform(), _1 ), claw::tween::easing_linear::ease_in )
	// );
	// tweenSeq_.insert(group);
}

void GUI_Button::onHoverLost()
{
	images_[ButtonState::UP]->setVisible( true );
	images_[ButtonState::HOVER]->setVisible( false );	
	images_[ButtonState::DOWN]->setVisible( false );

	// claw::tween::tweener_group group;
	// group.insert(
	// 	claw::tween::single_tweener( TWEEN_HOVER_SCALE, 1.0f, TWEEN_HOVER_DURATION, boost::bind( &Transform::setScaleX, &transform(), _1 ), claw::tween::easing_linear::ease_in )
	// );
	// group.insert(
	// 	claw::tween::single_tweener( TWEEN_HOVER_SCALE, 1.0f, TWEEN_HOVER_DURATION, boost::bind( &Transform::setScaleY, &transform(), _1 ), claw::tween::easing_linear::ease_in )
	// );

	// tweenSeq_.insert(group);
}

void GUI_Button::onClick()
{
	images_[ButtonState::UP]->setVisible( false );
	images_[ButtonState::HOVER]->setVisible( false );	
	images_[ButtonState::DOWN]->setVisible( true );
	
	// claw::tween::tweener_group group1;
	// claw::tween::tweener_group group2;
	// group1.insert(
	// 	claw::tween::single_tweener( TWEEN_HOVER_SCALE, TWEEN_HIT_SCALE, TWEEN_HIT_DURATION, boost::bind( &Transform::setScaleX, &transform(), _1 ), claw::tween::easing_linear::ease_in )
	// );
	// group1.insert(
	// 	claw::tween::single_tweener( TWEEN_HOVER_SCALE, TWEEN_HIT_SCALE, TWEEN_HIT_DURATION, boost::bind( &Transform::setScaleY, &transform(), _1 ), claw::tween::easing_linear::ease_in )
	// );
	// group2.insert(
	// 	claw::tween::single_tweener( TWEEN_HIT_SCALE, TWEEN_HOVER_SCALE, TWEEN_HIT_DURATION, boost::bind( &Transform::setScaleX, &transform(), _1 ), claw::tween::easing_linear::ease_in )
	// );
	// group2.insert(
	// 	claw::tween::single_tweener( TWEEN_HIT_SCALE, TWEEN_HOVER_SCALE, TWEEN_HIT_DURATION, boost::bind( &Transform::setScaleY, &transform(), _1 ), claw::tween::easing_linear::ease_in )
	// );

	// tweenSeq_.insert(group1);
	// tweenSeq_.insert(group2);
}
