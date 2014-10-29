#include "Demo_DisplayObject.h"

#include "DisplayObject.h"
#include "Primitive.h"
#include "TextureMgr.h"
#include "GUI_Label.h"
#include "Eigen/Dense"
#include "Eigen/Geometry"

Eigen::Translation3f translate( 0, 0, 0  );
Eigen::AngleAxisf angle;
Eigen::DiagonalMatrix<float, 3> scale;
Eigen::Transform<float, 3, Eigen::Affine> t1;
Eigen::Transform<float, 3, Eigen::Affine> t2;
Eigen::Matrix4f matrix;

// Eigen::Matrix4f& getMatrix()
// {
// 	// std::cout << translate * worldTransform_.matrix();
// 	return t1.matrix();
// }

static void demo1( Demo_Base* container )
{
	container->releaseAllChildren();

	angle = ( Eigen::AngleAxisf( 0.0f, Eigen::Vector3f::UnitZ() ) );
	scale = Eigen::Scaling( 1.1f, 1.2f, 1.3f );
	// scale.diagonal()[0] = 2.1f;
	// std::cout << "scale !!!!: " << scale.diagonal()[0] << ", " << scale.diagonal()[1] << ", " << scale.diagonal()[2] << std::endl;
	// scale.x() = scale.y() = scale.z() = 1.0f;
	
	// t1 = translate * angle * scale;
	// std::cout << "t1: " << std::endl;
	// std::cout << t1.matrix() << std::endl;

	// t2 = t1;
	// std::cout << "t2 1: " << std::endl;
	// std::cout << t2.matrix() << std::endl;

	// translate.x() = 100.0f;
	// t2 = t1 * translate;
	// std::cout << "t2 2: " << std::endl;
	// std::cout << t2.matrix() << std::endl;
	
	// matrix = t.matrix();

	// std::cout << "transform: " << std::endl;
	// std::cout << matrix << std::endl;

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		SolidCircle shape( 0, 0, 50, 0xFF000000 );		
		Texture* texture = textureMgr.createPrimitiveTexture( shape );
		obj->setTexture( texture );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "primitive as display object", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

static void demo2( Demo_Base* container )
{
	container->releaseAllChildren();

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		DisplayObject* obj = new DisplayObject();
		// SolidCircle shape( 50, 50, 50, 0xFFFFFF00 );
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "image as display object", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

static DisplayObject* target_ = nullptr;
static float rot_ = 0.0f;

static void demo3( Demo_Base* container )
{
	container->releaseAllChildren();

	DisplayObjectContainer* parent = new DisplayObjectContainer();
	container->addChild( parent );
	container->drawFrame( parent );
	
	{
		// draw shape to display object
		target_ = new DisplayObject();
		DisplayObject* obj = target_;
		// SolidCircle shape( 50, 50, 50, 0xFFFFFF00 );
		Texture* texture = textureMgr.createImageTexture( "assets/alex.png" );
		obj->setTexture( texture );
		obj->transform().setPos( 200, 200 );
		parent->addChild( obj );
	}

	{
		GUI_Label* label = new GUI_Label( 0, 0, "rotate as display object", 8 );
		label->transform().setPos( 30, 30 );
		container->addChild( label );
	}
}

Demo_DisplayObject::Demo_DisplayObject()
{
}

Demo_DisplayObject::~Demo_DisplayObject()
{
}

void Demo_DisplayObject::update(const double dt)
{
	Demo_Base::update( dt );
	if ( target_ != nullptr ) {
 		// std::cout << "dt: " << dt << std::endl;
		rot_ += dt * 100;
		// std::cout << "rot: " << rot_ << std::endl;
		target_->transform().setRot( rot_ );
	}
}

bool Demo_DisplayObject::resolved()
{
	addDemo( demo1 );
	addDemo( demo2 );
	addDemo( demo3 );		
	
	return Demo_Base::resolved();
}
