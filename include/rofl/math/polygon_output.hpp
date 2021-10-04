#ifndef ROFL_MATH_POLYGON_OUTPUT_HPP_INCLUDED
#define ROFL_MATH_POLYGON_OUTPUT_HPP_INCLUDED

#include <rofl/math/polygon_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace rofl::math
{

template
<
	typename T,
	typename Ch,
	typename Traits
>
std::basic_ostream<Ch, Traits> &
operator<<(
	std::basic_ostream<Ch, Traits> &_stream,
	rofl::math::polygon<T> const &_polygon
)
{
	_stream <<
		_stream.widen('(');

	for(
		auto const &elem
		:
		_polygon
	)
	{
		_stream
			<<
			elem
			<<
			_stream.widen(',');
	}

	_stream <<
		_stream.widen(')');

	return
		_stream;
}

}

#endif
