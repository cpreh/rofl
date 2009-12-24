#ifndef SGE_LINE_STRIP_PARAMETERS_HPP_INCLUDED
#define SGE_LINE_STRIP_PARAMETERS_HPP_INCLUDED

#include "style.hpp"
#include <fcppt/math/vector/static.hpp>
#include <vector>
#include <iterator>

namespace sge
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
	2>::type point;
	typedef 
	std::vector
	<
		point
	> point_sequence;
	
	parameters();
	parameters &style(
		sge::line_strip::style::type);
	sge::line_strip::style::type style() const;
	Color const &color() const;
	parameters &color(
		Color const &);
	template
	<
		typename Container
	>
	parameters &points(
		Container const &);
	point_sequence const &points() const;
private:
	sge::line_strip::style::type style_;
	Color color_;
	point_sequence points_;
};
}
}

#endif
