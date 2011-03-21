#ifndef ROFL_MATH_AREA_SIGN_HPP_INCLUDED
#define ROFL_MATH_AREA_SIGN_HPP_INCLUDED

//#include <fcppt/math/vector/cross.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

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
// cross: l.x() * r.y() - l.y() * r.x()
	typename T::value_type 
	area2 = 
		(b-a).x() * (c-a).y() - (b-a).y() * (c-a).y();
#if 0
		fcppt::math::vector::cross(
			b-a,
			c-a);
#endif

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
