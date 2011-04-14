#ifndef ROFL_INDEXED_POINT_HPP_INCLUDED
#define ROFL_INDEXED_POINT_HPP_INCLUDED

#include <rofl/graph/object_fwd.hpp>
#include <rofl/index.hpp>
#include <rofl/point.hpp>
#include <rofl/symbol.hpp>
#include <boost/operators.hpp>

namespace rofl
{
class indexed_point
:
	public boost::equality_comparable<indexed_point>
{
public:
	ROFL_SYMBOL
	indexed_point(
		rofl::graph::object const &,
		index);

	ROFL_SYMBOL
	point const &
	representation() const;
	
	ROFL_SYMBOL
	bool 
	operator==(
		indexed_point const &) const;
private:
	rofl::graph::object const *parent_;
	index index_;
};
}

#endif
