#ifndef ROFL_ASTAR_TRAIL_HPP_INCLUDED
#define ROFL_ASTAR_TRAIL_HPP_INCLUDED

#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <fcppt/config/external_end.hpp>


namespace rofl::astar
{

using
trail
=
std::list<
	rofl::graph::vertex_descriptor
>;

}

#endif
