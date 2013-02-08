#ifndef ROFL_MATH_LINE_SEGMENT_IMPL_HPP_INCLUDED
#define ROFL_MATH_LINE_SEGMENT_IMPL_HPP_INCLUDED

#include <rofl/math/line_segment_decl.hpp>


template<
	typename Vector
>
rofl::math::line_segment<
	Vector
>::line_segment()
:
	start_(),
	end_()
{
}

template<
	typename Vector
>
rofl::math::line_segment<
	Vector
>::line_segment(
	point const &_start,
	point const &_end
)
:
	start_(
		_start
	),
	end_(
		_end
	)
{
}

template<
	typename Vector
>
typename
rofl::math::line_segment<
	Vector
>::point const &
rofl::math::line_segment<
	Vector
>::start() const
{
	return
		start_;
}

template<
	typename Vector
>
typename
rofl::math::line_segment<
	Vector
>::point const &
rofl::math::line_segment<
	Vector
>::end() const
{
	return
		end_;
}

template<
	typename Vector
>
bool
rofl::math::line_segment<
	Vector
>::operator==(
	line_segment const &_other
) const
{
	return
		(start_ == _other.start_ &&
		end_ == _other.end_) ||
		(start_ == _other.end_ &&
		end_ == _other.start_);
}

#endif
