#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <iostream>
#include "Eigen/Dense"
#include "EventDispatcher.h"

class DisplayObjectBase;

class Transform : public EventDispatcher
{
public:
	Transform( DisplayObjectBase* owner );
	~Transform();

public:
	void setPos( const float x, const float y );
	void setX( const float x );
	void setY( const float y );

	void setStageX( const float x );
	void setStageY( const float y );	
	
	void getPos( float& x, float& y );

	float getX();
	float getY();
	float getStageX();
	float getStageY();

	void setRot( const float angle );
	float getRot();

	void setScale( const float x, const float y, const float z = 1.0f );
	void setScaleX( const float scale );
	void setScaleY( const float scale );
	float getScaleX() const;
	float getScaleY() const;	
	
	Eigen::Matrix4f& getLocalMatrix();
	Eigen::Matrix4f& getWorldMatrix();

	void updateWorldTrans();
	void print();
	
private:
	void updateWorldTrans_();

	// inline void refreshMatrix() { matrix_ = ( localTrans_.translation() * localTrans_.rotation() ).matrix(); }
	
private:
	DisplayObjectBase* owner_;
	Eigen::AngleAxisf localRotAngle_;
	Eigen::Vector3f localScale_;
	Eigen::Transform<float, 3, Eigen::Affine> localTrans_;
	Eigen::Transform<float, 3, Eigen::Affine> worldTrans_;
	bool worldTransDirty_;
};

#endif
