#ifndef ROFL_GRAPH_OUT_EDGE_ITERATOR_HPP_INCLUDED
#define ROFL_GRAPH_OUT_EDGE_ITERATOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>

namespace rofl
{
namespace graph
{
typedef boost::graph_traits<object>::out_edge_iterator out_edge_iterator;
}
}

#endif