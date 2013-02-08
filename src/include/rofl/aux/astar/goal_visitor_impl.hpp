#ifndef ROFL_AUX_ASTAR_GOAL_VISITOR_IMPL_HPP_INCLUDED
#define ROFL_AUX_ASTAR_GOAL_VISITOR_IMPL_HPP_INCLUDED

#include <rofl/aux/astar/found_goal.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <rofl/graph/vertex_descriptor.hpp>


rofl::aux::astar::goal_visitor::goal_visitor(
	rofl::graph::vertex_descriptor const &_goal)
:
	goal_(
		_goal
	)
{
}

void
rofl::aux::astar::goal_visitor::examine_vertex(
	rofl::graph::vertex_descriptor const &_vertex,
	rofl::graph::object const &
)
{
	if(
		_vertex == goal_
	)
		throw rofl::aux::astar::found_goal();
}

#endif
