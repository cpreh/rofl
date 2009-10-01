#ifndef ROFL_GRAPH_VERTEX_DESCRIPTOR_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_DESCRIPTOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>

namespace rofl
{
namespace graph
{
typedef boost::graph_traits<object>::vertex_descriptor vertex_descriptor;
}
}

#endif