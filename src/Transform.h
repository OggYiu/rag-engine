#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <iostream>
#include "Eigen/Dense"
#include "Eigen/Geometry"
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

	void setStagePos( const float x, const float y );
	void setStageX( const float x );
	void setStageY( const float y );	
	
	void getPos( float& x, float& y );
	float getX();
	float getY();

	void getStagePos( float& x, float& y );
	float getStageX();
	float getStageY();

	void setRot( const float angle );
	float getRot();

	void setScale( const float x, const float y, const float z = 1.0f );
	void setScaleX( const float scale );
	void setScaleY( const float scale );
	void setScaleZ( const float scale );	
	float getScaleX() const;
	float getScaleY() const;
	float getScaleZ() const;	
	
    // Eigen::Matrix4f& getLocalMatrix();
    // Eigen::Matrix4f& getWorldMatrix();
	
    Eigen::Transform<float, 3, Eigen::Affine>& getLocalTransform();
    Eigen::Transform<float, 3, Eigen::Affine>& getWorldTransform();

	void worldToLocalPos( const float worldX, const float worldY, float& localX, float& localY );
	void localToWorldPos( const float localX, const float localY, float& worldX, float& worldY );
	void updateLocalTransform();
	void updateWorldTransform();
	void print();
	
private:
	DisplayObjectBase* owner_;
	Eigen::Translation3f localTranslate_;
	Eigen::AngleAxisf localRotAngle_;
	Eigen::DiagonalMatrix<float, 3> localScale_;
	Eigen::Transform<float, 3, Eigen::Affine> localTransform_;
	Eigen::Transform<float, 3, Eigen::Affine> worldTransform_;
};

#endif
