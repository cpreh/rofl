#include <rofl/graph/vertices_begin.hpp>

rofl::graph::vertex_iterator const rofl::graph::vertices_begin(
	object &o)
{
	return 
		boost::vertices(
			o).first;
}

rofl::graph::const_vertex_iterator const rofl::graph::vertices_begin(
	object const &o)
{
	return 
		boost::vertices(
			o).first;
}