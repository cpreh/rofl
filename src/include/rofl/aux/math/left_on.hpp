#ifndef ROFL_AUX_MATH_LEFT_ON_HPP_INCLUDED
#define ROFL_AUX_MATH_LEFT_ON_HPP_INCLUDED

#include <rofl/aux/math/area_sign.hpp>


namespace rofl
{
namespace aux
{
namespace math
{

template<
	typename T
>
bool
left_on(
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
		>= 0;
}

}
}
}

#endif
