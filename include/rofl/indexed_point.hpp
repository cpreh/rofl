#ifndef ROFL_INDEXED_POINT_HPP_INCLUDED
#define ROFL_INDEXED_POINT_HPP_INCLUDED

#include <rofl/index.hpp>
#include <rofl/indexed_point_fwd.hpp>
#include <rofl/point_fwd.hpp>
#include <rofl/symbol.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <fcppt/reference.hpp>


namespace rofl
{

class indexed_point
{
public:
	ROFL_SYMBOL
	indexed_point(
		rofl::graph::object const &,
		rofl::index
	);

	ROFL_SYMBOL
	rofl::point const &
	representation() const;

	ROFL_SYMBOL
	bool
	operator==(
		rofl::indexed_point const &
	) const;
private:
	typedef fcppt::reference<
		rofl::graph::object const
	> graph_reference;

	graph_reference parent_;

	rofl::index index_;
};

ROFL_SYMBOL
bool
operator!=(
	rofl::indexed_point const &,
	rofl::indexed_point const &
);

}

#endif
