#ifndef ROFL_GRAPH_FIND_ADJACENT_HPP_INCLUDED
#define ROFL_GRAPH_FIND_ADJACENT_HPP_INCLUDED

#include "placement.hpp"
#include <rofl/indexed_point.hpp>
#include <rofl/indexed_polygon.hpp>
#include <utility>

namespace rofl
{
namespace graph
{
std::pair
<
	indexed_point,
	placement::type
> const
find_adjacent(
	indexed_polygon const &,
	indexed_point const &,
	indexed_point const &);
}
}

#endif
