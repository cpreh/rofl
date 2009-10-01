#ifndef ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED

#include <rofl/polygon.hpp>
#include <rofl/point.hpp>
#include <sge/math/vector/basic_impl.hpp>

namespace rofl
{
namespace graph
{
class vertex_properties
{
public:
	// vertex properties have to be def-ctible
	vertex_properties();
	vertex_properties(
		rofl::polygon const &);
	rofl::polygon const &
	polygon() const;
	point const &
	barycenter() const;
private:
	rofl::polygon polygon_;
	point barycenter_;
};
}
}

#endif
