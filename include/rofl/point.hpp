#ifndef ROFL_MATH_POINT_HPP_INCLUDED
#define ROFL_MATH_POINT_HPP_INCLUDED

#include <rofl/unit.hpp>
#include <sge/math/vector/static.hpp>

namespace rofl
{
typedef
sge::math::vector::static_
<
	unit,
	2
>::type
point;
}

#endif
