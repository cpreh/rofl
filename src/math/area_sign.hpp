#ifndef ROFL_MATH_AREA_SIGN_HPP_INCLUDED
#define ROFL_MATH_AREA_SIGN_HPP_INCLUDED

#include <sge/math/vector/cross.hpp>
#include <sge/math/vector/arithmetic.hpp>

namespace rofl
{
namespace math
{
template<typename T>
int area_sign(
	T const &a,
	T const &b,
	T const &c)
{
	typename T::value_type 
	area2 = 
		sge::math::vector::cross(
			b-a,
			c-a);

	if (area2 > static_cast<typename T::value_type>(0.5)) 
		return 1;

	return 
		area2 < static_cast<typename T::value_type>(-0.5)
		?
			-1
		: 
			0;

}
}
}

#endif
