#ifndef ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED

#include <rofl/math/polygon.hpp>
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
		rofl::math::polygon<point> const &);
	rofl::math::polygon<point> const &
	polygon() const;
private:
	rofl::math::polygon<point> polygon_;
};
}
}

#endif
