#include "../log.hpp"
#include <rofl/log.hpp>

sge::log::object &
rofl::polygonizers::log()
{
	static sge::log::object o(
		sge::log::parameters::inherited(
			rofl::log(),
			SGE_TEXT("polygonizers")));
	return o;
}
