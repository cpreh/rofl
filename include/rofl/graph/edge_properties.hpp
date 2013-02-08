#ifndef ROFL_GRAPH_EDGE_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_EDGE_PROPERTIES_HPP_INCLUDED

#include <rofl/indexed_line_segment.hpp>
#include <rofl/unit.hpp>
#include <rofl/graph/edge_properties_fwd.hpp>


namespace rofl
{
namespace graph
{

class edge_properties
{
public:
	edge_properties(
		rofl::unit,
		rofl::indexed_line_segment const &
	);

	rofl::unit
	length() const;

	rofl::indexed_line_segment const &
	adjacent_edge() const;

	// public for boost properties
	rofl::unit length_;
private:
	rofl::indexed_line_segment adjacent_edge_;
};

}
}

#endif
