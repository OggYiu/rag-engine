#include "DisplayObjectContainer.h"

#include <iostream>
#include <assert.h>
#include <sstream>
#include <algorithm>

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
	DisplayObjectBase::update(dt);
	
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

void DisplayObjectContainer::addChild(DisplayObjectBase* entity)
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
}

void DisplayObjectContainer::releaseChild(DisplayObjectBase* entity)
{
	if (entity != nullptr)
	{
		removeChild(entity);
		delete entity;
		entity = nullptr;		
 	}
}

void DisplayObjectContainer::setX( const int x )
{
	int diff = x - position_[0];

	DisplayObjectBase::setX( x );

	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectBase* obj = nullptr;
	while (iter != _entityVec.end())
	{
		obj = (*iter);
		obj->setX( obj->getX() + diff );
		++iter;
	}
}

void DisplayObjectContainer::setY( const int y )
{
	int diff = y - position_[1];
	DisplayObjectBase::setY( y );	

	DisplayObjectVec::iterator iter = _entityVec.begin();
	DisplayObjectBase* obj = nullptr;
	while (iter != _entityVec.end())
	{
		obj = (*iter);
		obj->setY( obj->getY() + diff );
		++iter;
	}		
}

int DisplayObjectContainer::getIndex(const DisplayObjectBase* entity) const
{
	return find(_entityVec.begin(), _entityVec.end(), entity) - _entityVec.begin();
}

DisplayObjectContainer::DisplayObjectVec& DisplayObjectContainer::getChildren()
{
	return _entityVec;
}
