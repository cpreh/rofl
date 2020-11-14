#ifndef ROFL_MATH_POLYGON_WITH_HOLES_IMPL_HPP_INCLUDED
#define ROFL_MATH_POLYGON_WITH_HOLES_IMPL_HPP_INCLUDED

#include <rofl/math/polygon_with_holes_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename T
>
rofl::math::polygon_with_holes<
	T
>::polygon_with_holes()
:
	border_(),
	holes_()
{
}

template<
	typename T
>
rofl::math::polygon_with_holes<
	T
>::polygon_with_holes(
	polygon &&_border
)
:
	border_(
		std::move(
			_border
		)
	),
	holes_{}
{
}

template<
	typename T
>
rofl::math::polygon_with_holes<
	T
>::polygon_with_holes(
	polygon &&_border,
	hole_set &&_holes
)
:
	border_(
		std::move(
			_border
		)
	),
	holes_(
		std::move(
			_holes
		)
	)
{
}

template<
	typename T
>
void
rofl::math::polygon_with_holes<
	T
>::border(
	polygon &&_border
)
{
	border_ =
		std::move(
			_border
		);
}

template<
	typename T
>
typename
rofl::math::polygon_with_holes<
	T
>::polygon const &
rofl::math::polygon_with_holes<
	T
>::border() const
{
	return
		border_;
}

template<
	typename T
>
void
rofl::math::polygon_with_holes<
	T
>::add_hole(
	polygon &&_hole
)
{
	holes_.push_back(
		std::move(
			_hole
		)
	);
}

template<
	typename T
>
typename
rofl::math::polygon_with_holes<
	T
>::hole_set const &
rofl::math::polygon_with_holes<
	T
>::holes() const
{
	return
		holes_;
}

template<
	typename T
>
typename
rofl::math::polygon_with_holes<
	T
>::polygon &
rofl::math::polygon_with_holes<
	T
>::border()
{
	return
		border_;
}

template<
	typename T
>
typename rofl::math::polygon_with_holes<
	T
>::hole_set &
rofl::math::polygon_with_holes<
	T
>::holes()
{
	return
		holes_;
}

#endif
