#ifndef ROFL_ASTAR_TRAIL_HPP_INCLUDED
#define ROFL_ASTAR_TRAIL_HPP_INCLUDED

#include <rofl/graph/vertex_descriptor.hpp>
#include <list>

namespace rofl
{
namespace astar
{
typedef std::list
<
	graph::vertex_descriptor
>
trail;
}
}

#endif
