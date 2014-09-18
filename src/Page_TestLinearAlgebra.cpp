#include "Page_TestLinearAlgebra.h"

#include <iostream>
#include "Eigen/Dense"

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

	Eigen::MatrixXd m( 2, 2 );
	m( 0, 0 ) = 3;
	m( 1, 0 ) = 2.5;
	m( 0, 1 ) = -1;
	m( 1, 1 ) = m( 1, 0 ) + m( 0, 1 );
	std::cout << m << std::endl;

	Eigen::VectorXd v(2);
	v << 1.5f, 2;
	int value0 = v(0);
	int value1 = v(1);
	std::cout << value0 << ", " << value1 << std::endl;
	return true;
}


