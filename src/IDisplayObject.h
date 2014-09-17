#ifndef __DISPLAYOBJECTBASE_H__
#define __DISPLAYOBJECTBASE_H__

class DisplayObjectBase
{
public:
	DisplayObjectBase();
	virtual ~DisplayObjectBase();
	
public:
	virtual void render() = 0;
};

#endif
