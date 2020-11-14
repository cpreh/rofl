#ifndef ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_PROPERTIES_HPP_INCLUDED

#include <rofl/indexed_polygon.hpp>
#include <rofl/polygon.hpp>
#include <rofl/symbol.hpp>
#include <rofl/graph/vertex_properties_fwd.hpp>


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
	explicit
	vertex_properties(
		rofl::indexed_polygon &&
	);

	ROFL_SYMBOL
	vertex_properties(
		rofl::indexed_polygon &&,
		rofl::point const &
	);

	[[nodiscard]]
	ROFL_SYMBOL
	rofl::indexed_polygon const &
	polygon() const;

	ROFL_SYMBOL
	void
	polygon(
		rofl::indexed_polygon &&
	);

	[[nodiscard]]
	ROFL_SYMBOL
	rofl::point const &
	barycenter() const;

	ROFL_SYMBOL
	void
	barycenter(
		rofl::point const &
	);
private:
	rofl::indexed_polygon polygon_;

	rofl::point barycenter_;
};

}
}

#endif
