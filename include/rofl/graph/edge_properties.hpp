#ifndef ROFL_GRAPH_EDGE_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_EDGE_PROPERTIES_HPP_INCLUDED

#include <rofl/line_segment.hpp>
#include <rofl/unit.hpp>
#include <sge/math/vector/basic_impl.hpp>

namespace rofl
{
namespace graph
{
class edge_properties
{
public:
	edge_properties(
		unit,
		line_segment const &);

	unit 
	length() const;

	line_segment const &
	adjacent_edge() const;
private:
	line_segment
		adjacent_edge_;
	unit 
		length_;
};
}
}

#endif
