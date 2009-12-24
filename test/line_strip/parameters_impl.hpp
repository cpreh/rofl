#include "parameters.hpp"
#include <sge/image/colors.hpp>
#include <sge/image/color/init.hpp>
#include <fcppt/variant/object.hpp>
#include <algorithm>

template
<
	typename A,
	typename V
>
sge::line_strip::parameters<A,V>::parameters()
: 
	style_(
		style::no_loop),
	color_(
		sge::image::color::init::red %= 1.0f,
		sge::image::color::init::green %= 1.0f,
		sge::image::color::init::blue %= 1.0f,
		sge::image::color::init::alpha %= 1.0f),
	points_()
{
}

template
<
	typename A,
	typename V
>
sge::line_strip::parameters<A,V> &
sge::line_strip::parameters<A,V>::style(
	style::type const _style)
{
	style_ = _style;
	return *this;
}

template
<
	typename A,
	typename V
>
sge::line_strip::style::type 
sge::line_strip::parameters<A,V>::style() const
{
	return style_;
}

template
<
	typename A,
	typename V
>
sge::line_strip::parameters<A,V> &
sge::line_strip::parameters<A,V>::color(
	V const &_color)
{
	color_ = _color;
	return *this;
}

template
<
	typename A,
	typename V
>
V const &
sge::line_strip::parameters<A,V>::color() const
{
	return color_;
}

template
<
	typename A,
	typename V
>
typename
sge::line_strip::parameters<A,V>::point_sequence const &
sge::line_strip::parameters<A,V>::points() const
{
	return points_;
}


template
<
	typename A,
	typename V
>
template
<
	typename Container
>
sge::line_strip::parameters<A,V> &
sge::line_strip::parameters<A,V>::points(
	Container const &c)
{
	std::copy(
		c.begin(),
		c.end(),
		std::back_inserter(
			points_));
	return *this;
}
