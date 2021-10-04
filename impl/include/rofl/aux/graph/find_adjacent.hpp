#ifndef ROFL_AUX_GRAPH_FIND_ADJACENT_HPP_INCLUDED
#define ROFL_AUX_GRAPH_FIND_ADJACENT_HPP_INCLUDED

#include <rofl/indexed_point_fwd.hpp>
#include <rofl/indexed_polygon_fwd.hpp>
#include <rofl/aux/graph/placement_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace rofl::aux::graph
{

std::pair<
	rofl::indexed_point,
	rofl::aux::graph::placement
>
find_adjacent(
	rofl::indexed_polygon const &,
	rofl::indexed_point const &,
	rofl::indexed_point const &
);

}

#endif
