#ifndef ROFL_MATH_POLYGON_IMPL_HPP_INCLUDED
#define ROFL_MATH_POLYGON_IMPL_HPP_INCLUDED

#include <rofl/math/polygon_decl.hpp> // IWYU pragma: export


template<
	typename T
>
rofl::math::polygon<
	T
>::polygon()
:
	points_()
{
}

template<
	typename T
>
void
rofl::math::polygon<
	T
>::push_back(
	point const &_p
)
{
	points_.push_back(
		_p
	);
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::size_type
rofl::math::polygon<
	T
>::size() const
{
	return
		points_.size();
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::reference
rofl::math::polygon<
	T
>::front()
{
	return
		points_.front();
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::const_reference
rofl::math::polygon<
	T
>::front() const
{
	return
		points_.front();
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::reference
rofl::math::polygon<
	T
>::back()
{
	return
		points_.back();
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::const_reference
rofl::math::polygon<
	T
>::back() const
{
	return
		points_.back();
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::reference
rofl::math::polygon<
	T
>::operator[](
	size_type const _index
)
{
	return
		points_[
			_index
		];
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::const_reference
rofl::math::polygon<
	T
>::operator[](
	size_type const _index
) const
{
	return
		points_[
			_index
		];
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::iterator
rofl::math::polygon<
	T
>::begin()
{
	return
		points_.begin();
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::const_iterator
rofl::math::polygon<
	T
>::begin() const
{
	return
		points_.begin();
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::iterator
rofl::math::polygon<
	T
>::end()
{
	return
		points_.end();
}

template<
	typename T
>
typename
rofl::math::polygon<
	T
>::const_iterator
rofl::math::polygon<
	T
>::end() const
{
	return
		points_.end();
}

template<
	typename T
>
bool
rofl::math::polygon<
	T
>::empty() const
{
	return points_.empty();
}

template<
	typename T
>
template<
	typename It
>
void
rofl::math::polygon<
	T
>::insert(
	iterator const _pos,
	It const _begin,
	It const _end
)
{
	points_.insert(
		_pos,
		_begin,
		_end
	);
}

#endif
