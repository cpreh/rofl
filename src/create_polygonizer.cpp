#include <rofl/create_polygonizer.hpp>
#include <rofl/polygonizer.hpp>
#include <rofl/polygonizer_unique_ptr.hpp>
#include <rofl/aux/polygonizers/triangle/object.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


rofl::polygonizer_unique_ptr
rofl::create_polygonizer()
{
	return
		fcppt::unique_ptr_to_base<
			rofl::polygonizer
		>(
			fcppt::make_unique_ptr_fcppt<
				rofl::aux::polygonizers::triangle::object
			>()
		);
}
