#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_CLEAR_POD_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_CLEAR_POD_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace rofl::aux::polygonizers::triangle
{
template <typename T>
void clear_pod(T &_val)
  requires(std::is_standard_layout_v<T> && std::is_trivial_v<T>)
{
  std::memset(&_val, 0, sizeof(T));
}
}

#endif
