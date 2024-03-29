#ifndef ROFL_AUX_GRAPH_PLACEMENT_HPP_INCLUDED
#define ROFL_AUX_GRAPH_PLACEMENT_HPP_INCLUDED

#include <rofl/aux/graph/placement_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace rofl::aux::graph
{

enum class placement : std::uint8_t
{
	previous,
	next
};

}

#endif
