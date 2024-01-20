#ifndef ROFL_AUX_MATH_AREA_SIGN_HPP_INCLUDED
#define ROFL_AUX_MATH_AREA_SIGN_HPP_INCLUDED

//#include <fcppt/math/vector/cross.hpp>
#include <fcppt/math/vector/arithmetic.hpp> // IWYU pragma: keep

namespace rofl::aux::math
{

template <typename T>
int area_sign(T const &_a, T const &_b, T const &_c)
{
  // cross: l.x() * r.y() - l.y() * r.x()
  typename T::value_type const area2 = (_b - _a).x() * (_c - _a).y() - (_b - _a).y() * (_c - _a).y();
#if 0
		fcppt::math::vector::cross(
			b-a,
			c-a);
#endif
  constexpr typename T::value_type const half{0.5};

  if (area2 > half)
  {
    return 1;
  }

  return area2 < -half ? -1 : 0;
}

}

#endif
