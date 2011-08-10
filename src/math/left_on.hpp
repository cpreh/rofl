#ifndef ROFL_MATH_LEFT_ON_HPP_INCLUDED
#define ROFL_MATH_LEFT_ON_HPP_INCLUDED

#include "area_sign.hpp"

namespace rofl
{
namespace math
{
template<typename T>
bool left_on(
	T const &a,
	T const &b,
	T const &c)
{
	return
		area_sign(
			a,
			b,
			c) >= 0;
}
}
}

#endif
