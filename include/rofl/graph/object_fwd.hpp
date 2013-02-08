#ifndef ROFL_GRAPH_OBJECT_FWD_HPP_INCLUDED
#define ROFL_GRAPH_OBJECT_FWD_HPP_INCLUDED

#include <rofl/graph/edge_properties_fwd.hpp>
#include <rofl/graph/properties_fwd.hpp>
#include <rofl/graph/property_tag_fwd.hpp>
#include <rofl/graph/vertex_properties_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#define BOOST_NO_HASH
#include <boost/graph/adjacency_list.hpp>
#undef BOOST_NO_HASH
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace graph
{

typedef
boost::adjacency_list
<
	// TODO: where does this boost:: stuff come from?
	boost::setS,
	boost::vecS,
	boost::undirectedS,
	rofl::graph::vertex_properties,
	rofl::graph::edge_properties,
	boost::property
	<
		rofl::graph::property_tag,
		rofl::graph::properties
	>
>
object;

}
}

#endif
