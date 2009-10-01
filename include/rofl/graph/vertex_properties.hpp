#ifndef ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED

#include <rofl/polygon.hpp>
#include <rofl/indexed_polygon.hpp>
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
		indexed_polygon const &);
	vertex_properties(
		indexed_polygon const &,
		point const &);
	indexed_polygon const &
	polygon() const;
	point const &
	barycenter() const;
private:
	indexed_polygon polygon_;
	point barycenter_;
};
}
}

#endif
