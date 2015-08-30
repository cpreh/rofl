#ifndef ROFL_POLYGONIZER_UNIQUE_PTR_HPP_INCLUDED
#define ROFL_POLYGONIZER_UNIQUE_PTR_HPP_INCLUDED

#include <rofl/polygonizer_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace rofl
{

typedef fcppt::unique_ptr<
	rofl::polygonizer
> polygonizer_unique_ptr;

}

#endif
