#ifndef ROFL_POLYGONIZER_UNIQUE_PTR_HPP_INCLUDED
#define ROFL_POLYGONIZER_UNIQUE_PTR_HPP_INCLUDED

#include <rofl/polygonizer_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace rofl
{

typedef std::shared_ptr<
	rofl::polygonizer
> polygonizer_unique_ptr;

}

#endif
