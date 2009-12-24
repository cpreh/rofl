#include "../log.hpp"
#include <rofl/log.hpp>

fcppt::log::object &
rofl::polygonizers::log()
{
	static fcppt::log::object o(
		fcppt::log::parameters::inherited(
			rofl::log(),
			FCPPT_TEXT("polygonizers")));
	return o;
}
