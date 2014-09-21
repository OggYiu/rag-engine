#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Eigen/Dense"

class Transform
{
public:
	Transform();
	~Transform();

public:
	void setPos( const float x, const float y );
	void setX( const float x );
	void setY( const float y );
	
	void getPos( float& x, float& y );
	float getX();
	float getY();
	
	void setRot( const float angle );
	float getRot();

	Eigen::Matrix4f& getMatrix() { return matrix_; }

private:
	void refreshMatrix();
	
private:
	Eigen::Matrix4f matrix_;
	Eigen::Transform<float, 3, Eigen::Affine> translation_;
	Eigen::AngleAxisf rotation_;
};

#endif
