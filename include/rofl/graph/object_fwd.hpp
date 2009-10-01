#ifndef ROFL_GRAPH_OBJECT_FWD_HPP_INCLUDED
#define ROFL_GRAPH_OBJECT_FWD_HPP_INCLUDED

#include <boost/graph/adjacency_list.hpp>

namespace rofl
{
namespace graph
{
class vertex_properties;
class edge_properties;
class properties;

typedef
boost::adjacency_list
<
	boost::setS,
	boost::setS,
	boost::undirectedS,
	vertex_properties,
	edge_properties,
	properties
>
object;
}
}

#endif
