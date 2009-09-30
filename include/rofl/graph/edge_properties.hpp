#ifndef ROFL_GRAPH_EDGE_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_EDGE_PROPERTIES_HPP_INCLUDED

#include <rofl/math/line_segment.hpp>
#include <rofl/point.hpp>
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
		math::line_segment<point> const &);

	unit 
	length() const;

	math::line_segment<point> const &
	adjacent_edge() const;
private:
	math::line_segment<point> 
		adjacent_edge_;
	unit 
		length_;
};
}
}

#endif
