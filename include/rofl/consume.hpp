#ifndef ROFL_CONSUME_HPP_INCLUDED
#define ROFL_CONSUME_HPP_INCLUDED

#include <istream>

namespace rofl
{
template<typename T>
class consume_impl
{
public:
	consume_impl(
		T const _c) : c_(_c) {}
	T const c_;
};

template<typename T>
consume_impl<T> const consume(
	T const c)
{
	return consume_impl<T>(
		c);
}

}

template
<
  typename Ch,
  typename Traits
>
std::basic_istream<Ch, Traits> &
operator>>(
  std::basic_istream<Ch, Traits> &s,
  rofl::consume_impl<Ch> const &cc)
{
	if (s.eof())
	{
		s.setstate(
			std::ios_base::failbit);
		return s;
	}

	Ch c;
	s >> c;
	if (c != cc.c_)
		s.setstate(
			std::ios_base::failbit);

	return s;
}

#endif
