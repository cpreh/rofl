#ifndef ROFL_ASTAR_GENERATE_PATH_HPP_INCLUDED
#define ROFL_ASTAR_GENERATE_PATH_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <rofl/astar/trail.hpp>
#include <rofl/astar/path.hpp>
#include <rofl/point.hpp>

namespace rofl
{
namespace astar
{
void
generate_path(
	graph::object const &,
	trail const &,
	point const &start,
	point const &end,
	path &);
}
}

#endif
