#ifndef __DISPLAYOBJECTBASE_H__
#define __DISPLAYOBJECTBASE_H__

#include "SDL.h"
#include "Eigen/Dense"
#include "EventDispatcher.h"
#include "Tweener.h"

class DisplayObjectContainer;

#ifdef DEBUG
class Graphics;
#endif

class DisplayObjectBase : public EventDispatcher
{	
public:
	DisplayObjectBase();
	virtual ~DisplayObjectBase();
	
public:
   	void setParent( DisplayObjectContainer* parent );
	virtual void render() = 0;

public:
	virtual void update(const double dt);
	void refreshPos();
	void setPos( const float x, const float y );
	
	virtual void setX( const float x );
	virtual void setY( const float y );
	
	float getX() const { return localPos_[0]; }
	float getY() const { return localPos_[1]; }

	float getStageX() const { return stagePos_[0]; }
	float getStageY() const { return stagePos_[1]; }

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
	
	bool hitTest( const int x, const int y ) const;

	int getBBoxX() const { return boundingBox_.x; }
	int getBBoxY() const { return boundingBox_.y; }
	int getBBoxWidth() const { return boundingBox_.w; }
	int getBBoxHeight() const { return boundingBox_.h; }
	SDL_Rect& getBBox() { return boundingBox_; }

	Tweener& tweener() { return tweener_; }

	virtual void updateBoundingBox();

protected:
	DisplayObjectContainer* parent_;
	Eigen::Vector2f localPos_;
	Eigen::Vector2f stagePos_;
	Eigen::Vector2f anchor_;
	Eigen::Vector2f scale_;
	Eigen::Vector2i size_;
	float rotation_;
	bool dirtyBoundingBox_;
	SDL_Rect boundingBox_;
	bool visible_;
	Tweener tweener_;

#ifdef DEBUG
	Graphics* debugBBox_;
#endif
};

#endif
