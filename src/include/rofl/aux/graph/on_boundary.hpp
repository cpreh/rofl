#ifndef ROFL_AUX_GRAPH_ON_BOUNDARY_HPP_INCLUDED
#define ROFL_AUX_GRAPH_ON_BOUNDARY_HPP_INCLUDED

#include <rofl/math/line_segment_impl.hpp>


namespace rofl
{
namespace aux
{
namespace graph
{

template<
	typename T
>
bool
on_boundary(
	T const &_point,
	rofl::math::line_segment<
		T
	> const &_line
)
{
	return
		_point == _line.start()
		||
		_point == _line.end();
}

}
}
}

#endif
