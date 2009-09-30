#ifndef ROFL_GRAPH_OBJECT_HPP_INCLUDED
#define ROFL_GRAPH_OBJECT_HPP_INCLUDED

#include <rofl/graph/edge_properties.hpp>
#include <rofl/graph/vertex_properties.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace rofl
{
namespace graph
{
typedef
boost::adjacency_list
<
	boost::vecS,
	boost::vecS,
	boost::undirectedS,
	vertex_properties,
	edge_properties
>
object;
}
}

#endif
