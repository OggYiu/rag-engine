#ifndef __DISPLAYOBJECTCONTAINER_H__
#define __DISPLAYOBJECTCONTAINER_H__

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

protected:
	virtual void updateBoundingBox_();
	void updateAllWorldTrans_();
	virtual void handleTransformPositionChanged_();
	virtual void handleTransformRotationChanged_();
	virtual void handleTransformScaleChanged_();
	
	DisplayObjectMap _entityMap;
	DisplayObjectVec _entityVec;
};

#endif
