#include "Transform.h"

#include <math.h>
#include "Helper.h"
#include "DisplayObjectBase.h"
#include "DisplayObjectContainer.h"
#include "TransformEvent.h"

Transform::Transform( DisplayObjectBase* owner )
	: owner_( owner )
	, localTranslate_( 0.0f, 0.0f, 0.0f )
	, localRotAngle_( Eigen::AngleAxisf( 0.0f, Eigen::Vector3f::UnitZ() ) )
	, localScale_( Eigen::Scaling( 1.0f, 1.0f, 1.0f ) )
	, localTransform_( Eigen::Transform<float, 3, Eigen::Affine>::Identity() )
	, worldTransform_( Eigen::Transform<float, 3, Eigen::Affine>::Identity() )	  
{
	updateLocalTransform();
	updateWorldTransform();
}

Transform::~Transform()
{
}

void Transform::setPos( const float x, const float y ) {
	localTranslate_.x() = x;
	localTranslate_.y() = y;

	updateLocalTransform();
	updateWorldTransform();
	
	TransformEvent transformEvent( TransformEvent::TRANSFORM_POSITION_CHANGED, *this );
	this->dispatchEvent( transformEvent );
}

void Transform::setX( const float x ) {
	setPos( x, localTranslate_.y() );
}
	
void Transform::setY( const float y ) {
	setPos( localTranslate_.x(), y );	
}

void Transform::setStagePos( const float x, const float y )
{
	float localX, localY;
	worldToLocalPos( x, y, localX, localY );
	setPos( localX, localY );
}

void Transform::setStageX( const float x )
{
	setStagePos( x, getStageY() );
}

void Transform::setStageY( const float y )
{
	setStagePos( getStageX(), y );	
}
	
void Transform::getPos( float& x, float& y ) {
	x = localTranslate_.x();
	y = localTranslate_.y();
}

float Transform::getX()
{
	return localTranslate_.x();
}

float Transform::getY()
{
	return localTranslate_.y();
}

void Transform::getStagePos( float& x, float& y )
{
	x = worldTransform_.translation().x();
	y = worldTransform_.translation().y();
}

float Transform::getStageX()
{
	return worldTransform_.translation().x();
}

float Transform::getStageY()
{
	return worldTransform_.translation().y();
}

void Transform::setRot( const float angle )
{
	localRotAngle_.angle() = angle;
	updateLocalTransform();
	updateWorldTransform();
	
	TransformEvent transformEvent( TransformEvent::TRANSFORM_ROTATION_CHANGED, *this );
	this->dispatchEvent( transformEvent );
}

float Transform::getRot()
{
	return localRotAngle_.angle();
}

void Transform::setScale( const float x, const float y, const float z )
{
	localScale_.diagonal()[0] = x;
	localScale_.diagonal()[1] = y;
	localScale_.diagonal()[2] = z;
	
	updateLocalTransform();
	updateWorldTransform();

	TransformEvent transformEvent( TransformEvent::TRANSFORM_SCALE_CHANGED, *this );
	this->dispatchEvent( transformEvent );
}

void Transform::setScaleX( const float scale )
{
	setScale( scale, localScale_.diagonal()[1], localScale_.diagonal()[2] );
}

void Transform::setScaleY( const float scale )
{
	setScale( localScale_.diagonal()[0], scale, localScale_.diagonal()[2] );
}

void Transform::setScaleZ( const float scale )
{
	setScale( localScale_.diagonal()[0], localScale_.diagonal()[1], scale );
}

float Transform::getScaleX() const
{
	return localScale_.diagonal()[0];
}

float Transform::getScaleY() const
{
	return localScale_.diagonal()[1];
}

float Transform::getScaleZ() const
{
	return localScale_.diagonal()[2];
}
	
// Eigen::Matrix4f& Transform::getLocalMatrix()
// {
// 	return localTransform_.matrix();
// }

// Eigen::Matrix4f& Transform::getWorldMatrix()
// {
// 	return worldTransform_.matrix();
// }

Eigen::Transform<float, 3, Eigen::Affine>& Transform::getLocalTransform()
{
	return localTransform_;
}

Eigen::Transform<float, 3, Eigen::Affine>& Transform::getWorldTransform()
{
	return worldTransform_;
}

void Transform::worldToLocalPos( const float worldX, const float worldY, float& localX, float& localY )
{
	float stageX, stageY;
	this->getStagePos( stageX, stageY );
	localX = worldX - stageX;
	localY = worldY - stageY;
}

void Transform::localToWorldPos( const float localX, const float localY, float& worldX, float& worldY )
{
	if ( owner_->getParent() != nullptr ) {
		float parentX, parentY;
		owner_->getParent()->transform().getStagePos( parentX, parentY );
		worldX = parentX + localX;
		worldY = parentY + localY;		
	} else {
		worldX = localX;
		worldY = localY;
	}
}

void Transform::updateLocalTransform()
{
	localTransform_ = localTranslate_ * localRotAngle_ * localScale_;
}

void Transform::updateWorldTransform()
{
	if ( owner_->getParent() != nullptr ) {
		worldTransform_ = localTransform_ * owner_->getParent()->transform().getWorldTransform();
	} else {
		worldTransform_ = localTransform_;
	}
}

void Transform::print()
{
	std::cout << "transform print ------" << std::endl;
	std::cout << "lorcalTrans: " << std::endl << localTransform_.matrix() << std::endl << std::endl;
	std::cout << "worldtrans: " << std::endl << worldTransform_.matrix() << std::endl << std::endl;
}
