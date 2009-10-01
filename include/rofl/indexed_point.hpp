#ifndef ROFL_INDEXED_POINT_HPP_INCLUDED
#define ROFL_INDEXED_POINT_HPP_INCLUDED

#include <rofl/graph/object_fwd.hpp>
#include <rofl/index.hpp>
#include <rofl/point.hpp>

namespace rofl
{
class indexed_point
{
public:
	indexed_point(
		rofl::graph::object const &,
		index);

	point const &
	representation() const;
	
	bool 
	operator==(
		indexed_point const &) const;
private:
	rofl::graph::object const *parent_;
	index index_;
};
}

#endif
