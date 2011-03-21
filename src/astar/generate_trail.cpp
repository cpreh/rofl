#include <rofl/astar/generate_trail.hpp>
#include <rofl/graph/vertex_iterator.hpp>
#include <boost/graph/astar_search.hpp>
#include "found_goal.hpp"
#include "goal_visitor.hpp"
#include "heuristic.hpp"

void
rofl::astar::generate_trail(
	graph::object const &g,
	graph::vertex_descriptor const &start,
	graph::vertex_descriptor const &goal,
	trail &_trail)
{
	typedef
	std::map
	<
		graph::vertex_descriptor,
		graph::vertex_descriptor
	>
	predecessors;
	
	predecessors p;
		
	try
	{
		typedef 
		boost::property_map
		<
			graph::object, 
			rofl::unit rofl::graph::edge_properties::*
		>::type
		edge_weight_map;
		
		edge_weight_map w = 
			boost::get(
				&rofl::graph::edge_properties::length_, 
				const_cast<graph::object &>(
					g)); 

		boost::astar_search(
			const_cast<graph::object &>(
				g),
			start,
			heuristic(
				g,
				goal),
			predecessor_map(
				boost::associative_property_map<predecessors>(
					p))
			.weight_map(
				w)
			.visitor(goal_visitor(goal)));
	}
	catch (found_goal const &)
	{
	}
	
	for (graph::vertex_descriptor v = goal;;v = p[v])
	{
		_trail.push_front(
			v);
		if (p[v] == v)
			break;
	}
}
