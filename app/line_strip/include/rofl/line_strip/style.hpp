#ifndef ROFL_LINE_STRIP_STYLE_HPP_INCLUDED
#define ROFL_LINE_STRIP_STYLE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace rofl::line_strip
{

enum class style : std::uint8_t
{
	no_loop,
	loop
};

}

#endif
