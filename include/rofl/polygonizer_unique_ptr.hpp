#ifndef ROFL_POLYGONIZER_UNIQUE_PTR_HPP_INCLUDED
#define ROFL_POLYGONIZER_UNIQUE_PTR_HPP_INCLUDED

#include <rofl/polygonizer_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace rofl
{

using
polygonizer_unique_ptr
=
fcppt::unique_ptr<
	rofl::polygonizer
>;

}

#endif
