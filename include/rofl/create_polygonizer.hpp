#ifndef ROFL_CREATE_POLYGONIZER_HPP_INCLUDED
#define ROFL_CREATE_POLYGONIZER_HPP_INCLUDED

#include <rofl/polygonizer_unique_ptr.hpp>
#include <rofl/symbol.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace rofl
{

ROFL_SYMBOL
rofl::polygonizer_unique_ptr
create_polygonizer(
	fcppt::log::context_reference
);

}

#endif
