#ifndef __DISPLAYOBJECTCONTAINER_H__
#define __DISPLAYOBJECTCONTAINER_H__

//#include <ext/hash_map>
//#include <hash_map>
#include <unordered_map>
#include <vector>
#include "DisplayObjectBase.h"

class DisplayObjectContainer : public DisplayObjectBase
{
public:
	typedef std::unordered_map<int, DisplayObjectBase*> DisplayObjectMap;
	typedef std::vector<DisplayObjectBase*> DisplayObjectVec;
	
public:
	DisplayObjectContainer();
	virtual ~DisplayObjectContainer();

public:
	virtual void render();
	virtual void update(const double dt);
	
	void addChild( DisplayObjectBase* const entity );
	void removeChild( DisplayObjectBase* entity );
	void releaseChild( DisplayObjectBase* entity );
	void releaseAllChildren();
	int getIndex( const DisplayObjectBase* entity ) const;
	DisplayObjectVec& getChildren();

	virtual void setX( const int x );
	virtual void setY( const int y );

protected:
	void resetRenderPos_();
	
protected:
	DisplayObjectMap _entityMap;
	DisplayObjectVec _entityVec;
};

#endif
