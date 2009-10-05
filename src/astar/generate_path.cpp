#include <rofl/astar/generate_path.hpp>
#include <rofl/graph/vertex_iterator.hpp>
#include <boost/graph/astar_search.hpp>
#include "found_goal.hpp"
#include "goal_visitor.hpp"
#include "heuristic.hpp"

void
rofl::astar::generate_path(
	graph::object const &g,
	graph::vertex_descriptor const &start,
	graph::vertex_descriptor const &goal,
	path &_path)
{
	typedef
	std::map
	<
		graph::vertex_descriptor,
		graph::vertex_descriptor
	>
	predecessors;
	
	predecessors p;
	boost::associative_property_map<predecessors> pp(
		p);
		
	typedef
	std::map
	<
		graph::vertex_descriptor,
		unsigned
	>
	vertex_index_map;
	
	vertex_index_map vi;
	boost::associative_property_map<vertex_index_map> vip(
		vi);
	
	std::size_t i = 0;
	for(
		std::pair
		<
			graph::vertex_iterator,
			graph::vertex_iterator
		> p = boost::vertices(
			g);
		p.first != p.second;
		++p.first)
		vi[*p.first] = i++;
	
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
			boost::visitor(
				goal_visitor(
					goal)).
			weight_map(
				w).
			predecessor_map(
				pp).
			visitor(
				goal_visitor(
					goal)).
			vertex_index_map(
				vip));
	}
	catch (found_goal const &)
	{
	}
	
	for (graph::vertex_descriptor v = goal;;v = p[v])
	{
		_path.push_front(
			v);
		if (p[v] == v)
			break;
	}
}