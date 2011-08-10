#ifndef AI_POLYGON_WITH_HOLES_HPP_INCLUDED
#define AI_POLYGON_WITH_HOLES_HPP_INCLUDED

#include <rofl/math/polygon.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <vector>

namespace rofl
{
namespace math
{
template<typename T>
class polygon_with_holes
{
public:
	typedef math::polygon<T> polygon;

	typedef
	std::vector<polygon>
	hole_set;

	polygon_with_holes();

	polygon_with_holes(
		polygon const &,
		hole_set const & = hole_set());

	void
	border(
		polygon const &);

	polygon const &
	border() const;

	void
	add_hole(
		polygon const &);

	hole_set const &
	holes() const;

	polygon &
	border();

	hole_set &
	holes();
private:
	polygon border_;
	hole_set holes_;
};
}
}

template<typename T>
rofl::math::polygon_with_holes<T>::polygon_with_holes()
:
	border_(),
	holes_()
{
}

template<typename T>
rofl::math::polygon_with_holes<T>::polygon_with_holes(
	polygon const &_border,
	hole_set const &_holes)
:
	border_(
		_border),
	holes_(
		_holes)
{
}

template<typename T>
void
rofl::math::polygon_with_holes<T>::border(
	polygon const &_border)
{
	border_ =
		_border;
}

template<typename T>
typename
rofl::math::polygon_with_holes<T>::polygon const &
rofl::math::polygon_with_holes<T>::border() const
{
	return
		border_;
}

template<typename T>
void
rofl::math::polygon_with_holes<T>::add_hole(
	polygon const &_hole)
{
	holes_.push_back(
		_hole);
}

template<typename T>
typename
rofl::math::polygon_with_holes<T>::hole_set const &
rofl::math::polygon_with_holes<T>::holes() const
{
	return
		holes_;
}

template<typename T>
typename
rofl::math::polygon_with_holes<T>::polygon &
rofl::math::polygon_with_holes<T>::border()
{
	return
		border_;
}

template<typename T>
typename rofl::math::polygon_with_holes<T>::hole_set &
rofl::math::polygon_with_holes<T>::holes()
{
	return
		holes_;
}

#endif
