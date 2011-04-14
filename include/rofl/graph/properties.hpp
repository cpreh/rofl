#ifndef ROFL_GRAPH_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_PROPERTIES_HPP_INCLUDED

#include <rofl/point.hpp>
#include <rofl/symbol.hpp>
#include <vector>

namespace rofl
{
namespace graph
{
class properties
{
public:
	typedef std::vector<point> point_vector;
	
	ROFL_SYMBOL
	properties();

	ROFL_SYMBOL
	properties(
		point_vector const &);

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
