#ifndef ROFL_GRAPH_EDGE_ITERATOR_HPP_INCLUDED
#define ROFL_GRAPH_EDGE_ITERATOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>

namespace rofl
{
namespace graph
{
typedef boost::graph_traits<object>::edge_iterator edge_iterator;
}
}

#endif