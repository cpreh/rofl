#include "polygonizers/triangle/object.hpp"
#include <rofl/create_polygonizer.hpp>
#include <sge/make_shared_ptr.hpp>

rofl::polygonizer_ptr const rofl::create_polygonizer()
{
	return 
		sge::make_shared_ptr<polygonizers::triangle::object>();
}