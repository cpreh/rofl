#ifndef ROFL_POLYGONIZERS_TRIANGLE_OBJECT_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_OBJECT_HPP_INCLUDED

#include <rofl/graph/object_fwd.hpp>
#include <rofl/polygonizer.hpp>
#include <rofl/polygon_with_holes.hpp>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
class object
:
	public polygonizer
{
public:
	void
	polygonize(
		polygon_with_holes const &,
		graph::object &);
};
}
}
}

#endif
