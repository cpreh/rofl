#ifndef ROFL_ASTAR_GENERATE_PATH_HPP_INCLUDED
#define ROFL_ASTAR_GENERATE_PATH_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <rofl/astar/path.hpp>

namespace rofl
{
namespace astar
{
void
generate_path(
	graph::object const &,
	graph::vertex_descriptor const &,
	graph::vertex_descriptor const &,
	path &);
}
}

#endif