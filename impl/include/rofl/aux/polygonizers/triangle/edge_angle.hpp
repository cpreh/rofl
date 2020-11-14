#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_EDGE_ANGLE_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_EDGE_ANGLE_HPP_INCLUDED

#include <fcppt/math/vector/cross.hpp>


namespace rofl
{
namespace aux
{
namespace polygonizers
{
namespace triangle
{

template<
	typename Vector
>
typename
Vector::value_type
edge_angle(
	Vector const &_a,
	Vector const &_b,
	Vector const &_c
)
{
	return
		fcppt::math::vector::cross(
			_b-_a,
			_c-_b
		);
}

}
}
}
}

#endif
