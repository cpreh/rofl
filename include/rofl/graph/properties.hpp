#ifndef ROFL_GRAPH_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_PROPERTIES_HPP_INCLUDED

#include <rofl/point.hpp>
#include <vector>

namespace rofl
{
namespace graph
{
class properties
{
public:
	typedef std::vector<point> point_vector;
	
	properties();
	properties(
		point_vector const &);
	point_vector const &points() const;
	point_vector &points();
private:
	point_vector points_;
};
}
}

#endif
