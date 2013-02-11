#ifndef ROFL_ASTAR_GENERATE_PATH_HPP_INCLUDED
#define ROFL_ASTAR_GENERATE_PATH_HPP_INCLUDED

#include <rofl/point_fwd.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <rofl/astar/path.hpp>
#include <rofl/astar/trail.hpp>


namespace rofl
{
namespace astar
{

rofl::astar::path
generate_path(
	rofl::graph::object const &,
	rofl::astar::trail const &,
	rofl::point const &start,
	rofl::point const &end
);

}
}

#endif
