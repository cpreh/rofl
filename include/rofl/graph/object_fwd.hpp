#ifndef ROFL_GRAPH_OBJECT_FWD_HPP_INCLUDED
#define ROFL_GRAPH_OBJECT_FWD_HPP_INCLUDED

#define BOOST_NO_HASH
#include <boost/graph/adjacency_list.hpp>

namespace rofl
{
namespace graph
{
class vertex_properties;
class edge_properties;
class properties;

struct property_tag{};

typedef
boost::adjacency_list
<
	boost::setS,
	boost::vecS,
	boost::undirectedS,
	vertex_properties,
	edge_properties,
	boost::property
	<
		property_tag,
		properties
	>
>
object;
}
}

#endif
