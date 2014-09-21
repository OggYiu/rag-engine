#include "Transform.h"

#include <iostream>
#include <math.h>

Transform::Transform()
	: matrix_( Eigen::Matrix4f::Identity() )
{
	// matrix_ = Eigen::Matrix4f::Identity();
	translation_ = Eigen::Translation3f( 0.0f, 0.0f, 0.0f );
	rotation_ = Eigen::AngleAxisf( 0.0f, Eigen::Vector3f::UnitZ() );
}

Transform::~Transform()
{
}

void Transform::setPos( const float x, const float y )
{
	translation_.translation().x() = x;
	translation_.translation().y() = y;	
}

void Transform::setX( const float x )
{
	translation_.translation().x() = x;
}

void Transform::setY( const float y )
{
	translation_.translation().y() = y;
}
	
void Transform::getPos( float& x, float& y )	
{
	x = translation_.translation().x();
	y = translation_.translation().y();
}

float Transform::getX()
{
	return translation_.translation().x();
}

float Transform::getY()
{
	return translation_.translation().y();
}
	
void Transform::setRot( const float angle )
{
	rotation_.angle() = angle;// = Eigen::AngleAxisf( angle, Eigen::Vector3f::UnitZ() );
}

float Transform::getRot()
{
	return rotation_.angle();
}

void Transform::refreshMatrix()
{
	matrix_ = ( translation_ * rotation_ ).matrix();
}
