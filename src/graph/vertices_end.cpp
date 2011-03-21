#include <rofl/graph/vertices_end.hpp>

rofl::graph::vertex_iterator const rofl::graph::vertices_end(
	object &o)
{
	return 
		boost::vertices(
			o).second;
}

rofl::graph::const_vertex_iterator const rofl::graph::vertices_end(
	object const &o)
{
	return 
		boost::vertices(
			o).second;
}
