#include "polygonizers/triangle/object.hpp"
#include <rofl/create_polygonizer.hpp>
#include <fcppt/make_shared_ptr.hpp>

rofl::polygonizer_ptr const rofl::create_polygonizer()
{
	return 
		fcppt::make_shared_ptr<polygonizers::triangle::object>();
}
