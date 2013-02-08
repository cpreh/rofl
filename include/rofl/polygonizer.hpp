#ifndef ROFL_POLYGONIZER_HPP_INCLUDED
#define ROFL_POLYGONIZER_HPP_INCLUDED

#include <rofl/polygonizer_fwd.hpp>
#include <rofl/polygon_with_holes_fwd.hpp>
#include <rofl/graph/object_fwd.hpp>
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
	virtual
	void
	polygonize(
		rofl::polygon_with_holes const &,
		rofl::graph::object &
	) = 0;

	virtual
	~polygonizer() = 0;
};

}

#endif
