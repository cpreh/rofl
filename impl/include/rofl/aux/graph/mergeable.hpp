#ifndef ROFL_AUX_GRAPH_MERGEABLE_HPP_INCLUDED
#define ROFL_AUX_GRAPH_MERGEABLE_HPP_INCLUDED

#include <rofl/indexed_line_segment_fwd.hpp>
#include <rofl/indexed_polygon_fwd.hpp>


namespace rofl
{
namespace aux
{
namespace graph
{

bool
mergeable(
	rofl::indexed_polygon const &,
	rofl::indexed_polygon const &,
	rofl::indexed_line_segment const &
);

}
}
}

#endif
