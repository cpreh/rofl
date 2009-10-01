#ifndef ROFL_POLYGONIZERS_TRIANGLE_LINE_SEGMENTS_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_LINE_SEGMENTS_HPP_INCLUDED

#include <rofl/math/line_segment.hpp>
#include <rofl/math/polygon.hpp>
#include <vector>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
template<typename T>
std::vector
<
	math::line_segment<T>
> const
line_segments(
	math::polygon<T> const &p)
{
	std::vector < math::line_segment<T> > segments;
	for (typename math::polygon<T>::const_iterator i = p.begin(); i != p.end(); ++i)
	{
		T const &next = 
			i == boost::prior(p.end())
			?
				p.front()
			:
				*boost::next(i);
		segments.push_back(
			math::line_segment<T>(
				*i,
				next));
	}
	return segments;
}
}
}
}

#endif
