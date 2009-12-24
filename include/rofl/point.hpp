#ifndef ROFL_MATH_POINT_HPP_INCLUDED
#define ROFL_MATH_POINT_HPP_INCLUDED

#include <rofl/unit.hpp>
#include <fcppt/math/vector/static.hpp>

namespace rofl
{
typedef
fcppt::math::vector::static_
<
	unit,
	2
>::type
point;
}

#endif
