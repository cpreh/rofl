#ifndef ROFL_ASTAR_TRAIL_HPP_INCLUDED
#define ROFL_ASTAR_TRAIL_HPP_INCLUDED

#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace astar
{

typedef std::list
<
	rofl::graph::vertex_descriptor
>
trail;

}
}

#endif
