#ifndef __DISPLAYOBJECTBASE_H__
#define __DISPLAYOBJECTBASE_H__

#include "Eigen/Dense"
#include "EventDispatcher.h"

class DisplayObjectContainer;

class DisplayObjectBase : public EventDispatcher
{	
public:
	DisplayObjectBase();
	virtual ~DisplayObjectBase();
	
public:
   	void setParent( DisplayObjectContainer* parent );
	virtual void render() = 0;

public:
	// getter and setter
	void setPosition( const float x, const float y );
	
	virtual void setX( const float x );
	float getX() const;
	
	virtual void setY( const float y );
	float getY() const;

	void setSize( const int width, const int height );
	void setWidth( const int width );
	int getWidth() const;
	float getScaledWidth() const;
	
	void setHeight( const int height );
	int getHeight() const;
	float getScaledHeight() const;	

	void setScaleX( const float x );
	float getScaleX() const;

	void setScaleY( const float y );
	float getScaleY() const;

	void setAnchor( const float x, const float y );
	void setAnchorX( const float x );
	float getAnchorX() const;

	void setAnchorY( const float y );
	float getAnchorY() const;

	void setRotation( const float rotation );
	float getRotation() const;

	bool isVisible() const;
	void setVisible( const bool visible );
	
protected:
	DisplayObjectContainer* parent_;
	Eigen::Vector2f position_;
	Eigen::Vector2f anchor_;
	Eigen::Vector2f scale_;
	Eigen::Vector2i size_;
	float rotation_;
	bool dirtyRenderPos_;
	bool visible_;	
};

#endif
