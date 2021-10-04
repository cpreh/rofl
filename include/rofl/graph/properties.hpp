#ifndef ROFL_GRAPH_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_PROPERTIES_HPP_INCLUDED

#include <rofl/point.hpp>
#include <rofl/symbol.hpp>
#include <rofl/graph/properties_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace rofl::graph
{

class properties
{
public:
	using
	point_vector
	=
	std::vector<
		rofl::point
	>;

	ROFL_SYMBOL
	properties();

	ROFL_SYMBOL
	explicit
	properties(
		point_vector &&
	);

	[[nodiscard]]
	ROFL_SYMBOL
	point_vector const &
	points() const;

	[[nodiscard]]
	ROFL_SYMBOL
	point_vector &
	points();
private:
	point_vector points_;
};

}

#endif
