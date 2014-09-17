#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void update(const double dt);
	int getId() const;
	bool isReleased() const { return released_; }
	
protected:
	virtual bool resolved() { return true; }
	
public:
	bool released_;
	bool updated_;
	double age_;
	int id_;
	static int s_nextObjectId;
};

#endif
