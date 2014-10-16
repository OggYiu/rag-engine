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
	// resetAllChildrenClipRect_();
	
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
	// resetAllChildrenClipRect();
}

void DisplayObjectContainer::setClipRect( const int x, const int y, const int width, const int height )
{
	DisplayObjectBase::setClipRect( x, y, width, height );
	// resetAllChildrenClipRect();
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

	// std::cout << "DisplayObjectContainer::updateBoundingBox_ began ------------------------------" << std::endl;
	
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
		// std::cout << "children count: " << _entityVec.size() << std::endl;
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
	
	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectVec::iterator endIter = _entityVec.end();
	while ( iter != endIter )
	{
		(*iter)->handleTransformEvent();
		(*iter)->transform().updateWorldTrans();
		++iter;
	}
}

// void DisplayObjectContainer::foo()
// {
// 	if ( clipRect_ == nullptr ) {
// 		return;
// 	}
	
// 	DisplayObjectVec::iterator iter = _entityVec.begin();
// 	DisplayObjectVec::iterator endIter = _entityVec.end();
// 	float localX, localY;
// 	float stageX, stageY;
// 	while ( iter != endIter )
// 	{
// 		SDL_Rect& bbox = (*iter)->getBBox();
// 		(*iter)->transform().getPos( localX, localY );
// 		(*iter)->transform().getStagePos( stageX, stageY );			

// 		if ( localY < 0 ) {
// 			if ( localY < ( localY + bbox.h ) ) {
// 				(*iter)->setClipRect( 0, 0, 0, 0 );
// 				(*iter)->setRenderRect( 0, 0, 0, 0 );
// 			} else {
// 				float part1 = fabs( localY );
// 				float part2 = bbox.h - part1;
// 				(*iter)->setClipRect( 0, part1, bbox.w, part2 );
// 				(*iter)->setRenderRect( stageX, stageY + part1, bbox.w, part2 );
// 			}
// 		} else 	if ( clipRect_->h > ( localY + bbox.h ) ) {
// 			(*iter)->setClipRect( 0, 0, bbox.w, bbox.h );
// 			(*iter)->setRenderRect( stageX, stageY, bbox.w, bbox.h );						
// 		} else {
// 			if ( clipRect_->h > localY ) {
// 				(*iter)->setClipRect( 0, 0, bbox.w, ( clipRect_->h - localY) );
// 				(*iter)->setRenderRect( stageX, stageY, bbox.w, ( clipRect_->h - localY) );
// 			} else {
// 				(*iter)->setClipRect( 0, 0, 0, 0 );
// 				(*iter)->setRenderRect( 0, 0, 0, 0 );
// 			}
// 		}
// 		++iter;
// 	}
// }

// void DisplayObjectContainer::resetAllChildrenClipRect()
// {
// 	needResetAllChildrenClipRect_ = true;
// }

// void DisplayObjectContainer::resetAllChildrenClipRect_()
// {
// 	if ( !needResetAllChildrenClipRect_ ) {
// 		return;
// 	}

// 	float x, y;
// 	int w, h;
// 	float x1, x2, y1, y2;
// 	float a1, a2, b1, b2;
// 	a1 = clipRect_.x;
// 	b1 = clipRect_.y;
// 	a2 = clipRect_.x + clipRect_.w;
// 	b2 = clipRect_.y + clipRect_.h;
// 	std::cout << std::endl;
// 	std::cout << "cliprect 1111: " << clipRect_.x << ", " << clipRect_.y << ", " << clipRect_.w << ", " << clipRect_.h << std::endl;	
// 	DisplayObjectBase* obj;
// 	DisplayObjectVec::iterator iter = _entityVec.begin();
// 	DisplayObjectVec::iterator endIter = _entityVec.end();
// 	while ( iter != endIter )
// 	{
// 		obj = (*iter);
// 		obj->transform().getPos( x, y );
// 		obj->getSize( w, h );

// 		x1 = a1 > x? a1 : x;
// 		y1 = b1 > y? b1 : y;
// 		x2 = a2 < ( x + w )? a2 : ( x + w );
// 		y2 = b2 < ( y + h )? b2 : ( y + h );
// 		std::cout << "cliprect 2222: " << x1 << ", " << y1 << ", " << x2 << ", " << y2 << std::endl;	
// 		obj->setClipRect( x1, y1, x2 - x1, y2 - y1 );
		
// 		++iter;
// 	}
// 	std::cout << std::endl;	
// 	needResetAllChildrenClipRect_ = false;
// }

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
