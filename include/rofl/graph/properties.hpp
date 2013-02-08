#ifndef ROFL_GRAPH_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_PROPERTIES_HPP_INCLUDED

#include <rofl/point.hpp>
#include <rofl/symbol.hpp>
#include <rofl/graph/properties_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace graph
{

class properties
{
public:
	typedef std::vector<
		rofl::point
	> point_vector;

	ROFL_SYMBOL
	properties();

	ROFL_SYMBOL
	properties(
		point_vector const &
	);

	ROFL_SYMBOL
	point_vector const &
	points() const;

	ROFL_SYMBOL
	point_vector &
	points();
private:
	point_vector points_;
};

}
}

#endif
