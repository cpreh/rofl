#ifndef ROFL_POLYGONIZERS_TRIANGLE_TRIANGLE_LINE_SEGMENTS_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_TRIANGLE_LINE_SEGMENTS_HPP_INCLUDED

#include <rofl/line_segment.hpp>
#include <tr1/array>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
typedef
std::tr1::array
<
	line_segment,
	3
>
triangle_line_segments;
}
}
}

#endif