#ifndef ROFL_ASTAR_GENERATE_TRAIL_HPP_INCLUDED
#define ROFL_ASTAR_GENERATE_TRAIL_HPP_INCLUDED

#include <rofl/symbol.hpp>
#include <rofl/astar/trail.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <rofl/graph/vertex_descriptor.hpp>


namespace rofl
{
namespace astar
{

ROFL_SYMBOL
rofl::astar::trail
generate_trail(
	rofl::graph::object const &,
	rofl::graph::vertex_descriptor const &,
	rofl::graph::vertex_descriptor const &
);

}
}

#endif
