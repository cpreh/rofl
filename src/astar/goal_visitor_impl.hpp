#include "found_goal.hpp"

rofl::astar::goal_visitor::goal_visitor(
	graph::vertex_descriptor const &_goal)
:
	goal_(
		_goal)
{
}

void 
rofl::astar::goal_visitor::examine_vertex(
	graph::vertex_descriptor const &v,
	graph::object const &)
{
	if (v == goal_)
		throw found_goal();
}
