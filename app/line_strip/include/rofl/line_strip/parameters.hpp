#ifndef ROFL_LINE_STRIP_PARAMETERS_HPP_INCLUDED
#define ROFL_LINE_STRIP_PARAMETERS_HPP_INCLUDED

#include <rofl/line_strip/style.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace line_strip
{

template
<
	typename Value,
	typename Color
>
class parameters
{
public:
	typedef typename
	fcppt::math::vector::static_
	<
		Value,
		2
	>::type point;

	typedef
	std::vector
	<
		point
	> point_sequence;

	parameters();

	parameters &
	style(
		rofl::line_strip::style
	);

	rofl::line_strip::style
	style() const;

	Color const &
	color() const;

	parameters &
	color(
		Color const &
	);

	template
	<
		typename Container
	>
	parameters &
	points(
		Container const &
	);

	point_sequence const &
	points() const;
private:
	rofl::line_strip::style style_;

	Color color_;

	point_sequence points_;
};

}
}

#endif
