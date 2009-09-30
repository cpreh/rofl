#ifndef ROFL_POLYGONIZERS_TRIANGLE_EDGE_ANGLE_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_EDGE_ANGLE_HPP_INCLUDED

#include <sge/math/vector/cross.hpp>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
template<typename Vector>
typename 
Vector::value_type 
edge_angle(
	Vector const &a,
	Vector const &b,
	Vector const &c)
{
	return
		cross(
			b-a,
			c-b);
}
}
}
}

#endif