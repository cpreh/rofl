#include <rofl/graph/const_vertex_iterator.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_iterator.hpp>
#include <rofl/graph/vertices_begin.hpp>


rofl::graph::vertex_iterator const
rofl::graph::vertices_begin(
	rofl::graph::object &_graph
)
{
	return
		boost::vertices(
			_graph
		).first;
}

rofl::graph::const_vertex_iterator const
rofl::graph::vertices_begin(
	rofl::graph::object const &_graph
)
{
	return
		boost::vertices(
			_graph
		).first;
}
