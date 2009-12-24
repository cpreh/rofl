#ifndef ROFL_ASTAR_GENERATE_TRAIL_HPP_INCLUDED
#define ROFL_ASTAR_GENERATE_TRAIL_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <rofl/astar/trail.hpp>

namespace rofl
{
namespace astar
{
void
generate_trail(
	graph::object const &,
	graph::vertex_descriptor const &,
	graph::vertex_descriptor const &,
	trail &);
}
}

#endif