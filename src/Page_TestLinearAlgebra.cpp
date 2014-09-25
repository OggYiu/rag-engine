#include "Page_TestLinearAlgebra.h"

#include <iostream>
#include "Eigen/Dense"

#include "Transform.h"

Page_TestLinearAlgebra::Page_TestLinearAlgebra()
{
}

Page_TestLinearAlgebra::~Page_TestLinearAlgebra()
{
}

void Page_TestLinearAlgebra::update(const double dt)
{
	Page::update( dt );
}

void Page_TestLinearAlgebra::render()
{
	Page::render();
}

bool Page_TestLinearAlgebra::resolved()
{
	Page::resolved();

	// Eigen::Affine2f trans( Eigen::Translation2f( 150, 50 ) );
	// Eigen::Matrix3f m = trans.matrix();
	// std::cout << "matrix3f: " << m << std::endl;

	return true;
}
