#ifndef ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED

#include <rofl/polygon.hpp>
#include <rofl/indexed_polygon.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace rofl
{
namespace graph
{
// FIXME: vertex_properties sollte seinen Schwerpunkt selber ausrechnen
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
	
	void
	polygon(
		indexed_polygon const &);
	
	point const &
	barycenter() const;
	
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
