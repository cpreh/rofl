#ifndef ROFL_AUX_MATH_LEFT_HPP_INCLUDED
#define ROFL_AUX_MATH_LEFT_HPP_INCLUDED

#include <rofl/aux/math/area_sign.hpp>


namespace rofl::aux::math
{

template<
	typename T
>
bool
left(
	T const &_a,
	T const &_b,
	T const &_c
)
{
	return
		rofl::aux::math::area_sign(
			_a,
			_b,
			_c
		)
		> 0;
}

}

#endif
