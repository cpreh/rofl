#ifndef ROFL_POLYGONIZERS_TRIANGLE_LINE_SEGMENTS_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_LINE_SEGMENTS_HPP_INCLUDED

#include <rofl/math/line_segment.hpp>
#include <rofl/math/polygon.hpp>
#include <sge/assert.hpp>
#include <sge/assign/make_array.hpp>
#include <tr1/array>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
template<typename T>
std::tr1::array
<
	math::line_segment<T>,
	3
> const
line_segments(
	math::polygon<T> const &p)
{
	SGE_ASSERT(p.size() == 3);
	return 
		sge::assign::make_array
		<
			math::line_segment<T>
		>
			(math::line_segment<T>(p[0],p[1]))
			(math::line_segment<T>(p[1],p[2]))
			(math::line_segment<T>(p[2],p[0]));
}
}
}
}

#endif