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
	using
	graph_reference
	=
	fcppt::reference<
		rofl::graph::object const
	>;

	ROFL_SYMBOL
	indexed_point(
		graph_reference,
		rofl::index
	);

	[[nodiscard]]
	ROFL_SYMBOL
	rofl::point const &
	representation() const;

	[[nodiscard]]
	ROFL_SYMBOL
	bool
	operator==(
		rofl::indexed_point const &
	) const;
private:
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
