#ifndef ROFL_POLYGONIZER_HPP_INCLUDED
#define ROFL_POLYGONIZER_HPP_INCLUDED

#include <rofl/polygonizer_fwd.hpp>
#include <rofl/polygon_with_holes.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/point.hpp>
#include <fcppt/noncopyable.hpp>

namespace rofl
{
class polygonizer
{
	FCPPT_NONCOPYABLE(
		polygonizer
	);
protected:
	polygonizer();
public:
	virtual void 
	polygonize(
		polygon_with_holes const &,
		graph::object &) = 0;
	
	virtual ~polygonizer();
};
}

#endif
