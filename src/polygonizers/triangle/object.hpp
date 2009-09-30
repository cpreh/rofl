#ifndef ROFL_POLYGONIZERS_TRIANGLE_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_HPP_INCLUDED

#include <rofl/polygonizer.hpp>

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
