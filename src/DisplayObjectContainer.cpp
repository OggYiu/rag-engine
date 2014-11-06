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
	DisplayObjectVec::iterator iter = entityVec_.begin();
	DisplayObjectVec::iterator endIter = entityVec_.end();
	while ( iter != endIter )
	{
		SAFE_RELEASE(*iter);
		++iter;
	}

	entityVec_.clear();
}

void DisplayObjectContainer::update(const double dt)
{	
	DisplayObjectVec::iterator iter = entityVec_.begin();

//	std::cout << "size: " << entityVec_.size() << std::endl;
	while (iter != entityVec_.end())
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
	// resetAllChildrenClipRect_();
	
	DisplayObjectVec::iterator iter = entityVec_.begin();
	DisplayObjectVec::iterator endIter = entityVec_.end();	
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

	DisplayObjectVec::iterator iter = entityVec_.begin();
	DisplayObjectVec::iterator endIter = entityVec_.end();

#ifdef DEBUG
	while ( iter != endIter ) {
		if ( (*iter) == entity ) {
			logger.e( "xxxx", "duplicated entity" );
			return;
		}
		++iter;
	}
	iter = entityVec_.begin();
#endif

	// std::cout << "child added xxxx: " << entity->getId() << std::endl;
	entity->handleAddedToParent( this );
	entityVec_.push_back(entity);
	entity->transform().setPos( entity->transform().getX(), entity->transform().getY() );
	updateBoundingBox_();
}

void DisplayObjectContainer::setClipRect( const int x, const int y, const int width, const int height )
{
	DisplayObjectBase::setClipRect( x, y, width, height );
	// resetAllChildrenClipRect();
}

void DisplayObjectContainer::removeChild(DisplayObjectBase* entity)
{
	// std::cout << "entity remove child: " << entity->getId() << std::endl;
	// check if it existed already
	
	DisplayObjectVec::iterator iter = entityVec_.begin();
	DisplayObjectVec::iterator endIter = entityVec_.end();
	while ( iter != endIter ) {
		if ( (*iter) == entity ) {
			entity->handleRemovedFromParent( this );
			entityVec_.erase( iter );
			std::cout << entity->getId() << " removed from container" << std::endl;
			break;
		}
		std::cout << "child id found xxxxx: " << entity->getId() << std::endl;
		++iter;
	}
	
	updateBoundingBox_();
}

void DisplayObjectContainer::removeChildAt( const int index )
{
	if ( index < 0 || index >= (int)entityVec_.size() ) {
		assert( false && "invalid index" );
		return;
	}

	DisplayObjectBase* obj = entityVec_[index];
	removeChild( obj );
}

void DisplayObjectContainer::releaseChild(DisplayObjectBase* entity)
{
	if (entity != nullptr)
	{
		removeChild(entity);
		delete entity;
		entity = nullptr;

		updateBoundingBox_();
 	}
}

void DisplayObjectContainer::releaseChildAt( const int index )
{
	if ( index < 0 || index >= (int)entityVec_.size() ) {
		assert( false && "invalid index" );
		return;
	}

	DisplayObjectBase* obj = entityVec_[index];
	releaseChild( obj );
}

void DisplayObjectContainer::releaseAllChildren()
{
	DisplayObjectVec::iterator iter = entityVec_.begin();
	DisplayObjectVec::iterator endIter = entityVec_.end();

	while ( iter != endIter ) {
		// std::cout << (*iter)->getId() << " released" << std::endl;
		(*iter)->handleRemovedFromParent( this );
		SAFE_RELEASE( *iter );
		++iter;
	}
	
	entityVec_.clear();
	
	updateBoundingBox_();
}

int DisplayObjectContainer::getIndex(const DisplayObjectBase* entity) const
{
	return find(entityVec_.begin(), entityVec_.end(), entity) - entityVec_.begin();
}

DisplayObjectContainer::DisplayObjectVec& DisplayObjectContainer::getChildren()
{
	return entityVec_;
}

// void DisplayObjectContainer::updateBoundingBox()
// {
// 	DisplayObjectBase::updateBoundingBox();
// }

void DisplayObjectContainer::updateBoundingBox_()
{
	// if ( !needUpdateBoundingBox() ) {
	// 	return;
	// }
	// doneUpdateBoundingBox();

	// std::cout << "DisplayObjectContainer::updateBoundingBox_ began ------------------------------" << std::endl;
	
	if ( entityVec_.size() <= 0 ) {
		boundingBox_.x = 0;
		boundingBox_.y = 0;
		boundingBox_.w = 0;
		boundingBox_.h = 0;
	} else {
		int maxX = std::numeric_limits<int>::min();
		int minX = std::numeric_limits<int>::max();
		int maxY = std::numeric_limits<int>::min();
		int minY = std::numeric_limits<int>::max();

		DisplayObjectVec::iterator iter = entityVec_.begin();
		DisplayObjectVec::iterator endIter = entityVec_.end();
		// std::cout << "children count: " << entityVec_.size() << std::endl;
		SDL_Rect* bbox = nullptr;
		DisplayObjectBase* displayObj = nullptr;
		while ( iter != endIter )
		{
			displayObj = (*iter);
			displayObj->tryUpdateBoundingBox();
			bbox = &displayObj->getBBox();

			// std::cout << "obj bounding: " << bbox->x << ", " << bbox->y << ", " << bbox->w << ", " << bbox->h << std::endl;
			// float x1 = bbox->x + displayObj->transform().getX();
			// float x2 = x1 + bbox->w;
			// float y1 = bbox->y + displayObj->transform().getY();
			// float y2 = y1 + bbox->h;
			
			float x1 = bbox->x;
			float x2 = x1 + bbox->w;
			float y1 = bbox->y;
			float y2 = y1 + bbox->h;

			minX = std::min<int>( x1, minX );			
			maxX = std::max<int>( x2, maxX );
			minY = std::min<int>( y1, minY );			
			maxY = std::max<int>( y2, maxY );

			// std::cout << "min and max: " << minX << ", " << minY << ", " << maxX << ", " << maxY << std::endl << std::endl;

			++iter;
		}

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

		// std::cout << "result bounding box: " << boundingBox_.x << ", " << boundingBox_.y << ", " << boundingBox_.w << ", " << boundingBox_.h << std::endl;
	}

	// std::cout << "DisplayObjectContainer::updateBoundingBox_ end ------------------------------" << std::endl;
}

void DisplayObjectContainer::handleTransformEvent()
{
	DisplayObjectBase::handleTransformEvent();
	
	DisplayObjectVec::iterator iter = entityVec_.begin();
	DisplayObjectVec::iterator endIter = entityVec_.end();
	while ( iter != endIter )
	{
		(*iter)->handleTransformEvent();
		++iter;
	}
}
