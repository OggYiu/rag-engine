#ifndef __DISPLAYOBJECTBASE_H__
#define __DISPLAYOBJECTBASE_H__

#include <map>
#include "SDL.h"
#include "Eigen/Dense"
#include "EventDispatcher.h"
#include "Tweener.h"
#include "Transform.h"
#include "Logger.h"

class DisplayObjectContainer;
class Component_Base;

#ifdef DEBUG
class Graphics;
#endif

class DisplayObjectBase : public EventDispatcher
{
public:
	typedef std::map< std::string, Component_Base* > ComponentMap;
	typedef ComponentMap::iterator ComponentIter; 
	
public:
	DisplayObjectBase();
	virtual ~DisplayObjectBase();
	
public:
	DisplayObjectContainer* getParent() { return parent_; }
	virtual void render() = 0;
	virtual void update(const double dt);
	virtual void handleAddedToParent( DisplayObjectContainer* container );
	virtual void handleRemovedFromParent( DisplayObjectContainer* container );

	void detachFromParent();
	void release();	
	bool needReleased() { return needReleased_; }
	void setClipRect( const int x, const int y, const int width, const int height );
	
	void addComponent( Component_Base* component );
	void removeComponent( const std::string& name );

	void getSize( int* width, int* height );
	void setSize( const int width, const int height );
	void setWidth( const int width );
	int getWidth() const;
	float getScaledWidth() const;
	
	void setHeight( const int height );
	int getHeight() const;
	float getScaledHeight() const;	

	void setAnchor( const float x, const float y );
	void setAnchorX( const float x );
	void setAnchorY( const float y );
	
	float getAnchorX() const;
	float getAnchorY() const;

	void setRotation( const float rotation );
	float getRotation() const;

	bool isVisible() const;
	void setVisible( const bool visible );
	
	bool hitTest( const int x, const int y );
	SDL_Rect& getBBox() { return boundingBox_; }

	Tweener& tweener() { return tweener_; }
	Transform& transform() { return transform_; }
	
	void updateBoundingBox();
	void tryUpdateBoundingBox();
	virtual bool dragEventHandler( const Event& event );
	virtual void handleTransformEvent();
	
protected:
	bool transformEventHandler( const Event& event );
	virtual void updateBoundingBox_();
	bool needUpdateBoundingBox() { return dirtyBoundingBox_; }
	void doneUpdateBoundingBox() { dirtyBoundingBox_ = false; }

protected:
	DisplayObjectContainer* parent_;
	bool needReleased_;
	Eigen::Vector2f anchor_;
	Eigen::Vector2i size_;
	SDL_Rect clipRect_;
	SDL_Rect boundingBox_;
	bool visible_;
	Tweener tweener_;
	Transform transform_;
	ComponentMap components_;

#ifdef DEBUG
	Graphics* debugBBox_;
#endif

	bool dirtyBoundingBox_;
};

#endif
