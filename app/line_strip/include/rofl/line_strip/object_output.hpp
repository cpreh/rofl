#ifndef ROFL_LINE_STRIP_OBJECT_OUTPUT_HPP_INCLUDED
#define ROFL_LINE_STRIP_OBJECT_OUTPUT_HPP_INCLUDED

#include <fcppt/io/ostream.hpp>
#include <fcppt/math/detail/one_dimensional_output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <rofl/line_strip/object.hpp>


namespace rofl
{
namespace line_strip
{

template<typename A,typename B>
fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &o,
	rofl::line_strip::object<A,B> const &s)
{
	return
		fcppt::math::detail::one_dimensional_output(
			o,
			s.points());
}

}
}

#endif
