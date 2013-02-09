#include <rofl/create_polygonizer.hpp>
#include <rofl/polygonizer_unique_ptr.hpp>
#include <rofl/aux/polygonizers/triangle/object.hpp>
#include <fcppt/make_unique_ptr.hpp>


rofl::polygonizer_unique_ptr
rofl::create_polygonizer()
{
	return
		fcppt::make_unique_ptr<
			rofl::aux::polygonizers::triangle::object
		>();
}
