#ifndef ROFL_POLYGONIZER_HPP_INCLUDED
#define ROFL_POLYGONIZER_HPP_INCLUDED

#include <rofl/polygonizer_fwd.hpp>
#include <rofl/polygon_with_holes.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/point.hpp>

namespace rofl
{
class polygonizer
{
public:
	virtual void 
	polygonize(
		polygon_with_holes const &,
		graph::object &) = 0;
};
}

#endif
