#include "Transform.h"

#include <math.h>
#include "Helper.h"
#include "DisplayObjectBase.h"
#include "DisplayObjectContainer.h"
#include "TransformEvent.h"

Transform::Transform( DisplayObjectBase* owner )
	: owner_( owner )
	, localRotAngle_( Eigen::AngleAxisf( 0.0f, Eigen::Vector3f::UnitZ() ) )
{
	// {
	// 	localTrans_.matrix().setIdentity();
	// 	worldTrans_.matrix().setIdentity();

	// 	localTrans_.translation().x() = 120;
	// 	localTrans_.translation().y() = 60;

	// 	worldTrans_.translation().x() = 60;
	// 	worldTrans_.translation().y() = 20;

	// 	std::cout << "matrix: " << std::endl << ( worldTrans_ * localTrans_ ).matrix() << std::endl << std::endl;
	// }
	
	localTrans_.matrix().setIdentity();

	setScale( 1.0f, 1.0f, 1.0f );
	// print();
	updateWorldTrans();
}

Transform::~Transform()
{
}

void Transform::setPos( const float x, const float y ) {
	localTrans_.translation().x() = x;
	localTrans_.translation().y() = y;
	updateWorldTrans();
	this->dispatchEvent( TransformEvent( TransformEvent::TRANSFORM_POSITION_CHANGED, *this ) );
}

void Transform::setX( const float x ) {
	// std::cout << "transform, setx: " << x << std::endl;
	localTrans_.translation().x() = x;
	updateWorldTrans();
	this->dispatchEvent( TransformEvent( TransformEvent::TRANSFORM_POSITION_CHANGED, *this ) );
}
	
void Transform::setY( const float y ) {
	localTrans_.translation().y() = y;
	updateWorldTrans();
	this->dispatchEvent( TransformEvent( TransformEvent::TRANSFORM_POSITION_CHANGED, *this ) );
}

// void Transform::setStageX( const float x )
// {
// 	worldTransDirty_ = true;
// 	updateWorldTrans();
// 	setX( x- worldTrans_.translation().x );
// }

// void Transform::setStageY( const float y )
// {
// 	worldTransDirty_ = true;
// 	updateWorldTrans();
// 	setX( x- worldTrans_.translation().x );
// }
	
void Transform::getPos( float& x, float& y ) {
	x = localTrans_.translation().x();
	y = localTrans_.translation().y();
}

float Transform::getX()
{
	return localTrans_.translation().x();
}

float Transform::getY()
{
	return localTrans_.translation().y();
}

float Transform::getStageX()
{
	updateWorldTrans_();
	return worldTrans_.translation().x();
}

float Transform::getStageY()
{
	updateWorldTrans_();
	return worldTrans_.translation().y();
}

void Transform::setRot( const float angle )
{
	localRotAngle_.angle() = angle;
	localTrans_.rotate( localRotAngle_ );
	updateWorldTrans();
	this->dispatchEvent( TransformEvent( TransformEvent::TRANSFORM_ROTATION_CHANGED, *this ) );
}

float Transform::getRot()
{
	return localRotAngle_.angle();
}

void Transform::setScale( const float x, const float y, const float z )
{
	localScale_.x() = x;
	localScale_.y() = y;
	localScale_.z() = z;
	// std::cout << "setscale : " <<  localScale_.x() << ", " << localScale_.y() << ", " << localScale_.z() << std::endl;
	localTrans_.scale( localScale_ );
	updateWorldTrans();
	this->dispatchEvent( TransformEvent( TransformEvent::TRANSFORM_SCALE_CHANGED, *this ) );
}

void Transform::setScaleX( const float scale )
{
	localScale_.x() = scale;
	localTrans_.scale( localScale_ );
	updateWorldTrans();
	this->dispatchEvent( TransformEvent( TransformEvent::TRANSFORM_SCALE_CHANGED, *this ) );	
}

void Transform::setScaleY( const float scale )
{
	localScale_.y() = scale;
	localTrans_.scale( localScale_ );
	updateWorldTrans();
	this->dispatchEvent( TransformEvent( TransformEvent::TRANSFORM_SCALE_CHANGED, *this ) );	
}

float Transform::getScaleX() const
{
	return localScale_.x();
}

float Transform::getScaleY() const
{
	return localScale_.y();
}
	
Eigen::Matrix4f& Transform::getLocalMatrix()
{
	return localTrans_.matrix();
}

Eigen::Matrix4f& Transform::getWorldMatrix()
{
	updateWorldTrans_();
	return worldTrans_.matrix();
}

void Transform::updateWorldTrans()
{
	worldTransDirty_ = true;
}

void Transform::print()
{
	updateWorldTrans();
	updateWorldTrans_();
	std::cout << "transform print ------" << std::endl;
	std::cout << "lorcalTrans: " << std::endl << localTrans_.matrix() << std::endl << std::endl;
	std::cout << "worldtrans: " << std::endl << worldTrans_.matrix() << std::endl << std::endl;
}

void Transform::updateWorldTrans_()
{
	if ( !worldTransDirty_ ) {
		return;
	}
	
	worldTransDirty_ = false;
	if ( owner_->getParent() != nullptr ) {
		worldTrans_ = localTrans_ * owner_->getParent()->transform().getWorldMatrix();
	} else {
		worldTrans_ = localTrans_;
	}
}
