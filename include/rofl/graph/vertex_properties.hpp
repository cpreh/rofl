#ifndef ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED

#include <rofl/polygon.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/symbol.hpp>
#include <fcppt/math/vector/object_impl.hpp>

namespace rofl
{
namespace graph
{
// FIXME: vertex_properties sollte seinen Schwerpunkt selber ausrechnen
class vertex_properties
{
public:
	// vertex properties have to be def-ctible
	ROFL_SYMBOL
	vertex_properties();

	ROFL_SYMBOL
	vertex_properties(
		indexed_polygon const &);

	ROFL_SYMBOL
	vertex_properties(
		indexed_polygon const &,
		point const &);

	ROFL_SYMBOL
	indexed_polygon const &
	polygon() const;

	ROFL_SYMBOL
	void
	polygon(
		indexed_polygon const &);

	ROFL_SYMBOL
	point const &
	barycenter() const;

	ROFL_SYMBOL
	void
	barycenter(
		point const &);
private:
	indexed_polygon polygon_;
	point barycenter_;
};
}
}

#endif
