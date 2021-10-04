#ifndef ROFL_GRAPH_EDGE_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_EDGE_PROPERTIES_HPP_INCLUDED

#include <rofl/indexed_line_segment.hpp>
#include <rofl/unit.hpp>
#include <rofl/graph/edge_properties_fwd.hpp>


namespace rofl::graph
{

class edge_properties
{
public:
	edge_properties(
		rofl::unit,
		rofl::indexed_line_segment const &
	);

	[[nodiscard]]
	rofl::unit
	length() const;

	[[nodiscard]]
	rofl::indexed_line_segment const &
	adjacent_edge() const;

	// public for boost properties
	rofl::unit length_; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
private:
	rofl::indexed_line_segment adjacent_edge_;
};

}

#endif
