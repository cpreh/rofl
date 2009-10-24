#include "../log.hpp"
#include "../../log.hpp"

sge::log::object &
rofl::polygonizers::triangle::log()
{
	static sge::log::object o(
		sge::log::parameters::inherited(
			polygonizers::log(),
			SGE_TEXT("triangle")));
	return o;
}
