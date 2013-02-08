#ifndef ROFL_MATH_POLYGON_INPUT_HPP_INCLUDED
#define ROFL_MATH_POLYGON_INPUT_HPP_INCLUDED

#include <rofl/math/polygon_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace math
{

template
<
	typename T,
	typename Ch,
	typename Traits
>
std::basic_istream<Ch, Traits> &
operator>>(
	std::basic_istream<Ch, Traits> &_stream,
	rofl::math::polygon<T> &_polygon
)
{
	Ch ch;

	_stream >> ch;

	if(ch != _stream.widen('(') || _stream.eof())
	{
		_stream.setstate(
			std::ios_base::failbit);
		return _stream;
	}

	if (_stream.peek() == _stream.widen(')'))
	{
		_stream.ignore();
		return _stream;
	}

	for(;;)
	{
		T val;

		_stream >> val;

		if (!_stream)
			return _stream;

		_polygon.push_back(
			val
		);

		if (_stream.eof())
		{
			_stream.setstate(
				std::ios_base::failbit);
			return _stream;
		}

		_stream >> ch;

		if (ch == _stream.widen(')'))
			break;

		if (ch != _stream.widen(','))
		{
			_stream.setstate(
				std::ios_base::failbit);
			return _stream;
		}
	}

	return _stream;
}

}
}

#endif
