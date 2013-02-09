#include <rofl/dereference.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/polygon.hpp>


rofl::polygon
rofl::dereference(
	rofl::indexed_polygon const &_poly
)
{
	rofl::polygon ret;

	for(
		auto const &elem : _poly
	)
		ret.push_back(
			elem.representation()
		);

	return ret;
}
