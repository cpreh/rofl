#include <rofl/astar/generate_trail.hpp>
#include <rofl/astar/trail.hpp>
#include <rofl/aux/astar/found_goal.hpp>
#include <rofl/aux/astar/goal_visitor.hpp>
#include <rofl/aux/astar/heuristic.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_iterator.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/graph/astar_search.hpp>
#include <boost/graph/properties.hpp>
#include <fcppt/config/external_end.hpp>


rofl::astar::trail
rofl::astar::generate_trail(
	graph::object const &_graph,
	graph::vertex_descriptor const &_start,
	graph::vertex_descriptor const &_goal
)
{
	typedef
	std::map
	<
		rofl::graph::vertex_descriptor,
		rofl::graph::vertex_descriptor
	>
	predecessors;

	predecessors preds;

	try
	{
		typedef
		boost::property_map
		<
			rofl::graph::object,
			rofl::unit rofl::graph::edge_properties::*
		>::type
		edge_weight_map;

		edge_weight_map const weight(
			boost::get(
				&rofl::graph::edge_properties::length_,
				const_cast<
					rofl::graph::object &
				>(
					_graph
				)
			)
		);

		boost::astar_search(
			const_cast<
				rofl::graph::object &
			>(
				_graph
			),
			_start,
			rofl::aux::astar::heuristic(
				_graph,
				_goal
			),
			// TODO: where does this come from?
			predecessor_map(
				// TODO: and this?
				boost::associative_property_map<
					predecessors
				>(
					preds
				)
			)
			.weight_map(
				weight
			)
			.visitor(
				rofl::aux::astar::goal_visitor(
					_goal
				)
			)
		);
	}
	catch(
		rofl::aux::astar::found_goal const &
	)
	{
	}

	rofl::astar::trail ret;

	for(
		rofl::graph::vertex_descriptor vertex = _goal;
		;
		vertex = preds[vertex]
	)
	{
		ret.push_front(
			vertex
		);

		if(
			preds[vertex]
			==
			vertex
		)
			break;
	}

	return
		ret;
}
