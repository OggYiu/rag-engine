#include "DisplayObjectContainer.h"

#include <iostream>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include "Helper.h"

// #include "Texture.h"

DisplayObjectContainer::DisplayObjectContainer()
	: needResetAllChildrenClipRect_( false )
{
}

DisplayObjectContainer::~DisplayObjectContainer()
{
	DisplayObjectVec::iterator iter = _entityVec.begin();
	while (iter != _entityVec.end())
	{
		delete (*iter);
		(*iter) = nullptr;
		++iter;
	}

	_entityVec.clear();
}

void DisplayObjectContainer::update(const double dt)
{	
	DisplayObjectVec::iterator iter = _entityVec.begin();

//	std::cout << "size: " << _entityVec.size() << std::endl;
	while (iter != _entityVec.end())
	{
		// check if needed to release
		if( (*iter)->needReleased() )
		{
			releaseChild(*iter);
			--iter;
			continue;
		}
//		std::cout << "update" << std::endl;
		(*iter)->update(dt);
		++iter;
	}
	
	DisplayObjectBase::update(dt);
}

void DisplayObjectContainer::render()
{
	// std::cout << std::endl;
	if ( !isVisible() ) {
		return;
	}
	
	updateBoundingBox_();
	resetAllChildrenClipRect_();
	
	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectVec::iterator endIter = _entityVec.end();	
	while (iter != endIter )
	{
		if ( (*iter)->isVisible() )
		{
			(*iter)->render();
		}

		++iter;
	}
	// std::cout << std::endl;
}

void DisplayObjectContainer::addChild( DisplayObjectBase* const entity )
{
	if ( this == entity ) {
		logger.e( "DisplayObjectContainer", "you cannot add yourself" );
		return;
	}

	if (_entityMap[entity->getId()] != nullptr)
	{
		std::stringstream msg;
		msg << "entity " << entity->getId() << " is already added!";
		assert(false && msg);
		return;
	}

	entity->handleAddedToParent( this );
	_entityMap[entity->getId()] = entity;
	_entityVec.push_back(entity);
	// entity->transform().setPos( this->transform().getX() + entity->transform().getX(), this->transform().getY() + entity->transform().getY() );
	entity->transform().setPos( entity->transform().getX(), entity->transform().getY() );
	updateBoundingBox();
	resetAllChildrenClipRect();
}

void DisplayObjectContainer::setClipRect( const int x, const int y, const int width, const int height )
{
	DisplayObjectBase::setClipRect( x, y, width, height );
	resetAllChildrenClipRect();
}

void DisplayObjectContainer::removeChild(DisplayObjectBase* entity)
{
	// check if it existed already
	if (_entityMap[entity->getId()] == nullptr)
	{
		std::stringstream msg;
		msg << "entity " << entity->getId() << " is not added!";
		assert(false && msg);
		return;
	}

	_entityMap[entity->getId()] = nullptr;
	entity->handleRemovedFromParent( this );
//	std::vector<int> v;
	DisplayObjectVec::iterator iter = std::remove(_entityVec.begin(), _entityVec.end(), entity);
	_entityVec.erase(iter);
	
	updateBoundingBox();
}

void DisplayObjectContainer::removeChildAt( const int index )
{
	if ( index < 0 || index >= (int)_entityVec.size() ) {
		assert( false && "invalid index" );
		return;
	}

	DisplayObjectBase* obj = _entityVec[index];
	removeChild( obj );
}

void DisplayObjectContainer::releaseChild(DisplayObjectBase* entity)
{
	if (entity != nullptr)
	{
		removeChild(entity);
		delete entity;
		entity = nullptr;

		updateBoundingBox();
 	}
}

void DisplayObjectContainer::releaseChildAt( const int index )
{
	if ( index < 0 || index >= (int)_entityVec.size() ) {
		assert( false && "invalid index" );
		return;
	}

	DisplayObjectBase* obj = _entityVec[index];
	releaseChild( obj );
}

void DisplayObjectContainer::releaseAllChildren()
{
	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectVec::iterator endIter = _entityVec.end();

	while ( iter != endIter ) {
		this->removeChild( *iter );
		SAFE_RELEASE( *iter );
		++iter;
	}

	_entityVec.clear();
	
	updateBoundingBox();
}

int DisplayObjectContainer::getIndex(const DisplayObjectBase* entity) const
{
	return find(_entityVec.begin(), _entityVec.end(), entity) - _entityVec.begin();
}

DisplayObjectContainer::DisplayObjectVec& DisplayObjectContainer::getChildren()
{
	return _entityVec;
}

void DisplayObjectContainer::updateBoundingBox()
{
	DisplayObjectBase::updateBoundingBox();
}

void DisplayObjectContainer::updateBoundingBox_()
{
	if ( !needUpdateBoundingBox() ) {
		return;
	}

	doneUpdateBoundingBox();
	
	if ( _entityVec.size() <= 0 ) {
		boundingBox_.x = 0;
		boundingBox_.y = 0;
		boundingBox_.w = 0;
		boundingBox_.h = 0;
	} else {
		int maxX = std::numeric_limits<int>::min();
		int minX = std::numeric_limits<int>::max();
		int maxY = std::numeric_limits<int>::min();
		int minY = std::numeric_limits<int>::max();

		DisplayObjectVec::iterator iter = _entityVec.begin();
		DisplayObjectVec::iterator endIter = _entityVec.end();	
		// DisplayObjectBase* obj = nullptr;
		SDL_Rect* bbox = nullptr;
		// std::cout << "update bounding box..." << std::endl;
		while ( iter != endIter )
		{
			(*iter)->tryUpdateBoundingBox();
			bbox = &(*iter)->getBBox();
			(*iter)->updateBoundingBox();
			// std::cout << "bbox: " << bbox->x << ", " << bbox->y << ", " << bbox->w << ", " << bbox->h << std::endl;

			minX = std::min<int>( bbox->x, minX );			
			maxX = std::max<int>( bbox->x + bbox->w, maxX );
			minY = std::min<int>( bbox->y, minY );			
			maxY = std::max<int>( bbox->y + bbox->h, maxY );

			++iter;
		}

		// std::cout << minX << ", " << minY << ", " << maxX << ", " << maxY << std::endl;
		assert( ( maxX >= minX ) && "invalid maxx or minx" );
		assert( ( maxY >= minY ) && "invalid maxy or miny" );
		
		int mx = minX;
		int my = minY;
		int mwidth = maxX - minX;
		int mheight = maxY - minY;
		boundingBox_.x = mx + transform().getStageX();
		boundingBox_.y = my + transform().getStageY();
		boundingBox_.w = mwidth;
		boundingBox_.h = mheight;

		setSize( mwidth, mheight );
		// std::cout << "transfomr(): " << transform().getWorldMatrix() << std::endl;
		// std::cout << std::endl;
	}

	// std::cout << "container bounding box: " << boundingBox_.x << ", " << boundingBox_.y << ", " << boundingBox_.w << ", " << boundingBox_.h << std::endl;
}

void DisplayObjectContainer::handleTransformEvent()
{
	DisplayObjectBase::handleTransformEvent();
	
	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectVec::iterator endIter = _entityVec.end();
	while ( iter != endIter )
	{
		(*iter)->handleTransformEvent();
		(*iter)->transform().updateWorldTrans();
		++iter;
	}
}

void DisplayObjectContainer::resetAllChildrenClipRect()
{
	needResetAllChildrenClipRect_ = true;
}

void DisplayObjectContainer::resetAllChildrenClipRect_()
{
	if ( !needResetAllChildrenClipRect_ ) {
		return;
	}

	float x, y;
	int w, h;
	float x1, x2, y1, y2;
	float a1, a2, b1, b2;
	a1 = clipRect_.x;
	b1 = clipRect_.y;
	a2 = clipRect_.x + clipRect_.w;
	b2 = clipRect_.y + clipRect_.h;
	std::cout << std::endl;
	std::cout << "cliprect 1111: " << clipRect_.x << ", " << clipRect_.y << ", " << clipRect_.w << ", " << clipRect_.h << std::endl;	
	DisplayObjectBase* obj;
	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectVec::iterator endIter = _entityVec.end();
	while ( iter != endIter )
	{
		obj = (*iter);
		obj->transform().getPos( x, y );
		obj->getSize( w, h );

		x1 = a1 > x? a1 : x;
		y1 = b1 > y? b1 : y;
		x2 = a2 < ( x + w )? a2 : ( x + w );
		y2 = b2 < ( y + h )? b2 : ( y + h );
		std::cout << "cliprect 2222: " << x1 << ", " << y1 << ", " << x2 << ", " << y2 << std::endl;	
		obj->setClipRect( x1, y1, x2 - x1, y2 - y1 );
		
		++iter;
	}
	std::cout << std::endl;	
	needResetAllChildrenClipRect_ = false;
}

void DisplayObjectContainer::updateAllWorldTrans_()
{
	transform().updateWorldTrans();
	
	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectVec::iterator endIter = _entityVec.end();	
	DisplayObjectBase* obj = nullptr;
	while ( iter != endIter )
	{
		obj = (*iter);
		obj->transform().updateWorldTrans();
		++iter;
	}
}
