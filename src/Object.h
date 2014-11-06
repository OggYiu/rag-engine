#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object
{
private:
	static int s_nextId;
	
public:
	Object();
	virtual ~Object();

public:
	virtual void update(const double dt);
	int getId() { return id_; }
	
protected:
	virtual void resolved() {}
	
public:
	int id_;
	bool updated_;
};

#endif
