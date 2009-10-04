#ifndef ROFL_GRAPH_ON_BOUNDARY_HPP_INCLUDED
#define ROFL_GRAPH_ON_BOUNDARY_HPP_INCLUDED

#include <rofl/math/line_segment.hpp>

namespace rofl
{
namespace graph
{
template<typename T>
bool on_boundary(
	T const &p,
	rofl::math::line_segment<T> const &l)
{
	return 
		p == l.start() || p == l.end();
}

}
}

#endif