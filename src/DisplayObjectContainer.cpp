#include "DisplayObjectContainer.h"

#include <iostream>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include "Helper.h"

// #include "Texture.h"

DisplayObjectContainer::DisplayObjectContainer()
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
	// std::cout << "display object container update" << std::endl;
	DisplayObjectVec::iterator iter = _entityVec.begin();

//	std::cout << "size: " << _entityVec.size() << std::endl;
	while (iter != _entityVec.end())
	{
		// check if needed to release
		if((*iter)->isReleased())
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
	DisplayObjectVec::iterator iter = _entityVec.begin();
	while (iter != _entityVec.end())
	{
		if ( (*iter)->isVisible() )
		{
			(*iter)->render();
		}

		++iter;
	}
}

void DisplayObjectContainer::addChild( DisplayObjectBase* const entity )
{
//	std::cout << "add child" << std::endl;
	// check if it existed already

	if (_entityMap[entity->getId()] != nullptr)
	{
		std::stringstream msg;
		msg << "entity " << entity->getId() << " is already added!";
		assert(false && msg);
		return;
	}

	entity->setParent(this);
	_entityMap[entity->getId()] = entity;
	_entityVec.push_back(entity);
	entity->transform().setPos( this->transform().getX() + entity->transform().getX(), this->transform().getY() + entity->transform().getY() );

	dirtyBoundingBox_ = true;
//	std::cout << "add child ended" << std::endl;
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
//	std::vector<int> v;
	DisplayObjectVec::iterator iter = std::remove(_entityVec.begin(), _entityVec.end(), entity);
	_entityVec.erase(iter);
	
	dirtyBoundingBox_ = true;
}

void DisplayObjectContainer::releaseChild(DisplayObjectBase* entity)
{
	if (entity != nullptr)
	{
		removeChild(entity);
		delete entity;
		entity = nullptr;
		
		dirtyBoundingBox_ = true;
 	}
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
	
	dirtyBoundingBox_ = true;
}

int DisplayObjectContainer::getIndex(const DisplayObjectBase* entity) const
{
	return find(_entityVec.begin(), _entityVec.end(), entity) - _entityVec.begin();
}

DisplayObjectContainer::DisplayObjectVec& DisplayObjectContainer::getChildren()
{
	return _entityVec;
}

void DisplayObjectContainer::updateBoundingBox_()
{
	if ( !dirtyBoundingBox_ ) {
		return;
	}
	
	dirtyBoundingBox_ = false;
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
		boundingBox_.x = mx;
		boundingBox_.y = my;
		boundingBox_.w = mwidth;
		boundingBox_.h = mheight;

		// std::cout << std::endl;
	}
}

void DisplayObjectContainer::handleTransformPositionChanged_()
{
	DisplayObjectBase::handleTransformPositionChanged_();
	updateAllWorldTrans_();
}

void DisplayObjectContainer::handleTransformRotationChanged_()
{
	DisplayObjectBase::handleTransformRotationChanged_();
	updateAllWorldTrans_();
}

void DisplayObjectContainer::handleTransformScaleChanged_()
{
	DisplayObjectBase::handleTransformScaleChanged_();
	updateAllWorldTrans_();
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
