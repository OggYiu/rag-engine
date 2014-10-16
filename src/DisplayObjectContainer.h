#ifndef __DISPLAYOBJECTCONTAINER_H__
#define __DISPLAYOBJECTCONTAINER_H__

#include <string>
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
	
	virtual void addChild( DisplayObjectBase* const entity );
	virtual void setClipRect( const int x, const int y, const int width, const int height );	
	void removeChild( DisplayObjectBase* entity );
	void removeChildAt( const int index );
	void releaseChild( DisplayObjectBase* entity );
	void releaseChildAt( const int index );
	void releaseAllChildren();
	int getIndex( const DisplayObjectBase* entity ) const;
	DisplayObjectVec& getChildren();
	virtual void updateBoundingBox();
	void handleTransformEvent();
	// void foo();
	
protected:
	virtual void updateBoundingBox_();
	void updateAllWorldTrans_();
	// void resetAllChildrenClipRect();
	// void resetAllChildrenClipRect_();
	
	DisplayObjectMap _entityMap;
	DisplayObjectVec _entityVec;
	bool needResetAllChildrenClipRect_;
};

#endif
